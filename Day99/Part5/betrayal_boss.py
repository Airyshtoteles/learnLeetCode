import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    iterator = iter(input_data)
    try:
        BossHP = int(next(iterator))
        N_my = int(next(iterator))
        my_moves = []
        for _ in range(N_my):
            my_moves.append(int(next(iterator)))
            
        N_npc = int(next(iterator))
        npc_moves = []
        for _ in range(N_npc):
            npc_moves.append(int(next(iterator)))
    except StopIteration:
        return

    # Worst case analyis
    # Maximize my move, Minimize NPC move (assume NPC heals/negates)
    
    best_mine = max(my_moves) if my_moves else 0
    worst_npc = min(npc_moves) if npc_moves else 0
    
    if best_mine + worst_npc > 0:
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    solve()
