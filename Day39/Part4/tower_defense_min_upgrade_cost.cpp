#include <bits/stdc++.h>
using namespace std;

long long min_cost(const vector<long long>& HP, long long D){
    long long ans = 0;
    for(long long h: HP){ ans += (h + D - 1) / D; }
    return ans;
}

int main(){ ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << min_cost(vector<long long>{10,15,5}, 5) << "\n"; // 6
    return 0; }
