#include <iostream>
#include <vector>

using namespace std;


template <typename T>
class BST {
private:
    struct Node {
        T data;
        Node *left;
        Node *right;

        Node() {
            left = nullptr;
            right = nullptr;
        }

        Node (T data, Node *left = nullptr, Node *right = nullptr)
           : data(data), left(left), right(right) {}
    };

    Node *root;

    Node* clear(Node *n) {
        if (n == nullptr) {
            return nullptr;
        }
        clear(n->left);
        clear(n->right);
        return nullptr;
    }

    Node* insert(T data, Node *n) {
        if (n == nullptr) {
            n = new Node(data);
        } else if (data < n->data) {
            n->left = insert(data, n->left);
        } else if (data > n->data) {
            n->right = insert(data, n->right);
        }

        return n;
    }

    Node* min(Node *n) {
        if (n == nullptr) {
            return nullptr;
        } else if (n->left == nullptr) {
            return n;
        } else {
            return min(n->left);
        }
    }

    Node* max(Node *n) {
        if (n == nullptr) {
            return nullptr;
        } else if (n->right == nullptr) {
            return n;
        } else {
            return max(n->right);
        }
    }

    Node* erase(T data, Node *n) {
        if (n == nullptr) {
            return nullptr;
        } else if (data < n->data) {
            n->left = erase(data, n->left);
        } else if (data > n->data) {
            n->right = erase(data, n->right);
        } else if (n->left && n->right) {
            Node *ptr = min(n->right);
            n->data = ptr->data;
            n->right = erase(n->data, n->right);
        } else {
            Node *ptr = n;
            if (n->left == nullptr) {
                n = n->right;
            } else if (n->right == nullptr) {
                n = n->left;
            }
            delete ptr;
        }
        return n;
    }

    Node* find(T data, Node *n) {
        if (n == nullptr) {
            return nullptr;
        } else if (data < n->data) {
            return find(data, n->left);
        } else if (data > n->data) {
            return find(data, n->right);
        } else {
            return n;
        }
    }

    void print(Node *root) {
        if (root != nullptr) {
            print(root->left);
            cout << root->data << ' ';
            print(root->right);
        }
    }

public:
    BST() {
        root = nullptr;
    }

    ~BST() {
        root = clear(root);
    }

    void insert(T data) {
        root = insert(data, root);
    }

    void erase(T data) {
        root = erase(data, root);
    }

    T min() {
        if (root == nullptr) {
            throw runtime_error("Empty BST");
        }
        return min(root)->data;
    }

    T max() {
        if (root == nullptr) {
            throw runtime_error("Empty BST");
        }
        return max(root)->data;
    }

    bool find(T data) {
        if (find(data, root) != nullptr) {
            return true;
        }
        return false;
    }

    void print() {
        print(root);
        cout << endl;
    }
};

int main() {
    BST<int> bst;

    bst.insert(1);
    bst.insert(2);
    bst.insert(3);
    bst.insert(5);
    bst.insert(4);

    bst.erase(2);

    bst.print();

    cout << bst.find(2) << endl;
    cout << bst.max() << endl;
}
