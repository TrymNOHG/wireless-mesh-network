#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>
#include <queue>
#include <boost/graph/adjacency_list.hpp>

typedef boost::property<boost::vertex_name_t, std::string> VertexProperty;
typedef boost::property<boost::edge_weight_t, double> EdgeProperty;
typedef boost::property<boost::graph_name_t, std::string> GraphProperty;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexProperty, EdgeProperty, GraphProperty> Graph;

class PriorityQueue {
public:
    struct Node {
        unsigned int nodeDescriptor;

        explicit Node(const unsigned int& data) : nodeDescriptor(data) {}
    };

private:
    struct NodeComparator {
        const Graph* graph;

        explicit NodeComparator(const Graph* graph) : graph(graph) {}

        bool operator()(const Node& node1, const Node& node2) const {
            return boost::out_degree(node1.nodeDescriptor, *graph) < boost::out_degree(node2.nodeDescriptor, *graph);
        }
    };

    std::priority_queue<Node, std::vector<Node>, NodeComparator> queue;
    const Graph& graph;

public:
    explicit PriorityQueue(const Graph& graph);
    ~PriorityQueue();

    bool isEmpty() const;
    std::size_t getSize() const;

    void push(const unsigned int& data);
    unsigned int pop();
    unsigned int pop(const unsigned int& index);
    unsigned int peek();

    unsigned int getNodeByIndex(const unsigned int& index) const;
    void updateNodeByIndex(const unsigned int& index);

    void clear();
};

#endif // PRIORITY_QUEUE_H
