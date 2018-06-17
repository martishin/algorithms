#include <iostream>
#include <vector>

using namespace std;


template <typename T>
class SplayTree {
private:
    struct Node {
        T data;
        Node *left;
        Node *right;

        Node() {
            left = nullptr;
            right = nullptr;
        }

        Node(T data, Node *left = nullptr, Node *right = nullptr)
            : data(data), left(left), right(right) {}
    };

    Node *root;

    Node* clear(Node *node) {
        if (node == nullptr) {
            return nullptr;
        }
        clear(node->left);
        clear(node->right);
        return nullptr;
    }

    Node* rightRotate(Node *node) {
        Node *left_child = node->left;
        node->left = left_child->right;
        left_child->right = node;
        return left_child;
    }

    Node* leftRotate(Node *node) {
        Node *right_child = node->right;
        node->right = right_child->left;
        right_child->left = node;
        return right_child;
    }

    Node* splay(T data, Node* node) {
        if (!node) {
            return nullptr;
        }

        Node header;

        Node *left_tree_max = &header;
        Node *right_tree_min = &header;

        while (true) {
            if (data < node->data) {
                if (!node->left)
                    break;

                if (data < node->left->data) {
                    node = rightRotate(node);
                    if (!node->left)
                        break;
                }

                right_tree_min->left = node;
                right_tree_min = right_tree_min->left;
                node = node->left;
                right_tree_min->left = nullptr;
            } else if (data > node->data) {
                if (!node->right)
                    break;

                if (data > node->right->data) {
                    node = leftRotate(node);

                    if (!node->right)
                        break;
                }

                left_tree_max->right = node;
                left_tree_max = left_tree_max->right;
                node = node->right;
                left_tree_max->right = nullptr;
            } else {
                break;
            }
        }

        left_tree_max->right = node->left;
        right_tree_min->left = node->right;
        node->left = header.right;
        node->right = header.left;
        return node;
    }

    Node* insert(Node* node, T data) {
        Node *new_node = new Node(data);

        if (!node) {
            return new_node;
        }

        node = splay(data, node);

        if (data < node->data) {
            new_node->left = node->left;
            new_node->right = node;
            node->left = nullptr;
            node = new_node;
        } else if (data > node->data) {
            new_node->right = node->right;
            new_node->left = node;
            node->right = nullptr;
            node = new_node;
        }

        return node;
    }

    Node* erase(Node *node, T data) {
        if (!node)
            return nullptr;

        Node *ptr = node;

        node = splay(data, node);

        if (data != node->data) {
            return node;
        } else {
            if (!node->left) {
                node = node->right;
            } else {
                node = splay(data, node->left);
                node->right = ptr->right;
            }

            delete ptr;
            return node;
        }
    }

    void inorder(vector<T> &nodes, Node *n) {
        if (n != nullptr) {
            inorder(nodes, n->left);
            nodes.push_back(n->data);
            inorder(nodes, n->right);
        }
    }

    Node* find(Node *n, T data) {
        if (n == nullptr) {
            return nullptr;
        } else if (data < n->data) {
            return find(n->left, data);
        } else if (data > n->data) {
            return find(n->right, data);
        } else {
            return n;
        }
    }

public:
    SplayTree() {
        root = nullptr;
    }

    ~SplayTree() {
        root = clear(root);
    }

    void insert(T data) {
        root = insert(root, data);
    }

    void erase(T data) {
        root = erase(root, data);
    }

    bool find(T data) {
        if (find(root, data) != nullptr) {
            return true;
        }
        return false;
    }

    void print() {
        vector<T> nodes;
        inorder(nodes, root);

        for (size_t i = 0; i < nodes.size(); ++i) {
            cout << nodes[i] << ' ';
        }

        cout << endl;
    }
};


int main() {
    SplayTree<int> st;

    st.insert(1);
    st.insert(3);
    st.insert(2);
    st.insert(4);
    st.insert(5);
    st.insert(7);
    st.insert(6);

    st.erase(6);

    st.print();

    cout << st.find(7) << endl;
    return 0;
}
