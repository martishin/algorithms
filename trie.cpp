#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <array>

using namespace std;
using std::cout;
using std::endl;

class Trie {
private:
    struct TrieNode {
        array<unique_ptr<TrieNode>, 26> children;
        bool end = false;
    };

    unique_ptr<TrieNode> head;

    inline size_t getIdx(char c) {
        return c - 'a';
    }

public:
    Trie() {
        head = make_unique<TrieNode>();
    }

    void insert(string word) {
        auto current = head.get();

        for (const auto c : word) {
            size_t idx = getIdx(c);

            if (!current->children[idx]) {
                current->children[idx] = make_unique<TrieNode>();
            }

            current = current->children[idx].get();
        }

        current->end = true;
    }

    bool search(string word) {
        auto current = head.get();

        for (const auto c : word) {
            size_t idx = getIdx(c);

            if (!current->children[idx]) {
                return false;
            }

            current = current->children[idx].get();
        }

        return current->end;
    }

    bool startsWith(string prefix) {
        auto current = head.get();

        for (const auto c : prefix) {
            size_t idx = getIdx(c);

            if (!current->children[idx]) {
                return false;
            }

            current = current->children[idx].get();
        }

        return true;
    }
};


int main (void) {
    auto trie = new Trie();

    trie->insert("apple");
    cout << trie->search("apple") << endl;
    cout << trie->search("app") << endl;
    cout << trie->startsWith("app") << endl;
    trie->insert("app");
    cout << trie->search("app") << endl;

    return 0;
}
