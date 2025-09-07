#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node* child;

    Node(int val) {
        data = val;
        next = NULL;
        child = NULL;
    }
};

Node* flatten(Node* head) {
    if (!head) return NULL;

    Node* curr = head;
    while (curr) {
        if (curr->child) {
            Node* nextNode = curr->next;
            curr->next = curr->child;
            Node* temp = curr->child;
            while (temp->next) {
                temp = temp->next;
            }

            temp->next = nextNode;
            curr->child = NULL;
        }
        curr = curr->next;
    }
    return head;
}

void printList(Node* head) {
    Node* temp = head;
    while (temp) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL\n";
}

int main() {
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);

    head->next->child = new Node(7);
    head->next->child->next = new Node(8);
    head->next->child->next->child = new Node(11);
    head->next->child->next->child->next = new Node(12);
    head->next->child->next->next = new Node(9);
    head->next->child->next->next->next = new Node(10);

    head->next->next->next->child = new Node(5);
    head->next->next->next->child->next = new Node(6);

    cout << "Before Flattening:\n";
    cout << "Only top-level list: 1 -> 2 -> 3 -> 4\n";

    head = flatten(head);

    cout << "\nAfter Flattening:\n";
    printList(head);

    return 0;
}