#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    if (!(cin >> n)) return 0;

    vector<int> c(n);
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }

    // Strategy: Sort cooldowns in ascending order.
    // We assume the problem implies:
    // 1. Skills have initial cooldowns c[i].
    // 2. Using a skill takes 1 unit of time.
    // 3. During this time, other skills decay by 1 (natural) + 1 (bonus) = 2.
    // 4. We want to minimize total time.
    // By using small c[i] first, we allow large c[i] to decay faster for longer.
    
    sort(c.begin(), c.end());

    long long current_time = 0;
    
    // We simulate the process
    // However, the "cooldown" is relative to the start.
    // If we use skill i at absolute time T, we must have T >= c[i] - (decay from previous moves).
    // Let's track the "effective cooldown remaining" for each skill?
    // No, simpler:
    // Skill i needs c[i] initial wait.
    // If we use it as the k-th skill (0-indexed), it has received k * 2 decay.
    // So we need to wait max(0, c[i] - k * 2) additional time?
    // No, we need to wait until absolute time T such that T >= c[i] - (bonus decay).
    // Natural decay is included in T.
    // Bonus decay is k * 1.
    // So T >= c[i] - k.
    // Also T must be at least (previous_finish_time + 1).
    
    // Let's trace:
    // Skill 0: Wait c[0]. Time = c[0]. Finish = c[0] + 1.
    // Skill 1: Needs c[1]. Has received 1 bonus decay.
    //          Must start at T >= c[1] - 1.
    //          Also T >= Finish_0 = c[0] + 1.
    //          Start_1 = max(c[0] + 1, c[1] - 1).
    //          Finish_1 = Start_1 + 1.
    // Skill k: Needs c[k]. Has received k bonus decay.
    //          Start_k = max(Finish_{k-1}, c[k] - k).
    
    long long finish_time = 0;
    
    for (int k = 0; k < n; ++k) {
        long long required_start = c[k] - k;
        long long actual_start = max(finish_time, required_start);
        finish_time = actual_start + 1;
    }
    
    // The total time is the finish time of the last skill.
    // Wait, "waktu minimum untuk menggunakan semua skill".
    // Usually means the time the last skill *finishes* or *starts*?
    // "menggunakan" usually implies the action.
    // If action takes 1 unit, then finish time.
    // If action is instant but we wait, then start time.
    // Let's assume finish time (since "butuh waktu" in previous problems).
    // Actually, if we just need to "use" them, maybe just the time we trigger the last one?
    // Let's output the time the last operation completes.
    
    cout << finish_time << endl;

    return 0;
}
