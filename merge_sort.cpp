#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


void merge(vector<int>& nums, int l, int m, int r) {
    vector<int> leftSubarray;
    vector<int> rightSubarray;

    for (size_t i = l; i <= r; ++i) {
        if (i <= m) {
            leftSubarray.push_back(nums[i]);
        } else {
            rightSubarray.push_back(nums[i]);
        }
    }

    int leftPointer = 0;
    int rightPointer = 0;

    while (leftPointer < leftSubarray.size() && rightPointer < rightSubarray.size()) {
        if (leftSubarray[leftPointer] <= rightSubarray[rightPointer]) {
            nums[l++] = leftSubarray[leftPointer++];
        } else {
            nums[l++] = rightSubarray[rightPointer++];
        }
    }

    for (size_t i = leftPointer; i < leftSubarray.size(); ++i) {
        nums[l++] = leftSubarray[i];
    }

    for (size_t i = rightPointer; i < rightSubarray.size(); ++i) {
        nums[l++] = rightSubarray[i];
    }
}

void mergeSortRecursive(vector<int> &v, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSortRecursive(v, l, m);
        mergeSortRecursive(v, m + 1, r);
        merge(v, l, m, r);
    }
}

void mergeSortIterative(vector<int> &v, int n) {
    for (size_t c = 1; c < n; c *= 2) {
        for (size_t l = 0; l < n - 1; l += 2 * c) {
            int m = l + c - 1;
            int r = min((int)(l + 2 * c - 1), n - 1);
            merge(v, l, m, r);
        }
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
