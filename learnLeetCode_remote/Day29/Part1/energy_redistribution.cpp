#include <bits/stdc++.h>
using namespace std;

long long min_moves_to_equalize(const vector<long long>& energy){
    int n = (int)energy.size();
    if(n==0) return 0;
    long long S = 0; for(auto v: energy) S += v;
    if(S % n != 0) return -1;
    long long avg = S / n;
    long long surplus = 0;
    for(auto v: energy) if(v > avg) surplus += (v - avg);
    return surplus;
}

int main(){
    vector<long long> a = {1,3,5};
    cout << min_moves_to_equalize(a) << "\n"; // 2 (unit transfers)
    return 0;
}
