#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>

using std::cin;
using std::cout;
using std::endl;
using std::vector;


struct Node {
    int key;
    int left;
    int right;

    Node() : key(0), left(-1), right(-1) {}
    Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};


bool IsBinarySearchTree(const vector<Node>& tree, const Node& root, int min, int max) {
    if (root.key < min || root.key > max) {
        return false;
    }

    return (
        (root.left == -1 || IsBinarySearchTree(tree, tree[root.left], min, root.key - 1)) &&
        (root.right == -1 || IsBinarySearchTree(tree, tree[root.right], root.key, max))
    );
}


int main() {
    int nodes;
    cin >> nodes;
    vector<Node> tree;

    for (int i = 0; i < nodes; ++i) {
        int key, left, right;
        cin >> key >> left >> right;
        tree.push_back(Node(key, left, right));
    }

    if (nodes == 0 || IsBinarySearchTree(tree, tree[0], INT_MIN, INT_MAX)) {
        cout << "CORRECT" << endl;
    } else {
        cout << "INCORRECT" << endl;
    }
    return 0;
}
