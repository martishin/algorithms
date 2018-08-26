#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <climits>

using namespace std;

#define endl '\n'

//longest increasing subsequence

int findMax(vector<int> tree, int index, int left, int right, int query_start, int query_end) {
    if (left >= query_start && right <= query_end)
        return tree[index];

    if (left > query_end || right < query_start) {
        return 0;
    }

    int middle = (left + right) / 2;

    return max(
        findMax(tree, 2 * index + 1, left, middle, query_start, query_end),
        findMax(tree, 2 * index + 2, middle + 1, right, query_start, query_end)
    );
}


void buildTree(vector<int> &tree, int index,  int left, int right, int origin_index, int origin_value) {
    if (origin_index < left || origin_index > right)
        return;

    if (left == right) {
        tree[index] = origin_value;
        return;
    }

    int middle = (left + right) / 2;

    buildTree(tree, 2 * index + 1, left, middle, origin_index, origin_value);
    buildTree(tree, 2 * index + 2, middle + 1, right, origin_index, origin_value);

    tree[index] = max(tree[2 * index + 1], tree[2 * index + 2]);
}


void lis_tree(vector<int> &numbers) {
    int n = numbers.size();
    vector<pair<int, int> > pairs(n);

    for (size_t i = 0; i < n; ++i) {
        pairs[i].first = numbers[i];
        pairs[i].second = i;
    }

    sort(pairs.begin(), pairs.end(), [](const pair<int, int> &l, const pair<int, int> &r) {
        return (l.first == r.first) ? (l.second > r.second) : (l.first < r.first);
    });

    int size = pow(2, (int)(ceil(sqrt(n))) + 1) - 1;
    vector<int> tree(size, 0);

    for (size_t i = 0; i < n; ++i) {
        buildTree(tree, 0, 0, n - 1, pairs[i].second, findMax(tree, 0, 0, n - 1, 0, pairs[i].second) + 1);
    }

    cout << tree[0] << endl;
}


void lis_dp(vector<int> &numbers) {
    int n = numbers.size();

    vector<int> states(n + 1);
    vector<int> pos(n + 1);
    vector<int> prev(n + 1);

    int length = 0;

    pos[0] = -1;
    states[0] = numeric_limits<int>::min();

    for (size_t i = 1; i <= n; ++i)
        states[i] = numeric_limits<int>::max();

    for (size_t i = 0; i < n; ++i) {
        int j = upper_bound(states.begin(), states.end(), numbers[i]) - states.begin();

        if (states[j - 1] < numbers[i] && numbers[i] < states[j]) {
            states[j] = numbers[i];
            pos[j] = i;
            prev[i] = pos[j - 1];
            length = max(length, j);
        }
    }

    vector<int> result;

    int p = pos[length];

    while (p != -1) {
        result.push_back(numbers[p]);
        p = prev[p];
    }

    reverse(result.begin(), result.end());

    for (size_t i = 0; i < result.size(); ++i)
        cout << result[i] << ' ';

    cout << endl;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.precision(10);

    int n;
    cin >> n;

    vector<int> numbers(n);

    for (size_t i = 0; i < n; ++i)
        cin >> numbers[i];

    lis_dp(numbers);

    return 0;
}
