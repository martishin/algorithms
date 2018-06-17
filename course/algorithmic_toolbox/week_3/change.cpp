#include <iostream>

using namespace std;


int get_change(int m) {
    int tens = 0, fives = 0, ones = 0;
    tens = m / 10;
    fives = (m - tens * 10) / 5;
    ones = m - tens * 10 - fives * 5;
    return tens + fives + ones;
}

int main() {
    int m;
    std::cin >> m;
    std::cout << get_change(m) << '\n';
}
