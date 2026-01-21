import sys

# Recursion limit
sys.setrecursionlimit(5000)

groups = []
memo = {}

def rle_len(count):
    if count <= 0: return 0
    d = 1
    if count >= 100: d = 3
    elif count >= 10: d = 2
    return 1 + d

def solve_dp(l, r, k):
    if k < 0: return -float('inf')
    if l > r: return 0
    
    state = (l, r, k)
    if state in memo: return memo[state]
    
    if l == r:
        return rle_len(groups[l]['count'])
        
    res = 0
    
    # Skip L
    costL = groups[l]['count']
    if k >= costL:
        res = max(res, solve_dp(l + 1, r, k - costL))
        
    # Skip R
    costR = groups[r]['count']
    if k >= costR:
        res = max(res, solve_dp(l, r - 1, k - costR))
        
    # Match
    if groups[l]['c'] == groups[r]['c']:
        cntL = groups[l]['count']
        cntR = groups[r]['count']
        match_cost = abs(cntL - cntR)
        final_count = min(cntL, cntR)
        
        if k >= match_cost:
            inner = solve_dp(l + 1, r - 1, k - match_cost)
            if inner >= -1: # Valid
                res = max(res, 2 * rle_len(final_count) + inner)
                
    memo[state] = res
    return res

def solve():
    global groups, memo
    input_data = sys.stdin.read().split()
    if not input_data: return
    
    s = input_data[0]
    k_val = int(input_data[1])
    
    groups = []
    if s:
        curr_c = s[0]
        curr_cnt = 1
        for char in s[1:]:
            if char == curr_c:
                curr_cnt += 1
            else:
                groups.append({'c': curr_c, 'count': curr_cnt})
                curr_c = char
                curr_cnt = 1
        groups.append({'c': curr_c, 'count': curr_cnt})
        
    memo = {}
    print(solve_dp(0, len(groups) - 1, k_val))

if __name__ == "__main__":
    solve()
