#include <bits/stdc++.h>
using namespace std;

int max_profit_k(vector<array<int,3>> jobs, int K){
    if(jobs.empty() || K<=0) return 0;
    sort(jobs.begin(), jobs.end(), [](auto &a, auto &b){return a[1]<b[1];});
    int n = (int)jobs.size();
    vector<int> ends(n); for(int i=0;i<n;++i) ends[i]=jobs[i][1];
    vector<int> prev(n);
    for(int i=0;i<n;++i){
        int s=jobs[i][0];
        int idx = int(upper_bound(ends.begin(), ends.end(), s) - ends.begin()) - 1;
        prev[i]=idx;
    }
    vector<int> dp_prev(n+1,0), dp_cur(n+1,0);
    for(int k=1;k<=K;++k){
        fill(dp_cur.begin(), dp_cur.end(), 0);
        for(int i=1;i<=n;++i){
            int s=jobs[i-1][0], e=jobs[i-1][1], p=jobs[i-1][2];
            int pick = p + (prev[i-1]>=0 ? dp_prev[prev[i-1]+1] : 0);
            dp_cur[i] = max(dp_cur[i-1], pick);
        }
        dp_prev.swap(dp_cur);
    }
    return dp_prev[n];
}

int main(){ ios::sync_with_stdio(false); cin.tie(nullptr);
    vector<array<int,3>> jobs = {{1,3,50},{2,4,10},{3,5,40},{3,6,70}};
    cout << max_profit_k(jobs,2) << "\n"; // Expected 120
    return 0; }
