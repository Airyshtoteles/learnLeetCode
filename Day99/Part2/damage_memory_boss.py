import sys
sys.setrecursionlimit(20000)

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    iterator = iter(input_data)
    try:
        BossHP = int(next(iterator))
        K = int(next(iterator))
        N_attacks = int(next(iterator))
        attacks = []
        for _ in range(N_attacks):
            attacks.append(int(next(iterator)))
    except StopIteration:
        return

    # Backtracking DFS
    # To optimize: If we reach a state and we found a "long enough" path from it previously?
    # No, simple path problem is hard.
    # We rely on "YES" being reachable reasonably fast or space being small.
    
    # State: tuple
    path_visited = set()
    
    def dfs(history, current_dmg):
        if current_dmg >= BossHP:
            return True
            
        for dmg in attacks:
            # Construct next history
            # If len < K, append. If len == K, shift.
            if len(history) < K:
                nxt = history + (dmg,)
            else:
                nxt = history[1:] + (dmg,)
                
            if nxt not in path_visited:
                path_visited.add(nxt)
                if dfs(nxt, current_dmg + dmg):
                    return True
                path_visited.remove(nxt)
        return False

    if dfs(tuple(), 0):
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    solve()
