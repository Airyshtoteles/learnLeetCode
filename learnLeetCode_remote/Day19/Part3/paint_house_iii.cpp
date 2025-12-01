#include <bits/stdc++.h>
using namespace std;

// LC 1473 — Paint House III
// dp over houses, colors, neighborhoods

int minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target){
    const long long INF = (long long)1e15;
    vector<vector<long long>> dp_prev(n+1, vector<long long>(target+1, INF));
    // init for first house
    if (houses[0] != 0){
        int c = houses[0];
        dp_prev[c][1] = 0;
    } else {
        for (int c=1;c<=n;++c) dp_prev[c][1] = cost[0][c-1];
    }
    for (int i=1;i<m;++i){
        vector<vector<long long>> dp_cur(n+1, vector<long long>(target+1, INF));
        vector<int> allowed;
        if (houses[i] != 0) allowed = {houses[i]};
        else { allowed.resize(n); iota(allowed.begin(), allowed.end(), 1); }
        for (int c: allowed){
            long long add = (houses[i] == c ? 0 : (houses[i] != 0 ? 0 : cost[i][c-1]));
            for (int pc=1; pc<=n; ++pc){
                for (int k=1; k<=target; ++k){
                    long long prev = dp_prev[pc][k];
                    if (prev >= INF) continue;
                    if (c == pc){
                        dp_cur[c][k] = min(dp_cur[c][k], prev + add);
                    } else if (k+1 <= target){
                        dp_cur[c][k+1] = min(dp_cur[c][k+1], prev + add);
                    }
                }
            }
        }
        dp_prev.swap(dp_cur);
    }
    long long ans = INF;
    for (int c=1;c<=n;++c) ans = min(ans, dp_prev[c][target]);
    return ans>=INF ? -1 : (int)ans;
}

int main(){
    vector<int> houses = {0,0,0,0,0};
    vector<vector<int>> cost = {{1,10},{10,1},{10,1},{1,10},{5,1}};
    int m=5, n=2, target=3;
    cout << minCost(houses, cost, m, n, target) << "\n"; // 9
    return 0;
}
