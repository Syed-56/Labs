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
    Node* head;
    Node* tail;

public:
    LinkedList() {
        head = NULL;
        tail = NULL;
    }

    void pushBack(int val) {
        Node* n = new Node(val);
        if (!head) {
            head = n;
            tail = n;
            return;
        }
        tail->next = n;
        tail = n;
    }

    void print() {
        Node* temp = head;
        while (temp != NULL) {
            cout << " (" << temp->data << ") ->";
            temp = temp->next;
        }
        cout << " NULL\n";
    }

    bool checkPalindrome() {
        if (!head || !head->next) return true;

        Node* slow = head;
        Node* fast = head;
        while (fast != NULL && fast->next != NULL) {
            slow = slow->next;
            fast = fast->next->next;
        }

        Node* prev = NULL;
        Node* curr = slow;
        while (curr) {
            Node* nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
        }
        Node* secondHalf = prev;

        Node* firstHalf = head;
        Node* temp = secondHalf;
        bool palindrome = true;
        while (temp) {
            if (firstHalf->data != temp->data) {
                palindrome = false;
                break;
            }
            firstHalf = firstHalf->next;
            temp = temp->next;
        }
        return palindrome;
    }
};

int main() {
    LinkedList singlyList;
    singlyList.pushBack(10);
    singlyList.pushBack(20);
    singlyList.pushBack(30);
    singlyList.pushBack(20);
    singlyList.pushBack(10);

    singlyList.print();

    if (singlyList.checkPalindrome())        cout << "Palindrome\n";
    else        cout << "Not Palindrome\n";
}
