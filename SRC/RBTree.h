#include <iostream>
#include <memory>

enum class Color { RED, BLACK };

template <typename T>
class RBTree {
private:
    struct Node {
        T key;
        Color color;
        std::shared_ptr<Node> left, right, parent;

        Node(T key, Color color, std::shared_ptr<Node> parent = nullptr)
            : key(key), color(color), parent(parent), left(nullptr), right(nullptr) {}
    };

    std::shared_ptr<Node> root;

    void leftRotate(std::shared_ptr<Node> x) {
        auto y = x->right;
        x->right = y->left;
        if (y->left != nullptr) 
            y->left->parent = x;
        
        y->parent = x->parent;

        if (x->parent == nullptr) 
            root = y;
        else if (x == x->parent->left) 
            x->parent->left = y;
        else 
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rightRotate(std::shared_ptr<Node> x) {
        auto y = x->left;
        x->left = y->right;
        if (y->right != nullptr) 
            y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr) 
            root = y;
        else if (x == x->parent->right) 
            x->parent->right = y;
        else
            x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    void insertFixup(std::shared_ptr<Node> z) {
        while (z->parent != nullptr && z->parent->color == Color::RED) {
            if (z->parent == z->parent->parent->left) {
                auto y = z->parent->parent->right;
                if (y != nullptr && y->color == Color::RED) {
                    z->parent->color = Color::BLACK;
                    y->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    rightRotate(z->parent->parent);
                }
            } else {
                auto y = z->parent->parent->left;
                if (y != nullptr && y->color == Color::RED) {
                    z->parent->color = Color::BLACK;
                    y->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    leftRotate(z->parent->parent);
                }
            }
        } 
        root->color = Color::BLACK;
    }

    void transplant(std::shared_ptr<Node> u, std::shared_ptr<Node> v) {
        if (u->parent == nullptr) 
            root = v;
        else if (u == u->parent->left) 
            u->parent->left = v;
        else 
            u->parent->right = v;
        if (v != nullptr) 
            v->parent = u->parent;
    }

    std::shared_ptr<Node> minimum(std::shared_ptr<Node> x) {
        while (x->left != nullptr) 
            x = x->left;
        return x;
    }

    void deleteFixup(std::shared_ptr<Node> x) {
        while (x != root && x->color == Color::BLACK) {
            if (x == x->parent->left) {
                auto w = x->parent->right;
                if (w->color == Color::RED) {
                    w->color = Color::BLACK;
                    x->parent->color = Color::RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if ((w->left == nullptr || w->left->color == Color::BLACK) &&
                    (w->right == nullptr || w->right->color == Color::BLACK)) {
                    w->color = Color::RED;
                    x = x->parent;
                } else {
                    if (w->right == nullptr || w->right->color == Color::BLACK) {
                        if (w->left != nullptr) 
                            w->left->color = Color::BLACK;
                        w->color = Color::RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = Color::BLACK;
                    if (w->right != nullptr) 
                        w->right->color = Color::BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                auto w = x->parent->left;
                if (w->color == Color::RED) {
                    w->color = Color::BLACK;
                    x->parent->color = Color::RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if ((w->right == nullptr || w->right->color == Color::BLACK) &&
                    (w->left == nullptr || w->left->color == Color::BLACK)) {
                    w->color = Color::RED;
                    x = x->parent;
                } else {
                    if (w->left == nullptr || w->left->color == Color::BLACK) {
                        if (w->right != nullptr)
                            w->right->color = Color::BLACK;
                        w->color = Color::RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = Color::BLACK;
                    if (w->left != nullptr)
                        w->left->color = Color::BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            } 
        }
        x->color = Color::BLACK;
    }

    void removeNode(std::shared_ptr<Node> z) {
        auto y = z;
        auto yOriginalColor = y->color;
        std::shared_ptr<Node> x;
        if (z->left == nullptr) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == nullptr) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            yOriginalColor = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        if (yOriginalColor == Color::BLACK) deleteFixup(x);
    }

public:
    RBTree() : root(nullptr) {}

    void insert(T key) {
        auto z = std::make_shared<Node>(key, Color::RED);
        auto y = std::shared_ptr<Node>();
        auto x = root;
        while (x != nullptr) {
            y = x;
            if (z->key < x->key) 
                x = x->left;
            else 
                x = x->right;
        }
        z->parent = y;
        if (y == nullptr) 
            root = z;
        else if (z->key < y->key) 
            y->left = z;
        else 
            y->right = z;
        insertFixup(z);
    }

    bool contains(T key) {
        auto x = root;
        while (x != nullptr) {
            if (key < x->key) 
                x = x->left;
            else if (key > x->key) 
                x = x->right;
            else 
                return true;
        }
        return false;
    }

    void remove(T key) {
        auto z = root;
        while (z != nullptr && z->key != key) {
            if (key < z->key) 
                z = z->left;
            else 
                z = z->right;
        }
        if (z != nullptr) 
            removeNode(z);
    }

    void printInOrder(std::shared_ptr<Node> node) const {
        if (node != nullptr) {
            printInOrder(node->left);
            std::cout << node->key << " ";
            printInOrder(node->right);
        }
    }

    void print() const {
        printInOrder(root);
        std::cout << std::endl;
    }
};

int debugRBTree() {
    RBTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.insert(25);
    tree.insert(35);
    tree.insert(5);
    tree.insert(56);
    tree.insert(60);
    tree.insert(70);
    tree.print();  // 输出: 10 15 20 25 30

    tree.remove(20);
    tree.print();  // 输出: 10 15 25 30

    std::cout << "Contains 15: " << tree.contains(15) << std::endl;  // 输出: Contains 15: 1
    std::cout << "Contains 20: " << tree.contains(20) << std::endl;  // 输出: Contains 20: 0

    return 0;
}