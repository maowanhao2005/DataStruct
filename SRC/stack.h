#ifndef STACK_H
#define STACK_H
/// task :
/// # 1 把栈的每一个函数的功能注释说明清楚
/// # 2 把栈的每一个函数的具体实现注释说明清楚

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
    Node<DataType>* top = NULL;                                     //空间为空
    int size = 0;                                                   //空间为空
public:
    stack() = default;
    ~stack(){
        while(top!=NULL){                                           //空间不为空的时候
            Node<DataType>* temp = top;                             //让空间指针temp指向top
            top = top->next;                                        //让top指向下一个
            std::cout << "Deleting " << temp->data << std::endl;    //输出一句话和空间指针指向打他的值
            delete temp;                                            //删除上面的空间
        }
        std::cout << "Stack deleted" << std::endl;                  //输出一句话
    }

    /// @brief 将数据放入栈中存储
    /// @param data 将放入栈中的数据
    //
    void push(DataType data){
        if (top==NULL){                                             //如果栈为空
            top = new Node<DataType>;                               //空节点等于一个新建的空间
            top->data = data;                                       //给新建的这个空间的data赋一个新data值
            top->next = NULL;                                       //空间的下一个节点指向空
            size++;                                                 //空间扩展
        }
        else{                                                       //或者
            Node<DataType>* temp = new Node<DataType>;              //空间指向一个变量等于一个新的空间
            temp->data = data;                                      //给这个新的空间赋一个新的data的值
            temp->next = top;                                       //新的空间的下一个指针指向下面的节点
            top = temp;                                             //让top指针指向新空间
            size++;                                                 //空间扩展
        }
        // std::cout << "Pushed: " << data << ",size = "<< size << std::endl;//输出一句话加上data的值再输出一句话加上shize的值
    }

    /// @brief 拿出栈顶数据，并弹出元素
    /// @return 栈顶数据
    DataType pop(){
        if (top==NULL){                                             //如果空间为空
            std::runtime_error("Stack is empty");               // 报错
        }
        DataType data = top->data;                              //让data的top指向新的data
        Node<DataType>* temp = top;                             //让空间指向top
        top = top->next;                                        //让top指向下一个
        delete temp;                                            //删除最上面的空间
        size--;                                                 //空间删除
        // std::cout << "Popped: " << data << ",size = "<< size << std::endl;//输出一句话
        return data;                                            //返回data的值
    }
    
    /// @brief 获取栈顶数据，且并不会弹出元素
    /// @return 栈顶数据
    DataType peek(){
        if (top==NULL){                                             //如果空间为空
            std::runtime_error("Stack is empty");
        }
        return top->data;                                       //返回最上面的top指向的data
    }
    
    /// @brief 返回空间是否为空
    /// @return 如下所示
    bool isEmpty(){                                                 //创建一个布尔值的函数
        return top==NULL;                                          //判断空间是不是空
    }

    /// @brief 获取栈空间内元素个数
    /// @return 元素个数
    int getSize(){                                                  // 创建一个int类型的函数
        return size;                                                //返回size的值
    }
    
    
    ///@brief 从栈顶到栈底打印栈内元素
    ///@return 先让空间指针等于top指针,先搞一个while循环当空间指针不等于空的时候，输出空间指针指向的下一个data的值，再让空间指针指向下一个空间，换行
    void print(){
        Node<DataType>* temp = top;                                 //
        while(temp!=NULL){
            std::cout << temp->data << " ";                          //输出temp指向的data的值
            temp = temp->next;                                      //让temp指向下一个
        }
        std::cout << std::endl;                                     //换行
    }

    
    /// @brief 当top指向的下一个空间不为空的时候让top指向下一个空间删除上一个空间
    /// @note 清空栈内所有元素
    void clear(){
        while(top!=NULL){                                           //空间不等于空的时候
            Node<DataType>* temp = top;                             //让空间的temp指向top
            top = top->next;                                        //让top指向下一个
            delete temp;                                            //删除temp
        }
        size = 0;                                                   //空间等于0
        std::cout << "Stack cleared" << std::endl;                  //输出一句话
    }

};


/// @brief 创建空间和删除空间来输出size的值
///@return 使用std不用输出std,让stack改为用s来运用，用点函数来创建空间的值，之后输出size的空间数，之后是删除空间来输出size的值
void debugStack(){
    using namespace std;                                            //使用std输出
    stack<char> s;                                                  //定义stack为s

    s.push('a');
    s.push('b');
    s.push('c');
    s.push('d');
    s.push('e');
    
    cout << "size = " << s.getSize() << endl;                      //输出size

    s.print();                                                     //输出

    while(!s.isEmpty()){                                           ///当size不为空的时候
        cout << s.pop() << endl;                                   //输出
    }

    cout << "size = " << s.getSize() << endl;                       //输出size

    s.push('f');
}

#endif // STACK_H