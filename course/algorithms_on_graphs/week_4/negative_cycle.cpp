#include <iostream>
#include <vector>
#include <limits>

using namespace std;

bool negative_cycle(vector<vector<int> > &graph, vector<vector<int> > &cost) {
    int n = graph.size();

    vector<int> distance(n, 1e4);

    distance[0] = 0;

    for (size_t i = 0; i < n - 1; ++i) {
        for (size_t v = 0; v < n; ++v) {
            auto &adj = graph[v];
            auto &adjCost = cost[v];

            for (size_t j = 0; j < adj.size(); ++j) {
                auto nb = adj[j];

                if (distance[v] + adjCost[j] < distance[nb])
                    distance[nb] = distance[v] + adjCost[j];
            }
        }
    }

    for (size_t v = 0; v < n; ++v) {
        auto &adj = graph[v];
        auto &adjCost = cost[v];

        for (size_t j = 0; j < adj.size(); ++j) {
            auto nb = adj[j];

            if (distance[v] + adjCost[j] < distance[nb])
                return true;
        }
    }

    return false;
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

    cout << negative_cycle(graph, cost) << endl;
}
