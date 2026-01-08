import sys

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        N, K = map(int, line1)
        
        line2 = sys.stdin.readline().split()
        if not line2: P = []
        else: P = [int(x) for x in line2]
    except ValueError:
        return

    if N == 0:
        print(0)
        return

    # sold[i]: max profit up to day i ending with 0 stock
    # held[i]: max profit up to day i ending with 1 stock
    
    sold = [0] * N
    held = [-float('inf')] * N
    
    for i in range(N):
        # Update held[i]
        prev_held = held[i-1] if i > 0 else -float('inf')
        
        # To buy at i, we check sold[i-K-1]
        lookback = i - K - 1
        prev_sold_valid = 0
        if lookback >= 0:
            prev_sold_valid = sold[lookback]
        else:
            prev_sold_valid = 0 # No previous sales restricting us, or base 0
            
        held[i] = max(prev_held, prev_sold_valid - P[i])
        
        # Update sold[i]
        prev_sold = sold[i-1] if i > 0 else 0
        
        # We can sell if we held. 
        # Using held[i] allows Buy+Sell same day (Profit 0).
        # Standard "Buy Sell" logic usually allows this.
        sold[i] = max(prev_sold, held[i] + P[i])

    print(sold[N-1])

if __name__ == "__main__":
    solve()
