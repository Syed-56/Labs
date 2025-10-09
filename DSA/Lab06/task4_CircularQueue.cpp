#include <iostream>
using namespace std;

class CircularQueue {
    int *arr;
    int size, capacity;
    int front, rear;

    public:
    CircularQueue(int size) {
        capacity = size;
        front = 0, rear=-1;
        arr = new int[capacity];
        this->size = 0;
    }

    void push(int val) {
        if(size==capacity) {
            cout << "Circular Queue Overflow\n";
            return;
        }
        rear = (rear+1)%capacity;
        arr[rear] = val;
        size++;
    }
    void pop() {
        if(empty()) {
            cout << "Circular Queue Underflow\n";
            return;
        }
        front = (front+1)%capacity;
        front--;
        size--;
    }
    bool empty() {
        return size == 0;
    }
    int getFront() {
        if(empty()) {
            cout << "Circular Queue Underflow\n";
            return -1;
        }
        return arr[front];
    }

    void print() {
        if(empty()) {
            cout << "Circular Queue Underflow\n";
            return;
        }
        cout << "Queue: ";
        for(int i=0; i<size; i++)   cout << arr[(front+i)%capacity] << " ";
        cout << endl;
    }

    ~CircularQueue() {
        delete[] arr;
    }
};

int main() {
    CircularQueue q(5);
    q.push(10);
    q.push(20);
    q.push(30);
    q.print();

    q.pop();
    q.print();

    q.push(40);
    q.push(50);
    q.push(60);
    q.push(10);
    q.print();
}