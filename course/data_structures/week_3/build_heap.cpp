#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;


class HeapBuilder {
private:
    vector<int> heap;
    vector< pair<int, int> > swaps;

    int GetLeftChild(int parent_index) {
        return 2 * parent_index + 1;
    }

    int GetRightChild(int parent_index) {
        return 2 * parent_index + 2;
    }

    int GetParent(int child_index) {
        if (child_index % 2 == 0)
            return child_index / 2 - 1;
        else
            return child_index / 2;
    }

    void WriteResponse() const {
        cout << swaps.size() << "\n";
        for (int i = 0; i < swaps.size(); ++i) {
            cout << swaps[i].first << " " << swaps[i].second << "\n";
        }
    }

    void ReadData() {
        int n;
        cin >> n;
        heap.resize(n);

        for(int i = 0; i < n; ++i)
            cin >> heap[i];
    }

    void GenerateSwaps() {
        swaps.clear();
        // The following naive implementation just sorts
        // the given sequence using selection sort algorithm
        // and saves the resulting sequence of swaps.
        // This turns the given array into a heap,
        // but in the worst case gives a quadratic number of swaps.
        //
        // TODO: replace by a more efficient implementation
        for (int i = 0; i < heap.size(); ++i)
            for (int j = i + 1; j < heap.size(); ++j) {
                if (heap[i] > heap[j]) {
                    swap(heap[i], heap[j]);
                    swaps.push_back(make_pair(i, j));
                }
            }
    }

    void GenerateSwapsN() {
        swaps.clear();

        for (int i = size() / 2; i >= 0; --i)
            SiftDown(i);
    }

    void SiftDown(int parent_index) {
        int left_child_index = GetLeftChild(parent_index);
        int right_child_index = GetRightChild(parent_index);

        int min_value_index = [](const vector<pair<int, int> > &v) {
            return min_element(v.begin(), v.end())->second;
        }(
            {
                {
                    heap[parent_index],
                    parent_index
                },
                {
                    left_child_index < size() ? heap[left_child_index] : INT_MAX,
                    left_child_index
                },
                {
                    right_child_index < size() ? heap[right_child_index]: INT_MAX,
                    right_child_index
                }
            }
        );

        if (min_value_index != parent_index) {
            swap(heap[parent_index], heap[min_value_index]);
            swaps.push_back(make_pair(parent_index, min_value_index));
            SiftDown(min_value_index);
        }
    }

public:
    void Solve() {
        ReadData();
        GenerateSwapsN();
        WriteResponse();
    }

    unsigned int size() {
        return heap.size();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    HeapBuilder heap_builder;
    heap_builder.Solve();
    return 0;
}
