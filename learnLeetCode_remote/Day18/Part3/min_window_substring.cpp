#include <bits/stdc++.h>
using namespace std;

// LC 76 — Minimum Window Substring (sliding window)

string minWindow(string s, string t){
    if (t.empty() || s.size() < t.size()) return "";
    vector<int> need(128, 0);
    for(char c: t) need[(unsigned char)c]++;
    int missing = (int)t.size();
    int left = 0;
    int bestLen = INT_MAX, bestL = 0;
    for(int right=0; right<(int)s.size(); ++right){
        unsigned char c = s[right];
        if (need[c] > 0) missing--;
        need[c]--;
        while(missing == 0){
            if (right - left + 1 < bestLen){
                bestLen = right - left + 1;
                bestL = left;
            }
            unsigned char lc = s[left];
            need[lc]++;
            if (need[lc] > 0) missing++;
            left++;
        }
    }
    if (bestLen == INT_MAX) return "";
    return s.substr(bestL, bestLen);
}

int main(){
    cout << minWindow("ADOBECODEBANC", "ABC") << "\n"; // BANC
    return 0;
}
