#include <iostream>
#include <vector>
#include <map>

using namespace std;


struct Vertex {
    map<Vertex*, double> connections;
    int key;

    Vertex(int key) : key(key) {}
};


class Graph {
private:
    map<int, Vertex*> vertices;

public:
    void addVertex(const int key) {
        try {
            if (vertices.find(key) == vertices.end()) {
                Vertex *vertex = new Vertex(key);
                vertices[key] = vertex;
            } else {
                throw runtime_error("Vertex exists");
            }
        } catch (const runtime_error& e) {
            cout << e.what() << endl;
        }
    }

    void addEdge(const int from, const int to, double weight = 0.0) {
        if (vertices.find(from) == vertices.end())
            addVertex(from);

        if (vertices.find(to) == vertices.end())
            addVertex(to);

        vertices[from]->connections[vertices[to]] = weight;
    }

    void print() {
        for (auto const& vertex: vertices) {
            if (!vertex.second->connections.empty()) {
                cout << vertex.first << ": ";
                for (auto const& connections: vertex.second->connections) {
                    cout << "{" << connections.first->key << ", " << connections.second << "}" << ' ';
                }
                cout << endl;
            }
        }
    }
};


int main() {
    Graph graph;

    graph.addEdge(1, 2);
    graph.print();
}
