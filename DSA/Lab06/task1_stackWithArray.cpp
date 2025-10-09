#include <iostream>
using namespace std;
#define MAX 100

class Stack {
    int arr[MAX];
    int top=-1;

    public:
    void push(int val) {
        if(top >= MAX-1) {
            cout << "Stack Overflow\n";
            return;
        }
        top++;
        arr[top] = val;
    }
    void pop() {
        if(top==-1) {
            cout << "Stack Underflow\n";
            return;
        }
        arr[top]=0;
        top--;
    }
    int getTop() {
        return arr[top];
    }
    bool isEmpty() {
        return (top==-1);
    }
};

int main() {
    Stack s;
    s.pop();
    s.push(10);
    s.push(20);
    while(!s.isEmpty()) {
        cout << s.getTop() << " ";
        s.pop();
    }
}