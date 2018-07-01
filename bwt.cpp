#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;


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

string BWT(string& text) {
    string result = "";
    vector<string> matrix;

    for (size_t i = 0; i < text.size(); ++i) {
        std::rotate(text.begin(), text.begin() + 1, text.end());
        matrix.push_back(text);
    }

    std::sort(matrix.begin(), matrix.end());

    for (size_t i = 0; i < matrix.size(); ++i) {
        result += matrix[i].back();
    }

    return result;
}

int main() {
    string text;
    cin >> text;
    cout << BWT(text) << endl;
    return 0;
}
