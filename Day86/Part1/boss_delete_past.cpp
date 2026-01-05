#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Problem: Boss That Deletes the Past
// Boss HP H.
// After every attack i, boss removes one previous attack (worst case).
// Analysis suggests that at any point, we can have at most 2 active attacks in the history buffer
// before the boss deletes one.
// Specifically, if we attack with max damage D:
// 1. Attack D. Active: {D}. Sum D. Check Win. Boss deletes from {}. Active {D}.
// 2. Attack D. Active: {D, D}. Sum 2D. Check Win. Boss deletes D. Active {D}.
// 3. Attack D. Active: {D, D}. Sum 2D. Check Win. Boss deletes D. Active {D}.
// So the maximum damage we can ever "stack" is 2 * MaxDamage.
// If H <= MaxDamage, 1 attack.
// If H <= 2 * MaxDamage, 2 attacks.
// If H > 2 * MaxDamage, Impossible (-1).

int main() {
    long long H;
    if (!(cin >> H)) return 0;
    
    int N;
    cin >> N;
    long long max_dmg = 0;
    for (int i = 0; i < N; ++i) {
        long long d;
        cin >> d;
        max_dmg = max(max_dmg, d);
    }

    if (max_dmg == 0) {
        cout << -1 << endl;
        return 0;
    }

    if (H <= max_dmg) {
        cout << 1 << endl;
    } else if (H <= 2 * max_dmg) {
        cout << 2 << endl;
    } else {
        cout << -1 << endl;
    }

    return 0;
}
