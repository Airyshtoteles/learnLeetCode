def simulate(a):
    stack = []
    for x in a:
        if stack and stack[-1] == x:
            stack.pop()
        else:
            stack.append(x)
    return len(stack)

def solve():
    try:
        line = input().split()
        if not line: return
        n = int(line[0])
        
        a = list(map(int, input().split()))
        
        if n == 0:
            print(0)
            return
            
        min_remaining = n
        
        for i in range(n):
            temp = a[:i] + a[i+1:]
            remaining = simulate(temp)
            if remaining < min_remaining:
                min_remaining = remaining
                
        print(min_remaining)
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
