#include <iostream>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/property_map/dynamic_property_map.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/property_map/transform_value_property_map.hpp>

// Vertex properties
typedef boost::property < boost::vertex_name_t, std::string,
        boost::property < boost::vertex_color_t, float > > vertex_p;
// Edge properties
typedef boost::property < boost::edge_weight_t, double > edge_p;
// Graph properties
typedef boost::property < boost::graph_name_t, std::string > graph_p;
// adjacency_list-based type
typedef boost::adjacency_list < boost::vecS, boost::vecS, boost::undirectedS,
        vertex_p, edge_p, graph_p > graph_t;


int main() {
    // Construct an empty graph and prepare the dynamic_property_maps.
    graph_t graph(0);
    boost::dynamic_properties dp;

    // Property maps
    boost::property_map<graph_t, boost::vertex_name_t>::type name =
            get(boost::vertex_name, graph);
    dp.property("node_id", name);

    boost::property_map<graph_t, boost::vertex_color_t>::type mass =
            get(boost::vertex_color, graph);
    dp.property("mass", mass);

    boost::property_map<graph_t, boost::edge_weight_t>::type weight =
            get(boost::edge_weight, graph);
    dp.property("weight", weight);

    // Use ref_property_map to turn a graph property into a property map
    boost::ref_property_map<graph_t*, std::string> gname(get_property(graph, boost::graph_name));
    dp.property("name", gname);

    // Sample graph as an std::istream;
    //std::istringstream gvgraph("digraph { graph [name=\"graphname\"]  a  c e [mass = 6.66] }");

    std::ifstream dotFile("../graph1.dot");

    if (!dotFile.is_open()) {
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

    std::ofstream outputFile("../output.dot");
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open the output file." << std::endl;
        return 1;
    }
    //boost::dynamic_property_writer dpw(dp, boost::make_assoc_property_map(dp));

    write_graphviz_dp(std::cout, graph, dp);
    return 0;
}
