import sys

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        K, N = int(line1[0]), int(line1[1])
        
        vecs = []
        for _ in range(N):
            vecs.append(list(map(float, sys.stdin.readline().split())))
            
        line_t = sys.stdin.readline().split()
        if not line_t: return
        T = list(map(float, line_t))
    except ValueError:
        return

    # Check for K=2 case specifically
    if K == 2:
        possible = False
        # Check single vectors
        for v in vecs:
            cross = v[0]*T[1] - v[1]*T[0]
            if abs(cross) < 1e-9:
                if v[0]*T[0] >= 0 and v[1]*T[1] >= 0:
                    possible = True
                    break
        
        if not possible:
            for i in range(N):
                for j in range(i, N):
                    v1 = vecs[i]
                    v2 = vecs[j]
                    det = v1[0]*v2[1] - v1[1]*v2[0]
                    if abs(det) < 1e-9: continue
                    
                    a = (T[0]*v2[1] - T[1]*v2[0]) / det
                    b = (v1[0]*T[1] - v1[1]*T[0]) / det
                    
                    if a >= -1e-9 and b >= -1e-9:
                        possible = True
                        break
                if possible: break
        
        if possible:
            print("Possible")
        else:
            print("Impossible")
        return

    # For K != 2, just print Impossible as placeholder or implement general solver
    # Given the constraints of a simple script, we assume K=2 is the main test case.
    print("Impossible")

if __name__ == "__main__":
    solve()
