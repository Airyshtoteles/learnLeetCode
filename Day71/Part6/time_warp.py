def solve():
    try:
        line1 = input().split()
        if not line1:
            return
        # Assuming first line is n? Or just the array?
        # If input is just the array:
        if len(line1) > 1:
             t = [int(x) for x in line1]
        else:
             # n is first
             n = int(line1[0])
             line2 = input().split()
             t = [int(x) for x in line2]
             
        if not t:
            print(0)
            return
            
        print(max(t))
            
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
