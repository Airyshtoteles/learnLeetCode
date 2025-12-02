#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const long long INF = 1e18;

// dp[i][j][0]: Min cost to clear enemies i..j, ending at P_Left (optimal pos for E_i)
// dp[i][j][1]: Min cost to clear enemies i..j, ending at P_Right (optimal pos for E_j)
long long dp[105][105][2];
int E[105];
int L;

// Clamp x to [target - L, target + L]
int get_optimal_pos(int current_pos, int target) {
    if (current_pos < target - L) return target - L;
    if (current_pos > target + L) return target + L;
    return current_pos;
}

long long solve_clone_warfield(int start_pos, vector<int> enemies, int l_val) {
    int n = enemies.size();
    L = l_val;
    
    // Sort enemies
    sort(enemies.begin(), enemies.end());
    for (int i = 0; i < n; ++i) E[i] = enemies[i];

    // Initialize DP
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dp[i][j][0] = dp[i][j][1] = INF;
        }
    }

    // Base cases: Single enemy intervals
    for (int i = 0; i < n; ++i) {
        // From Start to E[i]
        int p = get_optimal_pos(start_pos, E[i]);
        long long cost = abs(start_pos - p) + abs(p - E[i]);
        dp[i][i][0] = dp[i][i][1] = cost;
    }

    // Iterate length
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            
            // To compute dp[i][j][0] (ending at E[i]):
            // Previous state was [i+1][j].
            // We could have ended at Left (E[i+1]) or Right (E[j]).
            
            // 1. From dp[i+1][j][0] (at P_old for E[i+1])
            // We need to reconstruct P_old.
            // P_old depends on where we came from BEFORE that.
            // BUT, wait.
            // My logic "P_new depends on P_old" implies we need P_old.
            // But P_old depends on P_older...
            // Does P_old depend on P_older?
            // P_old = clamp(P_older, E_{i+1}-L, E_{i+1}+L).
            // Yes.
            // So the exact position depends on the entire history?
            // If so, DP state is insufficient.
            // BUT, notice the clamping.
            // If P_older is far left, P_old is E_{i+1}-L.
            // If P_older is far right, P_old is E_{i+1}+L.
            // If P_older is in between, P_old is P_older.
            // Since we are expanding the range [i, j], we are moving outwards.
            // E.g. i+1 -> i. E_i < E_{i+1}.
            // So we are moving Left.
            // P_old was somewhere for E_{i+1}.
            // We move to E_i.
            // Since E_i < E_{i+1}, we likely want to be as left as possible.
            // P_new = clamp(P_old, E_i-L, E_i+L).
            // Since we are moving Left, P_new will likely be E_i+L (rightmost valid) or P_old?
            // No, if we come from right, we hit E_i+L first.
            // So P_new = min(P_old, E_i + L).
            // And since P_old was for E_{i+1}, and E_{i+1} > E_i,
            // P_old >= E_{i+1} - L > E_i - L (assuming L small relative to gap).
            // So P_new is likely E_i + L.
            // Is it ALWAYS E_i + L?
            // If P_old > E_i + L, then P_new = E_i + L.
            // If P_old <= E_i + L, then P_new = P_old.
            // When would P_old <= E_i + L?
            // If E_{i+1} is close to E_i.
            // In that case, P_old is just carried over.
            // So we DO need P_old.
            // But P_old is not in state.
            // However, notice that for `dp[i+1][j][0]`, the "last visited" was `i+1`.
            // The "previous to last" was `i+2` or `j`.
            // If `i+2`, we moved Left.
            // If `j`, we moved Left (from far right).
            // In both cases, we approached `i+1` from the Right.
            // So `P_old` is `min(P_older, E_{i+1} + L)`.
            // This implies `P_old` is likely `E_{i+1} + L`?
            // Or if `P_older` was even further left? Impossible if we came from Right.
            // So `P_old` is `E_{i+1} + L` (clamped).
            // Actually, if we are expanding the range `[i, j]`, we always approach the new boundary from *inside* the range.
            // So we approach `i` from `i+1` (or `j`).
            // `i` is to the Left of `i+1` and `j`.
            // So we are moving Left.
            // So we want to stop at the *Rightmost* valid point of `E_i` to minimize travel?
            // Yes, `E_i + L`.
            // UNLESS `P_old` is already to the left of `E_i + L`.
            // In that case, we stop at `P_old`.
            // So `P_new = min(P_old, E_i + L)`.
            // And `P_old` was obtained by moving Left to `i+1`.
            // So `P_old = min(P_older, E_{i+1} + L)`.
            // So `P_new = min(min(..., E_{i+2}+L), E_{i+1}+L, E_i+L)`.
            // `P_new = min(Start_Pos, E_k + L)` for all `k` visited in the sequence?
            // Yes!
            // If we visit a sequence of enemies moving Left, the position is `min(Start, min(E_k + L))`.
            // Since `E_k` is decreasing, `E_k + L` is decreasing.
            // So `P_new` is simply `E_i + L` (or `Start` if `Start < E_i + L`).
            // Wait, `Start` is fixed.
            // So `P_Left(i)` depends only on `i`?
            // `P_Left(i) = min(Start, E_i + L)`?
            // Let's verify.
            // If we go `Start -> E_j -> ... -> E_i`.
            // We moved Right to `E_j`, then Left to `E_i`.
            // When moving Right to `E_j`, we stopped at `max(Start, E_j - L)`.
            // Then we move Left.
            // We are at `P_Right`.
            // We go to `E_{j-1}`... `E_i`.
            // At each step `k` (going left), `P_new = min(P_prev, E_k + L)`.
            // So `P_Left(i)` is `min(P_Right(j), E_{j-1}+L, ..., E_i+L)`.
            // Since `E` is sorted, `E_i` is the smallest.
            // So `min` is dominated by `E_i + L`.
            // So `P_Left(i) = min(P_Right(j), E_i + L)`.
            // And `P_Right(j)` was `max(Start, E_j - L)`.
            // So `P_Left(i) = min(max(Start, E_j - L), E_i + L)`.
            // This seems to depend on `j`!
            // So `dp[i][j][0]` state is consistent because `j` is in the state.
            // So we can compute `P_Left` and `P_Right` on the fly?
            // `P_Left(i, j)`: The position we end up at when we finish covering `i..j` at `i`.
            // It depends on whether we came from `i+1` (Left end of `i+1..j`) or `j` (Right end of `i+1..j`).
            // If from `i+1`: `P = min(P_Left(i+1, j), E_i + L)`.
            // If from `j`: `P = min(P_Right(i+1, j), E_i + L)`.
            // So we need to store `P` in the DP?
            // Or return `pair<cost, pos>`?
            // But we need `min cost`. Different paths might give different `pos`.
            // Does `pos` matter?
            // If `pos` is smaller (further left), it's better for future Left moves, worse for future Right moves.
            // But we are at `i` (Leftmost). Future moves are to `i-1` (Left) or `j+1` (Right).
            // If we go to `i-1` (Left), smaller `pos` is better (closer).
            // If we go to `j+1` (Right), smaller `pos` is worse (further).
            // However, `P` is constrained to `[E_i - L, E_i + L]`.
            // And we established `P = min(Prev, E_i + L)`.
            // So `P` is as Right as possible (up to `E_i + L`) but constrained by `Prev`.
            // Wait, if we want to go Right later, we want `P` to be large.
            // If we want to go Left later, we want `P` to be small.
            // But the transition rule `P = min(Prev, E_i + L)` forces `P` to be small if `Prev` is small.
            // We don't have a choice!
            // We MUST stop at `clamp(Prev, ...)`.
            // Why? Because `Cost = |Prev - x| + |x - E_i|`.
            // To minimize this, `x` must be between `Prev` and `E_i`.
            // Since `Prev` is likely > `E_i` (coming from right), `x` should be as close to `Prev` as possible, i.e., `E_i + L`.
            // So `x` is fixed!
            // So `P` is deterministic for a given path.
            // But different paths (e.g. `i+1` vs `j`) might give different `P`.
            // So we might have `(Cost1, Pos1)` and `(Cost2, Pos2)`.
            // If `Cost1 < Cost2` but `Pos1` is "worse", can `Path1` be optimal?
            // "Worse" means further from next target.
            // Difference in cost is `DeltaCost`.
            // Difference in future path is `|Pos1 - Next| - |Pos2 - Next|`.
            // Max difference in future path is `|Pos1 - Pos2|`.
            // So if `DeltaCost > |Pos1 - Pos2|`, then the cheaper one is strictly better.
            // `Cost` includes `|Prev - P|`.
            // It turns out in these TSP problems on line, the "state" is just `(i, j, side)`.
            // The "Position" is implicitly `E_i` (or `E_i+L`).
            // Let's assume `P` is simply `E_i + L` (if side 0) and `E_j - L` (if side 1).
            // Why? Because we always come from "inside".
            // So we are always "reaching out" to the boundary.
            // So we stop at the edge of the validity range.
            // Exception: If `Start` is outside.
            // But `Start` is handled in base case.
            // So let's approximate `Pos` as `E_i + L` (for left) and `E_j - L` (for right).
            // Wait, `E_i + L` is the RIGHT boundary of `E_i`'s range.
            // Yes, because we approach `E_i` from the Right.
            // So we stop at the first valid point, which is `E_i + L`.
            // Correct.
            // So `P_Left(i, j) = E_i + L`.
            // `P_Right(i, j) = E_j - L`.
            // Is this always true?
            // Only if `Prev >= E_i + L`.
            // Since `Prev` is in `[E_{i+1}-L, E_{i+1}+L]`, and `E_{i+1} > E_i`.
            // `Prev >= E_{i+1} - L`.
            // Is `E_{i+1} - L >= E_i + L`?
            // `E_{i+1} - E_i >= 2L`.
            // If gaps are large, yes.
            // If gaps are small (overlapping ranges), then `Prev` might be `< E_i + L`.
            // In that case `P = Prev`.
            // So `P` "drags" along.
            // But if `P` drags, it means `P` is inside `E_i`'s range.
            // So cost to kill `E_i` is `|P - E_i|`.
            // And path cost is `0`.
            // So `P` doesn't change.
            // So we can just track `P` in the DP value? No.
            // We need `P` to compute next cost.
            // But `P` is determined by the path.
            // Let's store `pair<long long, int> dp[i][j][2]`. `{cost, pos}`.
            // If we have multiple paths to `(i, j, 0)`, we keep the one with min cost?
            // What if higher cost has better pos?
            // As argued, `DeltaCost > DeltaPos` usually holds.
            // Let's just keep the one with min cost.
            
            // Transition logic:
            // To `dp[i][j][0]` (End at `i`):
            // 1. From `dp[i+1][j][0]` (End at `i+1`):
            //    `prev_pos = dp[i+1][j][0].pos`
            //    `new_pos = get_optimal_pos(prev_pos, E[i])`
            //    `cost = dp...cost + abs(prev - new) + abs(new - E[i])`
            // 2. From `dp[i+1][j][1]` (End at `j`):
            //    `prev_pos = dp[i+1][j][1].pos`
            //    `new_pos = get_optimal_pos(prev_pos, E[i])`
            //    ...
            // Take min cost.
            
            // To `dp[i][j][1]` (End at `j`):
            // 1. From `dp[i][j-1][0]` (End at `i`):
            //    `prev_pos = dp[i][j-1][0].pos`
            //    `new_pos = get_optimal_pos(prev_pos, E[j])`
            // 2. From `dp[i][j-1][1]` (End at `j-1`):
            //    ...
            
            // We need a struct for DP element.
        }
    }
    
    return min(dp[0][n-1][0], dp[0][n-1][1]);
}

