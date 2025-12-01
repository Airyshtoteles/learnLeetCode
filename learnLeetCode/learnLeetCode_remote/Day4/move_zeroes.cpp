#include <iostream>
#include <vector>
using namespace std;

// Day 4 — Move Zeroes to End (Optimized)
// Approach: Single-pass two pointers with conditional swap to minimize writes.
// Time: O(n), Space: O(1)
void moveZeroes(vector<int>& nums) {
    int write = 0;
    for (int read = 0; read < (int)nums.size(); ++read) {
        if (nums[read] != 0) {
            if (read != write) {
                int tmp = nums[write];
                nums[write] = nums[read];
                nums[read] = tmp;
            }
            ++write;
        }
    }
}

int main() {
    vector<int> a{0,1,0,3,12};
    moveZeroes(a);
    cout << "[";
    for (size_t i = 0; i < a.size(); ++i) { if (i) cout << ", "; cout << a[i]; }
    cout << "]\n";

    vector<int> b{0,0,1};
    moveZeroes(b);
    if (b != vector<int>({1,0,0})) { cerr << "Test failed" << endl; return 1; }

    return 0;
}
