//
// Created by Trym Hamer Gudvangen on 5/16/23.

#ifndef WIRELESS_MESH_NETWORK_QUEUE
#define WIRELESS_MESH_NETWORK_QUEUE
#include "Queue.h"

template<typename T>
Queue<T>::Queue() : front(nullptr), rear(nullptr), size(0) {}

template<typename T>
Queue<T>::~Queue() {
    clear();
}

template<typename T>
bool Queue<T>::isEmpty() const {
    return size == 0;
}

template<typename T>
std::size_t Queue<T>::getSize() const {
    return size;
}

template<typename T>
void Queue<T>::push(const T& data) {
    Node* newNode = new Node(data);
    if (isEmpty()) {
        front = newNode;
        rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    size++;
}

template<typename T>
T Queue<T>::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty. Cannot pop.");
    }

    Node* temp = front;
    T data = temp->data;
    front = front->next;

    if (front == nullptr) {
        rear = nullptr;
    }

    delete temp;
    size--;

    return data;
}

template<typename T>
void Queue<T>::clear() {
    while (!isEmpty()) {
        pop();
    }
}

template<typename T>
void Queue<T>::shiftQueueForward() {
    if (isEmpty()) {
        return;
    }

    Node* temp = front;
    T data = temp->data;
    front = front->next;

    rear->next = temp;
    rear = temp;
    rear->next = nullptr;

    if (front == rear) {
        front = nullptr;
        rear = nullptr;
    }

}

template<typename T>
void Queue<T>::placeNodeAtRear(Node* node) {
    if (node == nullptr || node == rear) {
        return;
    }

    Node* prevNode = nullptr;
    Node* currNode = front;

    while (currNode != nullptr && currNode != node) {
        prevNode = currNode;
        currNode = currNode->next;
    }

    if (currNode == nullptr) {
        return;
    }

    if (prevNode != nullptr) {
        prevNode->next = currNode->next;
    } else {
        front = currNode->next;
    }

    currNode->next = nullptr;
    rear->next = currNode;
    rear = currNode;
}


template<typename T>
typename Queue<T>::Node *Queue<T>::getFrontNode() const {
    return front;
}

template<typename T>
typename Queue<T>::Node *Queue<T>::getRearNode() const {
    return rear;
}

#endif // WIRELESS_MESH_NETWORK_QUEUE
