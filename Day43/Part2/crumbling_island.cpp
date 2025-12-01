#include <bits/stdc++.h>
using namespace std;

struct State {
    int t, r, c;
    bool operator>(const State& other) const {
        return t > other.t;
    }
};

int min_time_survival(const vector<vector<int>>& times) {
    if (times.empty()) return -1;
    int n = times.size();
    if (times[0][0] <= 0) return -1;
    
    vector<vector<int>> dist(n, vector<int>(n, 1e9));
    priority_queue<State, vector<State>, greater<State>> pq;
    
    dist[0][0] = 0;
    pq.push({0, 0, 0});
    
    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};
    
    while(!pq.empty()) {
        State cur = pq.top(); pq.pop();
        
        if (cur.t > dist[cur.r][cur.c]) continue;
        if (cur.r == n-1 && cur.c == n-1) return cur.t;
        
        for(int i=0; i<4; ++i) {
            int nr = cur.r + dr[i];
            int nc = cur.c + dc[i];
            
            if(nr >= 0 && nr < n && nc >= 0 && nc < n) {
                int nt = cur.t + 1;
                if (nt < times[nr][nc]) {
                    if (nt < dist[nr][nc]) {
                        dist[nr][nc] = nt;
                        pq.push({nt, nr, nc});
                    }
                }
            }
        }
    }
    
    return -1;
}

int main() {
    vector<vector<int>> times = {
        {5, 2, 1},
        {5, 4, 3},
        {1, 5, 5}
    };
    cout << min_time_survival(times) << endl;
    return 0;
}
