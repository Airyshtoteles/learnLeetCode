#include <bits/stdc++.h>
using namespace std;

struct DualSet {
    multiset<long long> lo, hi; // lo: max side (size >= hi)
    int k;
    DualSet(int k): k(k) {}
    void rebalance(){
        while((int)lo.size() > (int)hi.size() + (k%2==1?1:0)){
            auto it = prev(lo.end());
            hi.insert(*it); lo.erase(it);
        }
        while((int)lo.size() < (int)hi.size()){
            auto it = hi.begin();
            lo.insert(*it); hi.erase(it);
        }
    }
    void insert(long long x){
        if(lo.empty() || x <= *prev(lo.end())) lo.insert(x);
        else hi.insert(x);
        rebalance();
    }
    void erase(long long x){
        auto it = lo.find(x);
        if(it != lo.end()) lo.erase(it);
        else {
            it = hi.find(x);
            if(it != hi.end()) hi.erase(it);
            else return; // should not happen
        }
        rebalance();
    }
    double median() const {
        if(k%2==1) return (double)(*prev(lo.end()));
        else return ((*prev(lo.end())) + (*hi.begin())) / 2.0;
    }
};

vector<double> medianSlidingWindow(vector<int> nums, int k){
    DualSet ds(k);
    vector<double> ans; ans.reserve(nums.size()>=k?nums.size()-k+1:0);
    for(int i=0;i<(int)nums.size();++i){
        ds.insert(nums[i]);
        if(i>=k) ds.erase(nums[i-k]);
        if(i>=k-1) ans.push_back(ds.median());
    }
    return ans;
}

int main(){ ios::sync_with_stdio(false); cin.tie(nullptr);
    auto v = medianSlidingWindow(vector<int>{1,3,-1,-3,5,3,6,7}, 3);
    cout.setf(std::ios::fixed); cout<<setprecision(1);
    for(size_t i=0;i<v.size();++i){ if(i) cout<<","; cout<<v[i]; } cout<<"\n";
    return 0; }
