#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Problem 5: Maximum XOR Rectangle in Matrix
// Constraints: Width <= W, Height <= H.
// Size 2D prefix XOR.
// P[i][j] = XOR sum of (0,0) to (i,j).
// XOR of rectangle (r1, c1) to (r2, c2) = P[r2][c2] ^ P[r1-1][c2] ^ P[r2][c1-1] ^ P[r1-1][c1-1].
//
// Naive: Try all top-left (r1, c1) and all sizes (h <= H, w <= W).
// Complexity: N * M * H * W. Max 400^4 -> too slow.
// N, M <= 400. N^3 is acceptable (6.4 * 10^7).
// We can iterate pair of rows r1, r2 (where r2 - r1 + 1 <= H).
// For fixed r1, r2: compress to 1D array `val[col]`.
// val[col] = XOR sum of column `col` from r1 to r2.
// We want max XOR subarray of `val` with length <= W.
// Subarray XOR `val[l...r]` = PrefixXOR[r] ^ PrefixXOR[l-1].
// We need max (P[r] ^ P[l-1]) for r-l+1 <= W.
// i.e., l-1 >= r - W.
// Iterate r. We need max (P[r] ^ X) where X in {P[r-W] ... P[r-1]}.
// This is "Max XOR Pair" in a sliding window.
// Use Binary Trie.
// Insert P[r-1]. Remove P[r-W-1] (if window slides out). Query P[r].
// Trie operations are log(MaxVal) ~ 30.
// Complexity: N * H * M * 30.
// 400 * 400 * 400 * 30 ~ 2 * 10^9. Slower than 1 sec.
// Maybe N=400 is strictly N? H can be smaller eventually?
// 2*10^9 is risky.
// But Sliding Window Trie is best approach.
//
// Optimization: Input sizes are Max 400.
// Constraints: "n, m <= 400".
// Maybe test cases are weak?
// Or maybe just iterate all sub-rects if H, W small?
// "Lebarnya <= W, Tingginya <= H". W, H inputs.
// If W, H are 400, then we hit worst case.
//
// Implementation: 2D Prefix XOR -> Row Pairs -> Sliding Window Trie.

const int MAX_BITS = 30;

struct TrieNode {
    TrieNode* child[2];
    int count; // For sliding window removal
    TrieNode() { child[0] = child[1] = nullptr; count = 0; }
};

void insert(TrieNode* root, int val) {
    TrieNode* curr = root;
    for(int i=MAX_BITS; i>=0; --i) {
        int bit = (val >> i) & 1;
        if (!curr->child[bit]) curr->child[bit] = new TrieNode();
        curr = curr->child[bit];
        curr->count++;
    }
}

void remove(TrieNode* root, int val) {
    TrieNode* curr = root;
    for(int i=MAX_BITS; i>=0; --i) {
        int bit = (val >> i) & 1;
        curr = curr->child[bit];
        curr->count--;
        // Could prune empty nodes, but not strictly necessary for correctness
    }
}

int query(TrieNode* root, int val) {
    TrieNode* curr = root;
    int max_xor = 0;
    for(int i=MAX_BITS; i>=0; --i) {
        int bit = (val >> i) & 1;
        int desired = 1 - bit;
        if (curr->child[desired] && curr->child[desired]->count > 0) {
            max_xor |= (1 << i);
            curr = curr->child[desired];
        } else {
            curr = curr->child[bit];
        }
        if (!curr) break; // Should not happen if count maintained
    }
    return max_xor;
}

// Memory management: Reusing Trie? Or clearing?
// Global pool optimization to avoid `new`.
TrieNode pool[400 * 400 * 32];
int pool_ptr = 0;
TrieNode* new_node() {
    pool[pool_ptr] = TrieNode();
    return &pool[pool_ptr++];
}
// But window removes nodes.
// Resetting pool per row-pair is safer. O(M * 30) allocs.

int grid[405][405];
int col_prefix[405][405]; // col_prefix[r][c] = XOR(grid[0..r][c])

