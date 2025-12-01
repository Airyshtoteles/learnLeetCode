import collections

def solve():
    # Hardcoded Input
    # 3 Layers, 3x3
    # Layer 0: Full
    # Layer 1: Center only
    # Layer 2: Corners only
    
    layers = [
        [
            [1, 1, 1],
            [1, 1, 1],
            [1, 1, 1]
        ],
        [
            [0, 0, 0],
            [0, 1, 0],
            [0, 0, 0]
        ],
        [
            [1, 0, 1],
            [0, 0, 0],
            [1, 0, 1]
        ]
    ]
    
    L = 3
    N = 3
    M = 3
    
    visited = set()
    cc_sizes = []
    
    def get_neighbors(k, r, c):
        # Same layer neighbors
        for dr, dc in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            nr, nc = r + dr, c + dc
            if 0 <= nr < N and 0 <= nc < M:
                if layers[k][nr][nc] == 1:
                    yield (k, nr, nc)
                    
        # Other layers same pos
        for nk in range(L):
            if nk != k:
                if layers[nk][r][c] == 1:
                    yield (nk, r, c)
    
    for k in range(L):
        for r in range(N):
            for c in range(M):
                if layers[k][r][c] == 1 and (k, r, c) not in visited:
                    # BFS for CC
                    q = collections.deque([(k, r, c)])
                    visited.add((k, r, c))
                    size = 0
                    
                    while q:
                        ck, cr, cc = q.popleft()
                        size += 1
                        
                        for nk, nr, nc in get_neighbors(ck, cr, cc):
                            if (nk, nr, nc) not in visited:
                                visited.add((nk, nr, nc))
                                q.append((nk, nr, nc))
                                
                    cc_sizes.append(size)
                    
    cc_sizes.sort(reverse=True)
    
    ans = 0
    if len(cc_sizes) >= 1:
        ans += cc_sizes[0]
    if len(cc_sizes) >= 2:
        ans += cc_sizes[1]
        
    print(f"Max Dominoes: {ans}")

if __name__ == "__main__":
    solve()
