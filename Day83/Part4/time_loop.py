import sys

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        N = int(line1[0])
        
        line2 = sys.stdin.readline().split()
        if not line2: return
        D = [int(x) for x in line2]
        
        line3 = sys.stdin.readline().split()
        if not line3: return
        K, HP = int(line3[0]), int(line3[1])
    except ValueError:
        return

    # DP for sums
    sums = {0}
    for _ in range(K):
        next_sums = set()
        for s in sums:
            for dmg in D:
                next_sums.add(s + dmg)
        sums = next_sums
        
    if not sums:
        print(-1)
        return

    sorted_sums = sorted(list(sums), reverse=True)
    v1 = sorted_sums[0]
    v2 = sorted_sums[1] if len(sorted_sums) > 1 else -1
    
    if v1 >= HP:
        print(1)
        return
        
    if v2 == -1:
        print(-1)
        return
        
    # Alternate v1, v2
    # We already did 0 loops.
    # Loop 1: v1
    current_hp = HP - v1
    loops = 1
    if current_hp <= 0:
        print(loops)
        return
        
    # Loop 2: v2
    current_hp -= v2
    loops += 1
    if current_hp <= 0:
        print(loops)
        return
        
    # Cycle v1, v2
    cycle_dmg = v1 + v2
    cycles = current_hp // cycle_dmg
    
    loops += cycles * 2
    current_hp -= cycles * cycle_dmg
    
    while current_hp > 0:
        current_hp -= v1
        loops += 1
        if current_hp <= 0: break
        
        current_hp -= v2
        loops += 1
        
    print(loops)

if __name__ == "__main__":
    solve()
