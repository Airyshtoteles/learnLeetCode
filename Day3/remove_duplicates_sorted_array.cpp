#include <iostream>
#include <vector>
using namespace std;

// Remove Duplicates from Sorted Array (Easy)
// Approach: Two pointers, in-place overwrite. Time O(n), Space O(1).
int removeDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;
    int write = 1;
    for (int read = 1; read < (int)nums.size(); ++read) {
        if (nums[read] != nums[write - 1]) {
            nums[write++] = nums[read];
        }
    }
    return write;
}

int main() {
    vector<int> nums{0,0,1,1,1,2,2,3,3,4};
    int k = removeDuplicates(nums);
    cout << "k = " << k << ", nums[:k] = [";
    for (int i = 0; i < k; ++i) {
        if (i) cout << ", ";
        cout << nums[i];
    }
    cout << "]\n";

    // basic checks
    vector<int> a; int k2 = removeDuplicates(a); if (k2 != 0) return 1;
    vector<int> b{1}; int k3 = removeDuplicates(b); if (!(k3==1 && b[0]==1)) return 1;
    vector<int> c{1,1,1}; int k4 = removeDuplicates(c); if (!(k4==1 && c[0]==1)) return 1;
    return 0;
}
