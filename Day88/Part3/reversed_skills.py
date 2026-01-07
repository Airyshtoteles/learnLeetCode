import sys

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        N, M, K = map(int, line1)
        
        Target = int(sys.stdin.readline())
        
        normal_deps = [[] for _ in range(N + 1)]
        reverse_deps = [[] for _ in range(N + 1)]
        
        for _ in range(M):
            u, v = map(int, sys.stdin.readline().split())
            # u -> v. Normal: v needs u. Reverse: u needs v.
            normal_deps[v].append(u)
            reverse_deps[u].append(v)
            
    except ValueError:
        return

    inventory = set()
    time = 0
    limit = 2 * K * (N + 2) # Safety margin
    
    while time < limit:
        if Target in inventory:
            print("Possible")
            return
            
        is_reverse = (time // K) % 2 == 1
        new_skills = []
        
        for i in range(1, N + 1):
            if i in inventory: continue
            
            deps = reverse_deps[i] if is_reverse else normal_deps[i]
            
            can_take = True
            for d in deps:
                if d not in inventory:
                    can_take = False
                    break
            
            if can_take:
                new_skills.append(i)
                
        for s in new_skills:
            inventory.add(s)
            
        if Target in inventory:
            print("Possible")
            return
            
        time += 1
        
    print("Impossible")

if __name__ == "__main__":
    solve()
