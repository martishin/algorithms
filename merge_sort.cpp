#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


void mergeSortMerge(vector<int> &v, int l, int m, int r);


void mergeSortRecursive(vector<int> &v, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSortRecursive(v, l, m);
        mergeSortRecursive(v, m + 1, r);
        mergeSortMerge(v, l, m, r);
    }
}


void mergeSortIterative(vector<int> &v, int n) {
    for (size_t c = 1; c <= n - 1; c *= 2) {
        for (size_t l = 0; l < n - 1; l += 2 * c) {
            int m = l + c - 1;
            int r = min((int)(l + 2 * c - 1), n - 1);
            mergeSortMerge(v, l, m, r);
        }
    }
}


void mergeSortMerge(vector<int> &v, int l, int m, int r) {
    int lp = 0, rp = 0;
    vector<int> L, R;

    for (size_t i = l; i <= r; ++i) {
        if (i <= m) {
            L.push_back(v[i]);
        } else {
            R.push_back(v[i]);
        }
    }

    while (lp < L.size() && rp < R.size()) {
        if (L[lp] <= R[rp]) {
            v[l++] = L[lp++];
        } else {
            v[l++] = R[rp++];
        }
    }

    while (lp < L.size()) {
        v[l++] = L[lp++];
    }

    while (rp < R.size()) {
        v[l++] = R[rp++];
    }
}


int main() {
    int n;

    cin >> n;
    vector<int> v(n);

    for (size_t i = 0; i < n; ++i) {
        cin >> v[i];
    }

//    mergeSortRecursive(v, 0, v.size() - 1);
    mergeSortIterative(v, v.size());

    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i] << ' ';
    }
    cout << endl;

    return 0;
}
