#include <bits/stdc++.h>
using namespace std;

vector<int> max_sum_of_three_subarrays(vector<int> nums, int k){
    int n = (int)nums.size();
    vector<int> win(n - k + 1);
    long long cur = 0;
    for(int i=0;i<k;++i) cur += nums[i];
    win[0] = (int)cur;
    for(int i=1;i<=n-k;++i){
        cur += nums[i+k-1] - nums[i-1];
        win[i] = (int)cur;
    }
    int m = (int)win.size();
    vector<int> left(m), right(m);
    int best = 0;
    for(int i=0;i<m;++i){
        if(win[i] > win[best]) best = i;
        left[i] = best;
    }
    best = m-1;
    for(int i=m-1;i>=0;--i){
        if(win[i] >= win[best]) best = i;
        right[i] = best;
    }
    vector<int> ans(3,-1);
    long long maxsum = -1;
    for(int mid=k; mid<=m-k-1; ++mid){
        int l = left[mid-k];
        int r = right[mid+k];
        long long s = (long long)win[l] + win[mid] + win[r];
        if(s > maxsum){ maxsum = s; ans = {l, mid, r}; }
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto res = max_sum_of_three_subarrays({1,2,1,2,6,7,5,1}, 2);
    cout << res[0] << "," << res[1] << "," << res[2] << "\n"; // Expected 0,3,5
    return 0;
}
