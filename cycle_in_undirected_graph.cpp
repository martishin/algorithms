#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <cassert>
#include <fstream>
#include <array>

using namespace std;

#define endl '\n'


bool hasCycleComponent(vector<vector<int> > &graph, set<int> &remainingVertices, int startVertex) {
    unordered_set<int> processedVertices;
    stack<pair<int, int>> vertices;

    vertices.push(make_pair(startVertex, startVertex));
    processedVertices.insert(startVertex);

    while (!vertices.empty()) {
        auto currentVertex = vertices.top();
        vertices.pop();
        remainingVertices.erase(currentVertex.first);

        for (const auto &neighbourVertex: graph[currentVertex.first]) {
            if (neighbourVertex == currentVertex.second) {
                continue;
            }

            if (processedVertices.find(neighbourVertex) != processedVertices.end()) {
                return true;
            } else {
                vertices.push(make_pair(neighbourVertex, currentVertex.first));
                processedVertices.insert(neighbourVertex);
            }
        }

    }

    return false;
}


bool hasCycle(vector<vector<int> > &graph) {
    set<int> remainingVertices;

    for (size_t i = 0; i < graph.size(); ++i) {
        remainingVertices.insert(i);
    }

    while (!remainingVertices.empty()) {
        int startVertex = *remainingVertices.begin();
        if (hasCycleComponent(graph, remainingVertices, startVertex)) {
            return true;
        }
    }

    return false;
}

int main() {
    int n, m, v, u;

    cin >> n >> m;

    vector<vector<int> > graph(n);

    for (size_t i = 0; i < m; ++i) {
        cin >> v >> u;
        --v;
        --u;
        graph[v].push_back(u);
        graph[u].push_back(v);
    }

    cout << hasCycle(graph) << endl;

    return 0;
}
