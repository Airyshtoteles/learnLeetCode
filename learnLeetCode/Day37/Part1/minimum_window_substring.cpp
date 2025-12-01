#include <bits/stdc++.h>
using namespace std;

string minWindow(string s, string t){
    if(t.empty()||s.empty()) return "";
    vector<int> need(128,0), have(128,0);
    int required=0;
    for(char c: t){ if(need[c]==0) ++required; ++need[c]; }
    int formed=0; int l=0; int bestLen=INT_MAX, bestL=0, bestR=-1;
    for(int r=0;r<(int)s.size();++r){
        char c = s[r];
        have[c]++;
        if(need[c]>0 && have[c]==need[c]) formed++;
        while(l<=r && formed==required){
            if(r-l+1<bestLen){ bestLen=r-l+1; bestL=l; bestR=r; }
            char lc=s[l];
            have[lc]--;
            if(need[lc]>0 && have[lc]<need[lc]) formed--;
            l++;
        }
    }
    return bestLen==INT_MAX? string(): s.substr(bestL, bestLen);
}

int main(){ ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << minWindow("ADOBECODEBANC","ABC") << "\n"; // Expected BANC
    return 0; }
