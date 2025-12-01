#include <bits/stdc++.h>
using namespace std;

// LC 2430 — Maximum Deletions on a String
// DP + Z-function per suffix: LCP(s[i:], s[i+k:]) = Z[k]

static vector<int> z_function(const string& s){
    int n = (int)s.size();
    vector<int> z(n);
    int l=0, r=0;
    for(int i=1;i<n;++i){
        if(i<=r) z[i] = min(r - i + 1, z[i - l]);
        while(i+z[i]<n && s[z[i]]==s[i+z[i]]) ++z[i];
        if(i+z[i]-1>r){ l=i; r=i+z[i]-1; }
    }
    if(n>0) z[0]=n;
    return z;
}

int maximumDeletions(string s){
    int n = (int)s.size();
    vector<int> dp(n+1, 0);
    for(int i=n-1;i>=0;--i){
        int best = 1;
        string t = s.substr(i);
        vector<int> z = z_function(t);
        int lim = (n - i)/2;
        for(int k=1;k<=lim;++k){
            if(z[k] >= k) best = max(best, 1 + dp[i + k]);
        }
        dp[i] = best;
    }
    return dp[0];
}

int main(){
    cout << maximumDeletions("abcabcdabc") << "\n"; // 2
    return 0;
}
