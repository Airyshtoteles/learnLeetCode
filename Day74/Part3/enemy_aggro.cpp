#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Interval {
    int start;
    int end;
};

bool compareIntervals(const Interval& a, const Interval& b) {
    return a.end < b.end;
}

int main() {
    int n;
    if (cin >> n) {
        if (n == 0) {
            cout << 0 << endl;
            return 0;
        }
        vector<int> t(n);
        for (int i = 0; i < n; ++i) cin >> t[i];
        vector<int> d(n);
        for (int i = 0; i < n; ++i) cin >> d[i];

        vector<Interval> intervals(n);
        for (int i = 0; i < n; ++i) {
            intervals[i].start = t[i];
            intervals[i].end = t[i] + d[i];
        }

        sort(intervals.begin(), intervals.end(), compareIntervals);

        int count = 0;
        int last_end = -1; // Assuming time >= 0

        for (const auto& interval : intervals) {
            if (interval.start >= last_end) {
                count++;
                last_end = interval.end;
            }
        }

        cout << count << endl;
    }
    return 0;
}
