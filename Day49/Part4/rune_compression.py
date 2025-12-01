from functools import lru_cache

def solve_rune_compression(s, k):
    n = len(s)
    
    @lru_cache(None)
    def get_len(count):
        if count == 1: return 1
        if count < 10: return 2
        if count < 100: return 3
        return 4
    
    @lru_cache(None)
    def dp(idx, k_left):
        if k_left < 0:
            return float('inf')
        if idx == n:
            return 0
            
        # Option 1: Delete s[idx]
        res = dp(idx + 1, k_left - 1)
        
        # Option 2: Keep s[idx] and form a group
        # We iterate forward to find all occurrences of s[idx] we can include
        # while deleting everything else in between.
        same = 0
        diff = 0
        
        for j in range(idx, n):
            if s[j] == s[idx]:
                same += 1
            else:
                diff += 1
                
            if diff > k_left:
                break
                
            cost = get_len(same) + dp(j + 1, k_left - diff)
            res = min(res, cost)
            
        return res

    return dp(0, k)

if __name__ == "__main__":
    s = "aaabcccd"
    k = 2
    result = solve_rune_compression(s, k)
    print(f"Minimum Length: {result}")
