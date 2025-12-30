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
            
        f = []
        for _ in range(n):
            f.append(int(next(iterator)))
            
        if n == 0:
            print(0)
            return
            
        removals = 0
        for i in range(1, n):
            if f[i] == f[i-1]:
                removals += 1
                
        print(removals)
        
    except Exception:
        pass

if __name__ == "__main__":
    solve()
