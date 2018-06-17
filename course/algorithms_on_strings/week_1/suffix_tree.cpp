#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cstring>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;

class Suffix {
public:
    int OriginNode;
    int FirstCharIndex;
    int LastCharIndex;
    Suffix(int node, int start, int stop)
        : OriginNode(node)
        , FirstCharIndex(start)
        , LastCharIndex(stop) {};
    bool IsExplicit() {
        return FirstCharIndex > LastCharIndex;
    }
    bool IsImplicit() {
        return LastCharIndex >= FirstCharIndex;
    }
    void Canonize();

};

class Edge {
public:
    int FirstCharIndex;
    int LastCharIndex;
    int StartNode;
    int EndNode;

    Edge() : StartNode(-1) {};
    Edge(int start, int stop, int parentNode);

    void Insert();
    void Remove();
    int SplitEdge(Suffix &suffix);
    static Edge Find(int node, int c);
    static int Hash(int node, int c);
};

class Node {
public:
    int SuffixNode;
    Node()
        :SuffixNode(-1) {};
    static int Count;
};

const int MAX_LENGTH = 6000;
const int HASH_TABLE_SIZE = 6607;

char BUFFER[MAX_LENGTH];
int N;

Edge Edges[HASH_TABLE_SIZE];

int Node::Count = 1;
Node Nodes[MAX_LENGTH * 2];

void Suffix::Canonize() {
    if (!IsExplicit()) {
        Edge edge = Edge::Find(OriginNode, BUFFER[FirstCharIndex]);
        int edgeSpan = edge.LastCharIndex - edge.FirstCharIndex;
        while (edgeSpan <= (LastCharIndex - FirstCharIndex)) {
            FirstCharIndex = FirstCharIndex + edgeSpan + 1;
            OriginNode = edge.EndNode;
            if (FirstCharIndex <= LastCharIndex) {
                edge = Edge::Find(edge.EndNode, BUFFER[FirstCharIndex]);
                edgeSpan = edge.LastCharIndex - edge.FirstCharIndex;
            }
        }
    }
}

Edge::Edge(int start, int stop, int parentNode) {
    FirstCharIndex = start;
    LastCharIndex = stop;
    StartNode = parentNode;
    EndNode = Node::Count++;
}

void Edge::Insert() {
    int h = Hash(StartNode, BUFFER[FirstCharIndex]);
    while (Edges[h].StartNode != -1) {
        h = ++h % HASH_TABLE_SIZE;
    }
    Edges[h] = *this;
}

void Edge::Remove() {
    int h = Hash(StartNode, BUFFER[FirstCharIndex]);
    while (Edges[h].StartNode != StartNode ||
           Edges[h].FirstCharIndex != FirstCharIndex) {
        h = ++h % HASH_TABLE_SIZE;
    }

    while (true) {
        Edges[h].StartNode = -1;
        int g = h;
        while (true) {
            h = ++h % HASH_TABLE_SIZE;
            if (Edges[h].StartNode == -1) {
                return;
            }
            int r = Hash(Edges[h].StartNode, BUFFER[Edges[h].FirstCharIndex]);
            if ((h >= r && r > g) || (r > g && g > h) || (g > h && h >= r)) {
                continue;
            }
            break;
        }
        Edges[g] = Edges[h];
    }
}

int Edge::SplitEdge(Suffix &suffix) {
    Remove();
    Edge *newEdge = new Edge(
        FirstCharIndex,
        FirstCharIndex + suffix.LastCharIndex - suffix.FirstCharIndex,
        suffix.OriginNode
    );
    newEdge->Insert();
    Nodes[newEdge->EndNode].SuffixNode = suffix.OriginNode;
    FirstCharIndex += suffix.LastCharIndex - suffix.FirstCharIndex  + 1;
    StartNode = newEdge->EndNode;
    Insert();
    return newEdge->EndNode;
}

Edge Edge::Find(int node, int c) {
    int h = Hash(node, c);
    while (true) {
        if (Edges[h].StartNode == node) {
            if (c == BUFFER[Edges[h].FirstCharIndex]) {
                return Edges[h];
            }
        }
        if (Edges[h].StartNode == -1) {
            return Edges[h];
        }
        h = ++h % HASH_TABLE_SIZE;
    }
}

int Edge::Hash(int node, int c) {
    return ((node << 8) + c) % HASH_TABLE_SIZE;
}

void AddPrefix(Suffix &active, int lastCharIndex) {
    int parentNode;
    int lastParentNode = -1;

    while (true) {
        Edge edge;
        parentNode = active.OriginNode;

        if (active.IsExplicit()) {
            edge = Edge::Find(active.OriginNode, BUFFER[lastCharIndex]);
            if (edge.StartNode != -1) {
                break;
            }
        } else {
            edge = Edge::Find(active.OriginNode, BUFFER[active.FirstCharIndex]);
            int span = active.LastCharIndex - active.FirstCharIndex;
            if (BUFFER[edge.FirstCharIndex + span + 1] == BUFFER[lastCharIndex]) {
                break;
            }
            parentNode = edge.SplitEdge(active);
        }

        Edge *newEdge = new Edge(lastCharIndex, N, parentNode);
        newEdge->Insert();
        if (lastParentNode > 0) {
            Nodes[lastParentNode].SuffixNode = parentNode;
        }
        lastParentNode = parentNode;

        if (active.OriginNode == 0) {
            ++active.FirstCharIndex;
        } else {
            active.OriginNode = Nodes[active.OriginNode].SuffixNode;
        }
        active.Canonize();
    }

    if (lastParentNode > 0) {
        Nodes[lastParentNode].SuffixNode = parentNode;
    }
    ++active.LastCharIndex;
    active.Canonize();
};

void DumpEdges(int n) {
    for (size_t i = 0; i < HASH_TABLE_SIZE; ++i) {
        Edge *edge = Edges + i;
        if (edge->StartNode == -1) {
            continue;
        }

        int end;
        if (n > edge->LastCharIndex) {
            end = edge->LastCharIndex;
        } else {
            end = n;
        }

        for (size_t j = edge->FirstCharIndex; j <= end; ++j) {
            cout << BUFFER[j];
        }
        cout << endl;
    }
}

// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding
// substrings of the text) in any order.
vector<string> ComputeSuffixTreeEdges(const string& text) {
    vector<string> result;
    text.copy(BUFFER, sizeof BUFFER);
    BUFFER[text.size()] = '\0';
    N = std::strlen(BUFFER) - 1;
    Suffix active(0, 0, -1);

    for (size_t i = 0; i <= N; ++i) {
        AddPrefix(active, i);
    }

    DumpEdges(N);
    return result;
}

int main() {
    string text;
    cin >> text;
    vector<string> edges = ComputeSuffixTreeEdges(text);
    for (int i = 0; i < edges.size(); ++i) {
        cout << edges[i] << endl;
    }
    return 0;
}
