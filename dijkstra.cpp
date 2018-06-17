#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;


int Dijkstra(vector<vector<int> > &graph, vector<vector<int> > &cost, int s, int t) {
    size_t n = graph.size();

    vector<int> distance(n, numeric_limits<int>::max());
    priority_queue<pair<int, int> > pq;

    pq.push(make_pair(0, s));
    distance[s] = 0;

    while (!pq.empty()) {
        auto v = pq.top().second;
        pq.pop();

        auto &adj = graph[v];
        auto &adjCost = cost[v];

        for (size_t i = 0; i < adj.size(); ++i) {
            auto nb = adj[i];
            if (distance[nb] > distance[v] + adjCost[i]) {
                distance[nb] = distance[v] + adjCost[i];
                pq.push(make_pair(distance[nb], nb));
            }
        }
    }

    if (distance[t] == numeric_limits<int>::max())
        return -1;

    return distance[t];
}


int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int> > graph(n, vector<int>());
    vector<vector<int> > cost(n, vector<int>());

    for (int i = 0; i < m; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        graph[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }

    int s, t;
    cin >> s >> t;
    s--;
    t--;

    cout << Dijkstra(graph, cost, s, t);
}
