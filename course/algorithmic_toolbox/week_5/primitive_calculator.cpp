#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using namespace std;


vector<int> greedy_sequence(int n) {
    std::vector<int> sequence;
    while (n >= 1) {
        sequence.push_back(n);
        if (n % 3 == 0) {
            n /= 3;
        } else if (n % 2 == 0) {
            n /= 2;
        } else {
            n = n - 1;
        }
    }
    reverse(sequence.begin(), sequence.end());
    return sequence;
}


vector<int> optimal_sequence(int n) {
    vector<int> sequence;
    vector<int> states(n + 1);

    for (size_t i = 1; i < states.size(); ++i) {
        states[i] = states[i - 1] + 1;
        if (i % 2 == 0) {
            states[i] = min(states[i / 2] + 1, states[i]);
        }
        if (i % 3 == 0) {
            states[i] = min(states[i / 3] + 1, states[i]);
        }
    }

    while (n > 1) {
        sequence.push_back(n);
        if (states[n - 1] == states[n] - 1) {
            --n;
        } else if (n % 2 == 0 && states[n / 2] == states[n] - 1) {
            n /= 2;
        } else if (n % 3 == 0 && states[n / 3] == states[n] - 1) {
            n /= 3;
        }
    }

    sequence.push_back(1);
    reverse(sequence.begin(), sequence.end());

    return sequence;
}


int main() {
    int n;
    std::cin >> n;
    vector<int> sequence = optimal_sequence(n);
    std::cout << sequence.size() - 1 << std::endl;
    for (size_t i = 0; i < sequence.size(); ++i) {
        std::cout << sequence[i] << " ";
    }
}
