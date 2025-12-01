from typing import List

def max_sum_of_three_subarrays(nums: List[int], k: int) -> List[int]:
    n = len(nums)
    win = [0]*(n-k+1)
    cur = sum(nums[:k])
    win[0] = cur
    for i in range(1, n-k+1):
        cur += nums[i+k-1] - nums[i-1]
        win[i] = cur

    left = [0]*len(win)
    best = 0
    for i in range(len(win)):
        if win[i] > win[best]:
            best = i
        left[i] = best

    right = [0]*len(win)
    best = len(win)-1
    for i in range(len(win)-1, -1, -1):
        if win[i] >= win[best]:
            best = i
        right[i] = best

    ans = [-1,-1,-1]
    maxsum = -1
    for m in range(k, len(win)-k):
        l = left[m-k]
        r = right[m+k]
        s = win[l] + win[m] + win[r]
        if s > maxsum:
            maxsum = s
            ans = [l, m, r]
    return ans

if __name__ == "__main__":
    print(max_sum_of_three_subarrays([1,2,1,2,6,7,5,1], 2))  # Expected [0,3,5]
