#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using namespace std;

string largest_number(vector<int> a) {
    int ii = 0, maxDigit;
    std::stringstream ret;
    while (!a.empty()) {
        maxDigit = a[0];
        ii = 0;
        for (size_t i = 0; i < a.size(); ++i) {
            if (a[i] > maxDigit) {
                maxDigit = a[i];
                ii = i;
            }
        }
        ret << maxDigit;
        a.erase(a.begin() + ii);
    }
    string result;
    ret >> result;
    return result;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }
    std::cout << largest_number(a);
}
