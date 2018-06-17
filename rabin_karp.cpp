#include <iostream>
#include <string>
#include <vector>

typedef unsigned long long ull;
typedef long long ll;
using namespace std;


struct Data {
    string pattern, text;
};


Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}


class HashFunction {
    int prime;
    int multiplier;

public:
    explicit HashFunction(int prime = 1000000007): prime(prime) {
        multiplier = rand() % (prime - 1) + 1;
    }

    ll from_string(const string& s) {
        ll hash = 0;

        for (ll i = static_cast<ll>(s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash;
    }

    int get_multiplier() {
        return multiplier;
    }

    int get_prime() {
        return prime;
    }
};


vector<ll> precompute_hashes(const string& text, const string& pattern, HashFunction& hash_function) {
    int text_length = text.size();
    int pattern_length = pattern.size();

    vector<ll> hashes(text_length - pattern_length + 1);
    const string text_without_pattern = text.substr(text_length - pattern_length, pattern_length);

    hashes[text_length - pattern_length] = hash_function.from_string(text_without_pattern);

    int multiplier = hash_function.get_multiplier();
    int prime = hash_function.get_prime();
    ll subtrahend = 1;

    for (size_t i = 0; i < pattern_length; ++i)
        subtrahend = subtrahend * multiplier % prime;

    for (int i = text_length - pattern_length - 1; i >= 0; --i) {
        ll pre_hash = multiplier * hashes[i + 1] + text[i] - subtrahend * text[i + pattern_length];

        while (pre_hash < 0)
            pre_hash += prime;

        hashes[i] = pre_hash % prime;
    }

    return hashes;
}


vector<int> get_occurrences(const Data& input) {
    HashFunction hash_function;

    const string& pattern = input.pattern, text = input.text;
    std::vector<int> occurrences;

    ll pattern_hash = hash_function.from_string(pattern);

    vector<ll> hashes = precompute_hashes(text, pattern, hash_function);

    for (size_t i = 0; pattern.size() + i <= text.size(); ++i)
        if (pattern_hash == hashes[i] && text.compare(i, pattern.size(), pattern) == 0)
            occurrences.push_back(i);
    return occurrences;
}


void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
