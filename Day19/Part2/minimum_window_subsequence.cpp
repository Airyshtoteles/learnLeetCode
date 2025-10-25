#include <bits/stdc++.h>
using namespace std;

// LC 727 — Minimum Window Subsequence
// Two-pointer: forward to find a window, then backward to shrink

string minWindow(string s, string t){
    int n = (int)s.size(), m = (int)t.size();
    if (m == 0) return "";
    string best = "";
    int i = 0;
    while(true){
        int pos = -1;
        // find first s[pos] == t[0] starting at i
        for(int p=i;p<n;++p){ if (s[p]==t[0]){ pos=p; break; } }
        if (pos == -1) break;
        // forward scan to match t
        int j = pos, k = 0;
        while(j < n && k < m){ if (s[j]==t[k]) ++k; ++j; }
        if (k < m) break; // not found, no more windows
        int end = j - 1;
        // backward shrink
        k = m - 1; j = end;
        while(j >= pos){ if (s[j]==t[k]){ --k; if (k < 0) break; } --j; }
    int start = j;
        string cand = s.substr(start, end - start + 1);
        if (best.empty() || cand.size() < best.size()) best = cand;
        i = start + 1; // move start forward for next search
    }
    return best;
}

int main(){
    cout << minWindow("abcdebdde", "bde") << "\n"; // bcde
    return 0;
}
