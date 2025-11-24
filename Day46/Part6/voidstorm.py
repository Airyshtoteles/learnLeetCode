def solve():
    # Hardcoded Input
    N = 10
    M = 10
    Start = (0, 0)
    H = 100
    D = 15
    
    # Formula Approach
    # Safe time is determined by the smaller dimension
    # Safe zone [t, N-1-t]. Valid if t <= N-1-t => 2t <= N-1 => t <= (N-1)/2
    # Note: At t=0, safe. At t=1, safe...
    # If t = (N-1)//2, safe.
    # At t = (N-1)//2 + 1, unsafe.
    # So we survive (N-1)//2 steps safely?
    # Let's trace N=4. 0,1,2,3.
    # t=0: [0,3]. Safe.
    # t=1: [1,2]. Safe.
    # t=2: Empty. Unsafe.
    # Safe steps: 0->1 (1 sec), 1->2 (1 sec). Total 2 seconds safe?
    # "Setiap detik... boundary mengecil".
    # Usually: Start t=0.
    # End of sec 1: Boundary shrinks. Check damage.
    # If N=4.
    # Sec 1: Move. Boundary becomes [1,2]. Check. Safe.
    # Sec 2: Move. Boundary becomes [2,1] (Empty). Check. Damage.
    # So 1 second safe.
    # Formula: (4-1)//2 = 1. Correct.
    
    t_safe = (min(N, M) - 1) // 2
    
    # Extra time
    # We take damage D per second after t_safe.
    # We survive k seconds if H - k*D > 0 => H > k*D => k < H/D.
    # Max integer k is (H-1)//D.
    
    extra_time = (H - 1) // D
    
    total_time = t_safe + extra_time
    
    print(f"Calculated Max Survival Time: {total_time}")
    
    # Simulation Verification
    curr_r, curr_c = Start
    curr_h = H
    t = 0
    
    center_r = (N - 1) / 2
    center_c = (M - 1) / 2
    
    while curr_h > 0:
        t += 1
        # print(f"Debug Time {t} Pos {curr_r},{curr_c} HP {curr_h}")
        if t > 1000: break
        
        # 1. Move towards center
        if curr_r < center_r: curr_r += 1
        elif curr_r > center_r: curr_r -= 1
        
        if curr_c < center_c: curr_c += 1
        elif curr_c > center_c: curr_c -= 1
        
        # 2. Boundary shrinks
        # Safe zone at end of second t is [t, N-1-t]
        min_safe = t
        max_safe_r = N - 1 - t
        max_safe_c = M - 1 - t
        
        in_safe = True
        if curr_r < min_safe or curr_r > max_safe_r: in_safe = False
        if curr_c < min_safe or curr_c > max_safe_c: in_safe = False
        
        if not in_safe:
            curr_h -= D
            # print(f"Time {t}: Took damage! HP: {curr_h}")
            
    print(f"Simulated Max Survival Time: {t - 1}")

if __name__ == "__main__":
    solve()
