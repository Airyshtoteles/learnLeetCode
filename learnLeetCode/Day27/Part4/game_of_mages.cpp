#include <bits/stdc++.h>
using namespace std;

long long max_power(const vector<int>& mana, const vector<int>& power){
    int n = mana.size();
    vector<int> rem_mask(n, 0);
    for(int i=0;i<n;++i){
        int mask=0;
        for(int j=0;j<n;++j){
            if(power[j] > power[i] && mana[j] < mana[i]) mask |= (1<<j);
        }
        rem_mask[i]=mask;
    }
    int N = 1<<n;
    vector<long long> sum_power(N,0);
    for(int s=1;s<N;++s){
        int b = __builtin_ctz(s);
        sum_power[s] = sum_power[s^(1<<b)] + power[b];
    }
    vector<long long> memo(N, LLONG_MIN);
    function<long long(int)> dfs = [&](int S)->long long{
        long long &res = memo[S]; if(res!=LLONG_MIN) return res;
        long long best = sum_power[S];
        for(int i=0;i<n;++i){
            if(S>>i & 1) continue;
            int S2 = (S & ~rem_mask[i]) | (1<<i);
            if(S2==S) continue;
            best = max(best, dfs(S2));
        }
        return res = best;
    };
    return dfs(0);
}

int main(){
    vector<int> mana={3,6,4,5};
    vector<int> power={5,3,8,7};
    cout << max_power(mana, power) << "\n"; // Expected 15 under removal-on-add interpretation
    return 0;
}
