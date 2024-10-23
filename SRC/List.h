

#ifndef LIST_H
#define LIST_H

#include <utility>

//nullptr:空类型
//new:新建

template <typename T>
class List
{
private:
    template <typename T>
    struct Node{
        T data;
        struct Node* nextPtr;   // 后节点指针
    };

private:

    Node<T> * head = nullptr;
    unsigned int size = 0;  // unsigned 表示无符号类型，符号就是负号，也就是一个没有负号的数，就是一个不小于0的数,   size : 尺寸
public:
    List<T>(){}

    Node<T>* insert( Node<T>* frontNode,T data){//在这链表里面都要从模板里面取变量所以不能用const
        if ( head == nullptr || size == 0 ){
            head = new Node<T>();// head=new：指向的新建的空间
            head->data = data;          // 获取head指向的空间中的data变量，并给其赋值
            head->nextPtr = nullptr;    // 获取head指向后节点，赋值为空值
            size++;                     // 新空间        空间不为空
            return head;
        }

        if ( frontNode == nullptr ) return nullptr;       // 如果他空间不为空，但是插入节点的前一个节点为空，因为我们无法在空节点后面插入节点，因此返回插入失败

        Node<T>* newNode = new Node<T>(); //
        newNode->data = data;
        newNode->nextPtr = frontNode->nextPtr;
        frontNode->nextPtr = newNode;
        size++;
        return newNode;
    }

    bool remove(Node<T>* node){
        if (node == nullptr) return false;  // 要移除的节点为空，返回失败
        if (size == 0) return false;        // 链表大小为0，说明其中不存在节点，自然无法移除节点，返回失败
        Node<T> * frontNode = head;  // 第一步，让指针指向链表的头节点
        if (node == head) {                 // 指针当前是否已经指向要删除的节点，如果是
            head = head->nextPtr;           // 说明要删除的节点是头节点，那么直接让head指向头节点的后一个节点
            delete node;                    // 回收需要删除的节点占据的空间
            return true;                    // 返回移除成功
        }
        while(frontNode->nextPtr != node && frontNode->nextPtr != nullptr){ // 循环遍历寻找需要删除的节点的前一个节点
            frontNode = frontNode->nextPtr;
        }
        if (frontNode->nextPtr == node){    // 找到需要删除的node节点的前一个节点了
            frontNode->nextPtr = node->nextPtr; // 将前一个节点的后节点指针指向需要删除的节点的后一个节点
            delete node;                    // 回收需要删除的节点占据的空间
            return true;                    // 返回移除成功
        }
        return false;                       // 找不到需要删除的节点的前一个节点，返回失败
    }
};



#endif // LIST_H
