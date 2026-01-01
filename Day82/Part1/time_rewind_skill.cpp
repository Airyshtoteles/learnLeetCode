#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int main() {
    int n;
    if (!(cin >> n)) return 0;

    vector<long long> c(n);
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }

    // Key insight: When we use skill i, time rewinds by c[i].
    // This means all cooldowns (including c[i] itself after being used) rewind by c[i].
    //
    // If we use skills in order i1, i2, ..., in:
    // - Before i1: all cooldowns = 0
    // - After i1: time = -c[i1], so all cooldowns decrease by c[i1] from 0
    //   But we "rewind", so it's as if c[i1] time didn't pass for cooldowns?
    //   The cooldowns of other skills were 0, so they remain effectively at 0 (can be used next).
    //   But i1's cooldown becomes... unclear.
    //
    // Re-interpretation: "waktu mundur" = time goes backward.
    // If at absolute time T, we use skill i, time becomes T - c[i].
    // Cooldowns that were at their "ready" time (0) still need to wait again after time reversal?
    // Or do they stay ready?
    //
    // Simpler interpretation: Each skill can only be used once (constraint given).
    // Time rewind doesn't prevent future use within the same "timeline".
    // We just need to check if there's a valid order.
    //
    // Since each skill can only be used once and initially all cooldowns are 0,
    // and using a skill doesn't create new cooldowns for other skills (only time rewind),
    // the answer is likely "true" for any n >= 1, as long as there's no circular dependency.
    //
    // Actually, re-reading: "Skill hanya bisa dipakai jika cooldown = 0".
    // And "Tidak boleh pakai skill yang sama dua kali".
    // If all start at cooldown 0, and using a skill rewinds time for all cooldowns,
    // then we can use any skill first (cooldown = 0), and time rewinds.
    // But for the next skill to be used, its cooldown must be 0.
    // If time rewind keeps cooldowns at 0 for others, we can use any order.
    //
    // Check for infinite loop: If using skills in some order causes time to loop back
    // to a state we've seen, that's an infinite loop.
    // Sum of all rewinds: sum(c[i]) for all i.
    // If sum > 0, time rewinds overall, which could cause loops.
    // If sum <= 0, time moves forward or stays neutral.
    //
    // Constraint: "Tidak boleh pakai skill yang sama dua kali" suggests each skill once.
    // So we need to check if we can use all n skills exactly once without infinite loop.

    long long total_rewind = 0;
    for (int i = 0; i < n; ++i) {
        total_rewind += c[i];
    }

    if (total_rewind == 0) {
        cout << "true" << endl;
    } else if (total_rewind > 0) {
        // Time rewinds overall. This could cause infinite loops.
        cout << "false" << endl;
    } else {
        // total_rewind < 0: time moves forward overall.
        cout << "true" << endl;
    }

    return 0;
}
