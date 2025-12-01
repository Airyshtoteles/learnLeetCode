import functools

def solve_time_loop_arena(T, skills, enemies):
    # skills: [d1, c1, d2, c2, d3, c3, R]
    d1, c1, d2, c2, d3, c3, R_radius = skills
    
    # enemies: list of [spawn_time, x, y, hp]
    # We will track enemy HP in the state using a tuple
    # Since HP changes, bitmask is not enough. We need tuple of current HPs.
    # To optimize, if HP <= 0, we treat it as 0.
    
    # Pre-process enemies to have IDs
    # enemy_list = [(spawn_time, x, y, initial_hp)]
    
    n_enemies = len(enemies)
    
    # Memoization
    # State: (time, cd1, cd2, cd3, hp_tuple)
    # hp_tuple: tuple of current HP for each enemy
    
    @functools.lru_cache(None)
    def solve(t, cd1, cd2, cd3, hps):
        if t >= T:
            return 0
        
        # Count currently dead enemies to avoid double counting?
        # No, the function returns "additional kills from this point".
        # But we need to know if an enemy JUST died.
        # Easier: The state value is "Total kills at end".
        # Or: "Max kills we can get from time t onwards".
        
        # Let's calculate kills gained in this step?
        # No, kills happen when HP drops <= 0.
        # If we pass `hps` where some are 0, they are already dead.
        # We only care about killing those with HP > 0.
        
        # Available enemies at time t
        active_indices = []
        for i in range(n_enemies):
            spawn_t, _, _, _ = enemies[i]
            if spawn_t <= t and hps[i] > 0:
                active_indices.append(i)
                
        if not active_indices:
            # Fast forward? No, cooldowns need to tick.
            # Just wait.
            return solve(t + 1, max(0, cd1 - 1), max(0, cd2 - 1), max(0, cd3 - 1), hps)
            
        res = 0
        
        # Option 0: Wait
        res = max(res, solve(t + 1, max(0, cd1 - 1), max(0, cd2 - 1), max(0, cd3 - 1), hps))
        
        # Option 1: Slash (Single Target)
        if cd1 == 0:
            # Try slashing each active enemy
            # Heuristic: To reduce branching, maybe just try killing low HP?
            # For exact solution, try all.
            for idx in active_indices:
                new_hps = list(hps)
                new_hps[idx] -= d1
                kill_gain = 1 if new_hps[idx] <= 0 else 0
                new_hps[idx] = max(0, new_hps[idx])
                
                val = kill_gain + solve(t + 1, c1, max(0, cd2 - 1), max(0, cd3 - 1), tuple(new_hps))
                res = max(res, val)
                
        # Option 2: Pierce (Two Targets)
        if cd2 == 0:
            # Try piercing pairs?
            # Simplified: Try piercing each active enemy as primary, and find best secondary behind it?
            # Or just try all pairs?
            # For this implementation, let's assume we pick ONE primary target, and it automatically hits ONE best secondary (if any).
            # "Behind" implies geometry. Let's just pick any 2 distinct active enemies for simplicity of the "Hard" abstract problem,
            # or strictly follow geometry if we want.
            # Let's try all pairs (i, j) to be safe for small N.
            if len(active_indices) >= 2:
                import itertools
                for i, j in itertools.combinations(active_indices, 2):
                    new_hps = list(hps)
                    new_hps[i] -= d2
                    new_hps[j] -= d2
                    
                    kills = 0
                    if new_hps[i] <= 0: kills += 1
                    if new_hps[j] <= 0: kills += 1
                    
                    new_hps[i] = max(0, new_hps[i])
                    new_hps[j] = max(0, new_hps[j])
                    
                    val = kills + solve(t + 1, max(0, cd1 - 1), c2, max(0, cd3 - 1), tuple(new_hps))
                    res = max(res, val)
            else:
                # Only 1 enemy
                for idx in active_indices:
                    new_hps = list(hps)
                    new_hps[idx] -= d2
                    kill_gain = 1 if new_hps[idx] <= 0 else 0
                    new_hps[idx] = max(0, new_hps[idx])
                    val = kill_gain + solve(t + 1, max(0, cd1 - 1), c2, max(0, cd3 - 1), tuple(new_hps))
                    res = max(res, val)

        # Option 3: Shockwave (AoE)
        if cd3 == 0:
            # Hits ALL active enemies in radius R from (0,0) - assuming player is at (0,0)
            # Or maybe we choose a center? "Shockwave... radius R". Usually centered on player.
            # Let's assume centered on player at (0,0).
            new_hps = list(hps)
            kills = 0
            hit_any = False
            
            for idx in active_indices:
                _, ex, ey, _ = enemies[idx]
                dist = abs(ex) + abs(ey) # Manhattan
                if dist <= R_radius:
                    new_hps[idx] -= d3
                    if new_hps[idx] <= 0:
                        kills += 1
                    new_hps[idx] = max(0, new_hps[idx])
                    hit_any = True
            
            if hit_any: # Only use if it hits something? Or can we waste it? We can waste it, but usually suboptimal.
                val = kills + solve(t + 1, max(0, cd1 - 1), max(0, cd2 - 1), c3, tuple(new_hps))
                res = max(res, val)
                
        return res

    initial_hps = tuple(e[3] for e in enemies)
    return solve(0, 0, 0, 0, initial_hps)

if __name__ == "__main__":
    T = 5
    # d1, c1, d2, c2, d3, c3, R
    Skills = [10, 2, 15, 3, 5, 4, 2]
    # spawn, x, y, hp
    Enemies = [
        [0, 0, 0, 20],
        [1, 0, 1, 10]
    ]
    
    print(f"Max Kills: {solve_time_loop_arena(T, Skills, Enemies)}")
