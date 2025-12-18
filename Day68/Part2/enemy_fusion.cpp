#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    if (cin >> n) {
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        if (n == 0) {
            cout << 0 << endl;
            return 0;
        }

        // dp[i][j] = min strength for range i..j
        vector<vector<int>> dp(n, vector<int>(n));

        for (int i = 0; i < n; ++i) {
            dp[i][i] = a[i];
        }

        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i <= n - len; ++i) {
                int j = i + len - 1;
                dp[i][j] = 2e9; // Infinity
                for (int k = i; k < j; ++k) {
                    int val = max(dp[i][k], dp[k + 1][j]) + 1;
                    if (val < dp[i][j]) {
                        dp[i][j] = val;
                    }
                }
            }
        }

        cout << dp[0][n - 1] << endl;
    }
    return 0;
}
