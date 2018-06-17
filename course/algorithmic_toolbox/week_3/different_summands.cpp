#include <iostream>
#include <vector>

using namespace std;

vector<int> optimal_summands(int n) {
    vector<int> summands;

    for (int k = n, l = 1; k > 0; ++l) {
        if (k <= 2 * l) {
            summands.push_back(k);
            k = 0;
        } else {
            summands.push_back(l);
            k -= l;
        }
    }

    return summands;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> summands = optimal_summands(n);
    std::cout << summands.size() << '\n';
    for (size_t i = 0; i < summands.size(); ++i) {
        std::cout << summands[i] << ' ';
    }
}
