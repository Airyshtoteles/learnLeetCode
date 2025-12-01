#include <bits/stdc++.h>
using namespace std;

// LeetCode 1553 — Minimum Number of Days to Eat N Oranges
// f(n) = 1 + min(n%2 + f(n/2), n%3 + f(n/3))

class Solution {
    unordered_map<long long, int> memo;
public:
    int minDays(int n) {
        if (n <= 1) return n;
        auto it = memo.find(n);
        if (it != memo.end()) return it->second;
        long long by2 = (n % 2) + minDays(n / 2);
        long long by3 = (n % 3) + minDays(n / 3);
        int ans = 1 + (int)min(by2, by3);
        memo[n] = ans;
        return ans;
    }
};

int main(){
    cout << Solution().minDays(10) << "\n"; // Expected 4
    return 0;
}
