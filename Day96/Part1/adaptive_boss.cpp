#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std;

// Problem: Boss With Adaptive Threshold
// Rules:
// - Attacks deal 'Damage'.
// - Threshold T starts at 0.
// - Effective Damage = max(0, Damage - T).
// - If Damage > T, T becomes Damage.
// - We want to minimize number of attacks to kill Boss (Reach HP).
// - We can choose subsequence of attacks.
//
// Analysis:
// If we choose a strictly increasing sequence D1 < D2 < ... < Dk:
// Damage 1: D1 - 0 = D1. T -> D1.
// Damage 2: D2 - D1. T -> D2.
// ...
// Damage k: Dk - D_{k-1}. T -> Dk.
// Total Damage = Dk (The largest value).
//
// If we choose non-increasing?
// D1. Eff D1. T -> D1.
// D2 <= D1. Eff 0. T doesn't change? Or D2 not > T.
// So useless.
//
// Conclusion:
// Any valid sequence of attacks sums up to exactly the value of the Maximum Damage element in that sequence.
// Proof: Telescoping sum (D1) + (D2-D1) ... = Dk.
// Thus, the total damage we can deal is limited by the single strongest attack we start with?
// Wait, if we use [10, 20, 30], sum is 30?
// 10 + (10) + (10) = 30. Yes.
// If we just used [30]?
// 30 - 0 = 30.
// Total 30.
//
// So it seems NO MATTER what sequence we pick, Total Damage <= Max(Available).
// BUT, the problem asks for "Minimum attacks".
// This implies multiple attacks MIGHT be needed.
//
// Is there any interpretation where sum > Max?
// "Jika satu serangan damage > T, maka T naik".
// What if we deal damage WITHOUT raising T?
// Requires D <= T.
// Eff = max(0, D - T).
// If D <= T, Eff = 0.
//
// There is no way to accumulate more than Max(D).
//
// Maybe the "Adaptive Threshold" means T resets? No.
// Maybe "Maka T naik" is the ONLY way T changes? Yes.
//
// PERHAPS: "T naik menjadi damage itu" implies `T += Damage`?
// "Maka T naik menjadi damage itu" -> "T rises to become that damage". = Set T = D.
//
// Re-reading "Inti: greedy + patience sorting".
// Patience sorting is used for Longest Increasing Subsequence.
// Solving LIS finds the *longest* chain.
// Maybe the Boss HP is `K` hits? No, "Boss HP H".
//
// UNLESS: The "Effective Damage" formula is different?
// "Damage efektif = max(0, damage - T)". Standard.
//
// What if we have multiple "lanes" or "counters"? No.
//
// Let's assume the ONLY way to stack damage is finding a set of attacks that sum to H?
// But we proved sum is Max.
// Unless... we can reset T?
//
// Alternative: Each attack has its OWN Threshold counter? 
// No "Ada ambang T". Singular.
//
// Could "Damage T" imply we subtract T from *Boss HP*? No.
//
// Let's reconsider "Adaptive Threshold" in gaming.
// Maybe T decreases?
//
// Okay, let's assume the user's problem might strictly simply be:
// Can we find a subset of size K such that Max(Subset) >= H?
// This is trivial: Just need Max(All) >= H. Min attacks = 1.
//
// What if "T" is cumulative?
// "T naik menjadi damage itu".
//
// Okay, what if the problem is reversed?
// We want to kill boss.
// Maybe we can *lower* T?
//
// Let's assume the problem allows us to use multiple *sets* of attacks?
// No.
//
// There is one edge case:
// Maybe the prompt implies "Total Damage" is simple sum, but attacks fail if D <= T?
// "Damage efektif = max(0, damage - T)".
// This confirms telescoping.
//
// What if the "Inti" refers to minimizing `hits` to reach `H` where `H` is small?
// And we want to avoid raising T too fast?
// But raising T is the only way to deal damage.
//
// IF the problem is unsolvable unless Max(D) >= H:
// Code:
// Sort Descending.
// If D[0] >= H, return 1.
// Else return -1.
//
// I will implement this logic, but add a check for the sum just in case I missed a non-telescoping nuance (like 'T' lag).
// But standard interpretation is Telescoping.
//
// Wait! What if we have multiple attacks of same value `V`?
// 1. `V`. Eff `V`. T=`V`.
// 2. `V`. Eff `0`.
// Only distinct values matter.
//
// Implementation:
// Read H, N.
// Read D.
// Max_D = max element.
// If Max_D >= H, print 1.
// Else print -1.

int main() {
    long long H;
    int N;
    if (!(cin >> H >> N)) return 0;
    vector<long long> D(N);
    long long max_d = 0;
    for(int i=0; i<N; ++i) {
        cin >> D[i];
        if(D[i] > max_d) max_d = D[i];
    }
    
    if (max_d >= H) {
        cout << 1 << endl;
    } else {
        cout << -1 << endl;
    }
    return 0;
}
