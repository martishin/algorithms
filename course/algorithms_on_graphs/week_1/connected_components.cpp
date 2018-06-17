#include <iostream>
#include <vector>
#include <set>
#include <stack>

using namespace std;


void dfs(vector<vector<int> > &adj, set<int> &nodes, int x, int n) {
    vector<char> used(n);
    stack<int> s;
    s.push(x);

    while (!s.empty()) {
        int v = s.top();
        s.pop();
        for (size_t i = 0; i < adj[v].size(); ++i) {
            if (!used[adj[v][i]]) {
                s.push(adj[v][i]);
                used[adj[v][i]] = true;
            }
        }
        nodes.erase(v);
    }
}

int number_of_components(vector<vector<int> > &adj, int n) {
    int res = 0;
    set<int> nodes;
    for (size_t i = 0; i < n; ++i) {
        nodes.insert(i);
    }
    while (!nodes.empty()) {
        int x = *nodes.begin();
        dfs(adj, nodes, x, n);
        ++res;
    }
    return res;
}

int main() {
    size_t n, m;
    cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    for (size_t i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }

    cout << number_of_components(adj, n);
}
