#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
    int n;
    long long D, limit;
    if (!(cin >> n >> D >> limit)) return 0;

    vector<long long> h(n);
    vector<long long> turns(n);
    for (int i = 0; i < n; ++i) {
        cin >> h[i];
        turns[i] = (h[i] + D - 1) / D;
    }

    // Calculate initial damage taken
    // Model: You take 1 damage from EACH living monster per turn.
    // Total damage = sum(turns[i] * (number of monsters alive during turn i))
    // Monsters alive during turn i (processing monster i) is (n - i).
    // So cost = turns[0]*n + turns[1]*(n-1) + ...
    
    long long current_damage = 0;
    for (int i = 0; i < n; ++i) {
        current_damage += turns[i] * (n - i);
    }

    if (current_damage <= limit) {
        cout << "true" << endl;
        return 0;
    }

    // Try to swap once to minimize damage
    // We want to maximize reduction.
    // Reduction when swapping i and j (i < j):
    // Old contribution: turns[i]*(n-i) + turns[j]*(n-j)
    // New contribution: turns[j]*(n-i) + turns[i]*(n-j)
    // Diff = (turns[i] - turns[j]) * (n-i - (n-j))
    //      = (turns[i] - turns[j]) * (j - i)
    // We want to maximize this difference.
    
    long long max_reduction = 0;
    
    // O(N^2) approach - acceptable for N <= 1000 or so.
    // If N is larger, we need a better approach.
    // For "Day 80", we'll assume N is reasonable.
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            long long reduction = (turns[i] - turns[j]) * (j - i);
            if (reduction > max_reduction) {
                max_reduction = reduction;
            }
        }
    }

    if (current_damage - max_reduction <= limit) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }

    return 0;
}
