#include <bits/stdc++.h>
using namespace std;

struct DSU{
    vector<int> p,r;
    DSU(int n):p(n),r(n,0){ iota(p.begin(), p.end(), 0); }
    int find(int x){ return p[x]==x?x:p[x]=find(p[x]); }
    bool unite(int a,int b){ a=find(a); b=find(b); if(a==b) return false; if(r[a]<r[b]) swap(a,b); p[b]=a; if(r[a]==r[b]) r[a]++; return true; }
};

vector<long long> factor(long long n){
    vector<long long> res; long long x=n; long long d=2;
    while(d*d<=x){
        if(x%d==0){ res.push_back(d); while(x%d==0) x/=d; }
        d += (d==2?1:2);
    }
    if(x>1) res.push_back(x);
    return res;
}

int count_components(const vector<long long>& nums){
    int n=nums.size(); DSU dsu(n); unordered_map<long long,int> owner; owner.reserve(n*2);
    for(int i=0;i<n;++i){
        auto primes=factor(nums[i]);
        for(auto p:primes){ auto it=owner.find(p); if(it==owner.end()) owner[p]=i; else dsu.unite(i,it->second); }
    }
    unordered_set<int> roots; roots.reserve(n*2);
    for(int i=0;i<n;++i) roots.insert(dsu.find(i));
    return (int)roots.size();
}

int main(){
    vector<long long> nums={2,3,6,15,35};
    cout<<count_components(nums)<<"\n"; // Expected 2
    return 0;
}
