#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

enum State {
    NOT_VISITED,
    VISITING,
    VISITED
};


bool hasCycleWithStart(int v, vector<vector<int> > &graph, vector<State> &visited) {
    bool cycle = false;

    visited[v] = VISITING;
    for (size_t i =0; i < graph[v].size(); ++i)
        if (visited[graph[v][i]] == VISITING) {
            return true;
        } else if (visited[graph[v][i]] == NOT_VISITED) {
            cycle |= dfs(graph[v][i], graph, visited);
        }
    visited[v] = VISITED;
    return cycle;
}


bool hasCycle(vector<vector<int> > &graph) {
    vector<State> visited(graph.size(),  NOT_VISITED);

    for (size_t i = 0; i < graph.size(); ++i) {
        if (visited[i] == NOT_VISITED) {
            if (hasCycleWithStart(i, graph, visited)) {
                return true;
            }
        }
    }

    return false;
}


int main() {
    size_t n, m;
    cin >> n >> m;

    vector<vector<int> > graph(n, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        graph[x - 1].push_back(y - 1);
    }
    cout << hasCycle(graph) << endl;
}
