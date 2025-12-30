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
            
        t = []
        for _ in range(n):
            t.append(int(next(iterator)))
            
        # Checkpoint i is reached at minimum time i.
        # Constraint: time <= t[i].
        
        possible = True
        for i in range(n):
            if i > t[i]:
                possible = False
                break
                
        print("true" if possible else "false")
        
    except Exception:
        pass

if __name__ == "__main__":
    solve()
