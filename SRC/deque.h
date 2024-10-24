#ifndef DEQUE_H
#define DEQUE_H
#include <iostream>
#include <stdexcept>

/// task :
/// # 1 把双端队列的每一个函数的功能注释说明清楚
/// # 2 把双端队列的每一个函数的具体实现注释说明清楚


template <typename T> 
class Deque {
private:
    template<typename U>
    struct Node {
        U data;
        Node<U> *next;
        Node<U> *prev;
    };

private:
    Node<T> *head;
    Node<T> *tail;
    int size;
    
public:
    Deque() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    void push_front(T data) {
        Node<T> *new_node = new Node<T>;
        new_node->data = data;
        new_node->next = head;
        new_node->prev = nullptr;
        if (head != nullptr) {
            head->prev = new_node;
        }
        head = new_node;
        if (tail == nullptr) {
            tail = new_node;
        }
        size++;
    }

    void push_back(T data) {
        Node<T> *new_node = new Node<T>;
        new_node->data = data;
        new_node->next = nullptr;
        new_node->prev = tail;
        if (tail != nullptr) {
            tail->next = new_node;
        }
        tail = new_node;
        if (head == nullptr) {
            head = new_node;
        }
        size++;
    }

    T pop_front() {
        if (head == nullptr) {
            throw std::runtime_error("Deque is empty");
        }
        Node<T> *temp = head;
        T data = temp->data;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        delete temp;
        size--;
        return data;
    }

    T pop_back() {
        if (tail == nullptr) {
            throw std::runtime_error("Deque is empty");
        }
        Node<T> *temp = tail;
        T data = temp->data;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        }
        delete temp;
        size--;
        return data;
    }

    T front() const {
        if (head == nullptr) {
            throw std::runtime_error("Deque is empty");
        }
        return head->data;
    }

    T back() const {
        if (tail == nullptr) {
            throw std::runtime_error("Deque is empty");
        }
        return tail->data;
    }

    bool empty() const {
        return size == 0;
    }

    int get_size() const {
        return size;
    }

    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    ~Deque() {
        clear();
    }

    class Iterator {    // 迭代器就是指针
        private:
        using constIterator = const Iterator;
    private:
        Node<T> *current;

    public:
        Iterator(Node<T> *node) : current(node) {}

        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        Iterator& operator--() {
            current = current->prev;
            return *this;
        }

        bool operator!=(constIterator& other) const {
            return current != other.current;
        }
    };
};

void debugDeque() {
    Deque<int> deque;
    deque.push_front(1);
    deque.push_front(2);
    deque.push_front(3);
    deque.push_back(4);
    deque.push_back(5);
    deque.push_back(6);

    std::cout << "Deque size: " << deque.get_size() << std::endl;
}


#endif // DEQUE_H