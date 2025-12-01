#include <bits/stdc++.h>
using namespace std;

using Grid = vector<vector<int>>;

static vector<int> gravity_down(const vector<int>& col){
    int n = col.size();
    vector<int> vals; vals.reserve(n);
    for(int v: col) if(v!=0) vals.push_back(v);
    vector<int> res(n,0);
    for(int i=0;i<(int)vals.size();++i) res[n-(int)vals.size()+i]=vals[i];
    return res;
}

static tuple<vector<int>, int, bool> explode_column(const vector<int>& col){
    int n=col.size();
    vector<char> mark(n,0);
    int destroyed=0; int i=0;
    while(i<n){
        int j=i;
        while(j<n && col[j]==col[i] && col[i]!=0) ++j;
        int run=j-i;
        if(col[i]!=0 && run>=3){
            for(int t=i;t<j;++t) mark[t]=1;
            destroyed+=run;
        }
        i = (j>i? j : i+1);
    }
    vector<int> newc(n);
    bool any=false;
    for(int r=0;r<n;++r){
        if(mark[r]){ newc[r]=0; any=true; }
        else newc[r]=col[r];
    }
    return {newc, destroyed, any};
}

static pair<Grid,int> simulate_column(const Grid& grid, int c){
    int n=grid.size();
    vector<int> col(n);
    for(int r=0;r<n;++r) col[r]=grid[r][c];
    int total=0; bool changed=true;
    while(changed){
        col = gravity_down(col);
        auto [nc, destroyed, exploded] = explode_column(col);
        col.swap(nc);
        total += destroyed;
        changed = exploded && destroyed>0;
    }
    Grid ng=grid;
    for(int r=0;r<n;++r) ng[r][c]=col[r];
    return {ng,total};
}

struct GridHash{
    size_t operator()(Grid const& g) const noexcept{
        size_t h=1469598103934665603ull;
        for(auto const& row: g){
            for(int v: row){ h ^= (size_t)(v+0x9e3779b97f4a7c15ull); h *= 1099511628211ull; }
        }
        return h;
    }
};
struct GridEq{ bool operator()(Grid const& a, Grid const& b) const noexcept{ return a==b; } };

class Solver{
    unordered_map<pair<Grid,int>, int, function<size_t(pair<Grid,int> const&)>, function<bool(pair<Grid,int> const&, pair<Grid,int> const&)>> memo;
public:
    Solver(){
        auto h = [](pair<Grid,int> const& p){
            GridHash gh; size_t x=gh(p.first); return x*1315423911u + p.second; };
        auto e = [](pair<Grid,int> const& a, pair<Grid,int> const& b){ return a.first==b.first && a.second==b.second; };
        memo = decltype(memo)(0, h, e);
    }
    int dfs(const Grid& g, int k){
        auto key = make_pair(g,k);
        auto it = memo.find(key); if(it!=memo.end()) return it->second;
        if(k==0) return memo[key]=0;
        int n=g.size(); int best=0;
        for(int c=0;c<n;++c){
            auto [ng, got] = simulate_column(g, c);
            best = max(best, got + dfs(ng, k-1));
        }
        return memo[key]=best;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Grid grid={{1,2,1},{2,1,2},{1,2,1}}; int k=3;
    Solver s; cout<<s.dfs(grid,k)<<"\n"; // Example target: 6
    return 0;
}
