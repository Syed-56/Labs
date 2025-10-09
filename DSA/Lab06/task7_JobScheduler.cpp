#include <iostream>
using namespace std;
#define MAX 100

class Processes {
    int id;
    string priority;

    public:
    Processes() {}
    Processes(int i, string p) {
        id = i;
        priority = p; 
    } 

    bool operator>(const Processes &obj) {
        return priority > obj.priority;
    }
    void operator=(const Processes &obj) {
        id = obj.id;
        priority = obj.priority;
    }

    void printOrder() {
        cout << "Order: " << id << " (" << priority << ")" << endl;
    }
};

class Stack {
    Processes arr[MAX];
    int top=-1;

    public:
    void push(Processes val) {
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
        top--;
    }
    Processes getTop() {
        return arr[top];
    }
    bool isEmpty() {
        return (top==-1);
    }
};

class Queue {
    int front=-1, rear=-1;
    Processes arr[MAX];

    public:
    bool isEmpty() {
        return (front == -1 || front > rear);
    }
    void enqueue(Processes val) {
        if(rear==MAX-1) {
            cout << "Queue Overflow. Enqueue Denied\n";
            return;
        }
        if(front==-1)   front=0;
        rear++;
        arr[rear] = val;
    }
    void dequeue() {
        if(isEmpty()) {
            cout << "Queue Underflow. Dequeue Denied\n";
            return;
        }
        if(front > rear) { // reset when queue becomes empty
            front = rear = -1;
        }
        front++;
    }
    Processes getFront() {
        if(isEmpty())   return Processes(0,"");
        else    return arr[front];
    }
    
};

int main() {
    Processes p[5];
    p[0] = Processes(100,"High");
    p[1] = Processes(101,"Low");
    p[2] = Processes(102,"Medium");
    p[3] = Processes(103,"Medium");
    p[4] = Processes(104,"High");

    Queue ProcessingOrders;
    for(int i=0; i<5; i++)  ProcessingOrders.enqueue(p[i]);
    cout << "Processing Queue:\n";
    while(!ProcessingOrders.isEmpty()) {
        Processes current = ProcessingOrders.getFront();
        current.printOrder();
        ProcessingOrders.dequeue();
    }

    Stack ExecutionOrders;
    for(int i=0; i<5; i++)  ExecutionOrders.push(p[i]);
    cout << "\nExecution of Stack:\n";
    while(!ExecutionOrders.isEmpty()) {
        Processes current = ExecutionOrders.getTop();
        current.printOrder();
        ExecutionOrders.pop();
    }
}