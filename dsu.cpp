#include <iostream>
#include <vector>

using namespace std;

class UnionSet {
public:
    UnionSet(const size_t size) {
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

    void Print() {
        for (size_t i = 0; i < Parent.size(); ++i) {
            cout << i << ' ' << Parent[i] << endl;
        }
    }
private:
    vector<int> Parent;
    vector<int> Rank;
};


int main() {
    UnionSet unionSet(3);

    for (size_t i = 0; i < 3; ++i)
        unionSet.MakeSet(i);

    unionSet.Union(0, 2);
    unionSet.Union(1, 2);
    unionSet.Union(0, 1);

    unionSet.Print();

    return 0;
}
