#include <bits/stdc++.h>
using namespace std;

int max_coins(vector<int> nums){
    vector<int> val; val.reserve(nums.size()+2);
    val.push_back(1); for(int x: nums) val.push_back(x); val.push_back(1);
    int n = (int)val.size();
    vector<vector<int>> dp(n, vector<int>(n,0));
    for(int len=2; len<n; ++len){
        for(int l=0; l+len<n; ++l){
            int r=l+len; int best=0;
            for(int k=l+1; k<r; ++k){
                best = max(best, dp[l][k] + val[l]*val[k]*val[r] + dp[k][r]);
            }
            dp[l][r] = best;
        }
    }
    return dp[0][n-1];
}

int main(){ ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << max_coins(vector<int>{3,1,5,8}) << "\n"; // Expected 167
    return 0; }
