import math

def solve_spirit_link(n, k, guardians):
    # guardians: list of [x, y, p, r]
    
    # Precompute adjacency (who can buff whom)
    # adj[i] contains list of j such that i can buff j
    adj = [[] for _ in range(n)]
    for i in range(n):
        xi, yi, pi, ri = guardians[i]
        for j in range(n):
            if i == j: continue
            xj, yj, pj, rj = guardians[j]
            dist = math.sqrt((xi - xj)**2 + (yi - yj)**2)
            if dist <= ri:
                adj[i].append(j)
                
    # DP State: dp[mask] = max total power of the subset 'mask'
    # The value stores the sum of powers of guardians in 'mask', 
    # CONSIDERING the optimal order of activation within that mask.
    
    # Wait, if we build the mask incrementally:
    # When we transition from mask -> mask | {u}, it means we activate u NEXT.
    # So u is activated AFTER everyone in 'mask'.
    # According to our rule: "Buffs apply to INACTIVE guardians".
    # So u (being inactive until now) receives buffs from everyone in 'mask' who can reach u.
    # Once u is active, u will buff everyone NOT in (mask | {u}).
    # But the DP value is "Total Power of Activated Guardians".
    # So when we add u, we add u's base power + buffs u received from 'mask'.
    # Does u's activation add value to future guardians?
    # No, the value of future guardians will be calculated when THEY are added.
    # So we just need to track the sum of powers of CURRENTLY active guardians.
    
    # dp[mask] = Max power sum of guardians in mask
    # Transitions:
    # For each u not in mask:
    #   new_mask = mask | {u}
    #   buffs_received = count(v in mask such that v buffs u)
    #   dp[new_mask] = max(dp[new_mask], dp[mask] + p[u] + buffs_received)
    
    # We only care about masks of size K.
    # We can iterate by mask size.
    
    dp = {} # mask -> value
    dp[0] = 0
    
    # Iterate size 0 to K-1
    # Since N is small (e.g. <= 15-18), we can iterate all masks?
    # If N=15, 2^15 = 32768. Easy.
    # If N=20, 10^6. Feasible.
    
    # Optimization: We only need to keep masks of size s to generate size s+1.
    current_layer = {0: 0}
    
    for _ in range(k):
        next_layer = {}
        for mask, val in current_layer.items():
            # Try adding one guardian u
            for u in range(n):
                if not (mask & (1 << u)):
                    # Calculate buffs u receives from already active guardians (in mask)
                    buffs = 0
                    # Check all v in mask
                    # To optimize, iterate set bits or precompute?
                    # N is small, iterating N is fine.
                    for v in range(n):
                        if (mask & (1 << v)):
                            # Check if v buffs u
                            # We can use precomputed adjacency check
                            # Is u in adj[v]?
                            if u in adj[v]:
                                buffs += 1
                                
                    new_val = val + guardians[u][2] + buffs
                    new_mask = mask | (1 << u)
                    
                    if new_mask not in next_layer or new_val > next_layer[new_mask]:
                        next_layer[new_mask] = new_val
                        
        current_layer = next_layer
        
    # Result is max value in current_layer (which has masks of size K)
    if not current_layer:
        return 0
    return max(current_layer.values())

if __name__ == "__main__":
    N = 3
    K = 3
    # x, y, p, r
    Guardians = [
        [0, 0, 10, 10], # G0
        [1, 0, 10, 0],  # G1
        [2, 0, 10, 0]   # G2
    ]
    
    result = solve_spirit_link(N, K, Guardians)
    print(f"Maximum Power: {result}")
