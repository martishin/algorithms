#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

enum States {
    NOT_VISITED,
    VISITING,
    VISITED
};


bool dfs(int v, vector<vector<int> > &graph, vector<States> &used) {
    bool cycle = false;

    used[v] = VISITING;
    for (size_t i =0; i < graph[v].size(); ++i)
        if (used[graph[v][i]] == VISITING)
            return true;
        else if (used[graph[v][i]] == NOT_VISITED)
            cycle |= dfs(graph[v][i], graph, used);
    used[v] = VISITED;
    return cycle;
}


bool acyclic(vector<vector<int> > &graph) {
    int n = graph.size();
    vector<States> used(n,  NOT_VISITED);

    for (size_t i = 0; i < n; ++i) {
        if (used[i] == NOT_VISITED)
            if (dfs(i, graph, used))
                return true;
    }

    return false;
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
    std::cout << acyclic(graph);
}
