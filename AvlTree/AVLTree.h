#pragma once
#include <iostream>
#include <memory>
#include <cmath>
#include <algorithm>
#include "Node.h"
//AVL Tree
template <typename T>
class AVLTree {
private:
    // Epsilon for comparison
    static constexpr double epsilon = 1e-9;

    // Root node
    std::unique_ptr<Node<T>> root;

    // Get height node
    int getHeight(const std::unique_ptr<Node<T>>& node) const {
        return node ? node->height : 0;
    }

    // Update node height 
    void updateHeight(Node<T>* node) {
        node->height = 1 + std::max(
            getHeight(node->left),
            getHeight(node->right)
        );
    }

    // Get balance factor of node
    int getBalanceFactor(const std::unique_ptr<Node<T>>& node) const {
        return getHeight(node->right) - getHeight(node->left);
    }

    // Left Rotation
    std::unique_ptr<Node<T>> rotateLeft(std::unique_ptr<Node<T>> a) {
        auto b = std::move(a->right);
        a->right = std::move(b->left);
        b->left = std::move(a);

        updateHeight(b->left.get());
        updateHeight(b.get());

        return b;
    }

    // Right Rotation
    std::unique_ptr<Node<T>> rotateRight(std::unique_ptr<Node<T>> a) {
        auto b = std::move(a->left);
        a->left = std::move(b->right);
        b->right = std::move(a);

        updateHeight(b->right.get());
        updateHeight(b.get());

        return b;
    }

    // Tree Balancing
    std::unique_ptr<Node<T>> balance(std::unique_ptr<Node<T>> node) {
        updateHeight(node.get());

        int balanceCount = getBalanceFactor(node);

        if (balanceCount == 2) {
            if (getBalanceFactor(node->right) < 0)
                node->right = rotateRight(std::move(node->right));
            return rotateLeft(std::move(node));
        }

        if (balanceCount == -2) {
            if (getBalanceFactor(node->left) > 0)
                node->left = rotateLeft(std::move(node->left));
            return rotateRight(std::move(node));
        }

        return node;
    }

    // Add node in Tree
    std::unique_ptr<Node<T>> insert(std::unique_ptr<Node<T>> node, T value) {
        if (!node)
            return std::make_unique<Node<T>>(value);

        if (equal(value, node->value)) {
            std::cout << "Duplicate ignored: " << value << "\n";
            return node;
        }

        if (less(value, node->value))
            node->left = insert(std::move(node->left), value);
        else
            node->right = insert(std::move(node->right), value);

        return balance(std::move(node));
    }

    // Find node with value
    Node<T>* find(Node<T>* node, T value) const {
        if (!node) return nullptr;

        if (equal(value, node->value))
            return node;

        if (less(value, node->value))
            return find(node->left.get(), value);
        else
            return find(node->right.get(), value);
    }

    // Comparison values
    bool equal(T a, T b) const {
        if constexpr (std::is_floating_point_v<T>)
            return std::abs(a - b) < epsilon;
        else
            return a == b;
    }

    // Check if a less b
    bool less(T a, T b) const {
        if constexpr (std::is_floating_point_v<T>)
            return a < b - epsilon;
        else
            return a < b;
    }

    // Find node with min value
    Node<T>* findMin(Node<T>* node) const {
        return node->left ? findMin(node->left.get()) : node;
    }

    // Delete node with min value
    std::unique_ptr<Node<T>> removeMin(std::unique_ptr<Node<T>> node) {
        if (!node) return nullptr;

        if (!node->left)
            return std::move(node->right);

        node->left = removeMin(std::move(node->left));
        return balance(std::move(node));
    }

    // Delete node with this value
    std::unique_ptr<Node<T>> remove(std::unique_ptr<Node<T>> node, T value) {
        if (!node) return nullptr;

        if (less(value, node->value))
            node->left = remove(std::move(node->left), value);
        else if (less(node->value, value))
            node->right = remove(std::move(node->right), value);
        else {
            if (!node->right)
                return std::move(node->left);

            auto min = findMin(node->right.get());
            node->value = min->value;
            node->right = remove(std::move(node->right), min->value);
        }

        return balance(std::move(node));
    }

    // Print values from min to max
    void inorder(const Node<T>* node) const {
        if (!node) return;
        inorder(node->left.get());
        std::cout << node->value << " ";
        inorder(node->right.get());
    }

    // Print left -> root -> right
    void preorder(const Node<T>* node) const {
        if (!node) return;
        std::cout << node->value << " ";
        preorder(node->left.get());
        preorder(node->right.get());
    }

    // Print left -> right -> root
    void postorder(const Node<T>* node) const {
        if (!node) return;
        postorder(node->left.get());
        postorder(node->right.get());
        std::cout << node->value << " ";
    }

    // Print nodes with one heigth
    void printLevel(Node<T>* node, int level, int maxLevel, int height) const {
        if (!node) {
            std::cout << " ";
            for (int j = 0; j < int(pow(2, height - level)) - 1; j++)
                std::cout << " ";
        }
        else if (level == maxLevel) {
            std::cout << node->value;
            for (int j = 0; j < int(pow(2, height - level)) - 1; j++)
                std::cout << " ";
        }
        else {
            printLevel(node->left.get(), level + 1, maxLevel, height);
            printLevel(node->right.get(), level + 1, maxLevel, height);
        }
    }

    // Print tree vertical
    void verticalPrint(Node<T>* node) const {
        int h = getHeight(root);

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < int(pow(2, h - i - 1)) - 1; j++)
                std::cout << " ";

            printLevel(node, 0, i, h);
            std::cout << "\n";
        }
    }

    // Print tree horizontal
    void horizontalPrint(Node<T>* node, int level = 0) const {
        if (!node) return;

        horizontalPrint(node->right.get(), level + 1);

        for (int i = 0; i < level; i++)
            std::cout << "     ";

        std::cout << node->value << "\n";

        horizontalPrint(node->left.get(), level + 1);
    }

public:

    // Add node with this value
    void InsertNode(T value) {
        root = insert(std::move(root), value);
    }

    // Remove node with this value
    void RemoveNode(T value) {
        root = remove(std::move(root), value);
    }

    // Show if contains node with this value
    bool ContainsNode(T value) const {
        return find(root.get(), value) != nullptr;
    }

    // Print values from min to max
    void printInOrder() const {
        inorder(root.get());
        std::cout << "\n";
    }

    // Print left -> root -> right
    void printPreOrder() const {
        preorder(root.get());
        std::cout << "\n";
    }

    // Print left -> right -> root
    void printPostOrder() const {
        postorder(root.get());
        std::cout << "\n";
    }

    // Print tree vertical
    void printVertical() const {
        verticalPrint(root.get());
    }

    // Print tree horizontal
    void printHorizontal() const {
        horizontalPrint(root.get());
    }
};