#include <bits/stdc++.h>
using namespace std;

// The Chrono Keys — functional graph along portals with time accumulation per visit.

bool can_reach_target(const vector<long long>& timeShift, const vector<int>& portal, long long target){
    int n = (int)timeShift.size();
    vector<int> nxt = portal;
    vector<int> seen_idx(n, -1);
    vector<long long> seen_time(n, 0);
    long long t = 0;
    int cur = 0, step = 0;
    while(cur != -1 && seen_idx[cur] == -1){
        seen_idx[cur] = step;
        t += timeShift[cur];
        seen_time[cur] = t;
        if(cur == n-1 && t == target) return true;
        cur = nxt[cur];
        ++step;
    }
    if(cur == -1) return false;
    int start = cur; long long start_time = seen_time[cur];
    // build cycle
    vector<int> cycle; long long C=0; int u = cur;
    do{ cycle.push_back(u); C += timeShift[u]; u = nxt[u]; }while(u != cur && u != -1);
    if(u == -1) return false; // degenerate
    // if n-1 in cycle, compute first b
    if(find(cycle.begin(), cycle.end(), n-1) != cycle.end()){
        long long tt = start_time; int v = start; long long b=-1;
        do{
            if(v == n-1){ b = tt; break; }
            v = nxt[v]; tt += timeShift[v];
        }while(v != start);
        if(b == -1) return false;
        if(C == 0) return b == target;
        long long diff = target - b;
        if(diff % C == 0 && diff / C >= 0) return true;
        return false;
    }
    return false;
}

int main(){
    vector<long long> ts = {3,-2,4,1}; vector<int> p = {1,2,3,-1};
    cout << (can_reach_target(ts,p,6) ? "true" : "false") << "\n";
    return 0;
}
