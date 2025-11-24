import itertools

def solve():
    # Hardcoded Input
    N = 15
    R = 2
    K = 2
    # Enemy spawn times
    enemies_spawn = [0, 1, 2, 5, 6, 7, 10, 12]
    
    # Precompute enemy trajectories
    # Enemy i: pos(t) = t - spawn_time
    # Exists in [0, N] during t in [spawn, spawn + N]
    
    max_time = max(enemies_spawn) + N + R + 5
    
    possible_positions = range(N + 1)
    
    max_kills = 0
    best_positions = []
    
    # Iterate all combinations of K towers
    for positions in itertools.combinations(possible_positions, K):
        current_kills = 0
        alive_enemies = set(range(len(enemies_spawn)))
        tower_ready_at = [0] * K
        
        # Simulation
        for t in range(max_time):
            # Find all possible actions: (enemy_id, tower_idx, exit_time)
            actions = []
            
            for tower_idx, p in enumerate(positions):
                if tower_ready_at[tower_idx] > t:
                    continue
                
                # Check all alive enemies
                for e_id in list(alive_enemies): # Copy to iterate safely? No, just reading
                    spawn = enemies_spawn[e_id]
                    e_pos = t - spawn
                    
                    # Check range [p-R, p+R]
                    if p - R <= e_pos <= p + R:
                        # Calculate when this enemy leaves this tower's range
                        # e_pos_exit = p + R
                        # t_exit - spawn = p + R => t_exit = p + R + spawn
                        exit_time = p + R + spawn
                        actions.append((exit_time, e_id, tower_idx))
            
            # Sort actions by Earliest Exit Time (Greedy)
            # If exit times are equal, maybe prioritize lower ID?
            actions.sort(key=lambda x: x[0])
            
            # Execute actions
            # We need to track which towers and enemies are used in this time step
            used_towers = set()
            
            for _, e_id, tower_idx in actions:
                if e_id in alive_enemies and tower_idx not in used_towers:
                    # Kill
                    alive_enemies.remove(e_id)
                    used_towers.add(tower_idx)
                    tower_ready_at[tower_idx] = t + 3
                    current_kills += 1
        
        if current_kills > max_kills:
            max_kills = current_kills
            best_positions = positions
            
    print(f"Max Kills: {max_kills}")
    print(f"Best Positions: {best_positions}")

if __name__ == "__main__":
    solve()
