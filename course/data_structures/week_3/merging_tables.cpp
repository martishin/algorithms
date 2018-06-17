#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;


struct DisjointSetsElement {
    int size, parent, rank;

    DisjointSetsElement(int size = 0, int parent = -1, int rank = 0):
        size(size), parent(parent), rank(rank) {}
};


struct DisjointSets {
    int size;
    int max_table_size;

    vector <DisjointSetsElement> sets;

    DisjointSets(int size): size(size), max_table_size(0), sets(size) {
        for (int i = 0; i < size; i++)
            sets[i].parent = i;
    }

    int getParent(int table) {
        // find parent and compress path
        if (sets[table].parent != table)
            sets[table].parent = getParent(sets[table].parent);
        return sets[table].parent;
    }

    void merge(int destination, int source) {
        destination = getParent(destination);
        source = getParent(source);

        if (destination != source) {
            // merge two components
            // use union by rank heuristic
            // update max_table_size
            if (sets[destination].rank > sets[source].rank) {
                sets[source].parent = destination;
                sets[destination].size += sets[source].size;
                sets[source].size = 0;
            } else {
                sets[destination].parent = source;
                sets[source].size += sets[destination].size;
                sets[destination].size = 0;
            }

            max_table_size = [](const vector<int> &v) {
                return *max_element(v.begin(), v.end());
            }(
                {
                    max_table_size,
                    sets[destination].size,
                    sets[source].size
                }
            );
        }
    }
};


int main() {
    int n, m;
    cin >> n >> m;

    DisjointSets tables(n);

    for (auto &table : tables.sets) {
        cin >> table.size;
        tables.max_table_size = max(tables.max_table_size, table.size);
    }

    for (int i = 0; i < m; i++) {
        int destination, source;
        cin >> destination >> source;
        --destination;
        --source;

        tables.merge(destination, source);
        cout << tables.max_table_size << endl;
    }

    return 0;
}
