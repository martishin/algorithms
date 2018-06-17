#include <iostream>
#include <string>
#include <vector>

using namespace std;


int edit_distance(const string &str1, const string &str2) {
    int n = str1.size();
    int m = str2.size();
    int cost = 0;
    vector<vector<int> > states(n + 1, vector<int>(m + 1, 0));

    for (size_t i = 0; i <= n; ++i) {
        states[i][0] = i;
    }

    for (size_t i = 0; i <= m; ++i) {
        states[0][i] = i;
    }

    for (size_t i = 1; i <= n; ++i) {
        for (size_t j = 1; j <= m; ++j) {
            if (str1[i - 1] == str2[j - 1]) {
                cost = 0;
            } else {
                cost = 1;
            }
            states[i][j] = min(
                min(states[i - 1][j], states[i][j - 1]) + 1,
                states[i - 1][j - 1] + cost
            );
        }
    }

    return states[n][m];
}


int main() {
    string str1;
    string str2;
    std::cin >> str1 >> str2;
    std::cout << edit_distance(str1, str2) << std::endl;
    return 0;
}
