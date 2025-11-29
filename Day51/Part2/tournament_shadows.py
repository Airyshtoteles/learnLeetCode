import heapq

def solve_tournament_shadows(damage, cooldown, cast_time, T):
    N = len(damage)
    
    # Beam Search
    # State: (current_damage, ready_times_tuple)
    # ready_times are absolute times when skills become ready.
    # We normalize? No, just keep absolute.
    # But we process by time.
    # Actually, we can just simulate.
    # Priority Queue: (current_time, current_damage, ready_times)
    # We want to MAXIMIZE damage.
    # Dijkstra minimizes cost. So store -damage.
    # PQ: (current_time, neg_damage, ready_times)
    
    # To avoid state explosion, we prune.
    # At any time t, if we have multiple states with same ready_times (normalized), keep max damage.
    # Normalized ready_times: (r0 - t, r1 - t, ...) clamped to 0.
    
    # Beam Width
    BEAM_WIDTH = 100
    
    # List of states at current time step?
    # Since cast times vary, it's not lock-step.
    # Use a PQ to order by time.
    
    pq = [(0, 0, tuple([0]*N))] # time, neg_damage, ready_times
    
    max_damage = 0
    
    # Visited pruning: (time, normalized_ready) -> max_damage
    # Since time is continuous/large, maybe just (normalized_ready) -> max_damage?
    # No, time matters for T.
    # But we can't store all times.
    # Let's just use Beam Search: Expand best nodes.
    
    # Iterations?
    # We pop min time.
    # If time > T, stop.
    
    # To limit PQ size, we can't just let it grow.
    # Maybe bucket by time?
    
    # Let's try a simplified approach:
    # DP[t] = max damage at time t.
    # But we need state.
    # Let's use the Beam Search with a fixed number of active states.
    
    states = [(0, tuple([0]*N))] # damage, ready_times
    # Current time is implicit? No.
    # State: (time, damage, ready_times)
    
    # We process events.
    # But events generate new events.
    
    # Let's use a PQ but prune aggressively.
    # Pruning key: (time, ready_times_normalized).
    # If we reach same state with less damage, discard.
    
    visited = {} # (time, ready_tuple) -> damage
    
    # Optimization: Only store states that are "promising".
    # Heuristic: damage / time?
    
    count = 0
    while pq and count < 100000: # Safety break
        t, neg_d, ready = heapq.heappop(pq)
        d = -neg_d
        
        max_damage = max(max_damage, d)
        
        if t >= T:
            continue
            
        # Try to cast each skill
        # We can wait until a skill becomes ready?
        # Or we just cast available skills NOW.
        # Or wait for the earliest next skill.
        
        # Option 1: Cast a ready skill immediately
        casted = False
        for i in range(N):
            if ready[i] <= t:
                # Cast i
                finish_time = t + cast_time[i]
                if finish_time <= T:
                    new_ready = list(ready)
                    new_ready[i] = finish_time + cooldown[i]
                    new_ready_tuple = tuple(new_ready)
                    
                    # Pruning
                    # Normalize for visited check?
                    # If we have seen this (finish_time, new_ready) with better damage, skip.
                    # But ready times can be large.
                    # We only care about ready - finish_time.
                    norm_ready = tuple(max(0, r - finish_time) for r in new_ready)
                    state_key = (finish_time, norm_ready)
                    
                    if state_key not in visited or visited[state_key] < d + damage[i]:
                        visited[state_key] = d + damage[i]
                        heapq.heappush(pq, (finish_time, -(d + damage[i]), new_ready_tuple))
                        casted = True
                        
        # Option 2: Wait for the next skill to become ready
        # Only if we didn't cast anything? Or always?
        # If we cast something, we advanced time.
        # If we couldn't cast anything (all on cooldown), we MUST wait.
        # If we could cast, maybe waiting for a BETTER skill is optimal.
        # So we should always consider waiting for the *earliest* ready skill that is currently on cooldown.
        
        next_ready_time = float('inf')
        for r in ready:
            if r > t:
                next_ready_time = min(next_ready_time, r)
                
        if next_ready_time != float('inf') and next_ready_time <= T:
             # Jump to next_ready_time
             # No damage gain, just time advance
             # Pruning
             norm_ready = tuple(max(0, r - next_ready_time) for r in ready)
             state_key = (next_ready_time, norm_ready)
             
             if state_key not in visited or visited[state_key] < d:
                 visited[state_key] = d
                 heapq.heappush(pq, (next_ready_time, neg_d, ready))
                 
        count += 1
        
    return max_damage

if __name__ == "__main__":
    damage = [100, 200]
    cooldown = [2, 5]
    cast_time = [1, 2]
    T = 10
    # Skill 0: 100 dmg, 1s cast, 2s cd (Total 3s cycle)
    # Skill 1: 200 dmg, 2s cast, 5s cd (Total 7s cycle)
    # Greedy:
    # t=0: Cast 0 (1s). Dmg 100. Ready at 3.
    # t=1: Cast 1 (2s). Dmg 200. Ready at 1+2+5=8.
    # t=3: Cast 0 (1s). Dmg 100. Ready at 6.
    # t=4: Wait?
    # t=6: Cast 0 (1s). Dmg 100. Ready at 9.
    # t=7: Wait?
    # t=8: Cast 1 (2s). Dmg 200. Ends at 10.
    # Total: 100+200+100+100+200 = 700.
    
    print(f"Max Damage: {solve_tournament_shadows(damage, cooldown, cast_time, T)}")
