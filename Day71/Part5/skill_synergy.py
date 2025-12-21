def simulate(p):
    if not p:
        return 0
    stack = []
    max_val = 0
    for x in p:
        max_val = max(max_val, x)
        stack.append(x)
        while len(stack) >= 2:
            if stack[-1] == stack[-2]:
                val = stack.pop()
                stack.pop()
                new_val = val + 1
                stack.append(new_val)
                max_val = max(max_val, new_val)
            else:
                break
    return max_val

def solve():
    try:
        line = input().split()
        if not line:
            return
        # Assuming first line is n? Or just the array?
        # Based on C++ code, I read n first.
        # Let's assume input is:
        # n
        # p1 p2 ... pn
        # Or just p1 p2 ... pn on one line?
        # The prompt format: "p = int[]". Usually implies standard competitive format.
        # I'll handle both single line or two lines.
        
        if len(line) == 1:
            n = int(line[0])
            line2 = input().split()
            p = [int(x) for x in line2]
        else:
            # Maybe just the array?
            p = [int(x) for x in line]
            n = len(p)
            
        if n == 0:
            print(0)
            return
        if n == 1:
            print(0)
            return
            
        global_max = 0
        for i in range(n):
            temp = p[:i] + p[i+1:]
            global_max = max(global_max, simulate(temp))
            
        print(global_max)
            
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
