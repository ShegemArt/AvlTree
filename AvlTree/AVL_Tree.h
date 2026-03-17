#include <iostream>
#include <cmath>
#define AVL_Tree

using namespace std;

template <typename T>
struct Item {
    T value;
    int h = 1;
    Item* up = nullptr;
    Item* left = nullptr;
    Item* right = nullptr;


    Item(T a) {
        this->value = a;
    }

    void add(T a) {
        if (a >= value) {
            if (right != nullptr) {
                right->add(a);
            }
            else {
                Item<T>* q = new Item<T>(a);
                q->up = this;
                right = q;
            }
        }
        else if (a < value) {
            if (left != nullptr) {
                left->add(a);
            }
            else {
                Item<T>* q = new Item<T>(a);
                q->up = this;
                left = q;
            }
        }
        h = height();
    }

    int height() {
        if (left == nullptr and right == nullptr) {
            return 1;
        }
        else if (left == nullptr and right != nullptr) {
            return 1 + right->height();
        }
        else if (left != nullptr and right == nullptr) {
            return 1 + left->height();
        }
        else {
            return 1 + max(right->height(), left->height());
        }
    }

    int num() {
        int k = 0;
        if (left != nullptr) {
            k += left->num();
        }
        if (right != nullptr) {
            k += right->num();
        }
        return k + 1;

    }

    int balance() {
        if (right == nullptr and left == nullptr) {
            return 0;
        }
        else if (right != nullptr and left == nullptr) {
            return right->h;
        }
        else if (right == nullptr and left != nullptr) {
            return 0 - left->h;
        }
        else {
            return right->h - left->h;
        }
    }

    void refresher() {
        if (left != nullptr) {
            left->refresher();
        }
        if (h != height()) {
            h = height();
        }
        if (right != nullptr) {
            right->refresher();
        }
    }

    void checker() {
        if (left != nullptr) {
            left->checker();
        }
        if (h != height()) {
            cout << "+1" << endl;
        }
        else if (h < height()) {
            cout << "-1" << endl;
        }
        if (right != nullptr) {
            right->checker();
        }
    }

    Item<T>* search(T num) {
        if (value == num) {
            return this;
        }
        else if ((num >= value and right == nullptr) or (num < value and left == nullptr)) {
            cout << "Search ERROR" << endl;
            return nullptr;
        }
        else if (num >= value) {
            return right->search(num);
        }
        else {
            return left->search(num);
        }
    }

    Item<T>* AVL_add(T a) {
        add(a);
        return rebalance(this);
    }
};

template <typename T>
Item<T>* delete_node(Item<T>* f, T num) {
    Item<T>* cur = f->search(num);
    if (cur == nullptr) {
        cout << "Delete ERROR" << endl;
        return nullptr;
    }
    else {
        if (cur->left == nullptr and cur->right == nullptr) {
            if (cur->value >= cur->up->value) {
                cur->up->right = nullptr;
            }
            else {
                cur->up->left = nullptr;
            }
            delete cur;
            f->refresher();
            return f;
        }
        else if (cur->right == nullptr and cur->left != nullptr) {
            if (cur->up != nullptr) {
                if (cur->value >= cur->up->value) {
                    cur->up->right = cur->left;
                }
                else {
                    cur->up->left = cur->left;
                }
                cur->left->up = cur->up;
                delete cur;
                f->refresher();
                return f;
            }
            else {
                f = cur->left;
                f->up = nullptr;
                delete cur;
                f->refresher();
                return f;
            }
        }
        else if (cur->right != nullptr and cur->left == nullptr) {
            if (cur->up != nullptr) {
                if (cur->value >= cur->up->value) {
                    cur->up->right = cur->right;
                }
                else {
                    cur->up->left = cur->right;
                }
                cur->right->up = cur->up;
                delete cur;
                f->refresher();
                return f;
            }
            else {
                f = cur->right;
                f->up = nullptr;
                delete cur;
                f->refresher();
                return f;
            }
        }
        else {
            Item<T>* p = cur->right;
            if (p->left != nullptr) {
                while (p->left != nullptr) {
                    p = p->left;
                }
                p->up->left = nullptr;
                if (cur->up != nullptr) {
                    p->up = cur->up;
                    if (p->value >= p->up->value) {
                        p->up->right = p;
                    }
                    else {
                        p->up->left = p;
                    }
                }
                else {
                    f = p;
                    f->up = nullptr;
                }
                p->left = cur->left;
                p->right = cur->right;
                delete cur;
                f->refresher();
                return f;
            }
            else {
                if (cur->up != nullptr) {
                    p->up = cur->up;
                    if (p->value >= p->up->value) {
                        p->up->right = p;
                    }
                    else {
                        p->up->left = p;
                    }
                }
                else {
                    f = p;
                    f->up = nullptr;
                }
                p->left = cur->left;
                delete cur;
                f->refresher();
                return f;
            }
        }
    }

}

