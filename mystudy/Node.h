//
// Created by Daniel St. John on 11/28/20.
//

#pragma once

#include <string>
#include <vector>
#include <array>
#include <chrono>

template <class T, int N = 10>
class Node {

public:

    Node(T data);

    void Add(Node<T> reachableNode);

    void Remove(Node<T> reachableCandidate);

private:

    std::chrono::time_point<std::chrono::system_clock > creationTime;

    std::string hashCode;

    std::vector<Node<T,N>> reachableNode;

    std::array<T,N> data;
};



