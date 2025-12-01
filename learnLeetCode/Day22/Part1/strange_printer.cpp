#include <bits/stdc++.h>
using namespace std;

// LC 664 — Strange Printer
// Interval DP with compression of consecutive duplicates

int strangePrinter(string s){
    string t; t.reserve(s.size());
    for(char c: s){ if(t.empty() || t.back()!=c) t.push_back(c); }
    int n = (int)t.size();
    if(n==0) return 0;
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for(int i=0;i<n;++i) dp[i][i]=1;
    for(int len=2; len<=n; ++len){
        for(int i=0; i+len-1<n; ++i){
            int j = i+len-1;
            int res = dp[i+1][j] + 1;
            for(int k=i+1; k<=j; ++k){
                if(t[i]==t[k]){
                    int left = (k-1>=i+1) ? dp[i+1][k-1] : 0;
                    res = min(res, left + dp[k][j]);
                }
            }
            dp[i][j] = res;
        }
    }
    return dp[0][n-1];
}

int main(){
    cout << strangePrinter("aba") << "\n"; // 2
    return 0;
}
