#include <bits/stdc++.h>
using namespace std;

// LC 1547 — Minimum Cost to Cut a Stick
// Interval DP (top-down with memoization)

int minCost(int n, vector<int>& cuts){
    cuts.push_back(0); cuts.push_back(n);
    sort(cuts.begin(), cuts.end());
    int m = cuts.size();
    vector<vector<int>> memo(m, vector<int>(m, -1));
    function<int(int,int)> dp = [&](int l, int r)->int{
        if (l + 1 >= r) return 0;
        if (memo[l][r] != -1) return memo[l][r];
        int best = INT_MAX;
        for (int i = l + 1; i < r; ++i){
            int cost = cuts[r] - cuts[l] + dp(l,i) + dp(i,r);
            best = min(best, cost);
        }
        return memo[l][r] = best;
    };
    return dp(0, m-1);
}

int main(){
    vector<int> cuts = {1,3,4,5};
    cout << minCost(7, cuts) << "\n"; // 16
    return 0;
}
