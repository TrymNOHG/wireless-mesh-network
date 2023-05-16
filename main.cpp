#include <iostream>
#include <cstdlib>
#include <random>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/property_map/dynamic_property_map.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/random.hpp>
#include "Queue.h"


// Vertex properties
typedef boost::property<boost::vertex_name_t, std::string> VertexProperty;
// Edge properties
typedef boost::property<
        boost::edge_weight_t, double
> EdgeProperty;
// Graph properties
typedef boost::property<boost::graph_name_t, std::string> GraphProperty;
// Adjacency list-based type
typedef boost::adjacency_list<
        boost::vecS, boost::vecS, boost::undirectedS,
        VertexProperty, EdgeProperty, GraphProperty
> Graph;



void edgeDistributionOptimizationAlgorithm(Graph &graph);
Graph createCompleteGraph(int numVertices, int weight);
void printEdges(Graph graph);

int main() {

    int percentage;
    int numVertices;
    std::cout << "Enter number of drones ";
    std::cin >> numVertices;
    std::cout << "Enter the percentage of edges to be removed: ";
    std::cin >> percentage;

    int numEdges = (numVertices * percentage / 100);


    boost::dynamic_properties dp;


    int weight = 5;
    Graph graph = createCompleteGraph(numVertices, weight);

    // Property map for the edge weight
    boost::property_map<Graph, boost::edge_weight_t>::type weightMap = boost::get(boost::edge_weight, graph);
    dp.property("weight", weightMap);

    // Use ref_property_map to turn a graph property into a property map
    boost::ref_property_map<Graph*, std::string> gname(get_property(graph, boost::graph_name));
    dp.property("name", gname);

    // Vertex property: node_id
    boost::property_map<Graph, boost::vertex_name_t>::type nodeIdMap = boost::get(boost::vertex_name, graph);
    dp.property("node_id", nodeIdMap);

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
    std::string dotCommand = "dot -Tsvg -Elabel=" + std::to_string(weight) + " ../output.dot -o ../output.svg";
    int conversionStatus = std::system(dotCommand.c_str());

    if (conversionStatus != 0) {
        std::cerr << "Failed to convert DOT to SVG." << std::endl;
        // Handle the error appropriately
    } else {
        std::cout << "DOT to SVG conversion successful." << std::endl;
    }



    return 0;
}

void edgeDistributionOptimizationAlgorithm(Graph &graph, int numMinEdges){
    Queue<boost::adjacency_list<>::vertex_descriptor> queue;

    std::pair<boost::adjacency_list<>::vertex_iterator,
            boost::adjacency_list<>::vertex_iterator> vs = boost::vertices(graph);
    for(; vs.first != vs.second; ++vs.first){
        queue.push(*vs.first);
    }

//    std::cout<< boost::out_degree(queue.getFrontNode()->data, graph) << std::endl;
//    boost::remove_edge(queue.getFrontNode()->data, queue.getFrontNode()->next->data, graph);
//    std::cout<< boost::out_degree(queue.getFrontNode()->data, graph) << std::endl;


    while(1){
        Queue<boost::adjacency_list<>::vertex_descriptor>::Node* first = queue.getFrontNode();
        Queue<boost::adjacency_list<>::vertex_descriptor>::Node* second = queue.getFrontNode()->next;

        while(!(boost::edge(first->data, second->data, graph).second)){
            second = second->next;
        }
        if(boost::out_degree(first->data, graph)
        <= numMinEdges || boost::out_degree(second->data, graph) <= numMinEdges) {
            break;
        }
        boost::remove_edge(queue.getFrontNode()->data, queue.getFrontNode()->next->data, graph);

        queue.placeNodeAtRear(first);
        queue.placeNodeAtRear(second);
    }

}


Graph createCompleteGraph(int numVertices, int weight) {
    Graph graph;
    boost::dynamic_properties dp;

    // Add vertices with node_id property
    for (int i = 0; i < numVertices; ++i) {
        boost::add_vertex(VertexProperty(std::to_string(i)), graph);
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
        std::cout << boost::source(edge, graph) << " -- " << boost::target(edge, graph) << std::endl;
    }
}



