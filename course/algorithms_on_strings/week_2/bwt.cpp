#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

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
