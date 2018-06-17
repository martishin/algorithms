#include <iostream>

using namespace std;

//greatest common divisor


int gcd(int n, int k) {
    while (k) {
        n %= k;
        swap(n, k);
    }
    return n;
}


int main() {
    int n, k;

    cin >> n >> k;

    cout << gcd(n, k) << endl;

    return 0;
}
