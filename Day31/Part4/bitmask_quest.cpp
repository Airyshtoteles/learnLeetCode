#include <bits/stdc++.h>
using namespace std;

long long max_reward(vector<int> reward, vector<vector<int>> require){
    int n = reward.size();
    vector<int> need(n,0);
    for(int i=0;i<n;++i){
        int m=0; for(int p: require[i]) m|=1<<p; need[i]=m;
    }
    int N=1<<n; const long long NEG = -(1LL<<60);
    vector<long long> dp(N, NEG); dp[0]=0; long long ans=0;
    for(int mask=0; mask<N; ++mask){
        if(dp[mask]==NEG) continue; ans=max(ans, dp[mask]);
        for(int i=0;i<n;++i){
            if(mask>>i & 1) continue;
            if( (mask & need[i]) == need[i] ){
                int nmask = mask | (1<<i);
                dp[nmask] = max(dp[nmask], dp[mask] + reward[i]);
            }
        }
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> reward={3,5,2,10};
    vector<vector<int>> require={{},{0},{0},{1,2}};
    cout<<max_reward(reward, require)<<"\n"; // Expected 20
    return 0;
}
