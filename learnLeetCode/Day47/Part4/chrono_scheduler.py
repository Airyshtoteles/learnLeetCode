import bisect

def solve_chrono_scheduler(n, d, c, attacks):
    # attacks: list of [time, damage]
    # Sort just in case, though problem says sorted
    attacks.sort()
    
    times = [a[0] for a in attacks]
    damages = [a[1] for a in attacks]
    
    # Prefix sum for damages
    # prefix_damage[i] = sum(damages[0]...damages[i-1])
    prefix_damage = [0] * (n + 1)
    for i in range(n):
        prefix_damage[i+1] = prefix_damage[i] + damages[i]
        
    def get_range_damage(start_idx, end_idx):
        # Sum of damages from index start_idx to end_idx - 1
        if start_idx >= end_idx:
            return 0
        return prefix_damage[end_idx] - prefix_damage[start_idx]

    # dp[i] = min damage from i to n-1
    dp = [0] * (n + 1)
    
    for i in range(n - 1, -1, -1):
        # Option 1: Take the hit
        take_hit = damages[i] + dp[i+1]
        
        # Option 2: Use Shield
        start_time = times[i]
        end_active = start_time + d
        end_cooldown = end_active + c
        
        # Find first attack that is NOT blocked (time > end_active)
        # bisect_right returns insertion point after all x <= val.
        # We want first x > val. So bisect_right is correct.
        idx_after_shield = bisect.bisect_right(times, end_active)
        
        # Find first attack that is available after cooldown (time >= end_cooldown)
        # bisect_left returns insertion point before all x >= val.
        idx_after_cooldown = bisect.bisect_left(times, end_cooldown)
        
        # Damage taken during cooldown period (unavoidable if we shield now)
        # Attacks from idx_after_shield to idx_after_cooldown - 1
        forced_damage = get_range_damage(idx_after_shield, idx_after_cooldown)
        
        use_shield = forced_damage + dp[idx_after_cooldown]
        
        dp[i] = min(take_hit, use_shield)
        
    return dp[0]

if __name__ == "__main__":
    N = 5
    D = 3
    C = 2
    Attacks = [
        [1, 10],
        [2, 20],
        [4, 10],
        [6, 50],
        [8, 5]
    ]
    
    result = solve_chrono_scheduler(N, D, C, Attacks)
    print(f"Minimum Damage: {result}")
