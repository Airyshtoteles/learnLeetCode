#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

long long calculateCost(const vector<int>& nums, const vector<int>& cost, int target) {
    long long total = 0;
    for (size_t i = 0; i < nums.size(); ++i) {
        total += (long long)abs(nums[i] - target) * cost[i];
    }
    return total;
}

int main() {
    int n;
    if (!(cin >> n)) return 0;
    
    vector<int> nums(n);
    vector<int> cost(n);
    
    for(int i=0; i<n; ++i) cin >> nums[i];
    for(int i=0; i<n; ++i) cin >> cost[i];

    vector<pair<int, int>> pairs(n);
    long long totalCost = 0;
    for(int i=0; i<n; ++i) {
        pairs[i] = {nums[i], cost[i]};
        totalCost += cost[i];
    }
    
    sort(pairs.begin(), pairs.end());
    
    long long currentCost = 0;
    long long medianCost = (totalCost + 1) / 2;
    int target = 0;
    
    for(int i=0; i<n; ++i) {
        currentCost += pairs[i].second;
        if (currentCost >= medianCost) {
            target = pairs[i].first;
            break;
        }
    }
    
    cout << calculateCost(nums, cost, target) << endl;
    
    return 0;
}
