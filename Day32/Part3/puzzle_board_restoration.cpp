#include <bits/stdc++.h>
using namespace std;

static string goal = "123456780";

static string serialize(const vector<vector<int>>& b){
    string s; s.reserve(9);
    for(auto &row: b) for(int v: row) s.push_back(char('0'+v));
    return s;
}

static int inversions(const string &s){
    vector<int> a; a.reserve(8);
    for(char ch: s) if(ch!='0') a.push_back(ch-'0');
    int inv=0; for(int i=0;i<(int)a.size();++i) for(int j=i+1;j<(int)a.size();++j) if(a[i]>a[j]) ++inv; return inv;
}

static bool solvable(const string& s){ return inversions(s)%2==0; }

static pair<int,int> pos_of(char v){ int d=v-'0'; return {(d-1)/3,(d-1)%3}; }

static int manhattan(const string& s){
    int dist=0;
    for(int i=0;i<9;++i){ char ch=s[i]; if(ch=='0') continue; auto [gr,gc]=pos_of(ch); int r=i/3,c=i%3; dist+=abs(r-gr)+abs(c-gc);} return dist;
}

int min_moves_8puzzle(const vector<vector<int>>& board){
    string start=serialize(board);
    if(start==goal) return 0;
    if(!solvable(start)) return -1;
    struct Node{int f,g; string s; bool operator>(Node const& o) const {return f>o.f;}};
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    unordered_map<string,int> seen;
    int h=manhattan(start); pq.push({h,0,start}); seen[start]=0;
    int dr[4]={-1,1,0,0}, dc[4]={0,0,-1,1};
    while(!pq.empty()){
        auto cur=pq.top(); pq.pop();
        if(cur.s==goal) return cur.g;
        if(seen[cur.s] < cur.g) continue;
        int z=cur.s.find('0'); int zr=z/3, zc=z%3;
        for(int i=0;i<4;++i){ int nr=zr+dr[i], nc=zc+dc[i]; if(nr<0||nr>=3||nc<0||nc>=3) continue; int nz=nr*3+nc; string t=cur.s; swap(t[z], t[nz]); int ng=cur.g+1; auto it=seen.find(t); if(it==seen.end()||ng<it->second){ seen[t]=ng; pq.push({ng+manhattan(t), ng, t}); } }
    }
    return -1;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    vector<vector<int>> b={{1,2,3},{4,0,6},{7,5,8}}; cout<<min_moves_8puzzle(b)<<"\n"; // Expected 2
    return 0;
}
