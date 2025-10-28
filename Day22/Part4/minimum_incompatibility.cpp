#include <bits/stdc++.h>
using namespace std;

// LC 1681 — Minimum Incompatibility
// DP over bitmask selecting valid groups of size n/k

int minimumIncompatibility(vector<int> nums, int k){
    int n = (int)nums.size();
    int group = n / k;

    // Early pruning: frequency of any value > k -> impossible
    unordered_map<int,int> cnt;
    for(int x: nums) cnt[x]++;
    for(auto &p: cnt) if(p.second > k) return -1;

    // Precompute valid subsets of indices of size 'group' with unique values and their cost
    vector<int> idx(n); iota(idx.begin(), idx.end(), 0);
    unordered_map<int,int> cost; // mask -> incompatibility

    // Enumerate all combinations of indices of size 'group'
    vector<int> choose(group);
    // We'll use combinations by bitmask: iterate all masks of size 'group'
    int total = 1 << n;
    for(int m=0; m<total; ++m){
        if(__builtin_popcount((unsigned)m) != group) continue;
        // collect values and check uniqueness
        int seen = 0; // we'll map values via map to ensure uniqueness; simpler: use unordered_set
        vector<int> vals; vals.reserve(group);
        bool ok = true;
        int mn = INT_MAX, mx = INT_MIN;
        unordered_set<int> seenVals; seenVals.reserve(group*2);
        for(int i=0;i<n;++i){
            if(m & (1<<i)){
                int v = nums[i];
                if(seenVals.count(v)){ ok=false; break; }
                seenVals.insert(v);
                mn = min(mn, v); mx = max(mx, v);
            }
        }
        if(!ok) continue;
        cost[m] = mx - mn;
    }

    const int INF = 1e9;
    vector<int> dp(total, INF);
    dp[0] = 0;

    for(int mask=0; mask<total; ++mask){
        if(dp[mask] == INF) continue;
        if(mask == total-1) continue;
        // find first free bit
        int i=0; while(i<n && (mask & (1<<i))) ++i;
        int rem = ((1<<n)-1) ^ mask;
        // iterate submasks of rem that include i
        for(int sub = rem; sub; sub = (sub-1) & rem){
            if(!(sub & (1<<i))) continue;
            if(__builtin_popcount((unsigned)sub) != group) continue;
            auto it = cost.find(sub);
            if(it == cost.end()) continue;
            dp[mask | sub] = min(dp[mask | sub], dp[mask] + it->second);
        }
    }

    return dp[total-1] >= INF ? -1 : dp[total-1];
}

int main(){
    cout << minimumIncompatibility({1,2,1,4}, 2) << "\n"; // 4
    cout << minimumIncompatibility({6,3,8,1,3,1,2,2}, 4) << "\n"; // 6
    return 0;
}
