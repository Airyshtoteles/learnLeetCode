#include <bits/stdc++.h>
using namespace std;

pair<long long,int> factor_info(long long x){
    if(x==0) return {0,-1};
    int e=0; while((x&1LL)==0){ x >>=1; ++e; }
    return {x,e};
}

vector<long long> build_odd(const vector<long long>& arr, vector<int>& exps){
    vector<long long> odd; odd.reserve(arr.size()); exps.reserve(arr.size());
    for(long long v: arr){ auto [o,e]=factor_info(v); odd.push_back(o); exps.push_back(e);} return odd;
}

vector<int> z_algorithm(const vector<long long>& s){
    int n=s.size(); vector<int> z(n); int l=0,r=0; z[0]=n;
    for(int i=1;i<n;++i){
        if(i<=r) z[i]=min(r-i+1,z[i-l]);
        while(i+z[i]<n && s[z[i]]==s[i+z[i]]) ++z[i];
        if(i+z[i]-1>r){ l=i; r=i+z[i]-1; }
    }
    return z;
}

bool can_time_warp_subarray(const vector<long long>& A, const vector<long long>& B, long long k){
    int n=A.size(), m=B.size(); if(m>n) return false;
    vector<int> expA, expB; auto oddA=build_odd(A,expA); auto oddB=build_odd(B,expB);
    long long sentinel = (long long)1e12+7;
    vector<long long> combined; combined.reserve(m+1+n);
    combined.insert(combined.end(), oddB.begin(), oddB.end());
    combined.push_back(sentinel);
    combined.insert(combined.end(), oddA.begin(), oddA.end());
    auto z=z_algorithm(combined);
    for(int start=0; start<=n-m; ++start){
        if(z[m+1+start] >= m){
            long long total=0; bool ok=true;
            for(int t=0;t<m;++t){
                long long oa=oddA[start+t], ob=oddB[t];
                if(ob==-1){ if(oa!=-1){ ok=false; break; } continue; }
                if(oa==-1){ ok=false; break; }
                total += llabs(expA[start+t]-expB[t]);
                if(total>k){ ok=false; break; }
            }
            if(ok && total<=k) return true;
        }
    }
    return false;
}

int main(){
    vector<long long> A={4,3,8,2,16};
    vector<long long> B={1,8};
    cout << (can_time_warp_subarray(A,B,3) ? "true" : "false") << "\n"; // true
    return 0;
}
