import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
        
    iterator = iter(input_data)
    try:
        H = int(next(iterator))
        Rate = int(next(iterator))
        L = int(next(iterator))
        K_limit = int(next(iterator))
        M_saves = int(next(iterator))
        
        min_s = None
        for _ in range(M_saves):
            s = int(next(iterator))
            if min_s is None or s < min_s:
                min_s = s
        
        # If min_s is None, no saves
        max_segment = 0
        if min_s is not None:
            max_segment = L - min_s
            
        possible = False
        
        # k=0
        if Rate * L >= H:
            possible = True
            
        if not possible and max_segment > 0:
            for k in range(1, K_limit + 1):
                # Python handles large integers automatically
                req_hp = H * (2 ** k)
                dmg = Rate * (L + k * max_segment)
                
                if dmg >= req_hp:
                    possible = True
                    break
        
        if possible:
            print("YES")
        else:
            print("NO")
            
    except StopIteration:
        return

if __name__ == "__main__":
    solve()
