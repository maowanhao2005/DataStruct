
#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

template <typename DataType>
class queue{
private:
    template<typename T>
    struct Node{
        T data;
        Node<T>* nextPtr;
    };
    
    
private:
    using Ptr = Node<DataType>*;


private:
    Ptr head = nullptr;
    Ptr tail = nullptr;
    size_t size = 0;

public:
    queue() = default;
    ~queue(){                   // 析构函数：释放本类所占的内存空间
        while (head != nullptr)
        {
            Ptr temp = head;
            head = head->nextPtr;
            std::cout << "delete " << temp->data << std::endl;
            delete temp;
        }
        tail = nullptr;
        std::cout << "queue has been deleted!" << std::endl;
    }

public:
    void push_back(DataType data){  // 向队列尾部添加元素
        if (head == nullptr)
        {
            head = new Node<DataType>;
            head->data = data;
            head->nextPtr = nullptr;
            tail = head;
            size++;
        }
        else
        {
            Ptr temp = new Node<DataType>;
            temp->data = data;
            temp->nextPtr = nullptr;
            tail->nextPtr = temp;
            tail = temp;
            size++;
        }
    }

    void pop_front(){   // 删除第一个节点
        if (head == nullptr)
        {
            std::cout << "queue is empty!" << std::endl;
        }
        else
        {
            Ptr temp = head;
            head = head->nextPtr;
            delete temp;
            size--;
            if (head == nullptr)
            {
                tail = nullptr;
            }
        }
    }

    DataType front(){   // 返回第一个元素
        return head->data;
    }

    size_t getSize(){   // 返回队列中元素的个数
        return size;
    }

    bool empty(){       // 判断队列是否为空
        return size == 0;
    }

    void print(){
        for (Ptr temp = head; temp != nullptr; temp = temp->nextPtr)
        {
            std::cout << temp->data << ",";
        }
        std::cout << std::endl;
    }
};

void debugQueue(){
    queue<int> q;
    
    q.push_back(1);
    q.push_back(2);
    q.push_back(3);
    q.push_back(4);
    q.push_back(5);
    q.push_back(6);
    q.push_back(7);
    q.push_back(8);
    q.push_back(9);
    q.push_back(10);

    // 将队列中的每一个数加起来
    
    int sum = 0;
    while(!q.empty()){
        sum += q.front();
        q.pop_front();
        std::cout << "size = "<< q.getSize() << std::endl;
    }
    q.push_back(12);    
    std::cout << "sum = " << sum << std::endl;
    q.push_back(11);
    
    return ;
}

#endif // QUEUE_H