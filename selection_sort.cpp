#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main() {
    int n, mv, mi;
    vector<int> v;

    while (cin >> n) {
        v.push_back(n);
    }

    for (size_t i = 0; i < v.size(); ++i) {
        mv = v[i];
        mi = i;
        for (size_t j = i; j < v.size(); ++j) {
            if (v[j] < mv) {
                mv = v[j];
                mi = j;
            }
        }
        swap(v[i], v[mi]);
    }

    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i] << ' ';
    }

    cout << endl;

    return 0;
}
