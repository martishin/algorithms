#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::pair;


struct PairHash {
    template<typename T1, typename T2>
    inline size_t operator()(const std::pair<T1, T2> &p) const {
        return std::hash<T1>()(p.first) ^ std::hash<T2>()(p.second);
    }
};

string InverseBWT(const string& bwt) {
    string text = "";

    vector<pair<char, size_t> > firstColumn;
    vector<pair<char, size_t> > lastColumn;

    std::unordered_map<pair<char, size_t>, pair<char, size_t>, PairHash> firstToLastColumn;
    std::unordered_map<pair<char, size_t>, pair<char, size_t>, PairHash> lastToFirstColumn;

    std::unordered_map<char, size_t> occurrences;

    for (const char &c: bwt) {
        ++occurrences[c];
        lastColumn.emplace_back(c, occurrences[c]);
    }

    firstColumn = lastColumn;
    std::sort(firstColumn.begin(), firstColumn.end());

    for (size_t i = 0; i < bwt.size(); ++i) {
        firstToLastColumn[firstColumn[i]] = lastColumn[i];
        lastToFirstColumn[lastColumn[i]] = firstColumn[i];
    }

    auto currentChar = firstColumn[0];
    bool reverse_ = false;

    while (text.size() < bwt.size()) {
        text += currentChar.first;

        if (reverse_) {
            currentChar = lastToFirstColumn[currentChar];
        } else {
            currentChar = firstToLastColumn[currentChar];
        }
    }

    std::reverse(text.begin(), text.end());

    return text;
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    string bwt;
    cin >> bwt;

    cout << InverseBWT(bwt) << endl;
    return 0;
}
