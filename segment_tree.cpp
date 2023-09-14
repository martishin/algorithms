#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

class SegmentTree {
public:
    SegmentTree(const vector<int>& arr) {
        size = arr.size();
        tree.resize(size * 4);
        build(arr, 0, 0, size - 1);
    }

    int query(int left, int right) {
        return query(0, 0, size - 1, left, right);
    }

    void update(int index, int value) {
        update(0, 0, size - 1, index, value);
    }

private:
    vector<int> tree;
    int size;

    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = start + (end - start) / 2;
            build(arr, node * 2 + 1, start, mid);
            build(arr, node * 2 + 2, mid + 1, end);
            tree[node] = tree[node * 2 + 1] + tree[node * 2 + 2];
        }
    }

    int query(int node, int start, int end, int left, int right) {
        if (right < start || end < left) {
            return 0;
        }
        if (left <= start && end <= right) {
            return tree[node];
        }
        int mid = start + (end - start) / 2;
        int p1 = query(node * 2 + 1, start, mid, left, right);
        int p2 = query(node * 2 + 2, mid + 1, end, left, right);
        return p1 + p2;
    }

    void update(int node, int start, int end, int index, int value) {
        if (start == end) {
            tree[node] = value;
        } else {
            int mid = start + (end - start) / 2;
            if (index <= mid) {
                update(node * 2 + 1, start, mid, index, value);
            } else {
                update(node * 2 + 2, mid + 1, end, index, value);
            }
            tree[node] = tree[node * 2 + 1] + tree[node * 2 + 2];
        }
    }
};

int main() {
    vector<int> arr = {1, 3, 5, 7, 9, 11};
    SegmentTree segmentTree(arr);

    cout << "Sum of values in range [1, 3]: " << segmentTree.query(1, 3) << endl; // Should print 15

    segmentTree.update(1, 10);
    cout << "Sum of values in range [1, 3]: " << segmentTree.query(1, 3) << endl; // Should print 22

    return 0;
}
