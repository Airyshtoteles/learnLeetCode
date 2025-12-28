import sys

def solve():
    try:
        input_data = sys.stdin.read().split()
        if not input_data:
            return
        
        iterator = iter(input_data)
        try:
            n = int(next(iterator))
            H = int(next(iterator))
        except StopIteration:
            return
            
        d = []
        for _ in range(n):
            d.append(int(next(iterator)))
            
        d.sort(reverse=True)
        
        current_sum = 0
        found = False
        for t in range(n):
            current_sum += d[t]
            if current_sum >= H:
                print(t)
                found = True
                break
                
        if not found:
            print(-1)
            
    except Exception:
        pass

if __name__ == "__main__":
    solve()
