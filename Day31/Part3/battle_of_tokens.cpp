#include <bits/stdc++.h>
using namespace std;

int max_score_diff(vector<int>& a){
    int n=a.size(); if(!n) return 0;
    vector<vector<long long>> dp(n, vector<long long>(n, LLONG_MIN));
    for(int i=0;i<n;++i) dp[i][i]=a[i];
    for(int i=0;i+1<n;++i){
        dp[i][i+1] = max({ (long long)a[i]-a[i+1], (long long)a[i+1]-a[i], (long long)a[i]+a[i+1] });
    }
    for(int len=3; len<=n; ++len){
        for(int l=0; l+len-1<n; ++l){
            int r=l+len-1;
            long long best=LLONG_MIN;
            best=max(best, (long long)a[l] - dp[l+1][r]);
            best=max(best, (long long)a[l]+a[l+1] - ( (l+2<=r)? dp[l+2][r]:0 ) );
            best=max(best, (long long)a[r] - dp[l][r-1]);
            best=max(best, (long long)a[r]+a[r-1] - ( (l<=r-2)? dp[l][r-2]:0 ) );
            dp[l][r]=best;
        }
    }
    return (int)dp[0][n-1];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> nums={1,5,233,7};
    cout<<max_score_diff(nums)<<"\n"; // Expected 222
    return 0;
}
