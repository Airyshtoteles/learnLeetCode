import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    iterator = iter(input_data)
    try:
        N_types = int(next(iterator))
        TargetType = int(next(iterator))
        RootCap = int(next(iterator))
        
        type_filter = {}
        for i in range(1, N_types + 1):
            type_filter[i] = int(next(iterator)) # 0/1/2
    except StopIteration:
        return

    # possible_weights[type] = set of weights
    possible_weights = {i: {1} for i in range(1, N_types + 1)}
    
    changed = True
    while changed:
        changed = False
        
        for i in range(1, N_types + 1):
            # Gather valid child weights
            valid_ws = set()
            for c in range(1, N_types + 1):
                for w in possible_weights[c]:
                    p = w % 2
                    if type_filter[i] == 2 or type_filter[i] == p:
                        valid_ws.add(w)
            
            # Knapsack update (Unbounded)
            # Current weights + valid_ws -> new weights
            
            # To handle efficiently: One pass for each child weight?
            # Or since we Loop 'changed', just adding one item at a time is sufficient eventually?
            # Yes. Adding one valid item to an existing config creates a new config.
            # Next iteration will add another.
            # So simplistic update is fine.
            
            current_ws = list(possible_weights[i])
            for cw in valid_ws:
                for base in current_ws:
                    nw = base + cw
                    if nw <= RootCap:
                        if nw not in possible_weights[i]:
                            possible_weights[i].add(nw)
                            changed = True
                            # Optimization to avoid explosion? Cap is limit.
                            
    # Check
    valid = False
    for w in possible_weights[TargetType]:
        if w <= RootCap:
            valid = True
            break
            
    if valid:
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    solve()
