#include <bits/stdc++.h>
using namespace std;

// LC 2218 — Maximum Value of K Coins From Piles
// 1D DP with prefix sums per pile

int maxValueOfCoins(vector<vector<int>>& piles, int k){
    vector<int> dp(k+1, 0);
    for (auto &pile : piles){
        vector<int> pref(1,0);
        int r=0; for (int v: pile){ r+=v; pref.push_back(r);} // pref[0]=0
        int m = min((int)pile.size(), k);
        vector<int> ndp = dp;
        for (int j=1;j<=k;++j){
            int best = dp[j];
            int limit = min(m, j);
            for (int x=1;x<=limit;++x){
                best = max(best, dp[j-x] + pref[x]);
            }
            ndp[j] = best;
        }
        dp.swap(ndp);
    }
    return dp[k];
}

int main(){
    vector<vector<int>> piles = {{1,100,3},{7,8,9}};
    cout << maxValueOfCoins(piles, 2) << "\n"; // 101
    return 0;
}
