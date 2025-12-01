#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    double new21Game(int n, int k, int maxPts) {
        if (k == 0 || n >= k - 1 + maxPts) return 1.0;
        vector<double> dp(n + 1, 0.0);
        dp[0] = 1.0;
        double window = 1.0; // sum of last maxPts dp[i] where i < k
        double res = 0.0;
        for (int x = 1; x <= n; ++x) {
            dp[x] = window / maxPts;
            if (x < k) window += dp[x];
            else res += dp[x];
            if (x - maxPts >= 0) {
                if (x - maxPts < k) window -= dp[x - maxPts];
            }
        }
        return res;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<tuple<int,int,int>> tests = {{10,1,10},{6,1,10},{21,17,10},{0,0,1}};
    Solution sol;
    for (auto [n,k,m] : tests) {
        cout << "(" << n << "," << k << "," << m << ") -> " << fixed << setprecision(6)
             << sol.new21Game(n,k,m) << "\n";
    }
    return 0;
}
