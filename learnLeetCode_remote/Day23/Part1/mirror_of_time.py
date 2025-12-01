# The Mirror of Time
# Minimum total |i-j| swap cost to make array a palindrome (if possible)
# Greedy two-pointer like "min adjacent swaps to make palindrome" but we can swap non-adjacently with cost = distance.
from typing import List

def min_cost_palindrome(arr: List[int]) -> int:
    a = arr[:]
    n = len(a)
    i, j = 0, n-1
    cost = 0
    while i < j:
        if a[i] == a[j]:
            i += 1; j -= 1
            continue
        # find match for a[i] from the right
        k = j
        while k > i and a[k] != a[i]:
            k -= 1
        if k == i:
            # a[i] is the lone middle element; move it one step toward center
            a[i], a[i+1] = a[i+1], a[i]
            cost += 1
        else:
            # swap a[k] directly to position j
            a[k], a[j] = a[j], a[k]
            cost += (j - k)
            i += 1; j -= 1
    # validate palindrome
    for x in range(n//2):
        if a[x] != a[n-1-x]:
            return -1
    return cost

if __name__ == "__main__":
    print(min_cost_palindrome([1,3,1]))  # 0
    print(min_cost_palindrome([1,2,3,2,1]))  # 0
    print(min_cost_palindrome([1,2,3,1,2]))  # 2 (swap 3 towards center)
    # Note: if all values are unique and length>1, it's impossible -> -1
