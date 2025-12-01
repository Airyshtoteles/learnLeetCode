#include <bits/stdc++.h>
using namespace std;

long long min_X(const vector<long long>& hate, const vector<long long>& threshold){
    long long total = 0, mx = 0;
    for(long long h: hate){ total += h; mx = max(mx, h); }
    return max(mx, total);
}

int main(){ ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << min_X(vector<long long>{3,2}, vector<long long>{20,15}) << "\n"; // 5 under consistent model
    return 0; }
