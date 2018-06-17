#include <iostream>
#include <vector>
#include <stack>

using namespace std;


int reach(vector<vector<int> > &adj, vector<char> &used, int x, int y) {
    if (x == y) {
        return 1;
    }
    used[x] = true;

    for (size_t i = 0; i < adj[x].size(); ++i) {
        if (!used[adj[x][i]]) {
            if (reach(adj, used, adj[x][i], y)) {
                return 1;
	    }
        }
    }
    return 0;
}

int main() {
    size_t n, m;
    cin >> n >> m;
    vector<char> used(n);
    vector<vector<int> > adj(n, vector<int>());
    for (size_t i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    int x, y;
    cin >> x >> y;
    cout << reach(adj, used, x - 1, y - 1) << endl;
}
