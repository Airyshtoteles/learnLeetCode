import sys
from collections import deque

def solve():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return

    iterator = iter(data)
    try:
        H = int(next(iterator))
        n = int(next(iterator))
        d = []
        for _ in range(n):
            d.append(int(next(iterator)))
    except StopIteration:
        return

    # BFS with states (hp, last_3_damages_tuple)
    q = deque()
    dist = {}
    
    initial_state = (H, tuple())
    q.append(initial_state)
    dist[initial_state] = 0
    
    ans = float('inf')
    
    while q:
        hp, seq = q.popleft()
        attacks = dist[(hp, seq)]
        
        if hp <= 0:
            ans = min(ans, attacks)
            continue
        
        # Try each damage
        for dmg in d:
            new_seq = seq + (dmg,)
            
            # Check forbidden pattern
            forbidden = False
            if len(new_seq) >= 6:
                # Last 3 damages vs 3 before that
                if (new_seq[-1] == new_seq[-4] and
                    new_seq[-2] == new_seq[-5] and
                    new_seq[-3] == new_seq[-6]):
                    forbidden = True
            
            if not forbidden:
                # Keep only last 3 damages
                if len(new_seq) > 3:
                    new_seq = new_seq[-3:]
                
                new_hp = hp - dmg
                new_attacks = attacks + 1
                new_state = (new_hp, new_seq)
                
                if new_state not in dist or dist[new_state] > new_attacks:
                    dist[new_state] = new_attacks
                    q.append(new_state)
    
    if ans == float('inf'):
        print(-1)
    else:
        print(ans)

if __name__ == "__main__":
    solve()
