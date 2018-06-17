#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using namespace std;

struct Segment {
    int start, end;

    bool operator<(const Segment& other) const {
        return end < other.end;
    }
};

vector<int> optimal_points(vector<Segment> &segments) {
    vector<int> points;
    sort(segments.begin(), segments.end());
    points.push_back(segments[0].end);
    for (size_t i = 1; i < segments.size(); ++i) {
        if (!(segments[i].start <= points.back() && segments[i].end >= points.back())) {
            points.push_back(segments[i].end);
        }
    }
    return points;
}

int main() {
    int n;
    cin >> n;
    vector<Segment> segments(n);
    for (size_t i = 0; i < segments.size(); ++i) {
        cin >> segments[i].start >> segments[i].end;
    }
    vector<int> points = optimal_points(segments);
    cout << points.size() << "\n";
    for (size_t i = 0; i < points.size(); ++i) {
        cout << points[i] << " ";
    }
}
