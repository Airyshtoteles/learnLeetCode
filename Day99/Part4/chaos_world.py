import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    iterator = iter(input_data)
    try:
        N = int(next(iterator))
        # Assuming functional graph layout input
        # No M if outdegree=1.
        # But if problem format is standard graph list...
        # Wait, if world changes, maybe functional graph changes?
        # Re-reading: "World berubah tiap langkah".
        # This implies u -> v depends on t.
        # Maybe F_t(u).
        # Assuming simple static functional graph for now based on "day99" patterns.
        # If input has M edges: u, v. And we pick?
        # "Strategi". Implies choice.
        # If random choice? No, "Strategi pasti berhasil". 
        # This is Synchronizing Word problem (DFA).
        # We assume input is DFA: N states, K symbols. Transitions u,c -> v.
        # Task: Find sequence of symbols that maps {1..N} -> {Target}.
        # Sync word existence is PSPACE? Or just BFS in power set?
        # Power set BFS.
        
        M_inputs = int(next(iterator)) # Number of symbols/moves available
        Target = int(next(iterator))
        
        adj = {} # (u, symbol) -> v
        # Read transitions: u, symbol, v
        # Usually N*M lines? Or sparse.
        
        # Let's assume input format:
        # N, Symbols, Target.
        # Then N*Symbols lines? Or M edges.
        
        # Heuristic reader
        num_edges = int(next(iterator)) # Explicit edge count
        for _ in range(num_edges):
            u = int(next(iterator))
            sym = int(next(iterator))
            v = int(next(iterator))
            adj[(u, sym)] = v
            
    except StopIteration:
        return

    # BFS on Subset State
    # Start State: All nodes {1..N}
    # Goal: {Target}
    # Transitions: For each symbol s, next_state = { adj[u][s] for u in current }
    
    initial_set = frozenset(range(1, N+1))
    queue = [initial_set]
    visited = {initial_set}
    
    import collections
    q = collections.deque([initial_set])
    
    while q:
        curr = q.popleft()
        
        if len(curr) == 1 and Target in curr:
            print("YES")
            return
            
        for sym in range(1, M_inputs + 1): # Assume symbols 1..M
            next_set = set()
            valid_move = True
            for u in curr:
                if (u, sym) in adj:
                    next_set.add(adj[(u, sym)])
                else:
                    # Deterministic? If edge missing, maybe self loop or invalid?
                    # Assume self loop or dead end (empty).
                    # If dead end, set shrinks (good).
                    # If undefined, assume stays?
                    # Let's assume strict input: all defined or implicit dead.
                    pass 
            
            if next_set:
                frozen = frozenset(next_set)
                if frozen not in visited:
                    visited.add(frozen)
                    q.append(frozen)
    
    print("NO")

if __name__ == "__main__":
    solve()
