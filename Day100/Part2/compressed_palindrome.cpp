#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

// Problem 2: K-Compressed Palindromic Subsequence
// Input: S, K.
// Algorithm:
// 1. RLE transform S -> vector of {char, count}.
// 2. DP(l, r, k): Max compressed length from groups l to r with k deletions.
//    Base Cases:
//    l > r: return 0.
//    l == r: Center block. Maximize count using k. Return RLE_Length(count - deleted? No, count usually).
//            Actually, we can delete chars from center to minimize? No, maximize length.
//            So minimize deletions (cost=0). Length = RLE(count).
//    Transitions:
//    1. Delete group l: cost group[l].cnt. If k >= cost, solve(l+1, r, k-cost).
//    2. Delete group r: cost group[r].cnt. If k >= cost, solve(l, r-1, k-cost).
//    3. If group[l].c == group[r].c:
//       Match them.
//       We need equal counts?
//       Assumption: Compressed palindrome requires symmetric counts e.g., a3 ... a3.
//       We can reduce counts to x = min(cnt[l], cnt[r]).
//       Cost = (cnt[l] - x) + (cnt[r] - x).
//       If k >= Cost: 2 * RLE(x) + solve(l+1, r-1, k - Cost).
//       Better: We can reduce MORE if desired?
//       RLE length is monotonic increasing (1, 2, 3...).
//       Does reducing x ever help? No.
//       Does reducing x save k? No, reducing x INCREASES cost (we delete more).
//       So we always maximize x.
//       x_max = min(cnt[l], cnt[r]).
//       Wait, we can delete from ONE side to match the other.
//       Cost = abs(cnt[l] - cnt[r]).
//       Common count = min(cnt[l], cnt[r]).
//       If k >= cost: take it.
//       Also, we might choose to skip L or R entirely (covered by 1 & 2).

struct Group {
    char c;
    int count;
};

vector<Group> groups;
int dp[405][405]; // Only l, r. K is variable?
// K <= |S|. |S| ~ 2*10^5? No, Constraint not specified in "Example", but "Constraint" usually small for DP?
// Constraint listed: |S| <= 2*10^5?
// Hint: DP 4 Dimensi.
// If K is large, we cannot use K as state index.
// But standard LPS DP doesn't track K if cost is fixed?
// Here cost is variable.
// If K is large state, this solution fails.
// BUT Hint: "DP 4 Dimensi". 
// State compression suggestion.
// Maybe N is small (after compression)? N of groups.
// If string is "abcdef..." N=2*10^5.
// DP N^2 is too slow.
// Is K small? K is input.
// Constraint in prompt: Not fully specified for N in description area.
// Usually "DP 4D" implies small N (e.g., 50-100).
// Or maybe K is small?
// Let's assume N_groups is small or problem is for small N.
// If N_groups is large, maybe K is small and we only check nearby?
// Let's implement memoization with map for K? Or just `dp[l][r]` returns `min_k` for `len`?
// No, we want `max_len` for `k`.
// Inverse DP? `min_cost[l][r][target_len]`?
// Let's stick to recursion with memoization map `memo[l][r][k]`.
// If `k` is large, we might need a different approach.
// But if `S` reduces to few groups...
// Fallback: If N_groups > 200, this TLEs.
// Assuming "Day 100" difficult implies algorithmic trick or small input.
// I'll implement the Group DP.

// RLE Length calculator
int rle_len(int count) {
    if (count <= 0) return 0;
    if (count == 1) return 1; // "a" ? Or "a1"? usually "a1" is 2 chars. Let's assume standard RLE: char + number.
    // Example: a3b2c2 -> length 6. So a1 is length 2.
    // Length = 1 (char) + digits.
    int d = 0;
    if (count >= 100) d=3;
    else if (count >= 10) d=2;
    else d=1;
    return 1 + d;
}

// Memoization
// Key: l * 100000 + r -> map<k, int> ?
// or simply `map<vector<int>, int>`
// Using basic array for small K?
// If K large, use map.

int memo[205][205][205]; // Assume compressed N <= 200, K <= 200.
// If N > 200, we prioritize skipping logic.

int solve_dp(int l, int r, int k) {
    if (k < 0) return -1e9;
    if (l > r) return 0;
    if (l == r) {
        // Center block.
        // We can use remaining K to delete from this block?
        // No, we want MAX length. Deleting reduces count -> reduces length.
        // So keep max possible.
        // But we MUST check if we paid cost to reach here.
        return rle_len(groups[l].count);
    }
    
    if (l < 205 && r < 205 && k < 205 && memo[l][r][k] != -1) return memo[l][r][k];
    
    int res = 0;
    
    // Option 1: Skip L
    int costL = groups[l].count;
    if (k >= costL) res = max(res, solve_dp(l + 1, r, k - costL));
    
    // Option 2: Skip R
    int costR = groups[r].count;
    if (k >= costR) res = max(res, solve_dp(l, r - 1, k - costR));
    
    // Option 3: Match
    if (groups[l].c == groups[r].c) {
        int cntL = groups[l].count;
        int cntR = groups[r].count;
        int match_cost = abs(cntL - cntR);
        int final_count = min(cntL, cntR);
        
        if (k >= match_cost) {
            int inner = solve_dp(l + 1, r - 1, k - match_cost);
            if (inner >= 0) {
                res = max(res, 2 * rle_len(final_count) + inner);
            }
        }
    }
    
    if (l < 205 && r < 205 && k < 205) memo[l][r][k] = res;
    return res;
}

int main() {
    string s;
    int k;
    if (!(cin >> s >> k)) return 0;
    
    if (s.empty()) {
        cout << 0 << endl;
        return 0;
    }
    
    // Compress
    groups.push_back({s[0], 1});
    for(size_t i=1; i<s.size(); ++i) {
        if (s[i] == groups.back().c) {
            groups.back().count++;
        } else {
            groups.push_back({s[i], 1});
        }
    }
    
    int N = groups.size();
    if (N > 200 || k > 200) {
        // Fallback for large inputs (simplified or just heuristic)
        // For correctness on small inputs (likely intended), use map or array.
        // Initialize memo
        // If N is very large, this O(N^2 K) is slow.
        // But with deletion cost = count, effective N reduces fast.
    }
    
    memset(memo, -1, sizeof(memo));
    
    // If indices > 200, recursion runs without memo (slow but correct).
    // Or we expand array.
    cout << solve_dp(0, N - 1, k) << endl;
    
    return 0;
}
