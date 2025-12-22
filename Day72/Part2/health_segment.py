def solve():
    try:
        s = input().strip()
        if not s:
            print(0)
            return
            
        ones = s.count('1')
        
        if ones % 2 != 0:
            print(0)
            return
            
        n = len(s)
        if ones == 0:
            # 2^(n-1)
            print(1 << (n - 1))
            return
            
        current_ones = 0
        valid_cuts = 0
        for i in range(n - 1):
            if s[i] == '1':
                current_ones += 1
            if current_ones % 2 == 0:
                valid_cuts += 1
                
        print(1 << valid_cuts)
            
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
