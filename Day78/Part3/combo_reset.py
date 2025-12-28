import sys

def solve():
    try:
        input_data = sys.stdin.read().split()
        if not input_data:
            return
        
        s = input_data[0]
        n = len(s)
        
        if n == 0:
            print(0)
            return
        if n == 1:
            # If we remove, 0. If not, 1. Max 1.
            print(1)
            return
            
        L = [1] * n
        for i in range(1, n):
            if s[i] >= s[i-1]:
                L[i] = L[i-1] + 1
                
        R = [1] * n
        for i in range(n - 2, -1, -1):
            if s[i] <= s[i+1]:
                R[i] = R[i+1] + 1
                
        max_score = max(L)
        
        for i in range(1, n - 1):
            if s[i-1] <= s[i+1]:
                max_score = max(max_score, L[i-1] + R[i+1])
                
        print(max_score)
        
    except Exception:
        pass

if __name__ == "__main__":
    solve()
