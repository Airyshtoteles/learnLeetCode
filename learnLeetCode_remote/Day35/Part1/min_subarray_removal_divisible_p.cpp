#include <bits/stdc++.h>
using namespace std;

int min_subarray(vector<int> nums, int p){
    long long total = 0; for(int x: nums) total += x;
    int target = (int)(total % p);
    if(target == 0) return 0;
    unordered_map<int,int> pos; pos.reserve(nums.size()*2); pos[0] = -1;
    int res = (int)nums.size();
    long long cur = 0;
    for(int i=0;i<(int)nums.size();++i){
        cur = (cur + nums[i]) % p;
        int need = (int)((cur - target) % p);
        if(need < 0) need += p;
        auto it = pos.find(need);
        if(it != pos.end()) res = min(res, i - it->second);
        pos[(int)cur] = i;
    }
    return res < (int)nums.size() ? res : -1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << min_subarray(vector<int>{3,1,4,2}, 6) << "\n"; // Expected 1
    return 0;
}
