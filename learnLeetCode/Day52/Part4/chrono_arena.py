import heapq

def solve_chrono_arena(speed, t_limit, skills):
    # skills: list of (name, damage, cast_time, cooldown, cp_change)
    # Add a "Wait" action? Or assume Basic Attack exists?
    # Let's assume the input includes a basic attack or we handle "no move" as stop.
    # Actually, if we can't move, we stop.
    
    N = len(skills)
    fill_time = 100.0 / speed
    
    # Beam Search / Dijkstra
    # We want max damage. Dijkstra minimizes cost.
    # We can't use simple Dijkstra because "Damage" is the objective, not fixed cost.
    # But we can use Beam Search ordered by Time.
    # State: (time, -damage, cp, cooldowns_tuple)
    # cooldowns_tuple: (ready_time_0, ready_time_1, ...)
    
    initial_cooldowns = tuple([0.0] * N)
    pq = [(fill_time, 0, 0, initial_cooldowns)] # Start after first fill
    
    # Pruning: (cp, normalized_cooldowns) -> max_damage
    # But time is continuous.
    # Let's just use Beam Search with width.
    # Or simply: At each step, we pick a skill.
    # Since steps are sequential, we can just maintain a list of "Active States".
    
    # Let's use a Priority Queue to explore.
    # To prune, we can bucket by time?
    # Or just use a visited set with some discretization?
    # Let's use a visited map: (cp, quantized_cooldowns) -> max_damage_at_time?
    # This is hard.
    
    # Let's use Beam Search by "Turns".
    # But turns have different lengths.
    
    # Let's stick to PQ and prune if we have a "dominated" state.
    # State A dominates B if:
    # time_A <= time_B AND damage_A >= damage_B AND cp_A >= cp_B AND cooldowns_A <= cooldowns_B
    # Checking dominance is expensive.
    
    # Heuristic: Sort PQ by time.
    # Keep a limited number of states?
    # Let's limit PQ size.
    
    max_damage = 0
    
    # To prevent explosion, we can limit the number of states processed.
    count = 0
    LIMIT = 50000
    
    # Visited for simple pruning: (cp, rounded_cooldowns) -> (min_time, max_damage)
    # Round cooldowns to 1 decimal place?
    
    while pq and count < LIMIT:
        t, neg_d, cp, cds = heapq.heappop(pq)
        d = -neg_d
        
        if d > max_damage:
            max_damage = d
            
        if t > t_limit:
            continue
            
        # Choose a skill
        # We are at time 't', gauge is full.
        # Available skills: cds[i] <= t AND cp check
        
        can_act = False
        for i in range(N):
            name, dmg, cast, cd, cp_chg = skills[i]
            
            # Check Cooldown
            if cds[i] <= t:
                # Check CP
                if cp_chg < 0 and cp < -cp_chg:
                    continue
                    
                # Valid move
                can_act = True
                
                new_cp = cp + cp_chg
                new_cp = min(5, max(0, new_cp))
                
                step_time = cast
                finish_time = t + step_time
                
                if finish_time <= t_limit:
                    # Next turn ready time
                    next_ready = finish_time + fill_time
                    
                    # Update cooldowns
                    new_cds = list(cds)
                    new_cds[i] = finish_time + cd
                    
                    # Optimization: Cooldowns that are already ready can be clamped to current time?
                    # No, because relative order matters?
                    # Actually, if a skill is ready at T=5 and we are at T=10, it's just ready.
                    # We can clamp ready times to be max(r, finish_time)?
                    # No, ready time is absolute.
                    
                    heapq.heappush(pq, (next_ready, -(d + dmg), new_cp, tuple(new_cds)))
                    
        if not can_act:
            # If no skill can be used (e.g. all on CD or no CP), we are stuck?
            # In real game, we might wait.
            # But here, let's assume we stop this branch.
            pass
            
        count += 1
        
    return max_damage

if __name__ == "__main__":
    # Example 1
    # Speed 50 -> Fill time 2.0
    # Skill 1: Dmg 100, Cast 1.0, CD 0, CP +1
    # Skill 2: Dmg 300, Cast 2.0, CD 5.0, CP -2
    # T_limit = 10.0
    
    # T=2.0: Use S1. End T=3.0. Dmg 100. CP 1. Next T=5.0.
    # T=5.0: Use S1. End T=6.0. Dmg 200. CP 2. Next T=8.0.
    # T=8.0: Use S2 (Cost 2 CP). End T=10.0. Dmg 500. CP 0. Next T=12.0 (Stop).
    # Total 500.
    
    speed = 50
    t_limit = 10.0
    skills = [
        ("Slash", 100, 1.0, 0.0, 1),
        ("Finisher", 300, 2.0, 5.0, -2)
    ]
    
    print(f"Max Damage (Ex 1): {solve_chrono_arena(speed, t_limit, skills)}")
    
    # Example 2: Only Basic
    # Speed 100 -> Fill 1.0
    # Basic: 10 dmg, 0.5 cast, 0 cd, 0 cp.
    # T=5.0
    # T=1.0: Basic. End 1.5. Next 2.5.
    # T=2.5: Basic. End 3.0. Next 4.0.
    # T=4.0: Basic. End 4.5. Next 5.5.
    # Total 3 hits -> 30 dmg.
    
    speed2 = 100
    t_limit = 5.0
    skills2 = [("Basic", 10, 0.5, 0.0, 0)]
    print(f"Max Damage (Ex 2): {solve_chrono_arena(speed2, t_limit, skills2)}")
