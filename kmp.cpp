#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> computePrefix(const string& pattern) {
    vector<int> prefix(pattern.size(), 0);

    for (size_t i = 1; i < pattern.size(); ++i) {
        int p = prefix[i - 1];
        while (p > 0 && pattern[p] != pattern[i]) {
                p = prefix[p - 1];
        }

        if (pattern[p] == pattern[i]) {
                p += 1;
        }

        prefix[i] = p;
    }

    return prefix;
}

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where
// the pattern starts in the text.
vector<int> findPattern(const string& pattern, const string& text) {
    vector<int> result;
    auto prefix = computePrefix(pattern);
    int p = 0;

    for (size_t i = 0; i < text.size(); ++i) {
        while (p > 0 && pattern[p] != text[i]) {
            p = prefix[p - 1];
        }

        if (pattern[p] == text[i]) {
            ++p;
        }

        if (p == pattern.size()) {
            result.push_back(i - pattern.size() + 1);
        }
    }

    return result;
}

int main() {
    string pattern, text;
    cin >> pattern;
    cin >> text;
    vector<int> result = findPattern(pattern, text);
    for (int i = 0; i < result.size(); ++i) {
        cout << result[i] << ' ';
    }
    cout << endl;
    return 0;
}
