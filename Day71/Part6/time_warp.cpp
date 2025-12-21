#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    if (cin >> n) {
        vector<long long> t(n);
        long long max_time = 0;
        for (int i = 0; i < n; ++i) {
            cin >> t[i];
            if (t[i] > max_time) {
                max_time = t[i];
            }
        }
        // If n=0, 0.
        // If n=1, max(0, t[0])? Or just 0 if we don't wait?
        // Assuming we must satisfy the time constraint of the checkpoint we are at.
        cout << max_time << endl;
    }
    return 0;
}
