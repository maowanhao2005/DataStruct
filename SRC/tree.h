
#ifndef TREE_H
#define TREE_H


#include <iostream>
#include "stack.h"
using namespace std;

template <class T>
class Tree{
private:
    struct Node{
        T data;
        Node* left;     // 左子树的任意一个节点都小于
        Node* right;
        ~Node(){
            if (left) delete left;
            if (right) delete right;
        }
   };
private:
    Node* root;

public:
    Tree(){
        root = NULL;
    }

    ~Tree(){
        delete root;
    }

public:
    void insert(T data){
        root = insert(root, data);
        return;
    }

    void remove(T data){
        root = remove(root, data);
        return;
    }

    bool search(T data){
        return search(root, data);
    }
    
    void preOrder(){
        preOrder(root);
    }

    void inOrder(){
        inOrder(root);
    }

    void postOrder(){
        postOrder(root);
    }

    void levelOrder(){
        levelOrder(root);
    }

    void printTree() {
        printTreeWithLines(root);
    }



private:
    Node* insert(Node* node, T data){
        if (node == NULL){
            node = new Node;
            node->data = data;
            node->left = NULL;
            node->right = NULL;
        }else if (data < node->data){
            node->left = insert(node->left, data);
        }else if (data > node->data){
            node->right = insert(node->right, data);
        }
        return node;
    }

    Node* remove(Node* node, T data){
        if (node == NULL){
            return node;
        }else if (data < node->data){
            node->left = remove(node->left, data);
        }else if (data > node->data){
            node->right = remove(node->right, data);
        }else{
            if (node->left == NULL && node->right == NULL){
                delete node;
                return NULL;
            }else if (node->left == NULL){
                Node* temp = node->right;
                delete node;
            }
        }
        return node;
    }

    /// node就是要移除的节点
    void removeNode(Node* root,Node* node){
        if (root == nullptr) return;
        
        stack<Node*> s;
        s.push(root);
        while (!s.isEmpty())
        {
            Node* tmp = s.peek();

            if(tmp->data < node->data){   // 在根节点的右子树中
                if(tmp->right!=nullptr){
                    s.push(tmp->right);
                }
                else{
                    return;
                }
            }
            else if(tmp->data > node->data){
                if(tmp->left != nullptr){
                    s.push(tmp->left);
                }
                else{
                    return;
                }
            }
            else{   // 找到这个节点了
                // tmp 就是要删掉的节点
                // 判断这个节点是不是根节点
                if (tmp == root){
                    
                }
            }
            
        }
        

    }


    bool search(Node* node, T data){
        if (node == NULL){
            return false;
        }else if (data < node->data){
            return search(node->left, data);
        }else if (data > node->data){
            return search(node->right, data);
        }else{
            return true;
        }
        return false;
    }
    
    void preOrder(Node* node){
        if (node != NULL){
            std::cout << node->data << " ";
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    void inOrder(Node* node){
        if (node != NULL){
            inOrder(node->left);
            std::cout << node->data << " ";
            inOrder(node->right);
        }
    }

    void postOrder(Node* node){
        if (node != NULL){
            postOrder(node->left);
            postOrder(node->right);
            std::cout << node->data << " ";
        }
    }

    void levelOrder(Node* node){
        if (node == NULL){
            return;
        }
        stack<Node*> stack;
        stack.push(node);
        while (!stack.isEmpty()){
            Node* temp = stack.pop();
            std::cout << temp->data << " ";
            if (temp->left != NULL){
                stack.push(temp->left);
            }
            if (temp->right != NULL){
                stack.push(temp->right);
            }
        }
    }

    /// 打印树结构的函数
    void printTreeWithLines(Node* root, bool isLeft, string prefix = "") {
        if (root == nullptr) {
            return;
        }

        cout << prefix;
        cout << (isLeft ? "├──" : "└──");
        cout << root->data << endl;

        if (root->left || root->right) {
            string newPrefix = prefix + (isLeft ? "│   " : "    ");
            printTreeWithLines(root->left, true, newPrefix);
            printTreeWithLines(root->right, false, newPrefix);
        }
    }

        /// 打印树的结构，带连线
    void printTreeWithLines(Node* root) {
        if (root == nullptr) {
            return;
        }
        cout << root->data << endl;
        if (root->left || root->right) {
            printTreeWithLines(root->left, true, "");
            printTreeWithLines(root->right, false, "");
        }
    }
};

void debugTree(){
    Tree<int> tree;
    // tree.insert(1);
    // tree.insert(3);
    // tree.insert(2);
    // tree.insert(10);
    // tree.insert(7);
    // tree.insert(6);
    // tree.insert(5);
    // tree.insert(8);
    // tree.insert(9);
    // tree.insert(4);

    tree.insert(5);
    tree.insert(3);
    tree.insert(4);
    tree.insert(2);
    tree.insert(1);
    tree.insert(7);
    tree.insert(6);
    tree.insert(8);
    tree.insert(9);

    
    tree.levelOrder();

    std::cout << std::endl;

    tree.printTree();

    std::cout << std::endl;
}

#endif // TREE_H