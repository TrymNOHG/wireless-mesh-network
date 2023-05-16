//
// Created by Trym Hamer Gudvangen on 5/16/23.

#ifndef WIRELESS_MESH_NETWORK_QUEUE
#define WIRELESS_MESH_NETWORK_QUEUE
#include "PriorityQueue.h"

PriorityQueue::PriorityQueue(const Graph& graph) : queue(NodeComparator(&graph)), graph(graph) {}

PriorityQueue::~PriorityQueue() {
    clear();
}

bool PriorityQueue::isEmpty() const {
    return queue.empty();
}

std::size_t PriorityQueue::getSize() const {
    return queue.size();
}

void PriorityQueue::push(const unsigned int& data) {
    Node newNode(data);
    queue.push(newNode);
}

unsigned int PriorityQueue::pop() {
    if (isEmpty()) {
        throw std::runtime_error("PriorityQueue is empty. Cannot pop.");
    }

    unsigned int data = queue.top().nodeDescriptor;
    queue.pop();
    return data;
}

unsigned int PriorityQueue::pop(const unsigned int& fileDescriptor) {
    // Search for the node with the matching file descriptor
    std::vector<Node> elements;
    unsigned int poppedData = 0;

    while (!queue.empty()) {
        Node topNode = queue.top();
        queue.pop();

        if (topNode.nodeDescriptor == fileDescriptor) {
            poppedData = topNode.nodeDescriptor;
            break;
        }

        elements.push_back(topNode);
    }

    // Reconstruct the heap
    queue = std::priority_queue<Node, std::vector<Node>, NodeComparator>(elements.begin(), elements.end(), NodeComparator(&graph));

    return poppedData;
}


unsigned int PriorityQueue::peek() {
    if (isEmpty()) {
        throw std::runtime_error("PriorityQueue is empty. Cannot peek.");
    }
    unsigned int data = queue.top().nodeDescriptor;
    return data;
}

void PriorityQueue::updateNodeByIndex(const unsigned int& index){
    pop(index);
    push(index);
}


unsigned int PriorityQueue::getNodeByIndex(const unsigned int& index) const {
    if (index >= getSize()) {
        throw std::runtime_error("Index out of bounds.");
    }

    std::priority_queue<Node, std::vector<Node>, NodeComparator> tempQueue = queue;
    for (unsigned int i = 0; i < index; i++) {
        tempQueue.pop();
    }
    return tempQueue.top().nodeDescriptor;
};


void PriorityQueue::clear() {
    while (!isEmpty()) {
        queue.pop();
    }
}


#endif // WIRELESS_MESH_NETWORK_QUEUE
