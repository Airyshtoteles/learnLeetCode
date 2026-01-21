import sys
from collections import defaultdict

def solve():
    # DP with State Compression
    # Input: N, K, T_limit
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    iter_in = iter(input_data)
    try:
        N = int(next(iter_in))
        K = int(next(iter_in))
        T_limit = int(next(iter_in))
        
        Skills = []
        for _ in range(N):
            c = int(next(iter_in))
            d = int(next(iter_in))
            Skills.append((c, d))
    except StopIteration:
        return

    # Valid time travel amounts: 1 to MaxCD? 
    # Or 't' is arbitrary? "Mundur t langkah".
    # Player chooses t?
    # Optimal t is usually to make a skill ready.
    # So t = min(CD) is a candidate?
    # Or t = CD[i] for some i.
    # Constraint: All CDs >= t.
    # So t <= min(active_CDs).
    # If we rewind, we rewind by `min(active_CDs)` to just ready one skill.
    # Rewinding less is suboptimal? Yes.
    # Rewinding more is impossible.
    
    # State: (k_left, cd_tuple) -> max_dmg
    current_states = { (K, tuple([0]*N)): 0 }
    
    global_max = 0
    
    for _ in range(T_limit):
        next_states = defaultdict(int)
        
        for (k, cds), val in current_states.items():
            # 1. Use Skill (Takes 1 turn)
            # Creates new state at T+1
            
            # Decay for turn passage
            decayed = [max(0, x - 1) for x in cds]
            
            # Use skill i (if original cds[i] == 0)
            acted = False
            for i in range(N):
                if cds[i] == 0:
                    acted = True
                    # Result CDs: Decayed, but i is BaseCD
                    # Wait, if we use skill, does it start cooldown locally?
                    # Usually: Action -> Effect -> CD set. Turn ends.
                    # Start turn: CD 0. Cast. CD becomes Base. End turn: CD becomes Base-1.
                    new_cds = list(decayed)
                    new_cds[i] = Skills[i][0] - 1 # Base - 1 (end of turn)
                    if new_cds[i] < 0: new_cds[i] = 0
                    
                    nst = tuple(new_cds)
                    new_val = val + Skills[i][1]
                    if new_val > next_states[(k, nst)]:
                        next_states[(k, nst)] = new_val
                    if new_val > global_max: global_max = new_val
                        
            # 2. Wait (Takes 1 turn)
            nst_wait = tuple(decayed)
            if val > next_states[(k, nst_wait)]:
                next_states[(k, nst_wait)] = val
            
            # 3. Time Travel (Instant? Or takes turn?)
            # Usually strict manipulation. Assume Instant (doesn't consume T_limit step, but consumes K).
            # But we process it "within" the step or as a free move?
            # State expansion: We can perform TT *before* taking action?
            # Or TT is the action?
            # If TT is action, we lose turn but gain CD reduction.
            # Tradeoff: 1 turn for T reduction.
            # If TT is instant, it's powerful.
            # Prompt: "Mundur waktu t langkah".
            # Assume Instant.
            # If K > 0:
            #   t_max = min(cds)
            #   If t_max > 0:
            #      new_cds = cds - t_max
            #      new_k = k - 1
            #      This new state is reachable INSTANTLY. 
            #      We should process it in the SAME turn loop?
            #      Or add to `current_states` queue?
            
            if k > 0:
                # Calculate max possible rewind
                # Paradox if CD < 0.
                # So t <= all CDs.
                # t_limit = min(cds)
                # If we rewind t_limit, one skill becomes 0.
                t_limit = min(cds)
                if t_limit > 0:
                    rewound_cds = tuple([x - t_limit for x in cds])
                    # Add to current_states to be processed in THIS step
                    # (Instant chain)
                    # Be careful of infinite loop if t_limit = 0 (handled check)
                    
                    if val > current_states.get((k-1, rewound_cds), -1):
                        current_states[(k-1, rewound_cds)] = val
                        # This modifies dictionary during iteration? No in Py 3.
                        # Need queue approach.
                        
        # Handling instant transitions properly:
        # Use a queue for "Instant Phase" before "Action Phase"?
        # Or simply: TT moves are transitions within the 'current' time step.
        # Since TT reduces CD, it helps Use Skill.
        # Logic: Expand all TT states first. Then Simulate Turn.
        pass # To implement properly, use two buffers.

    # Simplified Simulation
    # Re-build loop
    
    states = { (K, tuple([0]*N)): 0 }
    
    for _ in range(T_limit):
        # Expand Instant Rewinds
        # Repeat until no new states (K limits depth)
        
        # Pull states to list to avoid runtime modification issues
        # Actually simplest is to iterate K from Max down to 0?
        # If we have K, we can generate K-1.
        # Order: Process K=Max, then K=Max-1...
        # So effective states propagate down.
        
        # Group by K
        by_k = defaultdict(dict) # k -> (cds -> val)
        for (k, c), v in states.items():
            if v > by_k[k].get(c, -1): by_k[k][c] = v
            
        # Propagate Rewinds (High K to Low K)
        for k in range(K, 0, -1):
            for c, v in list(by_k[k].items()):
                # Try rewind
                t = min(c)
                if t > 0:
                    new_c = tuple([x - t for x in c])
                    if v > by_k[k-1].get(new_c, -1):
                        by_k[k-1][new_c] = v
                        
        # Flatten for Actions
        flat_states = []
        for k, d in by_k.items():
            for c, v in d.items():
                flat_states.append((k, c, v))
                
        next_states = defaultdict(int)
        
        for k, cds, val in flat_states:
            # Decay
            decayed = [max(0, x - 1) for x in cds]
            
            # Wait
            nst = (k, tuple(decayed))
            if val > next_states[nst]: next_states[nst] = val
            
            # Cast
            for i in range(N):
                if cds[i] == 0:
                    # Cast i
                    nxt_c = list(decayed)
                    nxt_c[i] = max(0, Skills[i][0] - 1)
                    nst_cast = (k, tuple(nxt_c))
                    new_v = val + Skills[i][1]
                    if new_v > next_states[nst_cast]:
                        next_states[nst_cast] = new_v
                    if new_v > global_max:
                        global_max = new_v
                        
        states = next_states

    print(global_max)

if __name__ == "__main__":
    solve()
