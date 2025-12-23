import math

def solve():
    try:
        line = input().split()
        if not line:
            return
        a = int(line[0])
        b = int(line[1])
        
        # Logic: The process is x -> (x + a) % (a + b)
        # Number of unique states is (a + b) / gcd(a, a+b)
        # gcd(a, a+b) = gcd(a, b)
        
        g = math.gcd(a, b)
        print((a + b) // g)
            
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
