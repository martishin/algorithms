#include <iostream>
#include <vector>


long long get_fibonacci_huge_naive(long long n, long long m) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % m;
}

long long get_fibonacci_huge_fast(long long n, long long m) {
    std::vector<long long> pisano_sequence;
    long long curr;
    size_t pre = 1;

    if (n <= 1) {
        return n;
    }

    pisano_sequence.push_back(0);
    pisano_sequence.push_back(1);

    while (true) {
        curr = (pisano_sequence[pre] + pisano_sequence[pre - 1]) % m;
        if (curr == 0 && (curr + pisano_sequence[pre]) % m == 1) {
            break;
        } else {
            pisano_sequence.push_back(curr);
        }
        pre++;
    }

    return pisano_sequence[n % pisano_sequence.size()];
}

int main() {
    long long n, m;
    std::cin >> n >> m;
    std::cout << get_fibonacci_huge_fast(n, m) << '\n';
}
