#include <string>
#include <iostream>
#include <vector>
#include <map>

using std::map;
using std::vector;
using std::string;
using std::cout;
using std::endl;

typedef map<char, int> Edges;
typedef vector<Edges> Trie;

Trie build_trie(vector<string> & patterns) {
    Trie trie(1);

    for (const auto &pattern: patterns) {
        size_t currentNode = 0;

        for (const auto &currentSymbol: pattern) {
            if (trie[currentNode].find(currentSymbol) != trie[currentNode].end()) {
                currentNode = trie[currentNode][currentSymbol];
            } else {
                trie.emplace_back();
                size_t newNode = trie.size() - 1;
                trie[currentNode][currentSymbol] = newNode;
                currentNode = newNode;
            }
        }
    }

    return trie;
}

int main() {
    size_t n;
    std::cin >> n;
    vector<string> patterns;
    for (size_t i = 0; i < n; i++) {
        string s;
        std::cin >> s;
        patterns.push_back(s);
    }

    Trie t = build_trie(patterns);
    for (size_t i = 0; i < t.size(); ++i) {
        for (const auto & j : t[i]) {
            std::cout << i << "->" << j.second << ":" << j.first << "\n";
        }
    }

    return 0;
}
