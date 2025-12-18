def solve():
    try:
        line = input().split()
        if not line: return
        n = int(line[0])
        H = int(line[1])
        k = int(line[2])
        
        d = list(map(int, input().split()))
        d.sort(reverse=True)
        
        current_damage = 0
        multiplier = 1
        attacks = 0
        
        for dmg in d:
            if current_damage >= H:
                break
                
            damage_dealt = dmg * multiplier
            old_damage = current_damage
            current_damage += damage_dealt
            attacks += 1
            
            old_thresholds = old_damage // k
            new_thresholds = current_damage // k
            
            diff = new_thresholds - old_thresholds
            multiplier *= (2 ** diff)
            
        if current_damage < H:
            print(n)
        else:
            print(attacks)
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
