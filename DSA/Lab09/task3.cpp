#include <iostream>
using namespace std;

class Node {
public:
    int data;          // severity score
    int height;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        height = 0;
        left = right = NULL;
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


Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
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
    return root;
}

Node* insert(Node* root, int val) {
    if (!root) {
        cout << "Inserted severity: " << val << endl;
        return new Node(val);
    }

    if (val < root->data)
        root->left = insert(root->left, val);
    else if (val > root->data)
        root->right = insert(root->right, val);
    else
        return root;

    Node* newRoot = balance(root);

    cout << "Tree Height after insert: " << newRoot->height << "\n";
    cout << "Highest severity patient now: " << newRoot->data << "\n\n";

    return newRoot;
}

Node* findMin(Node* root) {
    while (root->left)
        root = root->left;
    return root;
}

Node* deleteNode(Node* root, int key) {
    if (!root)
        return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);

    else {
        cout << "Patient discharged with severity: " << key << endl;

        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        } else {
            Node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    Node* newRoot = balance(root);

    if (newRoot) {
        cout << "Tree Height after delete: " << newRoot->height << "\n";
        cout << "Highest severity patient now: " << newRoot->data << "\n\n";
    }

    return newRoot;
}

int highestSeverity(Node* root) {
    if (!root) return -1;
    while (root->right)
        root = root->right;
    return root->data;
}



int main() {
    Node* tree = NULL;

    tree = insert(tree, 50);
    tree = insert(tree, 70);
    tree = insert(tree, 30);
    tree = insert(tree, 80);
    tree = insert(tree, 90);
    tree = insert(tree, 60);

    tree = deleteNode(tree, 80);
    tree = deleteNode(tree, 50);

    return 0;
}
