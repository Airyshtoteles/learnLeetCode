#include <bits/stdc++.h>
using namespace std;

struct Key{
    int a,b,ma,mb,t;
    bool operator==(Key const& o) const {return a==o.a&&b==o.b&&ma==o.ma&&mb==o.mb&&t==o.t;}
};
struct KeyHash{ size_t operator()(Key const& k) const noexcept{ 
    size_t h = k.a; h = h*1315423911u + k.b; h = h*1315423911u + k.ma; h = h*1315423911u + k.mb; h = h*2 + k.t; return h; } };

class Solver{
    int X,Y,M; static constexpr int MAXHP=100; 
    unordered_map<Key,bool,KeyHash> memo;
public:
    Solver(int X,int Y,int M):X(X),Y(Y),M(M){}
    bool dfs(int hpA,int hpB,int manaA,int manaB,int turn){
        if(hpA<=0 && hpB<=0) return false; // tie -> current loses
        if(hpA<=0) return false;
        if(hpB<=0) return true;
        if(manaA==0 && manaB==0) return hpA>hpB;
        Key key{hpA,hpB,manaA,manaB,turn};
        auto it=memo.find(key); if(it!=memo.end()) return it->second;
        bool ans;
        if(turn==0){
            if(manaA==0){ ans = dfs(hpA,hpB,manaA,manaB,1); }
            else{
                if(dfs(hpA, hpB - X, manaA-1, manaB, 1)) { ans=true; }
                else {
                    int nhpA=min(MAXHP, hpA+Y);
                    ans = dfs(nhpA, hpB, manaA-1, manaB, 1);
                }
            }
        }else{
            if(manaB==0){ ans = dfs(hpA,hpB,manaA,manaB,0); }
            else{
                if(!dfs(hpA - X, hpB, manaA, manaB-1, 0)) { ans=false; }
                else{
                    int nhpB=min(MAXHP, hpB+Y);
                    ans = !dfs(hpA, nhpB, manaA, manaB-1, 0);
                }
            }
        }
        memo[key]=ans; return ans;
    }
};

bool can_A_win(int X,int Y,int M){
    Solver s(X,Y,M); return s.dfs(100,100,M,M,0);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout<<(can_A_win(20,10,5)?"True":"False")<<"\n"; // Expected True
    return 0;
}
