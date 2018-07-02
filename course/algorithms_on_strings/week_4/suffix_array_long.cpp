#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
const int alphabet = 5;

int ToDigit(char c) {
    switch(c) {
        case '$' : return  0;
        case 'A' : return  1;
        case 'C' : return  2;
        case 'G' : return  3;
        case 'T' : return  4;
        default  : return -1;
    }
}

vector<int> SortCharacters(const string &text) {
    vector<int> order(text.size()), cnt(alphabet, 0);
    for (size_t i = 0; i < text.size(); ++i) {
        ++cnt[ToDigit(text[i])];
    }
    for (size_t i = 1; i < alphabet; ++i) {
        cnt[i] += cnt[i - 1];
    }
    for (int i = text.size() - 1; i >= 0; --i) {
        order[--cnt[ToDigit(text[i])]]= i;
    }
    return order;
}

vector<int> ComputeCharClasses(const string& text, const vector<int>& order) {
    vector<int> classes(text.size(), 0);
    for (size_t i = 1; i < text.size(); ++i) {
        if (text[order[i]] != text[order[i - 1]]) {
            classes[order[i]] = classes[order[i - 1]] + 1;
        } else {
            classes[order[i]] = classes[order[i - 1]];
        }
    }
    return classes;
}

vector<int> SortDoubled(const string& text, const vector<int>& order, const vector<int>& classes, size_t l) {
    vector<int> cnt(text.size(), 0), newOrder(text.size());
    for (size_t i = 0; i < text.size(); ++i) {
        ++cnt[classes[i]];
    }
    for (size_t i = 1; i < text.size(); ++i) {
        cnt[i] += cnt[i - 1];
    }
    for (int i = text.size() - 1; i >= 0; --i) {
        int start = (order[i] - l + text.size()) % text.size();
        newOrder[--cnt[classes[start]]] = start;
    }
    return newOrder;
}

vector<int> UpdateClasses(const vector<int>& newOrder, const vector<int>& classes, size_t l) {
    vector<int> newClasses(newOrder.size(), 0);
    newClasses[newOrder[0]] = 0;
    for (size_t i = 1; i < newOrder.size(); ++i) {
        int cur = newOrder[i];
        int prev = newOrder[i - 1];
        int mid = (cur + l) % newOrder.size();
        int midPrev = (prev + l) % newOrder.size();
        if (classes[cur] != classes[prev] || classes[mid] != classes[midPrev])
            newClasses[cur] = newClasses[prev] + 1;
        else
            newClasses[cur] = newClasses[prev];
    }
    return newClasses;
}

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.
vector<int> BuildSuffixArray(const string& text) {
    vector<int> order = SortCharacters(text);
    vector<int> classes = ComputeCharClasses(text, order);

    size_t l = 1;

    while (l < text.size()) {
	order = SortDoubled(text, order, classes, l);
	classes = UpdateClasses(order, classes, l);
	l *= 2;
    }

    return order;
}

int main() {
    string text;
    cin >> text;
    vector<int> suffix_array = BuildSuffixArray(text);

    for (int i = 0; i < suffix_array.size(); ++i) {
	    cout << suffix_array[i] << ' ';
    }

    cout << endl;
    return 0;
}
