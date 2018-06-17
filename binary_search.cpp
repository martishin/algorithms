#include <iostream>
#include <vector>

using namespace std;


int binarySearchRecursive(const vector<int> &v, int l, int r, int k) {
    if (l >= r)
        return -1;

    int m = l + (r - l) / 2;

    if (v[m] == k)
        return m;
    else if (v[m] > k)
        return binarySearchRecursive(v, l, m, k);
    else
        return binarySearchRecursive(v, m + 1, r, k);
}


int binarySearchIterative(const vector<int> &v, int k) {
    int l = 0;
    int r = v.size();
    int m;

    while (l < r) {
        m = (l + r) / 2;

        if (v[m] == k)
            return m;
        else if (v[m] > k)
            r = m;
        else
            l = m + 1;
    }

    return -1;
}


int main() {
    int n, k;

    cin >> n >> k;
    vector<int> v(n);

    for (size_t i = 0; i < n; ++i)
        cin >> v[i];

    cout << binarySearchRecursive(v, 0, v.size(), k) << endl;
    cout << binarySearchIterative(v, k) << endl;
}
