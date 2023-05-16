#include <iostream>
#include <cstdlib>
#include <random>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/property_map/dynamic_property_map.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/random.hpp>


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



Graph createCompleteGraph(int numVertices, int weight);

int main() {

    // Construct an empty graph and prepare the dynamic_property_maps.
    boost::dynamic_properties dp;


//    // Property maps
//    boost::property_map<GraphType, boost::vertex_name_t>::type name =
//            get(boost::vertex_name, graph);
//    dp.property("node_id", name);

    int numVertices = 5;
    int weight = 5;
    Graph graph = createCompleteGraph(numVertices, weight);

    // Print the edges of the graph
    std::cout << "Edges of the graph:" << std::endl;
    for (auto edge : boost::make_iterator_range(boost::edges(graph))) {
        std::cout << boost::source(edge, graph) << " -- " << boost::target(edge, graph) << std::endl;
    }

    // Property map for the edge weight
    boost::property_map<Graph, boost::edge_weight_t>::type weightMap = boost::get(boost::edge_weight, graph);
    dp.property("weight", weightMap);

    // Use ref_property_map to turn a graph property into a property map
    boost::ref_property_map<Graph*, std::string> gname(get_property(graph, boost::graph_name));
    dp.property("name", gname);

    // Vertex property: node_id
    boost::property_map<Graph, boost::vertex_name_t>::type nodeIdMap = boost::get(boost::vertex_name, graph);
    dp.property("node_id", nodeIdMap);

//
//    // Read the graph from the input DOT file
//    std::ifstream dotFile("../graph1.dot");
//    if (!dotFile) {
//        std::cerr << "Failed to open the dot file." << std::endl;
//        return 1;
//    }
//
//    bool status = read_graphviz(dotFile, graph, dp, "node_id");
//    dotFile.close();
//    if (!status) {
//        std::cerr << "Failed to read the graph from the dot file." << std::endl;
//        return 1;
//    }
//
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
    std::cout << std::to_string(weight) << std::endl;
    std::string dotCommand = "dot -Tsvg -Elabel=" + std::to_string(weight) + " ../output.dot -o ../output.svg";
    int conversionStatus = std::system(dotCommand.c_str());

    if (conversionStatus != 0) {
        std::cerr << "Failed to convert DOT to SVG." << std::endl;
        // Handle the error appropriately
    } else {
        std::cout << "DOT to SVG conversion successful." << std::endl;
    }

    //    graph_t::edge_iterator it, end;
//    std::tie(it, end) = boost::edges(graph);
//    for (; it != end; ++it) {
//        double edgeWeight = boost::get(weight, *it);
//        std::cout << "Edge: " << edgeWeight << std::endl;
//    }

    return 0;
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


