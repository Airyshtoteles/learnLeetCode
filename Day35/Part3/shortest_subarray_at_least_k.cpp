#include <bits/stdc++.h>
using namespace std;

int shortest_subarray(vector<int> nums, long long K){
    int n = (int)nums.size();
    vector<long long> P(n+1,0);
    for(int i=0;i<n;++i) P[i+1]=P[i]+nums[i];
    deque<int> dq;
    int ans = n+1;
    for(int i=0;i<=n;++i){
        while(!dq.empty() && P[i]-P[dq.front()]>=K){
            ans = min(ans, i - dq.front());
            dq.pop_front();
        }
        while(!dq.empty() && P[i] <= P[dq.back()]) dq.pop_back();
        dq.push_back(i);
    }
    return ans<=n?ans:-1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << shortest_subarray(vector<int>{2,-1,2}, 3) << "\n"; // Expected 3
    return 0;
}
