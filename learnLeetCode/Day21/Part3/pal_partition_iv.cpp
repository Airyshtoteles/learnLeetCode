#include <bits/stdc++.h>
using namespace std;

// LC 1745 — Palindrome Partitioning IV
// Check if string can be split into three palindromic substrings

bool checkPartitioning(string s){
    int n = s.size();
    vector<vector<char>> pal(n, vector<char>(n, 0));
    for(int i=n-1;i>=0;--i){
        for(int j=i;j<n;++j){
            if (s[i]==s[j] && (j-i<=1 || pal[i+1][j-1])) pal[i][j]=1;
        }
    }
    for(int i=0;i<=n-3;++i){
        if (!pal[0][i]) continue;
        for(int j=i+1;j<=n-2;++j){
            if (pal[i+1][j] && pal[j+1][n-1]) return true;
        }
    }
    return false;
}

int main(){
    cout << (checkPartitioning("abcbdd") ? "true" : "false") << "\n"; // true
    return 0;
}
