#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <array>

using std::vector;
using std::cout;
using std::endl;

const int LettersCount = 4;

class Trie {
public:
    Trie() : root(nullptr) {}

    void Insert(const std::string& pattern) {
        if (root == nullptr) {
            root = std::make_unique<TrieNode>();
        }

        TrieNode *currentNode = root.get();

        for (const auto &letter: pattern) {
            auto letterIndex = letterToIndex(letter);

            if (currentNode->Next[letterIndex] == nullptr) {
                currentNode->Next[letterIndex] = std::make_unique<TrieNode>();
            }

            currentNode = currentNode->Next[letterIndex].get();
        }

        currentNode->IsLeaf = true;
    }

    bool Match(const std::string& text, size_t startIndex) const {
        if (root == nullptr) {
            return false;
        }

        TrieNode *currentNode = root.get();

        for (size_t i = startIndex; i < text.size(); ++i) {
            auto letterIndex = letterToIndex(text[i]);

            if (currentNode->IsLeaf) {
                return true;
            } else if (currentNode->Next[letterIndex] == nullptr) {
                return false;
            }

            currentNode = currentNode->Next[letterIndex].get();
        }


        return currentNode->IsLeaf;
    }

    static inline size_t letterToIndex (char letter) {
        switch (letter) {
            case 'A': return 0; break;
            case 'C': return 1; break;
            case 'G': return 2; break;
            case 'T': return 3; break;
            default: assert (false); return -1;
        }
    }
private:
    struct TrieNode;
    using TrieNodePtr = std::unique_ptr<TrieNode>;

    struct TrieNode {
        std::array<TrieNodePtr, LettersCount> Next;
        bool IsLeaf;
        TrieNode() : IsLeaf(false) {}
    };

    TrieNodePtr root;
};


vector <size_t> solve(const std::string& text, int n, const vector <std::string>& patterns) {
    vector<size_t> result;
    Trie trie;

    for (const auto &pattern: patterns) {
        trie.Insert(pattern);
    }

    for (size_t i = 0; i < text.size(); ++i) {
        if (trie.Match(text, i)) {
            result.push_back(i);
        }
    }

    return result;
}

int main (void) {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    std::string text;
    std::cin >> text;

    int n;
    std::cin >> n;

    vector <std::string> patterns (n);
    for (int i = 0; i < n; i++) {
        std::cin >> patterns[i];
    }

    vector <size_t> ans;
    ans = solve(text, n, patterns);

    for (size_t i = 0; i < ans.size(); i++) {
        std::cout << ans[i];
        if (i + 1 < ans.size()) {
            std::cout << " ";
        }
        else {
            std::cout << std::endl;
        }
    }

    return 0;
}
