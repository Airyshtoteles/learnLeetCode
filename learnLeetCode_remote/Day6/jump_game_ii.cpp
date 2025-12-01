#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Day 6 — Jump Game II (Medium)
// Approach: Greedy with max reach tracking - O(n) time, O(1) space.
// Avoids DP's O(n²) complexity by using optimal substructure property.
int jump(const vector<int>& nums) {
    int n = nums.size();
    if (n <= 1) return 0;
    
    int jumps = 0;
    int currentEnd = 0;      // End of current jump range
    int farthestReach = 0;   // Farthest position reachable so far
    
    // We don't need to jump from the last position
    for (int i = 0; i < n - 1; ++i) {
        // Update farthest reachable position
        farthestReach = max(farthestReach, i + nums[i]);
        
        // If we've reached the end of current jump range
        if (i == currentEnd) {
            ++jumps;
            currentEnd = farthestReach;
            
            // Early termination if we can reach the end
            if (currentEnd >= n - 1) {
                break;
            }
        }
    }
    
    return jumps;
}

int jumpVerbose(const vector<int>& nums) {
    int n = nums.size();
    if (n <= 1) return 0;
    
    int jumps = 0;
    int currentEnd = 0;
    int farthestReach = 0;
    
    cout << "Starting with nums: [";
    for (int i = 0; i < n; ++i) {
        if (i > 0) cout << ",";
        cout << nums[i];
    }
    cout << "]\n";
    
    for (int i = 0; i < n - 1; ++i) {
        farthestReach = max(farthestReach, i + nums[i]);
        cout << "  i=" << i << ", nums[i]=" << nums[i] 
             << ", farthestReach=" << farthestReach << "\n";
        
        if (i == currentEnd) {
            ++jumps;
            currentEnd = farthestReach;
            cout << "  -> Jump #" << jumps << ", new range end: " << currentEnd << "\n";
            
            if (currentEnd >= n - 1) {
                cout << "  -> Can reach end, breaking\n";
                break;
            }
        }
    }
    
    return jumps;
}

int main() {
    // Test cases from examples
    cout << "Testing Day 6 solutions:\n";
    cout << "[2,3,1,1,4] -> " << jump({2,3,1,1,4}) << " (expected: 2)\n";
    cout << "[2,3,0,1,4] -> " << jump({2,3,0,1,4}) << " (expected: 2)\n";
    
    // Validation
    if (jump({2,3,1,1,4}) != 2 ||
        jump({2,3,0,1,4}) != 2 ||
        jump({0}) != 0 ||
        jump({1}) != 0 ||
        jump({1,1}) != 1 ||
        jump({5,1,1,1,1}) != 1) {
        cerr << "Test failed!" << endl;
        return 1;
    }
    
    // Demonstration with verbose output
    cout << "\n=== Verbose walkthrough ===\n";
    int result = jumpVerbose({2,3,1,1,4});
    cout << "Result: " << result << "\n\n";
    
    cout << "All tests passed!\n";
    return 0;
}