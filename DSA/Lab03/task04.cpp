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

class CircularList {
public:
    Node* head;

    CircularList() {
        head = NULL;
    }

    void create(int n) {
        if (n <= 0) return;
        head = new Node(1);
        Node* prev = head;
        for (int i = 2; i <= n; i++) {
            Node* temp = new Node(i);
            prev->next = temp;
            prev = temp;
        }
        prev->next = head; 
    }

    int josephus(int k) {
        if (!head || head->next == head) return head ? head->data : -1;

        Node* prev = head;
        Node* curr = head;

        while (prev->next != head) {
            prev = prev->next;
        }

        while (curr->next != curr) {
            for (int count = 1; count < k; count++) {
                prev = curr;
                curr = curr->next;
            }

            cout << "Eliminating: " << curr->data << endl;
            prev->next = curr->next;
            Node* del = curr;
            curr = curr->next;
            delete del;
        }

        return curr->data; 
    }
};

int main() {
    int n = 5, k = 2;
    CircularList cl;
    cl.create(n);

    int survivor = cl.josephus(k);
    cout << "Survivor: " << survivor << endl;

    return 0;
}
