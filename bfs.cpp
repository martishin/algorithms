#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;


void bfs(vector<vector<int> > &graph, vector<int> &dist, int b) {
    queue<int> q;

    dist[b] = 0;
    q.push(b);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (size_t i = 0; i < graph[v].size(); ++i) {
            int nv = graph[v][i];

            if (dist[nv] == numeric_limits<int>::max()) {
                q.push(nv);
                dist[nv] = dist[v] + 1;
            }
        }
    }
}


int distance(vector<vector<int> > &graph, int b, int e) {
    int n = graph.size();
    vector<int> dist(n, numeric_limits<int>::max());

    bfs(graph, dist, b);

    if (dist[e] != numeric_limits<int>::max())
        return dist[e];

    return -1;
}


int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int> > graph(n, vector<int>());

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        graph[x - 1].push_back(y - 1);
        graph[y - 1].push_back(x - 1);
    }

    int b, e;
    cin >> b >> e;
    b--, e--;
    cout << distance(graph, b, e);
}
