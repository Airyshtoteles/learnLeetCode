def solve_arcane_fusion(nums):
    basis = [0] * 64
    
    # Build the Linear Basis
    for num in nums:
        for i in range(63, -1, -1):
            if (num >> i) & 1:
                if basis[i] == 0:
                    basis[i] = num
                    break
                else:
                    num ^= basis[i]
                    
    # Construct Maximum XOR
    max_xor = 0
    for i in range(63, -1, -1):
        if (max_xor ^ basis[i]) > max_xor:
            max_xor ^= basis[i]
            
    return max_xor

if __name__ == "__main__":
    nums = [3, 10, 5, 25, 2, 8]
    result = solve_arcane_fusion(nums)
    print(f"Maximum XOR: {result}")
