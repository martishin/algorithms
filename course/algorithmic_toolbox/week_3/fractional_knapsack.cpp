#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
    double value = 0.0;
    int weight = 0;
    vector<pair<int, double> > costs;

    for (size_t i = 0; i != weights.size(); ++i) {
        costs.push_back(make_pair(i, double(values[i]) / weights[i]));
    }

    sort(costs.begin(), costs.end(), [](const pair<int, double> &left, const pair<int, double> &right) {
        return left.second > right.second;
    });

    for (size_t i = 0; i != weights.size(); ++i) {
        if (weight + weights[costs[i].first] < capacity) {
            weight += weights[costs[i].first];
            value += weights[costs[i].first] * costs[i].second;
        } else {
            value += (capacity - weight) * costs[i].second;
            break;
        }
    }

    return value;
}

int main() {
    int n;
    int capacity;
    std::cin >> n >> capacity;
    vector<int> values(n);
    vector<int> weights(n);
    for (int i = 0; i < n; i++) {
        std::cin >> values[i] >> weights[i];
    }

    double optimal_value = get_optimal_value(capacity, weights, values);

    cout.precision(10);
    cout << optimal_value << endl;
    return 0;
}
