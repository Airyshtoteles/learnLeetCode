#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    if (cin >> n) {
        vector<long long> r(n);
        for (int i = 0; i < n; ++i) cin >> r[i];

        sort(r.begin(), r.end());

        long long current_time = 0;
        long long total_time = 0;

        for (int i = 0; i < n; ++i) {
            if (r[i] > current_time) {
                current_time = r[i];
            } else {
                current_time++;
            }
            total_time += current_time;
        }

        cout << total_time << endl;
    }
    return 0;
}
