import sys

def solve():
    try:
        input_data = sys.stdin.read().split()
        if not input_data:
            return
        
        iterator = iter(input_data)
        try:
            n = int(next(iterator))
        except StopIteration:
            return
            
        shield = []
        for _ in range(n):
            shield.append(int(next(iterator)))
            
        attacks = []
        for x in iterator:
            attacks.append(int(x))
            
        if not attacks:
            if sum(shield) == 0:
                print("true")
            else:
                print("false")
            return
            
        M = len(attacks)
        
        # Calculate slots and sort
        targets = []
        for i in range(n):
            slots = M // n + (1 if i < M % n else 0)
            if slots == 0:
                if shield[i] > 0:
                    print("false")
                    return
                avg = 0
            else:
                avg = shield[i] / slots
            targets.append((avg, i, slots, shield[i]))
            
        targets.sort(key=lambda x: x[0], reverse=True)
        attacks.sort(reverse=True)
        
        attack_idx = 0
        possible = True
        
        for avg, idx, slots, req in targets:
            current_sum = 0
            for _ in range(slots):
                if attack_idx < M:
                    current_sum += attacks[attack_idx]
                    attack_idx += 1
            
            if current_sum < req:
                possible = False
                break
                
        print("true" if possible else "false")
        
    except Exception:
        pass

if __name__ == "__main__":
    solve()
