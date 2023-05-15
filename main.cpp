#include <iostream>
#include <cstdlib>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/property_map/dynamic_property_map.hpp>
#include <boost/property_map/property_map.hpp>

// Vertex properties
typedef boost::property<boost::vertex_name_t, std::string> VertexProperty;
// Edge properties
typedef boost::property<
        boost::edge_weight_t, double,
        boost::property<
                boost::edge_weight2_t, double,
                boost::property<boost::edge_color_t, std::string>
        >
> EdgeProperty;
// Graph properties
typedef boost::property<boost::graph_name_t, std::string> GraphProperty;
// Adjacency list-based type
typedef boost::adjacency_list<
        boost::vecS, boost::vecS, boost::undirectedS,
        VertexProperty, EdgeProperty, GraphProperty
> GraphType;

int main() {
    // Construct an empty graph and prepare the dynamic_property_maps.
    GraphType graph;
    boost::dynamic_properties dp;

    // Property maps
    boost::property_map<GraphType, boost::vertex_name_t>::type name =
            get(boost::vertex_name, graph);
    dp.property("node_id", name);

    boost::property_map<GraphType, boost::edge_weight_t>::type weight =
            get(boost::edge_weight, graph);
    dp.property("weight", weight);

    boost::property_map<GraphType, boost::edge_weight2_t>::type minlen =
            get(boost::edge_weight2, graph);
    dp.property("minlen", minlen);

    boost::property_map<GraphType, boost::edge_color_t>::type color =
            get(boost::edge_color, graph);
    dp.property("color", color);

    // Use ref_property_map to turn a graph property into a property map
    boost::ref_property_map<GraphType*, std::string> gname(get_property(graph, boost::graph_name));
    dp.property("name", gname);

    // Read the graph from the input DOT file
    std::ifstream dotFile("../graph1.dot");
    if (!dotFile) {
        std::cerr << "Failed to open the dot file." << std::endl;
        return 1;
    }

    bool status = read_graphviz(dotFile, graph, dp, "node_id");
    dotFile.close();
    if (!status) {
        std::cerr << "Failed to read the graph from the dot file." << std::endl;
        return 1;
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
    std::string dotCommand = "dot -Tsvg ../output.dot -o ../output.svg";
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
