# Day 31 — Part 3: Battle of Tokens

You have a line of integers nums[i]. Two players alternately take 1 or 2 tokens from either the left or right end, summing what they take. Compute the maximum score difference (A - B) achievable by the first player under optimal play.

Approach:
- Let dp[l][r] be the best difference (current player minus opponent) for subarray nums[l..r]. The current player can pick:
  - 1 from left:  nums[l]   - dp[l+1][r]
  - 2 from left: (nums[l]+nums[l+1]) - dp[l+2][r]
  - 1 from right: nums[r]   - dp[l][r-1]
  - 2 from right:(nums[r]+nums[r-1]) - dp[l][r-2]
- Take the maximum among valid options.
- Initialize base cases for length 1 and 2 accordingly.

Complexity: O(n^2) time and O(n^2) space.

Files:
- battle_of_tokens.py — Python implementation.
- battle_of_tokens.cpp — C++17 implementation.
