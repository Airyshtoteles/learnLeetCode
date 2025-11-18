#include <bits/stdc++.h>
using namespace std;

int min_changes_split_k_palindromes(const string &s, int K) {
    int n = (int)s.size();
    vector<vector<int>> cost(n, vector<int>(n, 0));
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i + len - 1 < n; ++i) {
            int j = i + len - 1;
            cost[i][j] = (s[i] == s[j] ? 0 : 1) + (i+1 <= j-1 ? cost[i+1][j-1] : 0);
        }
    }
    const int INF = 1e9;
    vector<vector<int>> dp(K+1, vector<int>(n+1, INF));
    dp[0][0] = 0;
    for (int k = 1; k <= K; ++k) {
        for (int i = 1; i <= n; ++i) {
            int best = INF;
            for (int t = k-1; t <= i-1; ++t) { // last segment t..i-1
                int c = (t == i-1 ? 0 : cost[t][i-1]);
                best = min(best, dp[k-1][t] + c);
            }
            dp[k][i] = best;
        }
    }
    return dp[K][n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << min_changes_split_k_palindromes("abc", 2) << "\n"; // 1
    cout << min_changes_split_k_palindromes("aabbc", 3) << "\n"; // expected 1
    return 0;
}
