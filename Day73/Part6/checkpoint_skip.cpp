#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    if (cin >> n) {
        if (n == 0) {
            cout << 0 << endl;
            return 0;
        }
        vector<long long> t(n);
        for (int i = 0; i < n; ++i) {
            cin >> t[i];
        }

        if (n <= 2) {
            // Cannot skip start (0) or end (n-1).
            // If n=1, time is t[0].
            // If n=2, time is max(t[0], t[1]).
            long long max_val = 0;
            for(long long val : t) max_val = max(max_val, val);
            cout << max_val << endl;
            return 0;
        }

        // We can skip one checkpoint in range [1, n-2].
        // The total time is max(t[0], t[n-1], max(t[1]...t[n-2] excluding skipped)).
        // To minimize this, we should skip the largest element in [1, n-2].
        // If we skip the largest, the new max is the second largest in that range.
        
        long long fixed_max = max(t[0], t[n-1]);
        
        // Find largest and second largest in middle
        long long max1 = -1;
        long long max2 = -1;
        
        for (int i = 1; i < n - 1; ++i) {
            if (t[i] > max1) {
                max2 = max1;
                max1 = t[i];
            } else if (t[i] > max2) {
                max2 = t[i];
            }
        }
        
        // If we skip max1, the remaining max is max2.
        // If range [1, n-2] was empty (handled by n<=2), max2 is -1.
        // If range had 1 element, max2 is -1.
        
        long long middle_max_after_skip = max2;
        
        // If middle_max_after_skip is -1 (meaning only 1 element in middle, and we skipped it),
        // then middle contribution is 0 (effectively).
        if (middle_max_after_skip == -1) middle_max_after_skip = 0;
        
        cout << max(fixed_max, middle_max_after_skip) << endl;
    }
    return 0;
}
