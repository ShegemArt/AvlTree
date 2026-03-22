#include "AVLTree.h"
#include <iostream>

int main() {
    AVLTree<int> tree;

    tree.InsertNode(10);
    tree.InsertNode(5);
    tree.InsertNode(15);
    tree.InsertNode(12);
    tree.InsertNode(11);

    std::cout << "\nVertical print:\n";
    tree.printVertical();

    std::cout << "\nHorizontal print:\n";
    tree.printHorizontal();

    std::cout << "\nTraversals:\n";
    std::cout << "InOrder: ";
    tree.printInOrder();

    std::cout << "PreOrder: ";
    tree.printPreOrder();

    std::cout << "PostOrder: ";
    tree.printPostOrder();

    std::cout << "\nSearch\n";
    std::cout << "Contains 12: " << tree.ContainsNode(12) << "\n";
    std::cout << "Contains 99: " << tree.ContainsNode(99) << "\n";

    std::cout << "\nDuplicate Test\n";
    tree.InsertNode(10);

    std::cout << "\nRemove\n";
    tree.RemoveNode(12);

    std::cout << "After removing 12:\n";
    tree.printVertical();

    std::cout << "\n\nRotations Tests\n";

    {
        std::cout << "\n1. Small Left Turn\n";
        AVLTree<int> t;

        t.InsertNode(10);
        t.InsertNode(20);
        t.InsertNode(30);

        t.printVertical();
    }

    {
        std::cout << "\n2. Small Rigth Turn\n";
        AVLTree<int> t;

        t.InsertNode(30);
        t.InsertNode(20);
        t.InsertNode(10);

        t.printVertical();
    }

    {
        std::cout << "\n3. Big Left Turn\n";
        AVLTree<int> t;

        t.InsertNode(10);
        t.InsertNode(30);
        t.InsertNode(20);

        t.printVertical();
    }

    {
        std::cout << "\n4. Big Rigth Turn\n";
        AVLTree<int> t;

        t.InsertNode(30);
        t.InsertNode(10);
        t.InsertNode(20);

        t.printVertical();
    }

    return 0;
}