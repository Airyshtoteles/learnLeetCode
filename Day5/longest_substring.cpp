#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>
using namespace std;

// Day 5 — Longest Substring Without Repeating Characters
// Approach: Sliding window with hash set to track unique characters.
// Time: O(n), Space: O(min(m,n)) where m is character set size.
int lengthOfLongestSubstring(const string& s) {
    unordered_set<char> charSet;
    int left = 0;
    int maxLength = 0;
    
    for (int right = 0; right < (int)s.length(); ++right) {
        // Shrink window from left until no duplicates
        while (charSet.find(s[right]) != charSet.end()) {
            charSet.erase(s[left]);
            ++left;
        }
        
        // Add current character and update max length
        charSet.insert(s[right]);
        maxLength = max(maxLength, right - left + 1);
    }
    
    return maxLength;
}

int main() {
    // Test cases from examples
    cout << "Testing Day 5 solutions:\n";
    cout << "abcabcbb -> " << lengthOfLongestSubstring("abcabcbb") << " (expected: 3)\n";
    cout << "bbbbb -> " << lengthOfLongestSubstring("bbbbb") << " (expected: 1)\n";
    cout << "pwwkew -> " << lengthOfLongestSubstring("pwwkew") << " (expected: 3)\n";
    
    // Basic validation
    if (lengthOfLongestSubstring("abcabcbb") != 3 ||
        lengthOfLongestSubstring("bbbbb") != 1 ||
        lengthOfLongestSubstring("pwwkew") != 3 ||
        lengthOfLongestSubstring("") != 0 ||
        lengthOfLongestSubstring("a") != 1) {
        cerr << "Test failed!" << endl;
        return 1;
    }
    
    cout << "All tests passed!\n";
    return 0;
}