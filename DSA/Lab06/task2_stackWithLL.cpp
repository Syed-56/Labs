#include <iostream>
using namespace std;

class Node {
    public:
    int data;
    Node* next;

    Node(int val) {
        data = val;
        next = NULL;
    }
};

class Stack {
    Node* top=NULL;
    public:
    void push(int val) {
       Node* temp = new Node(val);
       if(!temp) {
        cout << "Stack Overflow\n";
       }
       temp->next = top;
       top = temp;
    }   
    void pop() {
        if(!top) {
            cout << "Stack Underflow\n";
            return;
        }
        Node* temp = top;
        top = top->next;
        delete temp;
    }
    Node* getTop() {
       if(top) return top;
       else return NULL;
    }
    bool isEmpty() {
        return (!top);
    }
};

int main() {
    Stack s;
    s.push(10);
    s.push(20);
    s.push(30);

    while(!s.isEmpty()) {
        cout << s.getTop()->data << " ";
        s.pop();
    }
}