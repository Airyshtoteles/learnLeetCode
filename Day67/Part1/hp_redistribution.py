def solve():
    try:
        line = input().split()
        if not line: return
        n = int(line[0])
        
        hp = list(map(int, input().split()))
        
        total = sum(hp)
        
        if n > 0 and total % n == 0:
            print("True")
        else:
            print("False")
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
