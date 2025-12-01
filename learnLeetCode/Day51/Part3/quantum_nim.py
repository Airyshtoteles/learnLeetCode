import sys

# Memoization table
memo = {}

def get_affected_indices(N, edges):
    adj = [[] for _ in range(N)]
    for u, v in edges:
        adj[u].append(v)
        adj[v].append(u)
    
    # Precompute masks or lists of affected indices for each pile move
    # Move on pile i affects i and all neighbors
    affected = []
    for i in range(N):
        indices = [i] + adj[i]
        affected.append(indices)
    return affected

def solve_quantum_nim(stones, edges):
    N = len(stones)
    affected = get_affected_indices(N, edges)
    
    # Clear memo for new game
    global memo
    memo = {}
    
    return can_win(tuple(stones), N, affected)

def can_win(state, N, affected):
    if state in memo:
        return memo[state]
    
    # Try all possible moves
    # A move: choose pile i, remove k stones
    # Valid if all piles in affected[i] have >= k stones
    
    # Optimization:
    # Iterate through piles.
    # For each pile i, max possible k is min(state[j] for j in affected[i])
    # If max_k == 0, no move possible on this pile.
    
    possible_moves = False
    
    for i in range(N):
        # Find max k
        max_k = state[i]
        for neighbor in affected[i]:
            if neighbor != i: # affected[i] includes i
                max_k = min(max_k, state[neighbor])
        
        if max_k == 0:
            continue
            
        # Try all k from 1 to max_k
        # Heuristic: Try largest k first? Or smallest?
        # Usually small k leads to more states.
        for k in range(1, max_k + 1):
            possible_moves = True
            
            # Construct next state
            next_state_list = list(state)
            for idx in affected[i]:
                next_state_list[idx] -= k
            next_state = tuple(next_state_list)
            
            if not can_win(next_state, N, affected):
                memo[state] = True
                return True
                
    memo[state] = False
    return False

if __name__ == "__main__":
    # Example 1: 3 piles, Line 0-1-2
    # Stones: [2, 2, 2]
    # Move 0: affects 0, 1.
    # Move 1: affects 0, 1, 2.
    # Move 2: affects 1, 2.
    
    stones = [3, 3, 3]
    edges = [(0, 1), (1, 2)]
    
    print(f"Stones: {stones}, Edges: {edges}")
    if solve_quantum_nim(stones, edges):
        print("Result: First Player Wins")
    else:
        print("Result: Second Player Wins")
        
    # Example 2: Disconnected
    stones2 = [2, 2]
    edges2 = []
    # Equivalent to Nim with piles 2, 2 -> XOR sum 0 -> Second wins.
    print(f"Stones: {stones2}, Edges: {edges2}")
    if solve_quantum_nim(stones2, edges2):
        print("Result: First Player Wins")
    else:
        print("Result: Second Player Wins")
