#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;
using std::pair;


void dfs(int v, vector<vector<int> > &graph, vector<char> &used, vector<int> &order) {
    used[v] = true;
    for (size_t i =0; i < graph[v].size(); ++i)
        if (!used[graph[v][i]])
            dfs(graph[v][i], graph, used, order);
    order.push_back(v);
}


vector<int> toposort(vector<vector<int> > graph) {
    int n = graph.size();

    vector<char> used(n, false);
    vector<int> order;

    for (size_t i = 0; i < n; ++i) {
        if (!used[i])
            dfs(i, graph, used, order);
    }

    reverse(order.begin(), order.end());

    return order;
}


int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int> > graph(n, vector<int>());

    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        graph[x - 1].push_back(y - 1);
    }

    vector<int> order = toposort(graph);

    for (size_t i = 0; i < order.size(); i++) {
        std::cout << order[i] + 1 << " ";
    }
}
