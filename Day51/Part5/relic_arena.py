import bisect

def solve_relic_arena(relics, K):
    # Sort by end time
    # relics: list of (start, end, value)
    # We sort by end time. If end times equal, maybe sort by start? Doesn't strictly matter for correctness but good for stability.
    sorted_relics = sorted(relics, key=lambda x: x[1])
    
    N = len(sorted_relics)
    if N == 0:
        return 0
        
    # Extract end times for binary search
    end_times = [r[1] for r in sorted_relics]
    
    # DP array
    # dp[i] stores max value using first i relics (1-based)
    # dp[0] = 0
    dp = [0] * (N + 1)
    
    for i in range(1, N + 1):
        current_relic = sorted_relics[i-1]
        start, end, value = current_relic
        
        # Option 1: Skip
        val_skip = dp[i-1]
        
        # Option 2: Take
        # Find the latest relic j < i such that end_j <= start - K
        # We search in end_times[:i-1]
        # bisect_right returns insertion point.
        # We want index p such that end_times[p] <= start - K.
        # bisect_right returns index where all elements to left are <= val?
        # No, bisect_right returns index where all elements to left are <= val is FALSE.
        # bisect_right returns first index where element > val.
        # So elements at 0..idx-1 are <= val.
        # So the index of the last valid relic is idx - 1.
        # Since dp is 1-based, dp[idx] corresponds to that relic.
        
        target = start - K
        idx = bisect.bisect_right(end_times, target, lo=0, hi=i-1)
        
        # idx is the count of relics that satisfy the condition
        # dp[idx] is the max value from those relics
        val_take = value + dp[idx]
        
        dp[i] = max(val_skip, val_take)
        
    return dp[N]

if __name__ == "__main__":
    # Example 1
    # (1, 3, 50), (3, 5, 20), (6, 8, 100)
    # K = 1
    # Relic 0: [1, 3]. Next must start >= 3+1=4.
    # Relic 1: [3, 5]. Start 3 < 4. Overlap with Relic 0 + K.
    # Relic 2: [6, 8]. Start 6 >= 3+1=4. Compatible with 0.
    # Start 6 >= 5+1=6. Compatible with 1.
    # Options:
    # {0, 2} -> 50 + 100 = 150.
    # {1, 2} -> 20 + 100 = 120.
    # Max 150.
    
    relics = [(1, 3, 50), (3, 5, 20), (6, 8, 100)]
    K = 1
    print(f"Max Value (Ex 1): {solve_relic_arena(relics, K)}")
    
    # Example 2
    # (1, 2, 10), (2, 3, 20), (3, 4, 30)
    # K = 0 (Standard Interval Scheduling)
    # [1,2], [2,3], [3,4]. All compatible?
    # [1,2] ends at 2. [2,3] starts at 2.
    # If start == end is allowed? Usually intervals are [s, e).
    # Problem says "present for entire duration".
    # If [1, 2] and [2, 3], do they overlap?
    # Usually yes, at point 2.
    # But if K=0, maybe we can switch instantly?
    # Let's assume closed intervals [s, e].
    # Then [1, 2] and [2, 3] overlap at 2.
    # So we need start > end + K? Or start >= end + K?
    # Problem says: start_j >= end_i + K.
    # If K=0, start >= end.
    # So [1, 2] and [2, 3] are compatible.
    # Then we can take all. 10+20+30 = 60.
    
    relics2 = [(1, 2, 10), (2, 3, 20), (3, 4, 30)]
    K2 = 0
    print(f"Max Value (Ex 2): {solve_relic_arena(relics2, K2)}")
