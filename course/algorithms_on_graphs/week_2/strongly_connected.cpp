#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;


//Kosaraju's algorithm
void dfs_order(int v, vector<vector<int> > &graph, vector<char> &used, vector<int> &order) {
    used[v] = true;
    for (size_t i = 0; i < graph[v].size(); ++i) {
        if (!used[graph[v][i]])
            dfs_order(graph[v][i], graph, used, order);
    }
    order.push_back(v);
}


void dfs_component(int v, vector<vector<int> > &transpose_graph, vector<char> &used, vector<int> &component) {
    used[v] = true;
    component.push_back(v);
    for (size_t i = 0; i < transpose_graph[v].size(); ++i) {
        if (!used[transpose_graph[v][i]])
            dfs_component(transpose_graph[v][i], transpose_graph, used, component);
    }
}


int strongly_connected_components(vector<vector<int> > &graph, vector<vector<int> > &transpose_graph) {
    int n = graph.size();

    vector<char> used(n, false);
    vector<int> order;
    vector<vector<int> > components;

    for (size_t i = 0; i < n; ++i) {
        if (!used[i])
            dfs_order(i, graph, used, order);
    }

    used.assign(n, false);

    for (size_t i = 0; i < n; ++i) {
        int v = order[n - 1 - i];
        if (!used[v]) {
            components.push_back(vector<int>());
            dfs_component(v, transpose_graph, used, components.back());
        }
    }

    return components.size();
}


int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int> > graph(n, vector<int>()), transpose_graph(n, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        graph[x - 1].push_back(y - 1);
        transpose_graph[y - 1].push_back(x - 1);
    }
    std::cout << strongly_connected_components(graph, transpose_graph);
}
