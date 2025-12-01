#include <bits/stdc++.h>
using namespace std;

bool can_reach_end(vector<long long> A, long long c){
    int n=A.size(); if(n==0) return false; if(n==1) return true;
    vector<long long> original=A;
    vector<long long> visits(n,0);
    vector<unordered_set<long long>> seen(n);
    deque<int> dq; dq.push_back(0);
    while(!dq.empty()){
        int pos=dq.front(); dq.pop_front();
        long long jump=A[pos];
        if(seen[pos].count(jump)) continue;
        seen[pos].insert(jump);
        long long nxt1=pos + jump, nxt2=pos - jump;
        if(nxt1==n-1 || nxt2==n-1) return true;
        if(nxt1>=0 && nxt1<n) dq.push_back((int)nxt1);
        if(nxt2>=0 && nxt2<n) dq.push_back((int)nxt2);
        if(visits[pos] < c){
            visits[pos]++;
            A[pos]++;
            if(visits[pos]==c){ A[pos]=0; }
            dq.push_back(pos);
        }
    }
    return false;
}

int main(){
    vector<long long> A={2,3,1,1,4}; long long c=2;
    cout<<(can_reach_end(A,c)?"true":"false")<<"\n";
    return 0;
}
