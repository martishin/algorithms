#include <iostream>

long gcd(long a, long b) {
    while (b) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

long lcm(long a, long b) {
    return a * b / gcd(a, b);
}

int main() {
    long a, b;
    std::cin >> a >> b;
    std::cout << lcm(a, b) << std::endl;
    return 0;
}
