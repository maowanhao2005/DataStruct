#include <iostream>
// #include "SRC/queue.h"

using namespace std;
// int main(int argc, char const *argv[]){
    
//     queue<int> q;
    
//     q.push_back(1);
//     q.push_back(2);
//     q.push_back(3);
//     q.push_back(4);
//     q.push_back(5);
//     q.push_back(6);
//     q.push_back(7);
//     q.push_back(8);
//     q.push_back(9);
//     q.push_back(10);

//     // 将队列中的每一个数加起来
    
//     int sum = 0;
//     while(!q.empty()){
//         sum += q.front();
//         q.pop_front();
//         cout << "size = "<< q.getSize() << endl;
//     }
//     q.push_back(12);    
//     cout << "sum = " << sum << endl;
//     q.push_back(11);
//     return 0;
// }

#include "SRC/stack.h"
int main(int argc, char const *argv[]){
    
    stack<char> s;

    s.push('a');
    s.push('b');
    s.push('c');
    s.push('d');
    s.push('e');
    
    cout << "size = " << s.getSize() << endl;   

    s.print();

    while(!s.isEmpty()){
        cout << s.pop() << endl;
    }

    cout << "size = " << s.getSize() << endl;

    s.push('f');
    
    return 0;
}

