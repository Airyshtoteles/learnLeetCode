def solve():
    try:
        line = input().split()
        if not line: return
        n = int(line[0])
        
        r = list(map(int, input().split()))
        
        current_reward = 0
        count = 0
        
        for i in range(n):
            if current_reward >= i:
                current_reward += r[i]
                count += 1
                
        print(count)
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
