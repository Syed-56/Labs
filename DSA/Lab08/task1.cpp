#include <iostream>
using namespace std;

class Node {
    public:
    string data;
    Node* left;
    Node* right;

    Node(string val) {
        data = val;
        left = right = NULL;
    }
};

Node* insertNode(Node* root, string child, string parent, char gender) {
    if(!root)   return new Node(child);
    if(root->data == child) {
        if(gender=='F')  root->left = new Node(parent);
        if(gender=='M')  root->right = new Node(parent);
        return root;
    }

    insertNode(root->left, child, parent, gender);
    insertNode(root->right, child, parent, gender);
    return root;
}

void printRoot(Node* root) {
    cout << root->data << endl;
}

void printLeaves(Node* root) {
    if (root == NULL) return;

    if (root->left == NULL && root->right == NULL) {
        cout << root->data << endl;
        return;
    }
    printLeaves(root->left);
    printLeaves(root->right);
}

int height(Node* root) {
    if(!root)   return 0;
    else    return 1 + max(height(root->left) , height(root->right));
}

void preorder(Node* root, int level) {
    if (!root) return;
    cout << "Node: " << root->data << "\tLevel: " << level << endl;
    preorder(root->left, level+1);
    preorder(root->right, level+1);
}

int main() {
    Node* root = new Node("Child");

    root = insertNode(root, "Child", "Me", 'M');
    root = insertNode(root, "Child", "Wifey", 'F');

    root = insertNode(root, "Me", "My Mom", 'F');
    root = insertNode(root, "Wifey", "Wifey Mom", 'F');
    root = insertNode(root, "Me", "My Dad", 'M');
    root = insertNode(root, "Wifey", "Wifey Dad", 'M');

    root = insertNode(root, "My Mom", "My GrandMa", 'F');
    root = insertNode(root, "Wifey Mom", "Wifey Grandma", 'F');
    root = insertNode(root, "My Mom", "My Grandpa", 'M');
    root = insertNode(root, "Wifey Mom", "Wifey Grandpa", 'M');
    root = insertNode(root, "My Dad", "My GrandMother", 'F');
    root = insertNode(root, "Wifey Dad", "Wifey GrandMother", 'F');
    root = insertNode(root, "My Dad", "My GrandFather", 'M');
    root = insertNode(root, "Wifey Dad", "Wifey GrandFather", 'M');

    cout << "Root = ";
    printRoot(root);
    cout << "\nLeaves\n";
    printLeaves(root);
    cout << "\nHeight of Tree = " << height(root);
    cout << "\nLevels of Each Node\n";
    preorder(root,0);
}