import sys

# Trie implementation in Python is slow. 
# But N=400. M=400. N^2 * M is 6.4e7 operations.
# Python might TLE.
# Implementing simple loop for Sliding Window Max XOR if W is small?
# If W is large, O(W) per cell is slow.
# Heuristic: Just do brute force loops if W is small?
# Or simplified Trie.

class TrieNode:
    def __init__(self):
        self.child = [None, None]
        self.count = 0

def solve():
    input_data = sys.stdin.read().split()
    if not input_data: return
    iterator = iter(input_data)
    
    try:
        N = int(next(iterator))
        M = int(next(iterator))
        H = int(next(iterator))
        W = int(next(iterator))
        
        grid = []
        for r in range(N):
            row = []
            for c in range(M):
                row.append(int(next(iterator)))
            grid.append(row)
            
    except StopIteration:
        return

    # Prefix Cols
    # col_pfx[r][c]
    col_pfx = [[0]*M for _ in range(N)]
    for c in range(M):
        curr = 0
        for r in range(N):
            curr ^= grid[r][c]
            col_pfx[r][c] = curr
            
    global_max = 0
    
    # Iterate r1, r2
    for r1 in range(N):
        r2_max = min(N - 1, r1 + H - 1)
        for r2 in range(r1, r2_max + 1):
            
            # Form 1D array
            vals = []
            for c in range(M):
                v = col_pfx[r2][c] ^ (col_pfx[r1-1][c] if r1 > 0 else 0)
                vals.append(v)
            
            # Max XOR Subarray valid length <= W
            # Python optimization: Just iterate window?
            # Sliding window of size W.
            # O(M * W) complexity for this row pair.
            # Total: N * H * M * W.
            # 400^4 = 2.5e10. Too slow.
            # But 400^3 * 30 is Trie. 
            # In Python Trie is overhead.
            # Compromise: Simple logic?
            # Or assume W is small? "Lebar <= W".
            # Just implement O(M*min(M, W))
            
            prefix_vals = [0] * (M + 1)
            curr = 0
            for i in range(M):
                curr ^= vals[i]
                prefix_vals[i+1] = curr
                
            # For each end j, we try start i (j - W + 1 <= i <= j + 1)
            # => prefix indices k in [j-W, j]
            # prefix_vals[j+1] ^ prefix_vals[k]
            
            for j in range(M):
                limit = max(0, j - W + 1)
                # Check k from limit to j (indices of vals, so pfx indices limit..j)
                # Pfx index is shifted by +1?
                # Subarray val[i..j] = pfx[j+1] ^ pfx[i].
                # i range [limit, j].
                # So pfx indices in [limit, j].
                
                pj = prefix_vals[j+1]
                # Loop last W items
                # Since W might be 400, this loop is tight.
                start_k = max(0, j - W + 1)
                
                # Check directly
                # Python slicing is fast
                # subset = prefix_vals[start_k : j+1]
                # best = max(x ^ pj for x in subset)
                # global_max = max(global_max, best)
                
                # Manual loop slightly faster than `max` generator?
                for k in range(start_k, j + 1):
                    val = pj ^ prefix_vals[k]
                    if val > global_max: global_max = val

    print(global_max)

if __name__ == "__main__":
    solve()
