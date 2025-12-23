#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// DP for min length
// dp[i][j] = min length of s[i..j]
int dp[105][105];
string s;

int solve(int i, int j) {
    if (i > j) return 0;
    if (i == j) return 1;
    if (dp[i][j] != -1) return dp[i][j];

    int min_len = j - i + 1;

    // Split
    for (int k = i; k < j; ++k) {
        min_len = min(min_len, solve(i, k) + solve(k + 1, j));
    }

    // Compress
    // If s[i..j] is a repetition of some prefix of length L
    int len = j - i + 1;
    for (int L = 1; L <= len / 2; ++L) {
        if (len % L == 0) {
            bool ok = true;
            for (int k = 0; k < len; ++k) {
                if (s[i + k] != s[i + (k % L)]) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                min_len = min(min_len, solve(i, i + L - 1));
            }
        }
    }

    return dp[i][j] = min_len;
}

int main() {
    if (cin >> s) {
        int n = s.length();
        for(int i=0; i<n; ++i)
            for(int j=0; j<n; ++j)
                dp[i][j] = -1;
                
        int min_len = solve(0, n - 1);
        cout << (n - min_len) << endl;
    }
    return 0;
}
