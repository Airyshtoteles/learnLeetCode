#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long solve_arcane_fusion(const vector<long long>& nums) {
    vector<long long> basis(64, 0);
    
    // Build Linear Basis
    for (long long num : nums) {
        for (int i = 63; i >= 0; --i) {
            if ((num >> i) & 1) {
                if (basis[i] == 0) {
                    basis[i] = num;
                    break;
                } else {
                    num ^= basis[i];
                }
            }
        }
    }
    
    // Construct Maximum XOR
    long long max_xor = 0;
    for (int i = 63; i >= 0; --i) {
        if ((max_xor ^ basis[i]) > max_xor) {
            max_xor ^= basis[i];
        }
    }
    
    return max_xor;
}

int main() {
    vector<long long> nums = {3, 10, 5, 25, 2, 8};
    cout << "Maximum XOR: " << solve_arcane_fusion(nums) << endl;
    return 0;
}
