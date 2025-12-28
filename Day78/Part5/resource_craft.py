import sys

def solve():
    try:
        input_data = sys.stdin.read().split()
        if not input_data:
            return
        
        iterator = iter(input_data)
        try:
            A = int(next(iterator))
            n = int(next(iterator))
        except StopIteration:
            return
            
        r = []
        for _ in range(n):
            r.append(int(next(iterator)))
            
        # Sort descending
        r.sort(reverse=True)
        
        current = A
        for val in r:
            if val != 0:
                current = (current // val) + 1
                
        print(current)
        
    except Exception:
        pass

if __name__ == "__main__":
    solve()
