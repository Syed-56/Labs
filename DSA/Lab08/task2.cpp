#include <iostream>
using namespace std;

class Node {
public:
    Node* left;
    Node* right;
    int playCount;
    string data;
    int height;

    Node(string val, int count) {
        data = val;
        playCount = count;
        left = right = NULL;
        height = 0;
    }
};

int height(Node* root) {
    return root ? root->height : -1;
}

int getBalance(Node* root) {
    if (!root) return 0;
    return height(root->left) - height(root->right);
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

Node* balancePlaylist(Node* root) {
    if (!root) return root;

    // Update height
    root->height = max(height(root->left), height(root->right)) + 1;

    int balance = getBalance(root);

    // LL
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // LR
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RR
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // RL
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Node* insert(Node* root, string val, int count) {
    if (!root)
        return new Node(val, count);

    if (count < root->playCount)
        root->left = insert(root->left, val, count);
    else if (count > root->playCount)
        root->right = insert(root->right, val, count);
    else
        return root;

    return balancePlaylist(root);
}

Node* search(Node* root, int count) {
    if (!root) return NULL;
    if (root->playCount == count) return root;
    if (count < root->playCount) return search(root->left, count);
    return search(root->right, count);
}

Node* minNode(Node* root) {
    while (root->left)
        root = root->left;
    return root;
}

Node* deleteNode(Node* root, int count) {
    if (!root) return NULL;

    if (count < root->playCount)
        root->left = deleteNode(root->left, count);
    else if (count > root->playCount)
        root->right = deleteNode(root->right, count);
    else {
        // 3 cases
        if (!root->left && !root->right) {
            delete root;
            return NULL;
        }
        else if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* succ = minNode(root->right);
        root->playCount = succ->playCount;
        root->data = succ->data;
        root->right = deleteNode(root->right, succ->playCount);
    }

    return balancePlaylist(root);
}

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << "(" << root->playCount << ") ";
    inorder(root->right);
}

void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << "(" << root->playCount << ") ";
}

int main() {
    Node* root = NULL;

    root = insert(root, "Faded", 100);
    root = insert(root, "Memories", 90);
    root = insert(root, "Unity", 80);
    root = insert(root, "Alone", 120);
    cout << search(root, 100)->data << " Searched sucessfully\n\n";


    cout << "Inorder: ";
    inorder(root);
    cout << endl;

    cout << "Postorder: ";
    postorder(root);
    cout << endl;

    cout << "\nDeleting 90...\n";
    root = deleteNode(root, 90);

    cout << "Inorder after delete: ";
    inorder(root);
    cout << endl;

    return 0;
}
