#include <bits/stdc++.h>
using namespace std;

long long min_swaps_circular(const vector<int>& nums, int k){
    int n = (int)nums.size();
    vector<int> pos; pos.reserve(n);
    for(int i=0;i<n;++i) if(nums[i]==1) pos.push_back(i);
    int m = (int)pos.size();
    if(k==0 || k==1) return 0;
    if(m < k) return -1;
    vector<long long> pos2; pos2.reserve(2*m);
    for(int x: pos) pos2.push_back(x);
    for(int x: pos) pos2.push_back(x + n);
    vector<long long> adj(2*m);
    for(int i=0;i<2*m;++i) adj[i] = pos2[i] - i;
    vector<long long> pref(2*m+1,0);
    for(int i=0;i<2*m;++i) pref[i+1]=pref[i]+adj[i];
    long long ans = LLONG_MAX;
    for(int s=0; s<m; ++s){
        int e = s + k - 1;
        int mid = (s + e) / 2;
        long long med = adj[mid];
        long long left_sum = med * (mid - s) - (pref[mid] - pref[s]);
        long long right_sum = (pref[e+1] - pref[mid+1]) - med * (e - mid);
        long long cost = left_sum + right_sum;
        if(k%2==0) cost -= 1LL*(k/2) * (k - k/2);
        ans = min(ans, cost);
    }
    return ans;
}

int main(){ ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << min_swaps_circular(vector<int>{1,0,1,0,1}, 2) << "\n"; // Expected 0
    return 0; }
