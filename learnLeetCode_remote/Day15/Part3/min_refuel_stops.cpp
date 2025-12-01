#include <bits/stdc++.h>
using namespace std;

// LeetCode 871 — Minimum Number of Refueling Stops
// Greedy with max-heap of reachable stations' fuel.

int minRefuelStops(int target, int startFuel, vector<vector<int>> stations){
    long long fuel = startFuel;
    int ans = 0, i = 0, n = stations.size();
    priority_queue<int> pq;
    while (fuel < target){
        while (i < n && stations[i][0] <= fuel){
            pq.push(stations[i][1]);
            ++i;
        }
        if (pq.empty()) return -1;
        fuel += pq.top(); pq.pop();
        ++ans;
    }
    return ans;
}

int main(){
    cout << minRefuelStops(100, 10, {{10,60},{20,30},{30,30},{60,40}}) << "\n"; // 2
    return 0;
}
