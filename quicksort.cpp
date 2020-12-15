#include <iostream>
#include <vector>

using namespace std;


int partition(vector<int>& nums, int l, int r, int pivotIdx) {
    swap(nums[l], nums[pivotIdx]);
    int newPivotIdx = l;

    for (size_t i = l + 1; i < r; ++i) {
        if (nums[i] <= nums[l]) {
            swap(nums[i], nums[++newPivotIdx]);
        }
    }

    swap(nums[l], nums[newPivotIdx]);

    return newPivotIdx;
}

void quickSort(vector<int>& nums, int l, int r) {
    if (l < r) {
        int pivotIdx = (l + r) / 2;
        pivotIdx = partition(nums, l, r, pivotIdx);

        quickSort(nums, l, pivotIdx);
        quickSort(nums, pivotIdx + 1, r);
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
