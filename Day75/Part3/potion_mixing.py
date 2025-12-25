import math

def solve():
    try:
        line = input().split()
        if not line:
            return
        
        if len(line) == 1:
            n = int(line[0])
            line2 = input().split()
            a = [int(x) for x in line2]
        else:
            a = [int(x) for x in line]
            
        if not a:
            print(0)
            return
            
        result = a[0]
        for i in range(1, len(a)):
            result = math.gcd(result, a[i])
            
        print(result)
            
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
