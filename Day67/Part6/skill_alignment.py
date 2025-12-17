import math

def solve():
    try:
        line = input().split()
        if not line: return
        n = int(line[0])
        if n == 0: return
        
        c = list(map(int, input().split()))
        
        result = 1
        for val in c:
            result = math.lcm(result, val)
            
        print(result)
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
