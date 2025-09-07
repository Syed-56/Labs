#include <iostream>
using namespace std;

class SNode {
public:
    int data;
    SNode* next;
    SNode(int val) {
        data = val;
        next = NULL;
    }
};

class DNode {
public:
    int data;
    DNode* prev;
    DNode* next;
    DNode(int val) {
        data = val;
        prev = NULL;
        next = NULL;
    }
};

class LinkedList {
public:
    SNode* head;

    LinkedList() {
        head = NULL;
    }

    void pushBack(int val) {
        SNode* n = new SNode(val);
        if (!head) {
            head = n;
            return;
        }
        SNode* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = n;
    }

    void print() {
        SNode* temp = head;
        while (temp) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }

    DNode* toDoubly() {
        if (!head) return NULL;

        SNode* temp = head;
        DNode* dHead = new DNode(temp->data);
        DNode* dCurr = dHead;

        temp = temp->next;
        while (temp) {
            DNode* newNode = new DNode(temp->data);
            dCurr->next = newNode;
            newNode->prev = dCurr;
            dCurr = newNode;
            temp = temp->next;
        }
        return dHead;
    }

    void toCircular() {
        if (!head) return;
        SNode* temp = head;
        while (temp->next) {
            temp = temp->next;
            if(temp = head) return;
        }
        temp->next = head;  
    }
};

void printDoubly(DNode* head) {
    DNode* temp = head;
    DNode* last = NULL;

    cout << "Forward: ";
    while (temp) {
        cout << temp->data << " <-> ";
        last = temp;
        temp = temp->next;
    }
    cout << "NULL\n";

    cout << "Backward: ";
    while (last) {
        cout << last->data << " <-> ";
        last = last->prev;
    }
    cout << "NULL\n";
}

void printCircular(SNode* head, int count) {
    if (!head) return;
    SNode* temp = head;
    for (int i=0; i<count; i++) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "\n";
}

int main() {
    LinkedList list;
    list.pushBack(10);
    list.pushBack(20);
    list.pushBack(30);
    list.pushBack(40);

    cout << "Singly Linked List: ";
    list.print();

    cout << "\nDoubly Linked List: ";
    DNode* dHead = list.toDoubly();
    printDoubly(dHead);

    cout << "\nCircular Linked List: ";
    list.toCircular();
    printCircular(list.head, 10);
}
