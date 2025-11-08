from typing import List

BITS = 31  # for up to 1e9 < 2^30

def insert_basis(basis: List[int], x: int) -> None:
    for i in reversed(range(BITS)):
        if not (x >> i) & 1:
            continue
        if basis[i] == 0:
            basis[i] = x
            return
        x ^= basis[i]

def merge_basis(dst: List[int], src: List[int]) -> None:
    for v in src:
        if v:
            insert_basis(dst, v)

def max_xor(basis: List[int]) -> int:
    res = 0
    for i in reversed(range(BITS)):
        if basis[i] and (res ^ basis[i]) > res:
            res ^= basis[i]
    return res

def k_alternating_max_xor(nums: List[int], k: int) -> int:
    n = len(nums)
    # Store bases B[i]; each basis is length BITS
    B = [ [0]*BITS for _ in range(n+ k + 1) ]  # extra padding to avoid bounds
    for i in range(n-1, -1, -1):
        # Start from B[i+1] (skip i case)
        cur = B[i][:]
        merge_basis(cur, B[i+1])
        # Include choosing i then jump to i+k
        choose_basis = B[i+k][:]
        insert_basis(choose_basis, nums[i])
        merge_basis(cur, choose_basis)
        B[i] = cur
    return max_xor(B[0])

if __name__ == "__main__":
    print(k_alternating_max_xor([3,10,5,25,2,8], 2))  # Expect 26 per problem example
