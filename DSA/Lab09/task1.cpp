#include <iostream>
#include <algorithm>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    int height;

    Node(int val) {
        data = val;
        left = right = NULL;
        height = 0;
    }
};

void updateHeight(Node* n) {
    if (!n) return;

    int leftH  = (n->left  ? n->left->height  : -1);
    int rightH = (n->right ? n->right->height : -1);

    n->height = 1 + max(leftH, rightH);
}


int getBalance(Node* n) {
    if (!n) return 0;

    int leftH  = (n->left  ? n->left->height  : -1);
    int rightH = (n->right ? n->right->height : -1);

    return leftH - rightH;
}


Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* t = y->left;

    y->left = x;
    x->right = t;

    updateHeight(x);
    updateHeight(y);

    return y;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* t = x->right;

    x->right = y;
    y->left = t;

    updateHeight(y);
    updateHeight(x);

    return x;
}

Node* balance(Node* root) {
    updateHeight(root);
    int balance = getBalance(root);

    // LL Case
    if (balance > 1 && getBalance(root->left) >= 0) {
        cout << "Right Rotation\n";
        return rightRotate(root);
    }

    // LR Case
    if (balance > 1 && getBalance(root->left) < 0) {
        cout << "Left Right Rotation\n";
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RR Case
    if (balance < -1 && getBalance(root->right) <= 0) {
        cout << "Left Rotation\n";
        return leftRotate(root);
    }

    // RL Case
    if (balance < -1 && getBalance(root->right) > 0) {
        cout << "Left Right Rotation\n";
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    cout << "Balance Factor of affected node (" << root->data << ") = " << getBalance(root) << endl;
    return root;
}

Node* insert(Node* root, int val) {
    if (!root)
        return new Node(val);

    if (val < root->data)
        root->left = insert(root->left, val);
    else if (val > root->data)
        root->right = insert(root->right, val);
    else
        return root;

    return balance(root);
}

Node* findMin(Node* root) {
    while (root->left)
        root = root->left;
    return root;
}

Node* deleteNode(Node* root, int val) {
    if (!root) return NULL;

    if (val < root->data)
        root->left = deleteNode(root->left, val);
    else if (val > root->data)
        root->right = deleteNode(root->right, val);

    else {
        if (!root->left || !root->right) {
            Node* temp = (root->left) ? root->left : root->right;
            delete root;
            return temp;
        } else {
            Node* succ = findMin(root->right);
            root->data = succ->data;
            root->right = deleteNode(root->right, succ->data);
        }
    }

    return balance(root);
}

int main() {
    Node* tree = NULL;
    tree = insert(tree,240585);
    cout << "height = " << tree->height << endl;
    tree = insert(tree,240581);
    cout << "height = " << tree->height << endl;
    tree = insert(tree,240586);
    cout << "height = " << tree->height << endl;
    tree = insert(tree,240578);
    cout << "height = " << tree->height << endl;
    tree = insert(tree,240546);
    cout << "height = " << tree->height << endl;
    tree = insert(tree,240802);
    cout << "height = " << tree->height << endl;
    tree = insert(tree,240860);
    cout << "height = " << tree->height << endl;

    tree = deleteNode(tree,240581);
    cout << "height = " << tree->height << endl;
    tree = deleteNode(tree,240586);
    cout << "height = " << tree->height << endl;
    tree = deleteNode(tree,240578);
    cout << "height = " << tree->height << endl;
}
