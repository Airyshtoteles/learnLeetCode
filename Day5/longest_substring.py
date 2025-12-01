"""
Day 5 — Longest Substring Without Repeating Characters

Problem: Find the length of the longest substring without repeating characters.
Approach: Sliding window with hash set to track unique characters.
Time: O(n), Space: O(min(m,n)) where m is character set size.
"""


def length_of_longest_substring(s: str) -> int:
    """
    Find length of longest substring without repeating characters.
    
    Args:
        s: Input string
        
    Returns:
        Length of longest substring without repeating characters
    """
    char_set = set()
    left = 0
    max_length = 0
    
    for right in range(len(s)):
        # Shrink window from left until no duplicates
        while s[right] in char_set:
            char_set.remove(s[left])
            left += 1
        
        # Add current character and update max length
        char_set.add(s[right])
        max_length = max(max_length, right - left + 1)
    
    return max_length


if __name__ == "__main__":
    # Test cases from examples
    assert length_of_longest_substring("abcabcbb") == 3  # "abc"
    assert length_of_longest_substring("bbbbb") == 1     # "b"
    assert length_of_longest_substring("pwwkew") == 3    # "wke"
    
    # Edge cases
    assert length_of_longest_substring("") == 0          # empty string
    assert length_of_longest_substring("a") == 1         # single char
    assert length_of_longest_substring("au") == 2        # no repeats
    assert length_of_longest_substring("dvdf") == 3      # "vdf"
    
    print("Day5 longest_substring.py: all tests passed")