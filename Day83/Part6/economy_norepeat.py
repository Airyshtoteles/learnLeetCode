import sys

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        N = int(line1[0])
        
        vecs = []
        for _ in range(N):
            vecs.append(list(map(int, sys.stdin.readline().split())))
            
        line_t = sys.stdin.readline().split()
        if not line_t: return
        Tx, Ty = int(line_t[0]), int(line_t[1])
    except ValueError:
        return

    if Tx == 0 and Ty == 0:
        print("Possible")
        return

    # Cone Check
    in_cone = False
    
    # Check single vectors
    for vx, vy in vecs:
        cross = vx * Ty - vy * Tx
        if cross == 0:
            if vx * Tx >= 0 and vy * Ty >= 0:
                in_cone = True
                break
    
    if not in_cone:
        for i in range(N):
            for j in range(i + 1, N):
                v1x, v1y = vecs[i]
                v2x, v2y = vecs[j]
                
                D = v1x * v2y - v1y * v2x
                if D == 0: continue
                
                # Cramer's rule
                # T = a*v1 + b*v2
                # a = det(T, v2) / D
                # b = det(v1, T) / D
                
                num_a = Tx * v2y - Ty * v2x
                num_b = v1x * Ty - v1y * Tx
                
                # Check signs
                if (num_a * D >= 0) and (num_b * D >= 0):
                    in_cone = True
                    break
            if in_cone: break
            
    if in_cone:
        print("Possible")
    else:
        print("Impossible")

if __name__ == "__main__":
    solve()
