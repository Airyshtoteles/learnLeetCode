def get_cost(x, v):
    ops = 0
    while x > v + 1:
        x //= 2
        ops += 1
    if x == v or x == v + 1:
        return ops
    return -1

def solve():
    try:
        line = input().split()
        if not line: return
        n = int(line[0])
        
        lvl = list(map(int, input().split()))
        if not lvl:
            print(0)
            return
            
        min_val = min(lvl)
        
        candidates = set()
        curr = min_val
        while True:
            candidates.add(curr)
            if curr > 0:
                candidates.add(curr - 1)
            if curr == 0:
                break
            curr //= 2
        candidates.add(0)
        
        min_ops = -1
        
        for v in candidates:
            if v < 0: continue
            
            current_ops = 0
            possible = True
            
            for x in lvl:
                cost = get_cost(x, v)
                if cost == -1:
                    possible = False
                    break
                current_ops += cost
                
            if possible:
                if min_ops == -1 or current_ops < min_ops:
                    min_ops = current_ops
                    
        print(min_ops)
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
