import sys

def solve():
    try:
        input_data = sys.stdin.read().split()
        if not input_data:
            return
        
        iterator = iter(input_data)
        try:
            n = int(next(iterator))
            T = int(next(iterator))
        except StopIteration:
            return
            
        a = []
        for _ in range(n):
            a.append(int(next(iterator)))
            
        stuns = 0
        current_stagger = 0
        
        for dmg in a:
            current_stagger += dmg
            if current_stagger >= T:
                stuns += 1
                current_stagger = 0
                
        print(stuns)
        
    except Exception:
        pass

if __name__ == "__main__":
    solve()
