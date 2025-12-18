def solve():
    try:
        line = input().split()
        if not line: return
        n = int(line[0])
        S = int(line[1])
        
        costs = list(map(int, input().split()))
        
        total_cost = sum(costs)
        
        if S > total_cost:
            print("True")
        else:
            print("False")
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
