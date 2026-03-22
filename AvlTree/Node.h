#pragma once
#pragma once
#include <memory>

// AVL Tree Node
template <typename T>
struct Node {
    T value;
    int height;

    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    Node(T val) : value(val), height(1) {}
};