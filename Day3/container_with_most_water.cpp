#include <iostream>
#include <vector>
using namespace std;

// Container With Most Water (Medium)
// Approach: Two pointers; move the shorter side inward. O(n) time, O(1) space.
int maxArea(const vector<int>& height) {
    int l = 0, r = (int)height.size() - 1;
    long long best = 0;
    while (l < r) {
        int h = min(height[l], height[r]);
        long long area = 1LL * h * (r - l);
        if (area > best) best = area;
        if (height[l] < height[r]) ++l; else --r;
    }
    return (int)best;
}

int main() {
    vector<int> h{1,8,6,2,5,4,8,3,7};
    cout << "max area: " << maxArea(h) << "\n";

    // basic checks
    if (maxArea({1,1}) != 1) return 1;
    if (maxArea({1,2,1}) != 2) return 1;
    return 0;
}