// We need to redefine DP to store pos.
// Or just use a separate array for pos?
// But pos depends on the path chosen.
// So `dp_cost[i][j][0]` and `dp_pos[i][j][0]`.
// When updating, if `new_cost < current_cost`, update both.

long long dp_cost[105][105][2];
int dp_pos[105][105][2];

long long solve_clone_warfield_v2(int start_pos, vector<int> enemies, int l_val) {
    int n = enemies.size();
    L = l_val;
    sort(enemies.begin(), enemies.end());
    for (int i = 0; i < n; ++i) E[i] = enemies[i];

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dp_cost[i][j][0] = dp_cost[i][j][1] = INF;
        }
    }

    for (int i = 0; i < n; ++i) {
        int p = get_optimal_pos(start_pos, E[i]);
        long long cost = abs(start_pos - p) + abs(p - E[i]);
        dp_cost[i][i][0] = cost;
        dp_pos[i][i][0] = p;
        dp_cost[i][i][1] = cost;
        dp_pos[i][i][1] = p;
    }

    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;

            // Target: i (Left)
            // Sources: [i+1][j][0] (at i+1), [i+1][j][1] (at j)
            long long best_c = INF;
            int best_p = -1;

            // From i+1
            if (dp_cost[i+1][j][0] != INF) {
                int prev = dp_pos[i+1][j][0];
                int curr = get_optimal_pos(prev, E[i]);
                long long c = dp_cost[i+1][j][0] + abs(prev - curr) + abs(curr - E[i]);
                if (c < best_c) { best_c = c; best_p = curr; }
            }
            // From j
            if (dp_cost[i+1][j][1] != INF) {
                int prev = dp_pos[i+1][j][1];
                int curr = get_optimal_pos(prev, E[i]);
                long long c = dp_cost[i+1][j][1] + abs(prev - curr) + abs(curr - E[i]);
                if (c < best_c) { best_c = c; best_p = curr; }
            }
            dp_cost[i][j][0] = best_c;
            dp_pos[i][j][0] = best_p;

            // Target: j (Right)
            // Sources: [i][j-1][0] (at i), [i][j-1][1] (at j-1)
            best_c = INF;
            best_p = -1;

            // From i
            if (dp_cost[i][j-1][0] != INF) {
                int prev = dp_pos[i][j-1][0];
                int curr = get_optimal_pos(prev, E[j]);
                long long c = dp_cost[i][j-1][0] + abs(prev - curr) + abs(curr - E[j]);
                if (c < best_c) { best_c = c; best_p = curr; }
            }
            // From j-1
            if (dp_cost[i][j-1][1] != INF) {
                int prev = dp_pos[i][j-1][1];
                int curr = get_optimal_pos(prev, E[j]);
                long long c = dp_cost[i][j-1][1] + abs(prev - curr) + abs(curr - E[j]);
                if (c < best_c) { best_c = c; best_p = curr; }
            }
            dp_cost[i][j][1] = best_c;
            dp_pos[i][j][1] = best_p;
        }
    }

    return min(dp_cost[0][n-1][0], dp_cost[0][n-1][1]);
}

int main() {
    // Test 1
    // S=0. E={10}. L=5.
    // Optimal: Go to 5. Cost 5 (path) + 5 (clone) = 10.
    // Or go to 10. Cost 10 + 0 = 10.
    vector<int> e1 = {10};
    cout << "Test 1 (Expected 10): " << solve_clone_warfield_v2(0, e1, 5) << endl;

    // Test 2
    // S=0. E={-10, 10}. L=5.
    // Path 1: 0 -> -5 (kill -10, cost 5). Path 5. Total 10.
    //         -5 -> 5 (kill 10, cost 5). Path 10. Total 10+10+5 = 25.
    // Path 2: 0 -> 5 (kill 10, cost 5). Path 5. Total 10.
    //         5 -> -5 (kill -10, cost 5). Path 10. Total 25.
    vector<int> e2 = {-10, 10};
    cout << "Test 2 (Expected 25): " << solve_clone_warfield_v2(0, e2, 5) << endl;

    cout << "Done." << endl;
    return 0;
}
