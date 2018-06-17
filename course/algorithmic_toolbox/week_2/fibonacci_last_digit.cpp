#include <iostream>
#include <vector>

int get_fibonacci_last_digit_naive(int n) {
    if (n <= 1)
        return n;

    int previous = 0;
    int current  = 1;

    for (int i = 0; i < n - 1; ++i) {
        int tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % 10;
}

int get_fibonacci_last_digit_fast(long n) {
    if (n <= 1) {
        return n;
    }

    int n2 = 0;
    int n1 = 1;
    int curr = 1;

    for (size_t i = 2; i < n; ++i) {
        n2 = n1;
        n1 = curr;
        curr = (n1 + n2) % 10;
    }

    return curr;
}

int main() {
    long n;
    std::cin >> n;
    int c = get_fibonacci_last_digit_fast(n);
    std::cout << c << '\n';
    return 0;
}
