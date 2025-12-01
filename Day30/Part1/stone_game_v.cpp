#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int stoneGameV(vector<int>& stoneValue) {
        int n = (int)stoneValue.size();
        vector<long long> prefix(n+1, 0);
        for (int i = 0; i < n; ++i) prefix[i+1] = prefix[i] + stoneValue[i];
        auto range_sum = [&](int l, int r){ return prefix[r+1] - prefix[l]; };
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int len = 2; len <= n; ++len) {
            for (int l = 0; l + len - 1 < n; ++l) {
                int r = l + len - 1;
                int best = 0;
                for (int k = l; k < r; ++k) {
                    long long left = range_sum(l, k);
                    long long right = range_sum(k+1, r);
                    if (left < right) {
                        best = max(best, (int)(left + dp[l][k]));
                    } else if (left > right) {
                        best = max(best, (int)(right + dp[k+1][r]));
                    } else {
                        best = max(best, (int)(left + max(dp[l][k], dp[k+1][r])));
                    }
                }
                dp[l][r] = best;
            }
        }
        return dp[0][n-1];
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<int>> tests = {
        {6,2,3,4,5,5},
        {7,7,7,7,7,7,7},
        {4},
        {1,2},
        {3,8,4,5,2}
    };
    Solution sol;
    for (auto arr : tests) {
        cout << "[";
        for (size_t i = 0; i < arr.size(); ++i) {
            if (i) cout << ", ";
            cout << arr[i];
        }
        cout << "] -> " << sol.stoneGameV(arr) << "\n";
    }
    return 0;
}