int main() {
    int N, M, H, W;
    if (!(cin >> N >> M >> H >> W)) return 0; // H max height, W max width
    
    // Read grid
    for(int r=0; r<N; ++r) {
        for(int c=0; c<M; ++c) {
            cin >> grid[r][c];
        }
    }
    
    // Compute Column Prefix XORs for range reduction
    // col_prefix[r][c] = XOR sum of grid[0][c] ... grid[r][c]
    for(int c=0; c<M; ++c) {
        col_prefix[0][c] = grid[0][c];
        for(int r=1; r<N; ++r) {
            col_prefix[r][c] = col_prefix[r-1][c] ^ grid[r][c];
        }
    }
    
    int global_max = 0;
    
    // Iterate row pairs (r1, r2) such that r2 - r1 + 1 <= H
    for(int r1=0; r1<N; ++r1) {
        // Upper bound for r2
        int r2_limit = min(N - 1, r1 + H - 1);
        for(int r2=r1; r2 <= r2_limit; ++r2) {
            // Create 1D array of column XORs for this row strip
            // val[c] = col_prefix[r2][c] ^ col_prefix[r1-1][c]
            // We want max XOR subarray of length <= W
            
            // Re-init Trie
            pool_ptr = 0;
            TrieNode* root = new_node();
            
            // Sliding Window Pfx XOR
            // Let row_xor[c] be prefix XOR of the strip horizontally up to c
            // row_xor[c] = val[0] ^ ... ^ val[c]
            // Subarray XOR (i..j) = row_xor[j] ^ row_xor[i-1]
            
            // We iterate j from 0 to M-1
            // We need to query max (row_xor[j] ^ X) where X is in window [j-W, j] (indices of row_xor)
            // Note: index -1 is valid (initial 0).
            
            // Insert 0 (for prefix logic)
            insert(root, 0);
            
            // Use deque to track insertions for removal?
            // "Remove P[j-W]".
            // Indices: -1, 0, 1 ... M-1.
            // When at j, valid starts are >= j - W + 1? No. Length <= W.
            // j - (i-1) <= W => i-1 >= j - W.
            
            int current_pfx = 0;
            
            // History of prefixes
            // pfx[-1] = 0.
            // pfx[0] = val[0].
            vector<int> pfx_history(M + 1); // shifted index +1
            pfx_history[0] = 0; // corresponds to index -1
            
            for(int c=0; c<M; ++c) {
                // Calculate val for column c
                int col_val = col_prefix[r2][c] ^ (r1 > 0 ? col_prefix[r1-1][c] : 0);
                
                current_pfx ^= col_val;
                pfx_history[c+1] = current_pfx;
                
                // Query Best in Window
                global_max = max(global_max, query(root, current_pfx));
                
                // Insert current_pfx to be available for FUTURE ends
                insert(root, current_pfx);
                
                // Remove outdated
                // At step c, we just inserted pfx corresponding to end `c`.
                // Valid starts for next step `c+1` must be >= (c+1) - W + 1 - 1 = c - W + 1.
                // Actually, logic:
                // For endpoint `c`, we query values `pfx[k]` where index `k` (conceptually i-1) satisfies `c - k <= W`? No.
                // Length is `c - (index_of_start) + 1`.
                // Start index `s`. `c - s + 1 <= W` => `s >= c - W + 1`.
                // Query uses `pfx[s-1]`. So we need `pfx` at indices `>= c - W`.
                //
                // Wait, standard sliding window:
                // 1. Add `pfx[current]` to window.
                // 2. Remove `pfx[current - W]` from window?
                // Subarray ends at `c`. Starts at `s`.
                // `pfx[c] ^ pfx[s-1]`.
                // Constraints: `1 <= c - s + 1 <= W`.
                // => `s >= c - W + 1`.
                // => `s-1 >= c - W`.
                // So valid `pfx` indices are `[c-W, c-1]`.
                // At start of loop `c`:
                // Available in Trie should be `pfx[c-W ... c-1]`.
                // `c=0`: valid `s=0` (`s-1=-1`). Range `[-W, -1]`. Contains `pfx[-1]=0`. Correct.
                // Query `pfx[c]` against Trie.
                // Then Insert `pfx[c]` into Trie for future.
                // Then Remove `pfx[c-W]` (if valid index) because for `c+1`, range shifts to `c+1-W`.
                
                int remove_idx = c - W; // Corresponds to pfx_history index `remove_idx + 1`
                if (remove_idx >= -1) {
                    remove(root, pfx_history[remove_idx + 1]);
                }
            }
        }
    }
    cout << global_max << endl;
    return 0;
}
