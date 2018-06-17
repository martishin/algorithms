#include <iostream>
#include <vector>

using namespace std;


int partition(vector<int> &v, int l, int r, int pivot) {
    swap(v[pivot], v[l]);
    int p = l;

    for (size_t i = l + 1; i < r; ++i) {
        if (v[i] <= v[l]) {
            ++p;
            swap(v[i], v[p]);
        }
    }
    swap(v[l], v[p]);

    return p;
}


void quickSort(vector<int> &v, int l, int r) {
    if (l < r) {
        int pivot = l + rand() % (r - l);
        int p = partition(v, l, r, pivot);

        quickSort(v, l, p);
        quickSort(v, p + 1, r);
    }
}


int main() {
    int n;

    cin >> n;

    vector<int> v(n);

    for (size_t i = 0; i < n; ++i) {
        cin >> v[i];
    }

    quickSort(v, 0, n);

    for (size_t i = 0; i < n; ++i) {
        cout << v[i] << ' ';
    }
    cout << endl;

    return 0;
}
