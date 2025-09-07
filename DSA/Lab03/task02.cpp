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

    Node* merge(Node* l1, Node* l2) {
        if (!l1) return l2;
        if (!l2) return l1;

        Node* head = nullptr;
        Node* tail = nullptr;

        if (l1->data <= l2->data) {
            head = l1;
            l1 = l1->next;
        } else {
            head = l2;
            l2 = l2->next;
        }
        tail = head; 
        while (l1 && l2) {
            if (l1->data <= l2->data) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }

        if (l1) tail->next = l1;
        else tail->next = l2;
        return head;
    }
};

int main() {
    LinkedList list1, list2, mergedList;

    list1.pushBack(1);
    list1.pushBack(3);
    list1.pushBack(5);

    list2.pushBack(2);
    list2.pushBack(4);
    list2.pushBack(6);

    cout << "List 1: ";
    list1.print();
    cout << "List 2: ";
    list2.print();

    Node* mergedHead = mergedList.merge(list1.head, list2.head);
    mergedList.head = mergedHead;
    cout << "Merged List: ";
    mergedList.print();
}
