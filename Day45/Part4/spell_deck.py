import heapq
import sys

def solve():
    # Example Input Hardcoded for demonstration if no stdin
    # In a real scenario, we'd read from stdin
    # Format: H, then N, then N lines of (power, cooldown, tag)
    
    # Let's use a sample input
    # Target HP: 50
    # Spells:
    # 1. Fireball: 10 dmg, 3s, "fire"
    # 2. Ice Shard: 8 dmg, 2s, "ice"
    # 3. Quick Flame: 4 dmg, 1s, "fire"
    
    # Expected: 
    # Start -> Quick Flame (4 dmg, 1s, tag=fire)
    # -> Fireball (20 dmg (doubled), 3s, tag=fire) -> Total 24 dmg, 4s
    # -> Fireball (20 dmg, 3s) -> Total 44 dmg, 7s
    # -> Quick Flame (8 dmg, 1s) -> Total 52 dmg, 8s.
    
    # Or maybe:
    # Ice (8, 2s) -> Ice (16, 2s) -> Ice (16, 2s) -> Ice (16, 2s) = 56 dmg in 8s.
    
    input_data = """100
4
10 3 fire
8 2 ice
4 1 fire
20 5 storm"""
    
    # Parsing
    lines = input_data.strip().split('\n')
    H = int(lines[0])
    N = int(lines[1])
    spells = []
    
    unique_tags = set()
    for i in range(N):
        parts = lines[2+i].split()
        p = int(parts[0])
        c = int(parts[1])
        t = parts[2]
        spells.append({'p': p, 'c': c, 't': t})
        unique_tags.add(t)
    
    # Map tags to ID
    tag_to_id = {tag: i for i, tag in enumerate(unique_tags)}
    num_tags = len(unique_tags)
    
    # Dijkstra
    # State: (time, current_damage, last_tag_id)
    # last_tag_id can be -1 for None
    
    pq = [(0, 0, -1)]
    
    # dist[damage][last_tag_id]
    # damage goes up to H.
    # last_tag_id goes 0..num_tags-1. We need to handle -1 index carefully or shift by 1.
    # Let's shift tag_id by 1. 0 = None, 1..T = tags.
    
    dist = {} # Using dict for sparse storage or list of lists?
    # H is 100 here, but could be larger. List of lists is safer for dense updates.
    # dist[dmg][tag_idx]
    
    # Initialize with infinity
    # We only track visited states to avoid cycles/redundancy if costs are 0 (not possible here)
    # Actually, we need to store best time for (dmg, tag) to prune.
    
    best_times = {} # (dmg, tag_id) -> time
    
    min_time_to_h = float('inf')
    
    while pq:
        time, dmg, last_tag = heapq.heappop(pq)
        
        if dmg >= H:
            min_time_to_h = min(min_time_to_h, time)
            return time # Since it's Dijkstra, first time we reach >= H is optimal? 
            # Yes, because edge weights (cooldowns) are non-negative.
            
        # Pruning
        state_key = (dmg, last_tag)
        if state_key in best_times and best_times[state_key] <= time:
            continue
        best_times[state_key] = time
        
        for spell in spells:
            s_power = spell['p']
            s_cool = spell['c']
            s_tag = spell['t']
            s_tag_id = tag_to_id[s_tag]
            
            # Calculate damage
            current_power = s_power
            if s_tag_id == last_tag:
                current_power *= 2
            
            new_dmg = min(H, dmg + current_power)
            new_time = time + s_cool
            
            # Push
            # Optimization: If we already found a way to reach new_dmg with s_tag_id faster, skip
            next_key = (new_dmg, s_tag_id)
            if next_key not in best_times or new_time < best_times[next_key]:
                heapq.heappush(pq, (new_time, new_dmg, s_tag_id))
                
    return -1

if __name__ == "__main__":
    result = solve()
    print(f"Minimum time to reach target damage: {result}")
