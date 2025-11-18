#include <iostream>
using namespace std;

class Node {
    public:
    Node* left;
    Node* right;
    int data;
    int height;

    Node(int val) {
        data = val;
        left = right = NULL;
        height=0;
    }
};

int height(Node* root) {
    if(!root)   return -1;
    else return 1+max(height(root->left), height(root->right));
}

//to get BF of a node
int getBalance(Node* root) {
    if(!root)   return 0;
    return height(root->left) - height(root->right);
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* z = y->left;
    y->left = x;
    x->right = z;

    x->height = height(x);
    y->height = height(y);
    return y;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* z = x->right;
    x->right=y;
    y->left=z;

    x->height = height(x);
    y->height = height(y);
    return x;
}

Node* balanceAVL(Node* root, int val) {
    root->height = height(root);
    int balance = getBalance(root);
    //now we have nodes and balance factor for each node, rotate them to correctly insert
    if(balance>1 && val < root->left->data)     return rightRotate(root);   //LL case
    if(balance<-1 && val > root->right->data)   return leftRotate(root);    //RR case
    if(balance<-1 && val < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }   //RL case
    if(balance>1 && val > root->left->data) {   //LR case
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    return root;
}

Node* insert(Node* root, int val) {
    if(!root)   return new Node(val);
    if(val < root->data)        root->left = insert(root->left, val);
    else if(val > root->data)   root->right = insert(root->right, val);
    else return root;

    return balanceAVL(root,val);
}

void searching(Node* root, int X, int Y) {
    if (!root)  return;
    searching(root->left, X, Y);
    if (root->data > X && root->data < Y)     cout << root->data << "$\n";
    searching(root->right, X, Y);
}

int main() {
    Node* tree = NULL;
    tree = insert(tree,100);
    tree = insert(tree,140);
    tree = insert(tree,150);
    tree = insert(tree,300);
    tree = insert(tree,200);
    searching(tree,99,200);
}