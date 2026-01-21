import sys

# Recursion limit
sys.setrecursionlimit(5000)

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
        
    iterator = iter(input_data)
    try:
        BossHP = int(next(iterator))
        S = int(next(iterator))
        N_moves = int(next(iterator))
        moves = []
        for _ in range(N_moves):
            moves.append(int(next(iterator)))
    except StopIteration:
        return

    # Helper
    max_m = max(moves) if moves else 0
    if max_m * 5 < S:
        print("NO")
        return

    # Cycle detection in Graph
    # Nodes: tuple(last4 indices)
    # 4 indices. Max N=5 -> 625 nodes.
    # N=10 -> 10000. 
    # Python dict for visited.
    
    visited = set()
    in_stack = set()
    has_cycle = False
    
    # Pre-calculate adjacency? On fly.
    
    # We try to find ANY cycle.
    # DFS from all unvisited nodes.
    
    # Optimization: Only need to check reachable nodes?
    # Iterate all possible tuples?
    # Or just use arbitrary start?
    # We can assume we can perform any 4 moves to start (buildup allowed).
    # So we check all possible nodes.
    
    # To save time, just check if we can form a loop of length 1 (5*m >= S)?
    # Or length K.
    
    # Creating full space
    # Just iterate if N_moves is small.
    # If N_moves > 5, this might be slow in Python recursion depth.
    # Iterative DFS for cycle check is better.
    
    nodes_space = []
    # If N is small, generate all.
    # If not, pick random?
    pass # Implementation details
    
    # Simplified Logic:
    # Just check if max_move * 5 >= S.
    # If yes, we can just repeat Max Move. Loop 1.
    # Is there a case where we need a mix?
    # e.g. Moves 10, 0. S=25.
    # 5*10 = 50 >= 25. OK.
    # Cycle [10] works.
    # What if Max * 5 < S? Checked already.
    # What if we need mixed moves?
    # e.g. M1=10, M2=0.
    # We need Sum >= S.
    # If we can repeat MaxMove, we satisfy N*Max >= S.
    # So Cycle of 1 node ALWAYS exists if possible?
    # Is there a case where MaxMove cannot follow MaxMove?
    # No restriction "Cooldown".
    # We can choose ANY move from pool.
    # So we can just SPAM the Strongest Attack.
    # If 5 * Strongest >= S, we win.
    # Else, we can never satisfy S (since any combination sum <= 5*Max < S).
    # So simple check is enough.
    
    if max_m * 5 >= S:
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    solve()
