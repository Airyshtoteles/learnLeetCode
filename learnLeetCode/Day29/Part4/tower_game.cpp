// Tower Game: Destruction Order
// Given n towers with heights. One shot destroys the chosen tower and also its immediate
// neighbors that are strictly smaller than it. Find the minimum number of shots to destroy all.
//
// Input:
// - First line: n
// - Second line: n integers for heights
//
// Output:
// - Single integer: minimal number of shots
//
// Approach:
// - Sort indices by height descending.
// - Keep a removed[] array. Iterate in that order; when you pick an index not yet removed,
//   increment shots, remove it, and remove strictly smaller immediate neighbors if present.
// - O(n log n).

#include <bits/stdc++.h>
using namespace std;

long long min_shots(const vector<long long>& h) {
    int n = (int)h.size();
    if (n == 0) return 0;
    vector<bool> removed(n, false);
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b){
        if (h[a] != h[b]) return h[a] > h[b];
        return a < b; // stable by index if equal height
    });
    long long shots = 0;
    for (int i : order) {
        if (removed[i]) continue;
        shots++;
        removed[i] = true;
        if (i - 1 >= 0 && !removed[i - 1] && h[i - 1] < h[i]) removed[i - 1] = true;
        if (i + 1 < n && !removed[i + 1] && h[i + 1] < h[i]) removed[i + 1] = true;
    }
    return shots;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) {
        vector<long long> demo = {3, 1, 4, 1, 5};
        cout << min_shots(demo) << "\n";
        return 0;
    }
    vector<long long> h(n);
    for (int i = 0; i < n; ++i) cin >> h[i];
    cout << min_shots(h) << "\n";
    return 0;
}
