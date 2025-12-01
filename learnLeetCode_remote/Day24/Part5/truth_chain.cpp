#include <bits/stdc++.h>
using namespace std;

// The Truth Chain
// Candidate must have outdegree 0 and be reachable (in reverse graph) from all others.

int master_of_truth(int n, const vector<pair<int,int>>& trust){
    vector<vector<int>> gr(n); vector<int> outdeg(n,0);
    for(auto [a,b]: trust){ --a; --b; gr[b].push_back(a); outdeg[a]++; }
    vector<int> cand; for(int i=0;i<n;++i) if(outdeg[i]==0) cand.push_back(i);
    for(int c: cand){
        vector<char> vis(n,0); queue<int> q; q.push(c); vis[c]=1; int seen=1;
        while(!q.empty()){
            int u=q.front(); q.pop();
            for(int v: gr[u]) if(!vis[v]){ vis[v]=1; ++seen; q.push(v); }
        }
        if(seen==n) return c+1;
    }
    return -1;
}

int main(){
    int n=4; vector<pair<int,int>> trust={{1,3},{2,3},{3,4}};
    cout << master_of_truth(n, trust) << "\n"; // 4
    return 0;
}
