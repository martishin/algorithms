#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


struct Query {
    string type, s;
    size_t index;
};


class QueryProcessor {
    int bucket_count;
    vector<vector<string> > hash_table;

    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {
        hash_table.resize(bucket_count);
    }

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.index;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {
        if (query.type == "check") {
            for (int i = static_cast<int> (hash_table[query.index].size()) - 1; i >= 0; --i) {
                if (hash_func(hash_table[query.index][i]) == query.index) {
                    cout << hash_table[query.index][i] << ' ';
                }
            }

            cout << endl;
        } else {
            vector<string>& hash_chain = hash_table[hash_func(query.s)];
            vector<string>::iterator it = std::find(hash_chain.begin(), hash_chain.end(), query.s);

            if (query.type == "find")
                writeSearchResult(it != hash_chain.end());
            else if (query.type == "add") {
                if (it == hash_chain.end())
                    hash_chain.push_back(query.s);
            } else if (query.type == "del") {
                if (it != hash_chain.end())
                    hash_chain.erase(it);
            }
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};


int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
