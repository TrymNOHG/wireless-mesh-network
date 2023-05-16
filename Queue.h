//
// Created by Trym Hamer Gudvangen on 5/16/23.
//

#ifndef WIRELESS_MESH_NETWORK_QUEUE_H
#define WIRELESS_MESH_NETWORK_QUEUE_H

#include <iostream>

template<typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;

        explicit Node(const T& data) : data(data), next(nullptr) {}
    };

    Node* front;
    Node* rear;
    std::size_t size;

public:
    Queue();
    ~Queue();

    bool isEmpty() const;
    std::size_t getSize() const;

    void push(const T& data);
    T pop();

    void shiftQueueForward();

    void clear();
};

#include "Queue.cpp"

#endif //WIRELESS_MESH_NETWORK_QUEUE_H
