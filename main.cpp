#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/random.hpp>
#include <boost/property_map/dynamic_property_map.hpp>
#include <boost/property_map/property_map.hpp>
#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>

#include "PriorityQueue.h"

// Vertex properties
typedef boost::property<boost::vertex_name_t, std::string,
                        boost::property<boost::vertex_color_t, std::string>>
    VertexProperty;

// Edge properties
typedef boost::property<boost::edge_weight_t, double> EdgeProperty;
// Graph properties
typedef boost::property<boost::graph_name_t, std::string> GraphProperty;
// Adjacency list-based type
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
                              VertexProperty, EdgeProperty, GraphProperty>
    Graph;

void edgeDistributionOptimizationAlgorithm(Graph &graph, int numMinEdges);
Graph createCompleteGraph(int numVertices, int weight);
void printEdges(Graph graph);

int main(int argc, char **argv) {
  int numVertices, percentage;
  if (argc < 3) {
    std::cout << "Enter number of drones ";
    std::cin >> numVertices;
    std::cout << "Enter the percentage of other drones any given drone has "
                 "connection to: ";
    std::cin >> percentage;
  } else {
    numVertices = atoi(argv[1]);
    percentage = atoi(argv[2]);
  }

  int numEdges = (numVertices * percentage / 100);

  boost::dynamic_properties dp;

  int weight = 5;
  Graph graph = createCompleteGraph(numVertices, weight);
  get_property(graph, boost::graph_name) = "sfdp";
  edgeDistributionOptimizationAlgorithm(graph, numEdges);

  // Property map for the edge weight
  boost::property_map<Graph, boost::edge_weight_t>::type weightMap =
      boost::get(boost::edge_weight, graph);
  dp.property("weight", weightMap);

  // Use ref_property_map to turn a graph property into a property map
  boost::ref_property_map<Graph *, std::string> gname(
      get_property(graph, boost::graph_name));
  dp.property("layout", gname);

  // Vertex property: node_id
  boost::property_map<Graph, boost::vertex_name_t>::type nodeIdMap =
      boost::get(boost::vertex_name, graph);
  dp.property("node_id", nodeIdMap);

  boost::property_map<Graph, boost::vertex_color_t>::type imageMap =
      boost::get(boost::vertex_color, graph);
  dp.property("image", imageMap);

  for (int i = 0; i < numVertices; ++i) {
    imageMap[i] = "../drone.png";
  }

  std::cout << "Graph has been read successfully." << std::endl;

  // Write the graph to the output DOT file
  std::ofstream outputFile("../output.dot");
  if (!outputFile) {
    std::cerr << "Failed to open the output file." << std::endl;
    return 1;
  }

  write_graphviz_dp(outputFile, graph, dp);
  outputFile.close();

  // Convert the DOT file to SVG using the dot command
  std::string dotCommand =
      "dot -Tpng -Nwidth=3 -Nheight=3 ../output.dot -o ../output.png";
  int conversionStatus = std::system(dotCommand.c_str());

  if (conversionStatus != 0) {
    std::cerr << "Failed to convert DOT to SVG." << std::endl;
    // Handle the error appropriately
  } else {
    std::cout << "DOT to SVG conversion successful." << std::endl;
  }

  return 0;
}

/**
 * This algorithm is a form for edge pruning in order to optimize the edge
 * distribution. Additionally, in order to conform to the use-case of mesh
 * networks, the algorithm takes into account whether graph is still completely
 * connected.
 *
 * Another method that could be explored is starting from a minimum spanning
 * tree and thereafter adding edges till the failure threshold is reached. This
 * would be computationally cheaper; however, it could also result in a less
 * resilient mesh network since redundancies (cycles) are less favored.
 * @param graph
 * @param numMinEdges
 */
void edgeDistributionOptimizationAlgorithm(Graph &graph, int numMinEdges) {
  PriorityQueue queue(graph);

  std::pair<boost::adjacency_list<>::vertex_iterator,
            boost::adjacency_list<>::vertex_iterator>
      vs = boost::vertices(graph);
  for (; vs.first != vs.second; ++vs.first) {
    queue.push(*vs.first);
  }

  while (queue.getSize() >= 2) {
    int currentIndex = 0;
    std::shared_ptr<PriorityQueue::Node> first = queue.peek();
    std::shared_ptr<PriorityQueue::Node> second =
        queue.getNodeByIndex(++currentIndex);

    while (second != nullptr &&
           !(boost::edge(first->nodeDescriptor, second->nodeDescriptor, graph)
                 .second) &&
           currentIndex < queue.getSize() - 1) {
      second = queue.getNodeByIndex(++currentIndex);
    }

    if (second == nullptr ||
        boost::out_degree(first->nodeDescriptor, graph) <= numMinEdges ||
        boost::out_degree(second->nodeDescriptor, graph) <= numMinEdges) {
      break;
    }

    // Temporarily remove the edge
    boost::remove_edge(first->nodeDescriptor, second->nodeDescriptor, graph);

    // Check if the graph is still connected
    std::vector<int> component(num_vertices(graph));
    int num = connected_components(graph, &component[0]);

    if (num > 1) {
      // Graph is disconnected, re-add the edge
      boost::add_edge(first->nodeDescriptor, second->nodeDescriptor,
                      EdgeProperty(5), graph);
    } else {
      // Graph is still connected, update the queue
      queue.updateNodeByIndex(0);
      queue.updateNodeByIndex(currentIndex);
    }
  }
}

Graph createCompleteGraph(int numVertices, int weight) {
  Graph graph;

  // Add vertices with node_id property
  for (int i = 0; i < numVertices; ++i) {
    VertexProperty vp("Drone:" + std::to_string(i));
    boost::add_vertex(vp, graph);
  }

  // Add edges to create a complete undirected graph
  for (int i = 0; i < numVertices; ++i) {
    for (int j = i + 1; j < numVertices; ++j) {
      boost::add_edge(i, j, EdgeProperty(weight), graph);
    }
  }

  return graph;
}

void printGraph(Graph graph) {
  // Print the edges of the graph
  std::cout << "Edges of the graph:" << std::endl;
  for (auto edge : boost::make_iterator_range(boost::edges(graph))) {
    std::cout << boost::source(edge, graph) << " -- "
              << boost::target(edge, graph) << std::endl;
  }
}
