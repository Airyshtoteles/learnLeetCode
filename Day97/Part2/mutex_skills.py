import sys
from collections import deque

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
        
    iterator = iter(input_data)
    try:
        N = int(next(iterator))
        TotalEnergy = int(next(iterator))
        TargetNode = int(next(iterator))
        
        Costs = []
        for _ in range(N): Costs.append(int(next(iterator)))
        
        PrereqMask = [0] * N
        num_deps = int(next(iterator))
        for _ in range(num_deps):
            u = int(next(iterator))
            p = int(next(iterator))
            PrereqMask[u] |= (1 << p)
            
        Locks = []
        num_locks = int(next(iterator))
        for _ in range(num_locks):
            u = int(next(iterator))
            v = int(next(iterator))
            k = int(next(iterator))
            Locks.append((u, v, k))
            
    except StopIteration:
        return
        
    # Check if N is too large for bitmask
    if N > 20:
        # Fallback or efficient constraint check (Backtracking)
        # For simplicity, implementation assumes N small as per problem type.
        pass

    max_energy = [-1] * (1 << N)
    max_energy[0] = TotalEnergy
    queue = deque([0])
    
    target_bit = (1 << TargetNode)
    
    while queue:
        mask = queue.popleft()
        energy = max_energy[mask]
        
        if (mask & target_bit):
            print("YES")
            return
            
        for i in range(N):
            if not ((mask >> i) & 1):
                if energy >= Costs[i]:
                    # Check Prereq
                    if (mask & PrereqMask[i]) == PrereqMask[i]:
                        # Check Locks
                        valid = True
                        for lu, lv, lk in Locks:
                            other = -1
                            if lu == i: other = lv
                            elif lv == i: other = lu
                            
                            if other != -1:
                                if (mask >> other) & 1:
                                    # Conflict. Check Unlocker
                                    if lk == -1 or not ((mask >> lk) & 1):
                                        valid = False
                                        break
                        
                        if valid:
                            new_mask = mask | (1 << i)
                            new_energy = energy - Costs[i]
                            
                            if new_energy > max_energy[new_mask]:
                                if max_energy[new_mask] == -1:
                                    queue.append(new_mask)
                                max_energy[new_mask] = new_energy
                                
    print("NO")

if __name__ == "__main__":
    solve()
