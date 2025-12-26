import sys

def solve():
    try:
        input_data = sys.stdin.read().split()
        if not input_data:
            return
        
        iterator = iter(input_data)
        try:
            L = int(next(iterator))
            t = int(next(iterator))
            k = int(next(iterator))
        except StopIteration:
            return
            
        # Logic: Can we place a wall before enemy crosses the arena?
        # Time to cross = L (assuming speed 1)
        # Time to get wall = t
        # Need wall count >= 1
        
        if k >= 1 and t < L:
            print("true")
        else:
            print("false")
            
    except Exception:
        pass

if __name__ == "__main__":
    solve()
