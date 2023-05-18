#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>
#include <queue>
#include <boost/graph/adjacency_list.hpp>

typedef boost::property<boost::vertex_name_t, std::string, boost::property<boost::vertex_color_t, std::string > > VertexProperty;
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

        bool operator()(const std::shared_ptr<Node>& node1, const std::shared_ptr<Node>& node2) const {
            return boost::out_degree(node1->nodeDescriptor, *graph) < boost::out_degree(node2->nodeDescriptor, *graph);
        }
    };

    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, NodeComparator> queue;
    const Graph& graph;

public:
    explicit PriorityQueue(const Graph& graph);
    ~PriorityQueue();

    bool isEmpty() const;
    std::size_t getSize() const;

    void push(const unsigned int& data);
    unsigned int pop();
    unsigned int pop(const unsigned int& index);
    const std::shared_ptr<PriorityQueue::Node>& peek() const;

    std::shared_ptr<Node> getNodeByIndex(const unsigned int& index);
    void updateNodeByIndex(const unsigned int& index);

    void clear();
};

#endif // PRIORITY_QUEUE_H
