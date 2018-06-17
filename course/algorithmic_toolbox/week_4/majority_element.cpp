#include <algorithm>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int count_number(vector<int> &a, int left, int right, int n) {
    return count(a.begin() + left, a.begin() + right + 1, n);
}

int get_majority_element(vector<int> &a, int left, int right) {
    if (left == right) {
        return a[left];
    }
    int middle = (left + right) / 2;
    int lm = get_majority_element(a, left, middle);
    int rm = get_majority_element(a, middle + 1, right);
    if (lm == rm) {
        return lm;
    }
    if (count_number(a, left, right, lm) > (right - left) / 2) {
        return lm;
    } else if (count_number(a, left, right, rm) > (right - left) / 2) {
        return rm;
    } else {
        return -1;
    }
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cin >> a[i];
    }
    std::cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
}
