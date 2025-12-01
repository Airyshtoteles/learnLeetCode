def solve_rogue_chess(board):
    N = len(board)
    
    # Find all pieces
    pieces = []
    for r in range(N):
        for c in range(N):
            if board[r][c] > 0:
                pieces.append((r, c, board[r][c]))
                
    max_score = 0
    
    # Knight moves
    moves = [
        (-2, -1), (-2, 1), (-1, -2), (-1, 2),
        (1, -2), (1, 2), (2, -1), (2, 1)
    ]
    
    def dfs(r, c, current_score):
        nonlocal max_score
        max_score = max(max_score, current_score)
        
        # Try all valid captures
        for dr, dc in moves:
            nr, nc = r + dr, c + dc
            
            if 0 <= nr < N and 0 <= nc < N and board[nr][nc] > 0:
                # Capture
                val = board[nr][nc]
                board[nr][nc] = 0 # Mark as taken
                
                dfs(nr, nc, current_score + val)
                
                board[nr][nc] = val # Backtrack

    # Try starting at each piece
    # Note: The problem might imply we start "off board" or at a specific empty square?
    # "Ada satu bidak Rogue Knight... bisa melanjutkan langkah hanya jika dia memakan bidak musuh"
    # Usually implies we are AT a square.
    # If we start by capturing, we pick a piece, take it, and are now at that square.
    
    for r, c, val in pieces:
        board[r][c] = 0 # Take the first piece
        dfs(r, c, val)
        board[r][c] = val # Backtrack
        
    return max_score

if __name__ == "__main__":
    # Example: 3x3 board
    # . 1 .
    # 2 . 3
    # . 4 .
    # Knight at (0,1) (val 1) can jump to (2,0) (val 4)? No, (0,1) -> (2,0) is dy=2, dx=-1. Yes.
    # (0,1) -> (2,2) (val ?)
    
    board = [
        [0, 10, 0],
        [20, 0, 30],
        [0, 40, 0]
    ]
    # Start at 10 (0,1).
    # (0,1) -> (2,0) [40] -> Score 50.
    # (0,1) -> (2,2) [0] (Empty).
    # Start at 20 (1,0).
    # (1,0) -> (0,2) [0].
    # (1,0) -> (2,2) [0].
    # Start at 40 (2,0).
    # (2,0) -> (0,1) [10] -> Score 50.
    
    print(f"Max Score: {solve_rogue_chess(board)}")
