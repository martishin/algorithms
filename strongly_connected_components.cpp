#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;


//Kosaraju's algorithm
void dfs_order(int v, vector<vector<int> > &graph, vector<char> &visited, vector<int> &order) {
    visited[v] = true;
    for (size_t i = 0; i < graph[v].size(); ++i) {
        if (!visited[graph[v][i]])
            dfs_order(graph[v][i], graph, visited, order);
    }
    order.push_back(v);
}


void dfs_component(int v, vector<vector<int> > &transpose_graph, vector<char> &visited, vector<int> &component) {
    visited[v] = true;
    component.push_back(v);
    for (size_t i = 0; i < transpose_graph[v].size(); ++i) {
        if (!visited[transpose_graph[v][i]])
            dfs_component(transpose_graph[v][i], transpose_graph, visited, component);
    }
}


int strongly_connected_components(vector<vector<int> > &graph, vector<vector<int> > &transpose_graph) {
    int n = graph.size();

    vector<char> visited(n, false);
    vector<int> order;
    vector<vector<int> > components;

    for (size_t i = 0; i < n; ++i) {
        if (!visited[i])
            dfs_order(i, graph, visited, order);
    }

    visited.assign(n, false);

    for (size_t i = 0; i < n; ++i) {
        int v = order[n - 1 - i];
        if (!visited[v]) {
            components.push_back(vector<int>());
            dfs_component(v, transpose_graph, visited, components.back());
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
