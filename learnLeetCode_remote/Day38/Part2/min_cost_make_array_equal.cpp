#include <bits/stdc++.h>
using namespace std;

long long min_cost(vector<int> nums, vector<int> cost){
    vector<pair<long long,long long>> a; a.reserve(nums.size());
    for(size_t i=0;i<nums.size();++i) a.emplace_back(nums[i], cost[i]);
    sort(a.begin(), a.end());
    long long total_w=0; for(auto &p: a) total_w += p.second;
    long long half = (total_w + 1)/2;
    long long acc=0; long long median=a.back().first;
    for(auto &p: a){ acc += p.second; if(acc>=half){ median=p.first; break; } }
    long long res=0; for(auto &p: a) res += p.second * llabs(p.first - median);
    return res;
}

int main(){ ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << min_cost(vector<int>{1,3,5,2}, vector<int>{2,3,1,14}) << "\n";
    return 0; }
