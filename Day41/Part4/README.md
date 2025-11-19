# String Reduction to Empty Using Double-Rule Deletions

Level: Hard (Observation)

You can delete any substring t if:
1. t is a palindrome of length ≥ 2, OR
2. All characters of t are pairwise distinct.

Determine if the string s can be fully reduced to empty.

## Key Insight
Any two-character substring qualifies: either characters equal (palindrome length 2) or distinct (distinct rule). Thus we can iteratively delete the string in chunks of length 2 (adjacent pairs) until possibly one character remains.
A single remaining character cannot be deleted.
Therefore: answer is True iff |s| ≠ 1.

Edge case: empty string (already empty) → True.

## Complexity
O(1) time, O(1) space.
