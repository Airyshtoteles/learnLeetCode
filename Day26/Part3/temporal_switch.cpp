#include <bits/stdc++.h>
using namespace std;

int min_presses(int n, int m, const vector<vector<int>>& connections){
    vector<int> masks(n, 0);
    for(int i=0;i<n;++i){
        int mask = 0;
        for(int lamp: connections[i]) mask ^= (1 << lamp);
        masks[i] = mask;
    }
    int target = (1<<m) - 1;
    queue<int> q; q.push(0);
    vector<int> dist(1<<m, -1); dist[0] = 0;
    while(!q.empty()){
        int s = q.front(); q.pop();
        if(s == target) return dist[s];
        for(int i=0;i<n;++i){
            int ns = s ^ masks[i];
            if(dist[ns] == -1){
                dist[ns] = dist[s] + 1;
                q.push(ns);
            }
        }
    }
    return -1;
}

int main(){
    int n=3, m=3;
    vector<vector<int>> connections = {
        {0,1}, {1,2}, {0,2}
    };
    cout << min_presses(n, m, connections) << "\n"; // Expected 3
    return 0;
}
