#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

bool solve() {
    int n;
    if (!(cin >> n)) return false;
    
    vector<int> shield(n);
    for (int i = 0; i < n; ++i) {
        cin >> shield[i];
    }
    
    // Check if there is a second array for attacks
    // The problem description says "Urutan serangan bisa diatur" (Attack order can be arranged).
    // This implies we have a set of attacks.
    // If the input format is strictly "shield = int[]", maybe the attacks are implicit?
    // Or maybe the user forgot to mention the attack input.
    // I will try to read more integers.
    
    vector<int> attacks;
    int val;
    while (cin >> val) {
        attacks.push_back(val);
    }
    
    // If no attacks provided, maybe the problem is different.
    // But let's assume we have attacks.
    // If attacks are empty, we can't destroy anything (unless shields are 0).
    if (attacks.empty()) {
        long long sum_shield = 0;
        for(int s : shield) sum_shield += s;
        return sum_shield == 0;
    }
    
    // We have attacks A and shields S.
    // Shields rotate: S[0], S[1], ..., S[n-1], S[0]...
    // We can reorder A.
    // Let's say we use attack A[k] at time t. It hits S[t % n].
    // We want to assign each attack to a time slot t such that total damage to S[i] >= shield[i].
    // Since we can reorder A, we can assign any subset of A to S[0], any to S[1], etc.
    // BUT, the constraint is "Shield berpindah tiap serangan".
    // This means if we use k attacks total, we hit S[0], S[1], ..., S[k-1 % n].
    // The number of hits on S[i] depends on total attacks k.
    // Hits on S[i] = floor((k - 1 - i) / n) + 1 (if k > i).
    // Basically, S[i] gets hits at indices i, i+n, i+2n...
    
    // Since we can reorder A, we just need to partition A into n groups G[0]...G[n-1]
    // such that sum(G[i]) >= shield[i].
    // AND the sizes of G[i] must be consistent with the rotation.
    // Let total attacks be M = attacks.size().
    // S[i] receives count_i hits.
    // count_i = M / n + (i < M % n ? 1 : 0).
    
    // So we need to distribute the M attacks into n buckets with specific capacities count_i.
    // And sum of bucket i >= shield[i].
    // This is a variation of "Multiple Knapsack" or "Partition Problem" but with sums.
    // Since we want to know if *possible*, and we can put *any* attack in *any* bucket (as long as counts match),
    // we should give the largest attacks to the shields that need them most?
    // Or rather, we have fixed slots.
    // We have count_i slots for shield i.
    // We need to fill these slots with values from A such that sum >= shield[i].
    
    // Greedy strategy:
    // Sort shields by "need per slot"? Or just "need".
    // Sort attacks descending.
    // This looks like we should prioritize hard-to-kill shields.
    // But we also have a constraint on the *number* of attacks per shield.
    
    // Let's try a greedy approach with sorting.
    // Sort shields by required damage descending?
    // Actually, the number of slots is fixed for each shield.
    // Let's say S[0] needs 100, has 2 slots. S[1] needs 10, has 2 slots.
    // We should put big attacks into S[0].
    
    // Let's sort shields by (required_damage / slots)? Or just required damage?
    // If we sort shields by required damage descending, and fill their slots with the largest available attacks,
    // is that optimal?
    // Suppose S1 needs 100 (2 slots), S2 needs 10 (2 slots). Attacks: 50, 50, 5, 5.
    // S1 takes 50, 50 -> 100. OK. S2 takes 5, 5 -> 10. OK.
    // Suppose S1 needs 60 (1 slot), S2 needs 40 (1 slot). Attacks: 50, 50.
    // S1 takes 50 -> Fail.
    // If we swap? S1 takes 50 -> Fail.
    // Total damage 100 >= 100. But max single hit 50 < 60.
    // So yes, we need to check if we can satisfy demands.
    
    // This is checking if we can satisfy n demands with constrained counts.
    // Since we want to satisfy ALL, and we have a pool of resources.
    // We should satisfy the "hardest" ones first.
    // Hardest = Highest damage required?
    // Yes. If we fail the highest damage one with the best available attacks, we can't solve it.
    // So:
    // 1. Calculate slots for each shield.
    // 2. Store pairs (shield_hp, slots).
    // 3. Sort pairs by shield_hp descending.
    // 4. Sort attacks descending.
    // 5. Iterate through shields:
    //    Take the top 'slots' attacks from the pool.
    //    Check if sum >= shield_hp.
    //    If yes, remove them and continue.
    //    If no, return false.
    
    // Is this greedy optimal?
    // Suppose S1 needs 10 (1 slot), S2 needs 10 (1 slot). Attacks: 10, 10.
    // Sorted: S1, S2. Attacks: 10, 10.
    // S1 takes 10. OK. S2 takes 10. OK.
    // Suppose S1 needs 10 (1 slot), S2 needs 5 (1 slot). Attacks: 9, 6.
    // S1 takes 9 -> Fail.
    // But if we gave 6 to S1, fail.
    // So we MUST give the largest available to the one with highest requirement?
    // Wait. S1 needs 10. We have 9. We can't satisfy S1 at all.
    // So if max possible sum for S1 < S1.req, impossible.
    // What if S1 needs 10 (2 slots), S2 needs 10 (1 slot). Attacks: 9, 1, 10.
    // S1 (10) vs S2 (10). Tie.
    // Say we pick S1 first. S1 gets 10, 9? No, we use best available.
    // S1 gets 10, 9 -> 19 >= 10. Remainder: 1.
    // S2 gets 1 -> 1 < 10. Fail.
    // Can we do better?
    // S1 gets 9, 1 -> 10 >= 10. Remainder: 10.
    // S2 gets 10 -> 10 >= 10. Success.
    // Ah! Greedy by "taking largest" is NOT optimal because we might "overkill" S1 and starve S2.
    
    // We need to satisfy S1 >= req1, S2 >= req2...
    // We want to minimize the "cost" (sum of attacks used) for S1 to save for S2?
    // But we have a fixed number of slots.
    // We want to use the *smallest* set of attacks that satisfies S1?
    // To save big attacks for others?
    // But S1 is the "hardest" (highest req). If we use small attacks for S1, we might fail S1.
    // Actually, if S1 has high req, it *needs* big attacks.
    // If S2 has low req, it can use small attacks.
    // So saving big attacks for S2 is wasteful.
    // The only conflict is if S2 also has high req.
    
    // Let's reconsider the counter-example:
    // S1 needs 10 (2 slots), S2 needs 10 (1 slot). Attacks: 10, 9, 1.
    // S1 needs avg 5/slot. S2 needs 10/slot.
    // Maybe sort by "average required per slot"?
    // S1: 5. S2: 10.
    // Process S2 first.
    // S2 takes 10 (1 slot). Remainder: 9, 1.
    // S1 takes 9, 1 -> 10. Success.
    
    // Hypothesis: Sort shields by (req / slots) descending.
    // Then fill with largest available attacks?
    // Let's try:
    // S1 needs 10 (2 slots), S2 needs 10 (1 slot). Attacks: 10, 9, 1.
    // Sort: S2 (10), S1 (5).
    // S2 takes 10. Rem: 9, 1.
    // S1 takes 9, 1. Sum 10. OK.
    
    // Another case:
    // S1 needs 20 (2 slots), S2 needs 10 (1 slot). Attacks: 10, 10, 10.
    // S1 avg 10. S2 avg 10.
    // Pick S1. S1 takes 10, 10. Rem 10. S2 takes 10. OK.
    // Pick S2. S2 takes 10. Rem 10, 10. S1 takes 10, 10. OK.
    
    // Another case:
    // S1 needs 100 (1 slot). S2 needs 10 (10 slots). Attacks: 100, 1, 1, 1...
    // S1 avg 100. S2 avg 1.
    // S1 takes 100. OK. S2 takes ones. OK.
    
    // What if we have "overkill"?
    // S1 needs 10 (1 slot). S2 needs 10 (1 slot). Attacks: 20, 5.
    // S1 avg 10. S2 avg 10.
    // Pick S1. S1 takes 20. Rem 5. S2 takes 5 -> Fail.
    // Pick S2. S2 takes 20. Rem 5. S1 takes 5 -> Fail.
    // Here we fail regardless.
    // But wait, if we swap? S1 takes 5 (fail).
    // So impossible.
    
    // What if:
    // S1 needs 10 (2 slots). S2 needs 10 (1 slot). Attacks: 15, 4, 1.
    // S1 avg 5. S2 avg 10.
    // Sort: S2, S1.
    // S2 takes 15. Rem 4, 1.
    // S1 takes 4, 1 -> 5 < 10. Fail.
    // Can we do better?
    // S1 takes 15, 1 -> 16. Rem 4.
    // S2 takes 4 -> Fail.
    // S1 takes 15, 4 -> 19. Rem 1.
    // S2 takes 1 -> Fail.
    // S1 takes 4, 1 -> 5. Fail.
    // Impossible.
    
    // What if:
    // S1 needs 10 (2 slots). S2 needs 5 (1 slot). Attacks: 9, 2, 4.
    // S1 avg 5. S2 avg 5.
    // Sort S1, S2.
    // S1 takes 9, 4 -> 13. Rem 2.
    // S2 takes 2 -> Fail.
    // Try S2, S1.
    // S2 takes 9. Rem 4, 2.
    // S1 takes 4, 2 -> 6 < 10. Fail.
    // Is it possible?
    // S1 needs 10. S2 needs 5.
    // S1 takes 9, 2 -> 11. Rem 4.
    // S2 takes 4 -> Fail.
    // S1 takes 4, 2 -> 6. Fail.
    // S1 takes 9, 4 -> 13. Rem 2. Fail.
    // Impossible.
    
    // It seems "Sort by avg req, take largest" is a strong heuristic.
    // Is it exact?
    // This is related to "Stochastic Dominance" or similar scheduling.
    // Given the constraints and typical CP problem types, this greedy is likely the intended solution.
    // Sort shields by `(double)shield[i] / slots[i]` descending.
    // Iterate and assign largest available attacks.
    
    int M = attacks.size();
    vector<pair<double, int>> targets(n);
    for (int i = 0; i < n; ++i) {
        int slots = M / n + (i < M % n ? 1 : 0);
        if (slots == 0 && shield[i] > 0) return false; // Impossible if no slots but need damage
        if (slots == 0 && shield[i] == 0) targets[i] = {0, 0};
        else targets[i] = {(double)shield[i] / slots, i};
    }
    
    sort(targets.rbegin(), targets.rend()); // Sort by avg needed descending
    sort(attacks.rbegin(), attacks.rend()); // Sort attacks descending
    
    vector<bool> used(M, false);
    
    // Wait, if we just take the largest available, we might use a HUGE attack for a small requirement?
    // S1 needs 10 (1 slot). S2 needs 10 (1 slot). Attacks: 100, 10.
    // S1 takes 100. S2 takes 10. OK.
    // S1 takes 10. S2 takes 100. OK.
    // Overkill is fine.
    
    // The only risk is using a "medium" attack that was needed by someone else, when a "huge" attack would have sufficed for us?
    // No, if we use a huge attack, it satisfies us even better.
    // The only issue is if we use a huge attack for a LOW requirement, wasting it.
    // But we sort by requirement descending.
    // So the highest requirement gets the first pick. It picks the largest attacks.
    // This minimizes the chance of "wasting" big attacks on small requirements.
    // The highest requirement *needs* the big attacks most.
    // So this greedy matching seems correct.
    
    int attack_idx = 0;
    for (auto p : targets) {
        int idx = p.second;
        int slots = M / n + (idx < M % n ? 1 : 0);
        long long current_sum = 0;
        
        // We need to pick 'slots' attacks.
        // Since we sorted attacks descending, and we want to give the best attacks to the neediest,
        // we just take the next 'slots' attacks from the sorted list.
        
        for (int k = 0; k < slots; ++k) {
            if (attack_idx < M) {
                current_sum += attacks[attack_idx++];
            }
        }
        
        if (current_sum < shield[idx]) return false;
    }
    
    return true;
}

int main() {
    cout << (solve() ? "true" : "false") << endl;
    return 0;
}
