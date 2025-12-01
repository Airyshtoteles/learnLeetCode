import collections

def solve():
    # Hardcoded Input
    # 5x5 Grid
    # Walls: Border and center (2,2)
    grid = [
        "#####",
        "#...#",
        "#.S.#", # S is just a placeholder here, we use explicit coords
        "#...#",
        "#####"
    ]
    N = len(grid)
    M = len(grid[0])
    
    # Coordinates
    start_A = (1, 1)
    goal_A = (1, 3)
    
    start_B = (3, 3)
    goal_B = (3, 1)
    
    # BFS
    # State: (rA, cA, rB, cB)
    queue = collections.deque()
    queue.append((start_A[0], start_A[1], start_B[0], start_B[1], 0))
    
    visited = set()
    visited.add((start_A[0], start_A[1], start_B[0], start_B[1]))
    
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)] # U, D, L, R
    
    while queue:
        rA, cA, rB, cB, steps = queue.popleft()
        
        if (rA, cA) == goal_A and (rB, cB) == goal_B:
            print(f"Minimum steps: {steps}")
            return
        
        for dr, dc in directions:
            # Move A
            nrA, ncA = rA + dr, cA + dc
            if not (0 <= nrA < N and 0 <= ncA < M and grid[nrA][ncA] != '#'):
                nrA, ncA = rA, cA # Hit wall/bound, stay
            
            # Move B
            nrB, ncB = rB + dr, cB + dc
            if not (0 <= nrB < N and 0 <= ncB < M and grid[nrB][ncB] != '#'):
                nrB, ncB = rB, cB # Hit wall/bound, stay
                
            state = (nrA, ncA, nrB, ncB)
            if state not in visited:
                visited.add(state)
                queue.append((nrA, ncA, nrB, ncB, steps + 1))
                
    print("-1")

if __name__ == "__main__":
    solve()
