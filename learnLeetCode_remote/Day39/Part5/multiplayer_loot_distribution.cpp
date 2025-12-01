#include <bits/stdc++.h>
using namespace std;

long long max_diff(vector<long long> value, vector<long long> rarity){
    vector<pair<long long,long long>> items;
    int n = (int)value.size(); items.reserve(n);
    for(int i=0;i<n;++i) items.push_back({value[i], rarity[i]});
    sort(items.begin(), items.end(), [](auto &a, auto &b){return a.first>b.first;});
    long long A=0, B=0; bool turnA=true;
    for(auto &it: items){
        long long v=it.first, r=it.second;
        if(turnA){ if((r&1)==0) A += v; }
        else { if((r&1)==1) B += v; }
        turnA = !turnA;
    }
    return A - B;
}

int main(){ ios::sync_with_stdio(false); cin.tie(nullptr);
    vector<long long> value={4,6,5,8}; vector<long long> rarity={2,3,2,5};
    cout << max_diff(value, rarity) << "\n";
    return 0; }
