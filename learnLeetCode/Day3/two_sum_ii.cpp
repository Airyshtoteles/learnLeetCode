#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Two Sum II — Input array is sorted (Easy)
// Approach: Two pointers. Time O(n), Space O(1).
vector<int> twoSumII(const vector<int>& numbers, int target) {
    int l = 0, r = (int)numbers.size() - 1;
    while (l < r) {
        long long s = (long long)numbers[l] + numbers[r];
        if (s == target) return {l + 1, r + 1}; // 1-based indices
        if (s < target) ++l; else --r;
    }
    return {};
}

int main() {
    vector<int> nums{2,7,11,15};
    int target = 9;
    auto ans = twoSumII(nums, target);
    cout << "Two Sum II: [" << (ans.size() ? to_string(ans[0]) : "")
         << (ans.size() ? ", " + to_string(ans[1]) : "") << "]\n";

    // basic checks
    vector<int> a{2,3,4};
    auto b = twoSumII(a, 6);
    if (!(b.size()==2 && b[0]==1 && b[1]==3)) {
        cerr << "Test failed" << endl; return 1;
    }
    return 0;
}
