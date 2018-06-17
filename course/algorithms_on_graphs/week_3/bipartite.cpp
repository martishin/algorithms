#include <iostream>
#include <vector>
#include <queue>

using namespace std;


enum color {WHITE, BLACK, GREY};


bool bipartite(vector<vector<int> > &graph) {
    int n = graph.size();
    vector<int> colors(n, GREY);
    queue<int> q;
    bool is_bipartite = true;

    colors[1] = WHITE;
    q.push(1);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (size_t i = 0; i < graph[v].size(); ++i) {
            int nv = graph[v][i];

            if (colors[nv] == GREY) {
                q.push(nv);

                if (colors[v] == WHITE)
                    colors[nv] = BLACK;
                else
                    colors[nv] = WHITE;
            } else if (colors[nv] == colors[v]) {
                is_bipartite = false;
                break;
            }
        }
    }

    return is_bipartite;
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
    cout << bipartite(graph) << endl;
}

