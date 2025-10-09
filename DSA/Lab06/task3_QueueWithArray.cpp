#include <iostream>
#define MAX 100
using namespace std;

class Queue {
    int front=-1, rear=-1;
    int arr[MAX];

    public:
    bool isEmpty() {
        return (front == -1 || front > rear);
    }
    void enqueue(int val) {
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
    int getFront() {
        if(isEmpty())   return -1;
        else    return arr[front];
    }
    
};

int main() {
    Queue q;
    q.dequeue();
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    while(!q.isEmpty()) {
        cout << q.getFront() << " ";
        q.dequeue();
    }
}