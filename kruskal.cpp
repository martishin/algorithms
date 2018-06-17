#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using std::vector;
using std::cin;
using std::cout;
using std::endl;


class TUnionSet {
public:
    TUnionSet(const size_t size) {
        Parent.resize(size);
        Rank.resize(size);
    }

    void MakeSet(const int element) {
        Parent[element] = element;
        Rank[element] = 0;
    }

    int Find(int element) {
        while (element != Parent[element])
            element = Parent[element];
        return element;
    }

    void Union(const int firstElement, const int secondElement) {
        auto firstElementParent = Find(firstElement);
        auto secondElementParent = Find(secondElement);

        if (firstElementParent == secondElementParent)
            return;

        if (Rank[firstElementParent] > Rank[secondElementParent])
            Parent[secondElementParent] = firstElementParent;
        else {
            Parent[firstElementParent] = secondElementParent;
            if (Rank[firstElementParent] == Rank[secondElementParent])
                ++Rank[secondElementParent];
        }
    }
private:
    vector<int> Parent;
    vector<int> Rank;
};

struct SVertex {
    size_t id;
    double x;
    double y;
};

struct SEdge {
    SVertex FirstVertex;
    SVertex SecondVertex;

    double Len;

    SEdge(const SVertex firstVertex, const SVertex secondVertex)
        : FirstVertex(firstVertex)
        , SecondVertex(secondVertex)
        , Len(std::sqrt(std::pow(firstVertex.x - secondVertex.x, 2) + pow(firstVertex.y - secondVertex.y, 2)))
    {}

    bool operator<(const SEdge &other) const {
        return Len < other.Len;
    }
};


double minimum_distance(const vector<SVertex> &vertices) {
    vector<SEdge> edges;
    double result = 0;

    size_t verticesSize = vertices.size();
    TUnionSet unionSet(verticesSize);

    for (auto const &vertex: vertices)
        unionSet.MakeSet(vertex.id);

    for (size_t i = 0; i < verticesSize; ++i) {
        for (size_t j = i + 1; j < verticesSize; ++j)
            edges.emplace_back(vertices[i], vertices[j]);
    }

    std::sort(std::begin(edges), std::end(edges));

    for (const auto &edge: edges) {
        if (unionSet.Find(edge.FirstVertex.id) != unionSet.Find(edge.SecondVertex.id)) {
            result += edge.Len;
            unionSet.Union(edge.FirstVertex.id, edge.SecondVertex.id);
        }
    }

    return result;
}

int main() {
    size_t n;
    cin >> n;

    vector<SVertex> vertices;
    double x, y;

    for (size_t i = 0; i < n; i++) {
        cin >> x >> y;
        vertices.push_back(SVertex{i, x, y});
    }

    cout << std::setprecision(10) << minimum_distance(vertices) << endl;
}
