import sys

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        N = int(line1[0])
        
        line2 = sys.stdin.readline().split()
        if not line2: return
        D = [int(x) for x in line2]
    except ValueError:
        return

    seen = set()
    total_damage = 0
    
    for x in D:
        if x in seen:
            break
        seen.add(x)
        total_damage += x
        
    print(total_damage)

if __name__ == "__main__":
    solve()
