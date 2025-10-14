#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Day 8 — Part 3: 4Sum
// Approach: Sort; fix i and j, then two-pointers on remaining range.
// Time: O(n^3), Space: O(1) extra (excluding output)
vector<vector<int>> fourSum(vector<int> nums, int target) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    vector<vector<int>> res;
    for (int i = 0; i < n; ++i) {
        if (i > 0 && nums[i] == nums[i-1]) continue; // skip dup i
        for (int j = i + 1; j < n; ++j) {
            if (j > i + 1 && nums[j] == nums[j-1]) continue; // skip dup j
            int l = j + 1, r = n - 1;
            while (l < r) {
                long long s = 1LL*nums[i] + nums[j] + nums[l] + nums[r];
                if (s == target) {
                    res.push_back({nums[i], nums[j], nums[l], nums[r]});
                    ++l; --r;
                    while (l < r && nums[l] == nums[l-1]) ++l;
                    while (l < r && nums[r] == nums[r+1]) --r;
                } else if (s < target) {
                    ++l;
                } else {
                    --r;
                }
            }
        }
    }
    return res;
}

int main() {
    vector<int> arr = {1,0,-1,0,-2,2};
    auto out = fourSum(arr, 0);
    cout << "Quadruplets:\n";
    for (auto &q : out) {
        cout << "[" << q[0] << "," << q[1] << "," << q[2] << "," << q[3] << "]\n";
    }

    // Basic checks
    auto ok = fourSum({1,0,-1,0,-2,2}, 0);
    if (ok.size() != 3) return 1; // canonical example size
    if (fourSum({0,0,0,0}, 0) != vector<vector<int>>{{0,0,0,0}}) return 1;
    return 0;
}