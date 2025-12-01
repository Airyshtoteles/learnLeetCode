#include <bits/stdc++.h>
using namespace std;

// LC 1569 — Number of Ways to Reorder Array to Get Same BST
// ways(arr) = C(n-1, L) * ways(left) * ways(right); answer = ways(nums) - 1

static const int MOD = 1'000'000'007;

long long modAdd(long long a, long long b){ a+=b; if(a>=MOD) a-=MOD; return a; }
long long modMul(long long a, long long b){ return (a*b)%MOD; }

vector<vector<int>> comb;

long long solve(const vector<int>& arr){
    int n = arr.size();
    if (n <= 2) return 1;
    int root = arr[0];
    vector<int> L, R;
    L.reserve(n); R.reserve(n);
    for (int i=1;i<n;++i){ if (arr[i] < root) L.push_back(arr[i]); else R.push_back(arr[i]); }
    long long lw = solve(L);
    long long rw = solve(R);
    int l = L.size(), r = R.size();
    long long ways = comb[l+r][l];
    ways = modMul(ways, modMul(lw, rw));
    return ways;
}

int numOfWays(vector<int> nums){
    int n = nums.size();
    comb.assign(n+1, vector<int>(n+1, 0));
    for (int i=0;i<=n;++i){
        comb[i][0] = comb[i][i] = 1;
        for (int j=1;j<i;++j) comb[i][j] = (comb[i-1][j-1] + comb[i-1][j]) % MOD;
    }
    long long ans = solve(nums);
    ans = (ans - 1 + MOD) % MOD;
    return (int)ans;
}

int main(){
    cout << numOfWays({2,1,3}) << "\n"; // 1
    return 0;
}
