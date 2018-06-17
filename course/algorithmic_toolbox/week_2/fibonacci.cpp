#include <iostream>
#include <cassert>
#include <vector>


long long fibonacci_naive(long n) {
    if (n <= 1)
        return n;

    return fibonacci_naive(n - 1) + fibonacci_naive(n - 2);
}

void print_vector(const std::vector<long long> &v) {
    for(auto i = v.begin(); i != v.end(); ++i) {
        std::cout << *i;
    }
    std::cout << '\n';
}

long long fibonacci_fast(const int n) {
    std::vector<long long> numbers;
    numbers.push_back(0);
    numbers.push_back(1);
    for (size_t i = 2; i < n + 1; ++i) {
        numbers.push_back(numbers[i - 1] + numbers[i - 2]);
    }
    return numbers[n];
}

void test_solution() {
    for (int n = 0; n < 20; ++n) {
        assert(fibonacci_fast(n) == fibonacci_naive(n));
    }
}

int main() {
    int n = 0;
    std::cin >> n;

    //std::cout << fibonacci_naive(n) << '\n';
    //test_solution();
    std::cout << fibonacci_fast(n) << '\n';
    return 0;
}
