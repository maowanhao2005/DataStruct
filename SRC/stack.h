

#include <iostream>

template<typename DataType>
class stack{
private:
    template<typename T>
    struct Node{
        T data;
        Node<T>* next;
    };

    
private:
    Node<DataType>* top = NULL;
    int size = 0;
public:
    stack() = default;
    ~stack(){
        while(top!=NULL){
            Node<DataType>* temp = top;
            top = top->next;
            std::cout << "Deleting " << temp->data << std::endl;
            delete temp;
        }
        std::cout << "Stack deleted" << std::endl;
    }

    void push(DataType data){
        if (top==NULL){
            top = new Node<DataType>;
            top->data = data;
            top->next = NULL;
            size++;
            std::cout << "Pushed first: " << data <<",size = "<< size << std::endl;
        }
        else{
            Node<DataType>* temp = new Node<DataType>;
            temp->data = data;
            temp->next = top;
            top = temp;
            size++;
            std::cout << "Pushed: " << data << ",size = "<< size << std::endl;
        }
    }

    DataType pop(){
        if (top==NULL){
            std::cout << "Stack is empty" << std::endl;
            return 0;
        }
        else{
            DataType data = top->data;
            Node<DataType>* temp = top;
            top = top->next;
            delete temp;
            size--;
            std::cout << "Popped: " << data << ",size = "<< size << std::endl;
            return data;
        }
    }

    DataType peek(){
        if (top==NULL){
            std::cout << "Stack is empty" << std::endl;
            return 0;
        }
        else{
            return top->data;
        }
    }

    bool isEmpty(){
        return top==NULL;
    }

    int getSize(){
        return size;
    }

    void print(){
        Node<DataType>* temp = top;
        while(temp!=NULL){
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    void clear(){
        while(top!=NULL){
            Node<DataType>* temp = top;
            top = top->next;
            delete temp;
        }
        size = 0;
        std::cout << "Stack cleared" << std::endl;
    }

};