#include <iostream>
#include <vector>
using namespace std;

// Move Zeroes (Easy)
// Approach: Single-pass two pointers with conditional swap for minimal writes.
// Time: O(n), Space: O(1).
void moveZeroes(vector<int>& nums) {
    int write = 0;
    for (int read = 0; read < (int)nums.size(); ++read) {
        if (nums[read] != 0) {
            if (read != write) {
                // swap keeps relative order and minimizes writes
                int tmp = nums[write];
                nums[write] = nums[read];
                nums[read] = tmp;
            }
            ++write;
        }
    }
}

int main() {
    vector<int> nums{0,1,0,3,12};
    moveZeroes(nums);
    cout << "[";
    for (size_t i = 0; i < nums.size(); ++i) {
        if (i) cout << ", ";
        cout << nums[i];
    }
    cout << "]\n";

    // basic checks
    vector<int> a{0}; moveZeroes(a); if (a != vector<int>({0})) return 1;
    vector<int> b{1,2,3}; moveZeroes(b); if (b != vector<int>({1,2,3})) return 1;
    vector<int> c{0,0,0}; moveZeroes(c); if (c != vector<int>({0,0,0})) return 1;
    vector<int> d{4,0,5,0,0,-1}; moveZeroes(d); if (d != vector<int>({4,5,-1,0,0,0})) return 1;
    return 0;
}