template <typename T>
Item<T>* small_left_turn(Item<T>* a) {
    Item<T>* b = a->right;
    a->right = b->left;
    if (b->left != nullptr) {
        b->left->up = a;
    }
    b->left = a;
    b->up = a->up;
    a->up = b;
    if (b->up != nullptr) {
        if (b->value >= b->up->value) {
            b->up->right = b;
        }
        else {
            b->up->left = b;
        }
    }
    b->refresher();
    return b;
}

template <typename T>
Item<T>* small_right_turn(Item<T>* a) {
    Item<T>* b = a->left;
    a->left = b->right;
    if (b->right != nullptr) {
        b->right->up = a;
    }
    b->right = a;
    b->up = a->up;
    a->up = b;
    if (b->up != nullptr) {
        if (b->value >= b->up->value) {
            b->up->right = b;
        }
        else {
            b->up->left = b;
        }
    }
    b->refresher();
    return b;
}

template <typename T>
Item<T>* big_left_turn(Item<T>* a) {
    a = small_right_turn(a->right)->up;
    a = small_left_turn(a);
    return a;
}

template <typename T>
Item<T>* big_right_turn(Item<T>* a) {
    a = small_left_turn(a->left)->up;
    a = small_right_turn(a);
    return a;
}

template <typename T>
Item<T>* rebalance(Item<T>* a) {
    if (a->balance() == 2) {
        if (a->right->balance() > 0) {
            return small_left_turn(a);
        }
        else {
            return big_left_turn(a);
        }
    }
    else if (a->balance() == -2) {
        if (a->left->balance() > 0) {
            return big_right_turn(a);
        }
        else {
            return small_right_turn(a);
        }
    }
    else {
        return a;
    }
}

template <typename T>
Item<T>* AVL_delete(Item<T>* f, T num) {
    f = delete_node(f, num);
    return rebalance(f);
}

template <typename T>
void print_level(Item<T>* numb, int level, int maxl, int h) {
    if (numb == nullptr) {
        cout << " ";
        for (int j = 0; j < int(pow(2, h - level)) - 1; j++) {
            cout << " ";
        }
    }
    else if (level == maxl) {
        cout << numb->value;
        for (int j = 0; j < int(pow(2, h - level)) - 1; j++) {
            cout << " ";
        }
    }
    else {
        print_level(numb->left, level + 1, maxl, h);
        print_level(numb->right, level + 1, maxl, h);
    }
}

template <typename T>
void print(Item<T>* cur) {
    if (cur->left != nullptr) {
        print(cur->left);
    }
    cout << cur->value << ' ';
    if (cur->right != nullptr) {
        print(cur->right);
    }
}

template <typename T>
void reverse_print(Item<T>* cur) {
    if (cur->right != nullptr) {
        reverse_print(cur->right);
    }
    cout << cur->value << ' ';
    if (cur->left != nullptr) {
        reverse_print(cur->left);
    }
}

template <typename T>
void top_down(Item<T>* cur) {
    cout << cur->value << ' ';
    if (cur->left != nullptr) {
        top_down(cur->left);
    }
    if (cur->right != nullptr) {
        top_down(cur->right);
    }
}

template <typename T>
void down_top(Item<T>* cur) {
    if (cur->left != nullptr) {
        down_top(cur->left);
    }
    if (cur->right != nullptr) {
        down_top(cur->right);
    }
    cout << cur->value << ' ';
}

template <typename T>
void vert_print(Item<T>* num) {
    int h = num->height();

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < int(pow(2, h - i - 1)) - 1; j++) {
            cout << " ";
        }
        print_level(num, 0, i, h);
        cout << endl;
    }
}

template <typename T>
void hor_print(Item<T>* a, int level = 0) {
    if (a != nullptr) {
        hor_print(a->right, level + 1);
        for (int i = 0; i < level; i++) {
            cout << "     ";
        }
        cout << a->value << endl;
        hor_print(a->left, level + 1);
    }
}

template <typename T>
void ultima_print(Item<T>* cur, string q) {
    if (q == "1") {
        print(cur);
        cout << endl;
    }
    else if (q == "-1") {
        reverse_print(cur);
        cout << endl;
    }
    else if (q == "2") {
        top_down(cur);
        cout << endl;
    }
    else if (q == "3") {
        down_top(cur);
        cout << endl;
    }
    else if (q == "->") {
        hor_print(cur);
        cout << endl;
    }
    else if (q == "<>") {
        vert_print(cur);
        cout << endl;
    }
    else {
        cout << "FAILURE!" << endl;
    }
}
