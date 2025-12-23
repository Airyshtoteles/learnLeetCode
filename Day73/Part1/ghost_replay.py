def solve():
    try:
        line = input().split()
        if not line:
            return
        
        # Check if first element is n
        if len(line) == 1:
            n = int(line[0])
            # Read array
            line2 = input().split()
            moves = [int(x) for x in line2]
        else:
            # Array is on the first line
            moves = [int(x) for x in line]
            n = len(moves)
            
        if n == 0:
            print(0)
        else:
            print(n - 1)
            
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
