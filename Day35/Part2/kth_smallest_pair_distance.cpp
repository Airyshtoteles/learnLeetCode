#include <bits/stdc++.h>
using namespace std;

long long count_pairs(const vector<int>& a, int d){
    long long cnt=0; int n=(int)a.size(); int j=0;
    for(int i=0;i<n;++i){
        while(j<n && a[j]-a[i]<=d) ++j;
        cnt += max(0, j - i - 1);
    }
    return cnt;
}

int smallest_distance_pair(vector<int> nums, int k){
    sort(nums.begin(), nums.end());
    int lo=0, hi=nums.back()-nums.front();
    while(lo<hi){
        int mid = lo + (hi-lo)/2;
        if(count_pairs(nums, mid) >= k) hi=mid; else lo=mid+1;
    }
    return lo;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << smallest_distance_pair(vector<int>{1,3,1}, 1) << "\n"; // Expected 0
    return 0;
}
