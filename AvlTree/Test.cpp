#include <iostream>
#include <cmath>
#include "AVL_Tree.h"

using namespace std;

int main() {
    Item<int>* q = new Item<int>(10);
    ultima_print(q, "<>");
    q = q->AVL_add(5);
    ultima_print(q, "<>");
    q = q->AVL_add(15);
    ultima_print(q, "<>");
    q = q->AVL_add(12);
    ultima_print(q, "<>");
    q = q->AVL_add(11);
    ultima_print(q, "<>");
    return 0;
}
