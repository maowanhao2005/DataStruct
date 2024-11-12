#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <queue>
#include <cstdint>

struct GUID{
    uint32_t session = 0;
    uint32_t local = 0;

    bool operator==(const GUID& o) const {
        return local == o.local && session == o.session;
    }
    bool operator<(const GUID& o) const {
        return session < o.session || (session == o.session && local < o.local);
    }
    bool operator>(const GUID& o) const {
        return session > o.session || (session == o.session && local > o.local);
    }
};



template <typename T>
class AVLTree {
private:
    template <typename U>
    struct Node {
        U data;               // 节点数据
        Node<U>* left;          // 左子树指针
        Node<U>* right;         // 右子树指针
        int height;          // 节点高度
        Node(U value) : data(value), left(nullptr), right(nullptr), height(1) {}
    };
    
    Node<T>* root;              // AVL树的根节点

    // 获取节点的高度
    int height(Node<T>* node) {
        return node ? node->height : 0;
    }

    // 获取节点的平衡因子
    int getBalance(Node<T>* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    // 右旋操作
    Node<T>* rightRotate(Node<T>* y) {
        Node<T>* x = y->left;
        Node<T>* T2 = x->right;

        x->right = y;         // 将 y 作为 x 的右子树
        y->left = T2;         // 将 T2 作为 y 的左子树

        // 更新高度
        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;

        return x;             // 返回新的根节点
    }

    // 左旋操作
    Node<T>* leftRotate(Node<T>* x) {
        Node<T>* y = x->right;
        Node<T>* T2 = y->left;

        y->left = x;          // 将 x 作为 y 的左子树
        x->right = T2;        // 将 T2 作为 x 的右子树

        // 更新高度
        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;

        return y;             // 返回新的根节点
    }

    // 插入新节点
    Node<T>* insert(Node<T>* node, T data) {
        if (!node) 
            return new Node<T>(data); // 创建新节点

        // 递归插入到左子树或右子树
        if (data < node->data)
            node->left = insert(node->left, data);
        else if (data > node->data)
            node->right = insert(node->right, data);
        else
            return node; // 不允许重复的值

        // 更新当前节点的高度
        node->height = 1 + std::max(height(node->left), height(node->right));

        // 计算平衡因子
        int balance = getBalance(node); // 

        // 左左情况
        if (balance > 1 && data < node->left->data)
            return rightRotate(node);
        // 右右情况
        if (balance < -1 && data > node->right->data)
            return leftRotate(node);
        // 左右情况
        if (balance > 1 && data > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // 右左情况
        if (balance < -1 && data < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node; // 返回未改变的节点指针
    }

    // 找到右子树中最小的节点
    Node<T>* minValueNode(Node<T>* node) {
        Node<T>* current = node;
        while (current && current->left) 
            current = current->left;
        return current;
    }

    // 删除节点
    Node<T>* deleteNode(Node<T>* root, T data) {
        if (!root) return root;

        // 递归删除节点
        if (data < root->data)
            root->left = deleteNode(root->left, data);
        else if (data > root->data)
            root->right = deleteNode(root->right, data);
        else {
            // 节点只有一个子节点或没有子节点
            if (!root->left || !root->right) {
                Node<T>* temp = root->left ? root->left : root->right;
                if (!temp) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp; // 复制内容
                }
                delete temp; // 释放删除节点的内存
            } else {
                // 找到右子树中最小的节点
                Node<T>* temp = minValueNode(root->right);
                root->data = temp->data; // 替换数据
                root->right = deleteNode(root->right, temp->data); // 删除替换的节点
            }
        }

        // 如果树只有一个节点
        if (!root) return root;

        // 更新高度
        root->height = 1 + std::max(height(root->left), height(root->right));
        int balance = getBalance(root);

        // 左左情况
        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);
        // 右右情况
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);
        // 左右情况
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        // 右左情况
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root; // 返回未改变的节点指针
    }

    // 层序遍历
    void levelOrder(Node<T>* root) {
        if (!root) return;
        std::queue<Node<T>*> q;
        q.push(root);
        while (!q.empty()) {
            Node<T>* current = q.front();
            q.pop();
            std::cout << current->data << " ";
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
    }

public:
    AVLTree() : root(nullptr) {} // 初始化空树

    // 插入数据
    void insert(T data) {
        root = insert(root, data);
    }

    // 删除数据
    void deleteNode(T data) {
        root = deleteNode(root, data);
    }

    // 层序遍历
    void levelOrder() {
        levelOrder(root);
        std::cout << std::endl;
    }
};

int debugAVL() {
    AVLTree<int> tree;

    int nodes[] = {1,15,2,8,4,12};
    for (int value : nodes) {
        tree.insert(value);
    }

    std::cout << "层序遍历插入后的 AVL 树节点：";
    tree.levelOrder();

    // 删除节点 8
    tree.deleteNode(8);
    std::cout << "删除 8 后的 AVL 树节点：";
    // tree.levelOrder();

    // 删除节点 4
    tree.deleteNode(4);
    std::cout << "删除 4 后的 AVL 树节点：";
    // tree.levelOrder();

    // 删除节点 12
    tree.deleteNode(12);
    std::cout << "删除 12 后的 AVL 树节点：";
    // tree.levelOrder();

    // 删除节点 1
    tree.deleteNode(1);
    std::cout << "删除 1 后的 AVL 树节点：";
    // tree.levelOrder();

    // 尝试删除节点 16（不存在）
    tree.deleteNode(16);
    std::cout << "尝试删除 16 后的 AVL 树节点：";
    // tree.levelOrder();

    return 0;
}

#endif