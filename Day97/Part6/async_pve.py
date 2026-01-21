import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
        
    iterator = iter(input_data)
    try:
        A = int(next(iterator))
        B = int(next(iterator))
        HP_enemy = float(next(iterator))
        HP_player = float(next(iterator))
        D_enemy = float(next(iterator))
        D_player = float(next(iterator))
        Decay = float(next(iterator))
            
    except StopIteration:
        return

    time_e = A
    time_p = B
    
    while HP_enemy > 1e-9 and HP_player > 1e-9:
        t = min(time_e, time_p)
        
        enemy_acts = (time_e == t)
        player_acts = (time_p == t)
        
        if enemy_acts:
            HP_player -= D_enemy
            D_enemy *= Decay
            time_e += A
            
        if player_acts:
            HP_enemy -= D_player
            D_player *= Decay
            time_p += B
            
        if D_enemy < 1e-9 and D_player < 1e-9:
            break
            
    if HP_player > 1e-9 and HP_enemy <= 1e-9:
        print("YES")
    elif HP_player <= 1e-9 and HP_enemy <= 1e-9:
        print("NO") # Draw treated as NO? "Menang tanpa mati"
    else:
        print("NO")

if __name__ == "__main__":
    solve()
