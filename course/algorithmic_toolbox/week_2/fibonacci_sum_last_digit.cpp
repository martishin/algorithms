#include <iostream>

int get_fibonacci_last_digit_fast(long long n) {
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

int fibonacci_sum_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current;
    }

    return sum % 10;
}

int fibonacci_sum_fast(long long n) {
    if (n <= 1) {
        return n;
    }

    int last_digit = get_fibonacci_last_digit_fast((n + 2) % 60);

    int sum_last_digit = last_digit - 1;
    if (sum_last_digit == -1) {
        sum_last_digit = 9;
    }

    return sum_last_digit;
}

int main() {
    long long n = 0;
    std::cin >> n;
    std::cout << fibonacci_sum_fast(n) << '\n';
}
