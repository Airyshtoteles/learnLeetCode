import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
        
    iterator = iter(input_data)
    try:
        N = int(next(iterator))
        HP_init = int(next(iterator))
        SkipCost = int(next(iterator))
        
        Base = []
        Factor = []
        for _ in range(N):
            Base.append(int(next(iterator)))
            Factor.append(int(next(iterator)))
            
    except StopIteration:
        return

    # dp[i] = max HP entering phase i
    # Phase 0 to N-1. Target is Phase N (Completed).
    
    dp = [-1] * (N + 1)
    dp[0] = HP_init
    
    for i in range(N):
        if dp[i] == -1:
            continue
            
        current_hp = dp[i]
        
        # Fight
        # Dmg = Base + (Current * Factor // 100)
        dmg = Base[i] + (current_hp * Factor[i] // 100)
        rem_fight = current_hp - dmg
        if rem_fight > 0:
            dp[i+1] = max(dp[i+1], rem_fight)
            
        # Skip
        rem_skip = current_hp - SkipCost
        if rem_skip > 0:
            dp[i+1] = max(dp[i+1], rem_skip)
            
    if dp[N] > 0:
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    solve()
