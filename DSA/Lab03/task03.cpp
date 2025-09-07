#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int val=0) {
        data = val;
        next = NULL;
    }
};

class LinkedList {
public:
    Node* head;
    Node* tail;

    LinkedList() {
        head = NULL;
        tail = NULL;
    }

    void pushBack(int val) {
        Node* n = new Node(val);
        if (!head) {
            head = tail = n;
            return;
        }
        tail->next = n;
        tail = n;
    }

    void print() {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
};

Node* reverseList(Node* head, int k) {
    Node* curr = head;
    int count = 0;

    while (curr && count < k) {
        curr = curr->next;
        count++;
    }
    if (count < k) return head;  

    curr = head;
    Node* prev = NULL;
    Node* nextNode = NULL;
    count = 0;
    while (curr && count < k) {
        nextNode = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextNode;
        count++;
    }

    if (nextNode) {
        head->next = reverseList(nextNode, k);
    }
    return prev;
}

int main() {
    LinkedList singlyList;
    singlyList.pushBack(10);
    singlyList.pushBack(20);
    singlyList.pushBack(30);
    singlyList.pushBack(40);
    singlyList.pushBack(50);

    cout << "Before Reversing: ";
    singlyList.print();

    singlyList.head = reverseList(singlyList.head, 2);

    cout << "After Reversing in groups of k=2: ";
    singlyList.print();
}
