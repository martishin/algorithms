#include <iostream>
#include <cassert>
#include <vector>

using namespace std;


int binary_search_recursive(const vector<int> &a, int x, int left, int right) {
    if (left > right) {
        return -1;
    }

    int center = (left + right) / 2;

    if (a[center] < x) {
        return binary_search_recursive(a, x, ++center, right);
    } else if (a[center] > x) {
        return binary_search_recursive(a, x, left, --center);
    } else {
        return center;
    }
}


int binary_search(const vector<int> &a, int x) {
    int left = 0, right = (int)a.size() - 1;
    int center;
    while (left <= right) {
        center = (left + right) / 2;
        if (a[center] < x) {
            left = ++center;
        } else if (a[center] > x) {
            right = --center;
        } else {
            return center;
        }
    }
    return -1;
}


int linear_search(const vector<int> &a, int x) {
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] == x) return i;
    }
    return -1;
}


int main() {
    int n;
    int m;

    cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < n; ++i) {
        cin >> a[i];
    }

    cin >> m;
    vector<int> b(m);
    for (size_t i = 0; i < m; ++i) {
        cin >> b[i];
    }

    for (size_t i = 0; i < m; ++i) {
        cout << binary_search(a, b[i]) << ' ';
    }

    cout << endl;
}
