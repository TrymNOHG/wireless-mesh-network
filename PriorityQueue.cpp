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
    std::shared_ptr<Node> newNode = std::make_shared<Node>(data);
    queue.push(newNode);
}

unsigned int PriorityQueue::pop() {
    if (isEmpty()) {
        throw std::runtime_error("PriorityQueue is empty. Cannot pop.");
    }

    unsigned int data = queue.top()->nodeDescriptor;
    queue.pop();
    return data;
}

unsigned int PriorityQueue::pop(const unsigned int& fileDescriptor) {
    std::vector<std::shared_ptr<Node>> elements;
    unsigned int poppedData = 0;

    while (!queue.empty()) {
        std::shared_ptr<Node> topNode = queue.top();
        queue.pop();

        if (topNode->nodeDescriptor == fileDescriptor) {
            poppedData = topNode->nodeDescriptor;
            break;
        }

        elements.push_back(topNode);
    }

    // Reconstruct the heap
    queue = std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, NodeComparator>(
            elements.begin(), elements.end(), NodeComparator(&graph));
    return poppedData;
}


const std::shared_ptr<PriorityQueue::Node>& PriorityQueue::peek() const{
    if (isEmpty()) {
        throw std::runtime_error("PriorityQueue is empty. Cannot peek.");
    }

    return queue.top();
}

void PriorityQueue::updateNodeByIndex(const unsigned int& index){
    pop(index);
    push(index);
}


std::shared_ptr<PriorityQueue::Node> PriorityQueue::getNodeByIndex(const unsigned int& index) const {
    std::cout << index << std::endl;
    std::cout << getSize() << std::endl;
    if (index >= getSize()) {
        throw std::runtime_error("Index out of bounds.");
    }

    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, NodeComparator> tempQueue = queue;

    for (unsigned int i = 0; i < index; i++) {
        tempQueue.pop();
    }

    std::cout << "Ok stuff is still working" << std::endl;
    std::cout << "The node descriptor is: " << tempQueue.top()->nodeDescriptor << std::endl;
    return std::make_shared<Node>(*tempQueue.top());
}


void PriorityQueue::clear() {
    while (!isEmpty()) {
        queue.pop();
    }
}


#endif // WIRELESS_MESH_NETWORK_QUEUE
