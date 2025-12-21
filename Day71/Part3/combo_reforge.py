def solve():
    try:
        s = input().strip()
        if not s:
            print(0)
            return
            
        target = s[-1]
        count = 0
        for c in s:
            if c != target:
                count += 1
                
        print(count)
            
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
