def solve():
    try:
        line = input().split()
        if not line: return
        n = int(line[0])
        K = int(line[1])
        
        d = list(map(int, input().split()))
        
        total_difficulty = 0
        modifier = 0
        
        for val in d:
            current_diff = val + modifier
            if current_diff < 0:
                current_diff = 0
            
            total_difficulty += current_diff
            modifier -= 1
            
        if total_difficulty <= K:
            print("True")
        else:
            print("False")
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
