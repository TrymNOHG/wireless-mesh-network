//
// Created by Trym Hamer Gudvangen on 5/16/23.

#ifndef WIRELESS_MESH_NETWORK_QUEUE
#define WIRELESS_MESH_NETWORK_QUEUE
#include "PriorityQueue.h"

/**
 * @brief This method constructs a PriorityQueue object.
 *
 * @param graph Reference to the graph used for the NodeComparator.
 */
PriorityQueue::PriorityQueue(const Graph& graph)
    : queue(NodeComparator(&graph)), graph(graph) {}

/**
 * @brief Destroys the PriorityQueue object.
 * Clears the queue.
 */
PriorityQueue::~PriorityQueue() {
  clear();
}

/**
 * @brief Checks if the queue is empty.
 *
 * @return True if the queue is empty, false otherwise.
 */
bool PriorityQueue::isEmpty() const {
  return queue.empty();
}

/**
 * @brief Returns the current size of the queue.
 *
 * @return The size of the queue.
 */
std::size_t PriorityQueue::getSize() const {
  return queue.size();
}

/**
 * @brief Pushes a new node into the queue.
 *
 * @param data The data to be pushed.
 */
void PriorityQueue::push(const unsigned int& data) {
  std::shared_ptr<Node> newNode = std::make_shared<Node>(data);
  queue.push(newNode);
}

/**
 * @brief Pops the top node from the queue.
 *
 * @return The data of the popped node.
 * @throws std::runtime_error if the queue is empty.
 */
unsigned int PriorityQueue::pop() {
  if (isEmpty()) {
    throw std::runtime_error("PriorityQueue is empty. Cannot pop.");
  }

  unsigned int data = queue.top()->nodeDescriptor;
  queue.pop();
  return data;
}

/**
 * @brief Pops a node with the given file descriptor from the queue.
 *
 * @param fileDescriptor The file descriptor of the node to be popped.
 * @return The data of the popped node.
 */
unsigned int PriorityQueue::pop(const unsigned int& fileDescriptor) {
  std::vector<std::shared_ptr<Node>> elements;
  unsigned int poppedData = 0;

  while (!queue.empty()) {
    std::shared_ptr<Node> topNode = queue.top();
    queue.pop();

    if (topNode->nodeDescriptor == fileDescriptor) {
      poppedData = topNode->nodeDescriptor;
    } else {
      elements.push_back(topNode);
    }
  }

  // Reconstruct the heap
  queue =
      std::priority_queue<std::shared_ptr<Node>,
                          std::vector<std::shared_ptr<Node>>, NodeComparator>(
          elements.begin(), elements.end(), NodeComparator(&graph));

  return poppedData;
}

/**
 * @brief Returns the top node of the queue.
 *
 * @return The top node of the queue.
 * @throws std::runtime_error if the queue is empty.
 */
const std::shared_ptr<PriorityQueue::Node>& PriorityQueue::peek() const {
  if (isEmpty()) {
    throw std::runtime_error("PriorityQueue is empty. Cannot peek.");
  }

  return queue.top();
}

/**
 * @brief Updates a node in the queue by its index.
 *
 * @param index The index of the node to be updated.
 */
void PriorityQueue::updateNodeByIndex(const unsigned int& index) {
  pop(index);
  push(index);
}

/**
 * @brief Returns a node from the queue by its index.
 *
 * @param index The index of the node.
 * @return The node at the given index.
 * @throws std::runtime_error if the index is out of bounds.
 */
std::shared_ptr<PriorityQueue::Node> PriorityQueue::getNodeByIndex(
    const unsigned int& index) {
  if (index >= getSize()) {
    std::cout << "Index: " << index << std::endl;
    throw std::runtime_error("Index out of bounds.");
  }

  std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>,
                      NodeComparator>
      tempQueue = queue;
  std::vector<std::shared_ptr<Node>> elements;
  for (unsigned int i = 0; i < index; i++) {
    elements.emplace_back(tempQueue.top());
    tempQueue.pop();
  }

  std::shared_ptr<Node> nodeByIndex = tempQueue.top();

  // Reconstruct the heap with all the elements
  tempQueue.pop();
  while (!tempQueue.empty()) {
    elements.emplace_back(tempQueue.top());
    tempQueue.pop();
  }

  elements.emplace_back(nodeByIndex);

  queue =
      std::priority_queue<std::shared_ptr<Node>,
                          std::vector<std::shared_ptr<Node>>, NodeComparator>(
          elements.begin(), elements.end(), NodeComparator(&graph));

  return nodeByIndex;
}

/**
 * @brief Clears the queue.
 */
void PriorityQueue::clear() {
  while (!isEmpty()) {
    queue.pop();
  }
}

#endif // WIRELESS_MESH_NETWORK_QUEUE
