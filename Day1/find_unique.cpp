#include <iostream>
#include <vector>

int singleNumber(const std::vector<int>& nums) {
    int acc = 0;
    for (int v : nums) {
        acc ^= v;
    }
    return acc;
}

int main() {
    std::vector<int> nums1 {4, 1, 2, 1, 2};
    std::vector<int> nums2 {2, 2, 3};

    std::cout << "Hasil 1: " << singleNumber(nums1) << '\n'; 
    std::cout << "Hasil 2: " << singleNumber(nums2) << '\n'; 

    return 0;
}