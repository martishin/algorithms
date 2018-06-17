#include <iostream>

long gcd_naive(long a, long b) {
    long current_gcd = 1;
    for (long d = 2; d <= a && d <= b; d++) {
        if (a % d == 0 && b % d == 0) {
            if (d > current_gcd) {
                current_gcd = d;
            }
        }
    }
    return current_gcd;
}

long gcd_fast(long a, long b) {
    while (b) {
        a %= b;
        std::swap(a,b);
    }
    return a;
}

int main() {
    long a, b;
    std::cin >> a >> b;
    std::cout << gcd_fast(a, b) << std::endl;
    return 0;
}
