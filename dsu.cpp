#include <iostream>
#include <vector>

using namespace std;

class DSU {
public:
    DSU(const size_t size)
        : parent(size)
        , rank(size)
    {
        for (size_t i = 0; i < size; ++i) {
            parent[i] = i;
        }
    }

    int find_set(int x) {
        if (x != parent[x]) {
            parent[x] = find_set(parent[x]);
        }
        return parent[x];
    }

    bool union_sets(int x, int y) {
        int xp = find_set(x);
        int yp = find_set(y);

        if (xp == yp) {
            return false;
        } else if (rank[xp] < rank[yp]) {
            parent[xp] = yp;
        } else if (rank[xp] > rank[yp]) {
            parent[yp] = xp;
        } else {
            parent[xp] = yp;
            ++rank[yp];
        }

        return true;
    }

    void print() {
        for (size_t i = 0; i < parent.size(); ++i) {
            cout << i << ' ' << parent[i] << endl;
        }
    }
private:
    vector<int> parent;
    vector<int> rank;
};


int main() {
    DSU dsu(3);

    dsu.union_sets(0, 2);
    dsu.union_sets(1, 2);
    dsu.union_sets(0, 1);

    dsu.print();

    return 0;
}
