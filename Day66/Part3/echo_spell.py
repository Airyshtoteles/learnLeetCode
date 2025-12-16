def solve():
    try:
        line = input().split()
        if not line: return
        n = int(line[0])
        
        spells = list(map(int, input().split()))
        
        stack = []
        for x in spells:
            current = x
            while stack and stack[-1] == current:
                stack.pop()
                current *= 2
            stack.append(current)
            
        print(sum(stack))
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
