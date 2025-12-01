#include <bits/stdc++.h>
using namespace std;

int min_presses(vector<int> clocks, const vector<vector<int>>& ops){
    int n=clocks.size(), m=ops.size();
    vector<int> cur=clocks;
    int best=INT_MAX;
    auto apply_button = [&](int i,int times){
        int t=((times%12)+12)%12; if(t==0) return;
        for(int j=0;j<n;++j) if(ops[i][j]) cur[j]=(cur[j]+t)%12;
    };
    function<void(int,int)> dfs = [&](int i,int used){
        if(used>=best) return;
        if(i==m){
            if(all_of(cur.begin(),cur.end(),[](int x){return x==0;})) best=min(best,used);
            return;
        }
        auto snapshot=cur;
        for(int t=0;t<12;++t){
            apply_button(i,t);
            dfs(i+1, used+t);
            cur=snapshot;
        }
    };
    dfs(0,0);
    return best==INT_MAX? -1: best;
}

int main(){
    vector<int> clocks={3,6,9};
    vector<vector<int>> ops={{1,0,1},{0,1,1}};
    cout<<min_presses(clocks,ops)<<"\n";
    return 0;
}
