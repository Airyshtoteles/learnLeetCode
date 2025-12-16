def solve():
    try:
        line1 = input().split()
        if not line1: return
        n = int(line1[0])
        M = int(line1[1])
        
        drain = list(map(int, input().split()))
        
        visited = set()
        current_pos = 0
        
        while M > 0:
            if current_pos in visited:
                print("True")
                return
            visited.add(current_pos)
            
            M -= drain[current_pos]
            if M <= 0:
                print("False")
                return
            
            current_pos = (current_pos + drain[current_pos]) % n
            
        print("False")
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
