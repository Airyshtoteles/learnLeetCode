#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main() {
    int n;
    if (cin >> n) {
        vector<int> power(n);
        vector<int> duration(n);
        for (int i = 0; i < n; ++i) cin >> power[i];
        for (int i = 0; i < n; ++i) cin >> duration[i];

        map<int, int> max_durations;
        for (int i = 0; i < n; ++i) {
            if (duration[i] > max_durations[power[i]]) {
                max_durations[power[i]] = duration[i];
            }
        }

        long long total_duration = 0;
        for (auto const& [p, d] : max_durations) {
            total_duration += d;
        }

        cout << total_duration << endl;
    }
    return 0;
}
