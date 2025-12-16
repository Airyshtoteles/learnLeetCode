import math

def solve():
    try:
        line = input().split()
        if not line: return
        n = int(line[0])
        if n == 0: return
        
        slots = list(map(int, input().split()))
        
        result = slots[0]
        for i in range(1, n):
            result = math.gcd(result, slots[i])
            
        print(result)
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
