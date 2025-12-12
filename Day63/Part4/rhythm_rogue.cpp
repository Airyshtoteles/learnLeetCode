#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct Interval {
    int start, end;
};

bool compareIntervals(const Interval& a, const Interval& b) {
    if (a.end != b.end) return a.end < b.end;
    return a.start < b.start;
}

map<int, int> parent;

int find_set(int v) {
    if (parent.find(v) == parent.end()) return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    // We want a to point to b (where b is find(a+1))
    // Actually, we just set parent[a] = find(b)
    // But find(b) might be b itself.
    // In our logic: parent[x] = find(x+1).
    // So we don't need a generic union.
    // We just do: parent[x] = find_set(x + 1);
}

int main() {
    int n;
    if (!(cin >> n)) return 0;

    vector<int> t(n), d(n);
    for (int i = 0; i < n; ++i) cin >> t[i];
    for (int i = 0; i < n; ++i) cin >> d[i];

    vector<Interval> intervals(n);
    for (int i = 0; i < n; ++i) {
        intervals[i] = {t[i] - d[i], t[i] + d[i]};
    }

    sort(intervals.begin(), intervals.end(), compareIntervals);

    int count = 0;
    for (const auto& interval : intervals) {
        int slot = find_set(interval.start);
        if (slot <= interval.end) {
            count++;
            parent[slot] = find_set(slot + 1);
        }
    }

    cout << count << endl;

    return 0;
}
