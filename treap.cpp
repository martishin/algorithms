#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;


template <typename T>
class Treap {
private:
    static const int PRIORITY_POOL = 100;

    struct Node {
        T data;
        int priority;
        unique_ptr<Node> left, right;

        Node() {
            left = nullptr;
            right = nullptr;
        }

        Node(T data) {
            this->data = data;
            priority = rand() % PRIORITY_POOL;
            left = nullptr;
            right = nullptr;
        }
    };

    unique_ptr<Node> root;

    unique_ptr<Node> rightRotate(unique_ptr<Node> &node) {
        unique_ptr<Node> left_child = move(node->left);
        node->left = move(left_child->right);
        left_child->right = move(node);
        return move(left_child);
    }

    unique_ptr<Node> leftRotate(unique_ptr<Node> &node) {
        unique_ptr<Node> right_child = move(node->right);
        node->right = move(right_child->left);
        right_child->left = move(node);
        return move(right_child);
    }

    unique_ptr<Node> insert(unique_ptr<Node> &node, T data) {
        if (!node)
            return make_unique<Node>(data);

        if (data <= node->data) {
            node->left = insert(node->left, data);

            if (node->left->priority > node->priority)
                node = move(rightRotate(node));
        } else {
            node->right = insert(node->right, data);

            if (node->right->priority > node->priority)
                node = move(leftRotate(node));
        }

        return move(node);
    }

    unique_ptr<Node> erase(unique_ptr<Node> &node, T data) {
        if (!node)
            return move(node);

        if (data < node->data)
            node->left = erase(node->left, data);
        else if (data > node->data)
            node->right = erase(node->right, data);
        else if (!node->left) {
            node = move(node->right);
        } else if (!node->right) {
            node = move(node->left);
        } else if (node->left->priority < node->right->priority){
            node = move(leftRotate(node));
            node->left = erase(node->left, data);
        } else {
            node = move(rightRotate(node));
            node->right = erase(node->right, data);
        }

        return move(node);
    }

    unique_ptr<Node> find(unique_ptr<Node> &node, T data) {
        if (!node)
            return nullptr;
        else if (data < node->data)
            return find(node->left, data);
        else if (data > node->data)
            return find(node->right, data);

        return move(node);
    }

    void inorder(unique_ptr<Node> &node, vector<pair<T, int> > &nodes) {
        if (node) {
            inorder(node->left, nodes);
            nodes.push_back(make_pair(node->data, node->priority));
            inorder(node->right, nodes);
        }
    }

public:
    Treap() {
        root = nullptr;
    }

    virtual ~Treap() {}

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
        vector<pair<T, int> > nodes;
        inorder(root, nodes);

        for (size_t i = 0; i < nodes.size(); ++i) {
            cout << "{d: " << nodes[i].first << ", p:" << nodes[i].second  << "} ";
        }

        cout << endl;
    }
};


int main() {
    Treap<int> t;

    t.insert(1);
    t.insert(3);
    t.insert(2);
    t.insert(4);
    t.insert(5);
    t.insert(7);
    t.insert(6);

    t.erase(6);

    t.print();

    cout << t.find(1) << endl;
    return 0;
}

