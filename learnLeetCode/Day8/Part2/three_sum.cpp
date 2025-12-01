#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Day 8 — Part 2: 3Sum
// Approach: Sort + two-pointers, skip duplicates.
// Time: O(n^2), Space: O(1) extra (excluding output)
vector<vector<int>> threeSum(vector<int> nums) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    vector<vector<int>> res;
    for (int i = 0; i < n; ++i) {
        if (i > 0 && nums[i] == nums[i-1]) continue; // skip duplicate anchor
        if (nums[i] > 0) break; // remaining will be positive
        int l = i + 1, r = n - 1;
        while (l < r) {
            long long s = 1LL*nums[i] + nums[l] + nums[r];
            if (s == 0) {
                res.push_back({nums[i], nums[l], nums[r]});
                ++l; --r;
                while (l < r && nums[l] == nums[l-1]) ++l;
                while (l < r && nums[r] == nums[r+1]) --r;
            } else if (s < 0) {
                ++l;
            } else {
                --r;
            }
        }
    }
    return res;
}

int main() {
    vector<int> nums = {-1,0,1,2,-1,-4};
    auto ans = threeSum(nums);
    // print result in any order
    cout << "Triplets:" << "\n";
    for (const auto& t : ans) {
        cout << "[" << t[0] << "," << t[1] << "," << t[2] << "]\n";
    }

    // basic checks
    // We can't assert order; just check size is 2 for given example
    if (threeSum({-1,0,1,2,-1,-4}).size() != 2) return 1;
    if (threeSum({0,0,0}) != vector<vector<int>>{{0,0,0}}) return 1;
    if (threeSum({}).size() != 0) return 1; // empty ok
    return 0;
}