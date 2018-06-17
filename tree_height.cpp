#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;


class Node {
public:
    int key;
    Node *parent;
    vector<Node *> children;

    Node() {
        this->parent = nullptr;
    }

    void setParent(Node *other) {
        parent = other;
        other->children.push_back(this);
    }
};


int getMax(vector<int> &v) {
    int result = v[0];

    for (size_t i = 0; i < v.size(); ++i) {
        if (v[i] > result) {
            result = v[i];
        }
    }
    return result;
}


int treeHeight(Node *node) {
    vector<int> depths;
    if (node->children.size() == 0) {
        return 1;
    } else {
        for (size_t i = 0; i < node->children.size(); ++i) {
            depths.push_back(treeHeight(node->children[i]));
        }
        return getMax(depths) + 1;
   }
}


int main() {
    ios_base::sync_with_stdio(0);
    int n, pi, ri;

    cin >> n;
    vector<Node> nodes(n);

    for (size_t ci = 0; ci < n; ++ci) {
        cin >> pi;
        if (pi >= 0) {
            nodes[ci].setParent(&nodes[pi]);
        } else {
            ri = ci;
        }
        nodes[ci].key = ci;
    }

    cout << treeHeight(&nodes[ri]) << endl;
}
