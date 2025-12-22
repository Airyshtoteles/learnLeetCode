#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main() {
    int n;
    if (cin >> n) {
        vector<int> seeds(n);
        for (int i = 0; i < n; ++i) {
            cin >> seeds[i];
        }

        if (n == 0) {
            cout << 0 << endl;
            return 0;
        }

        // Map to store max length ending with value v
        map<int, int> dp;
        int global_max = 0;

        for (int x : seeds) {
            int current_max = 0;
            // Find divisors
            for (int i = 1; i * i <= x; ++i) {
                if (x % i == 0) {
                    // Divisor i
                    if (dp.count(i)) {
                        current_max = max(current_max, dp[i]);
                    }
                    // Divisor x/i
                    int d2 = x / i;
                    if (d2 != i) {
                        if (dp.count(d2)) {
                            current_max = max(current_max, dp[d2]);
                        }
                    }
                }
            }
            dp[x] = current_max + 1;
            global_max = max(global_max, dp[x]);
        }

        cout << global_max << endl;
    }
    return 0;
}
