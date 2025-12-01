# LC 1359 — Count All Valid Pickup and Delivery Options
# Formula: product over i=1..n of i * (2*i - 1) mod 1e9+7

MOD = 10**9 + 7

def countOrders(n: int) -> int:
    ans = 1
    for i in range(1, n+1):
        ans = (ans * i) % MOD         # place pickup i among previous pairs
        ans = (ans * (2*i - 1)) % MOD # place delivery i among (2*i - 1) slots
    return ans

if __name__ == "__main__":
    print(countOrders(3))  # 90
