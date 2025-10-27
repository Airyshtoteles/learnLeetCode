#include <bits/stdc++.h>
using namespace std;

// LC 1312 — Minimum Insertion Steps to Make a String Palindrome
// Answer = n - LPS(s) where LPS is LCS(s, reverse(s))

int minInsertions(string s){
    string t = s; reverse(t.begin(), t.end());
    int n = s.size();
    vector<int> dp(n+1, 0);
    for (int i=1;i<=n;++i){
        int prev = 0;
        for (int j=1;j<=n;++j){
            int cur = dp[j];
            if (s[i-1] == t[j-1]) dp[j] = prev + 1;
            else dp[j] = max(dp[j], dp[j-1]);
            prev = cur;
        }
    }
    int lps = dp[n];
    return n - lps;
}

int main(){
    cout << minInsertions("zzazz") << "\n"; // 0
    cout << minInsertions("mbadm") << "\n"; // 2
    return 0;
}
