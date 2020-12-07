#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int binarySearchRecursiveIdx(const vector<int> &v, int l, int r, int k) {
    if (l >= r) {
        return -1;
    }

    int m = l + (r - l) / 2;

    if (v[m] == k) {
        return m;
    } else if (v[m] > k) {
        return binarySearchRecursiveIdx(v, l, m, k);
    } else {
        return binarySearchRecursiveIdx(v, m + 1, r, k);
    }
}


int binarySearchIterativeIdx(const vector<int> &v, int k) {
    int l = 0;
    int r = v.size();
    int m;

    while (l < r) {
        m = (l + r) / 2;

        if (v[m] == k) {
            return m;
        } else if (v[m] > k) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    return -1;
}

bool binarySearch(const vector<int> &v, int k) {
    int l = 0;
    int r = v.size();
    int m;

    while (l < r) {
        m = (l + r) / 2;

        if (v[m] == k) {
            return true;
        } else if (v[m] > k) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    return false;
}

size_t lowerBound(vector<int>& nums, int value) {
    size_t l = 0;
    size_t r = nums.size();

    while (l < r) {
        auto m = l + (r - l) / 2;

        if (value <= nums[m]) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    return l;
}

size_t upperBound(vector<int>& nums, int value) {
    size_t l = 0;
    size_t r = nums.size();

    while (l < r) {
        auto m = l + (r - l) / 2;

        if (value >= nums[m]) {
            l = m + 1;
        } else {
            r = m;
        }
    }

    return l;
}

int main() {
    vector<int> v {4, 6, 10, 12, 18, 20};
    int k = 6;

    for (const auto i : v) {
        cout << i << ' ';
    }
    cout << endl;
    cout << k << endl;

    cout << "binarySearchRecursiveIdx: " << binarySearchRecursiveIdx(v, 0, v.size(), k) << endl;
    cout << "binarySearchIterativeIdx: " << binarySearchIterativeIdx(v, k) << endl;

    cout << "binarySearch: " << binarySearch(v, k) << endl;
    cout << "binary_search: " << binary_search(v.begin(), v.end(), k) << endl;

    cout << "lowerBound: " << lowerBound(v, k) << endl;
    cout << "lower_bound: " << lower_bound(v.begin(), v.end(), k) - v.begin() << endl;

    cout << "upperBound: " << upperBound(v, k) << endl;
    cout << "upper_bound: " << upper_bound(v.begin(), v.end(), k) - v.begin() << endl;
}
