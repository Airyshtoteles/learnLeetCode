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
            
        v = []
        for _ in range(n):
            v.append(int(next(iterator)))
            
        if n == 0:
            print(0)
            return
            
        total_value = 0
        # First item
        total_value += v[0]
        
        for i in range(1, n):
            val = v[i]
            if v[i] < v[i-1]:
                val *= 2
            total_value += val
            
        print(total_value)
        
    except Exception:
        pass

if __name__ == "__main__":
    solve()
