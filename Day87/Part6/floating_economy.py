import sys
import heapq

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        A, B, W = int(line1[0]), int(line1[1]), int(line1[2])
        E_limit = float(line1[3])
        
        line2 = sys.stdin.readline().split()
        if not line2: M = 0
        else: M = int(line2[0])
        
        trans = []
        for _ in range(M):
            parts = sys.stdin.readline().split()
            trans.append((int(parts[0]), int(parts[1]), float(parts[2]))) # da, db, err
    except ValueError:
        return

    # Dijkstra
    # Priority Queue stores (error, a, b)
    pq = [(0.0, A, B)]
    visited = {} # (a, b) -> min_error
    visited[(A, B)] = 0.0
    
    while pq:
        cur_err, a, b = heapq.heappop(pq)
        
        if (a, b) in visited and visited[(a, b)] < cur_err:
            continue
            
        if a + b >= W:
            print("Possible")
            return
            
        for da, db, err in trans:
            na, nb = a + da, b + db
            n_err = cur_err + err
            
            if n_err <= E_limit:
                if (na, nb) not in visited or n_err < visited[(na, nb)]:
                    visited[(na, nb)] = n_err
                    heapq.heappush(pq, (n_err, na, nb))
                    
    print("Impossible")

if __name__ == "__main__":
    solve()
