#include <iostream>
#include <vector>
#include <cassert>

using namespace std;


long long fibonacci_modulo(long long n, long long m) {
    vector<long long> pisano_sequence;
    long long current;
    size_t previous = 1;

    if (n <= 1) {
        return n;
    }

    pisano_sequence.push_back(0);
    pisano_sequence.push_back(1);

    while (true) {
        current = (pisano_sequence[previous] + pisano_sequence[previous - 1]) % m;
        if (current == 0 && (current + pisano_sequence[previous]) % m == 1) {
            break;
        } else {
            pisano_sequence.push_back(current);
        }
        previous++;
    }

    return pisano_sequence[n % pisano_sequence.size()];
}


long long fibonacci_recursive(int n) {
    if (n < 2 )
        return n;
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}


long long fibonacci_dp(int n) {
    vector<long long> states(n);
    states[0] = 1;
    states[1] = 1;

    for (size_t i = 2; i < n; ++i)
        states[i] = states[i - 1] + states[i - 2];
    return states[n - 1];
}


long long fibonacci_dp_effective(int n) {
    long long x = 1, y = 0;
    for (size_t i = 1; i < n; ++i) {
        x += y;
        y = x - y;
    }
    return x;
}


long long fibonacci_matrix_exponentiation(int n) {
    int a = 1, ta,
        b = 1, tb,
        c = 1, rc = 0, tc,
        d = 0, rd = 1;

    while (n) {
        if (n % 2 != 0) {
            tc = rc;
            rc = rc * a + rd * c;
            rd = tc * b + rd * d;
        }

        ta = a;
        tb = b;
        tc = c;

        a = a * a + b * c;
        b = ta * b + b * d;
        c = c * ta + d * c;
        d = tc * tb + d * d;

        n /= 2;
    }

    return rc;
}


int main() {
    int n;
    cin >> n;
    assert (n > 0);

    cout << fibonacci_matrix_exponentiation(n) << endl;
}

