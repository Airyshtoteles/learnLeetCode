#include <bits/stdc++.h>
using namespace std;

// LC 2009 — Minimum Number of Operations to Make Array Continuous
// Sort unique + two pointers: maximize count kept within window [x, x+n-1]

int minOperations(vector<int> nums){
    int n = nums.size();
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    int m = nums.size();
    int ansKeep = 0;
    int j = 0;
    for(int i=0;i<m;++i){
        while(j<m && nums[j] < nums[i] + n) ++j;
        ansKeep = max(ansKeep, j - i);
    }
    return n - ansKeep;
}

int main(){
    cout << minOperations({4,2,5,3}) << "\n"; // 0
    cout << minOperations({1,2,3,5,6}) << "\n"; // 1
    return 0;
}
