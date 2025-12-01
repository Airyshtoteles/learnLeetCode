#include <bits/stdc++.h>
using namespace std;

int min_moves_with_portals(vector<string> grid){
    int n = grid.size();
    pair<int,int> S{-1,-1}, T{-1,-1};
    unordered_map<char, vector<pair<int,int>>> portals;
    for(int r=0;r<n;++r){
        for(int c=0;c<(int)grid[r].size();++c){
            char ch = grid[r][c];
            if(ch=='S') S={r,c};
            else if(ch=='T') T={r,c};
            else if(ch>='A' && ch<='Z') portals[ch].push_back({r,c});
        }
    }
    if(S.first==-1 || T.first==-1) return -1;
    unordered_map<long long, pair<int,int>> tele; // map encoded position to its pair
    auto enc=[&](int r,int c){return ((long long)r<<32) ^ c;};
    for(auto &kv: portals){
        if(kv.second.size()==2){
            auto a=kv.second[0]; auto b=kv.second[1];
            tele[enc(a.first,a.second)] = b;
            tele[enc(b.first,b.second)] = a;
        }
    }
    auto inb=[&](int r,int c){return 0<=r && r<n && 0<=c && c<(int)grid[r].size();};
    queue<tuple<int,int,int>> q; q.emplace(S.first,S.second,0);
    unordered_set<long long> vis; vis.insert(enc(S.first,S.second));
    int dr[4]={1,-1,0,0}; int dc[4]={0,0,1,-1};
    while(!q.empty()){
        auto [r,c,d]=q.front(); q.pop();
        if(r==T.first && c==T.second) return d;
        for(int i=0;i<4;++i){
            int nr=r+dr[i], nc=c+dc[i];
            if(!inb(nr,nc)) continue;
            if(grid[nr][nc]=='#') continue;
            int pr=nr, pc=nc;
            char ch=grid[nr][nc];
            auto it = tele.find(enc(nr,nc));
            if(ch>='A' && ch<='Z' && it!=tele.end()){
                pr=it->second.first; pc=it->second.second;
            }
            long long key=enc(pr,pc);
            if(vis.count(key)) continue;
            vis.insert(key);
            q.emplace(pr,pc,d+1);
        }
    }
    return -1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> grid={"S.A",".#A","..T"};
    cout<<min_moves_with_portals(grid)<<"\n"; // Expected 4
    return 0;
}
