#include <bits/stdc++.h>
using namespace std;

int min_operations(const vector<int>& nums){
    int n = (int)nums.size();
    bool all_equal = true;
    for(int i=1;i<n && all_equal;++i) if(nums[i]!=nums[0]) all_equal=false;
    if(all_equal) return 0;
    bool pal = true;
    for(int i=0;i<n/2 && pal;++i) if(nums[i]!=nums[n-1-i]) pal=false;
    if(pal) return 1;
    return 2;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << min_operations({1,3,2,3,1}) << "\n"; // 1
    cout << min_operations({5,5,5}) << "\n";     // 0
    cout << min_operations({1,2,3}) << "\n";     // 2
    return 0;
}
