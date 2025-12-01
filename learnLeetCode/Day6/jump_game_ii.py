"""
Day 6 — Jump Game II (Medium)

Problem: Find minimum number of jumps to reach the last index.
Approach: Greedy with max reach tracking - O(n) time, O(1) space.
Avoids DP's O(n²) complexity by using optimal substructure property.
"""
from typing import List


def jump(nums: List[int]) -> int:
    """
    Find minimum jumps to reach the last index using greedy approach.
    
    Args:
        nums: Array where nums[i] is max jump distance from index i
        
    Returns:
        Minimum number of jumps to reach last index
    """
    if len(nums) <= 1:
        return 0
    
    jumps = 0
    current_end = 0      # End of current jump range
    farthest_reach = 0   # Farthest position reachable so far
    
    # We don't need to jump from the last position
    for i in range(len(nums) - 1):
        # Update farthest reachable position
        farthest_reach = max(farthest_reach, i + nums[i])
        
        # If we've reached the end of current jump range
        if i == current_end:
            jumps += 1
            current_end = farthest_reach
            
            # Early termination if we can reach the end
            if current_end >= len(nums) - 1:
                break
    
    return jumps


def jump_verbose(nums: List[int]) -> int:
    """
    Same algorithm with detailed step tracking for learning purposes.
    """
    if len(nums) <= 1:
        return 0
    
    jumps = 0
    current_end = 0
    farthest_reach = 0
    
    print(f"Starting with nums: {nums}")
    
    for i in range(len(nums) - 1):
        farthest_reach = max(farthest_reach, i + nums[i])
        print(f"  i={i}, nums[i]={nums[i]}, farthest_reach={farthest_reach}")
        
        if i == current_end:
            jumps += 1
            current_end = farthest_reach
            print(f"  -> Jump #{jumps}, new range end: {current_end}")
            
            if current_end >= len(nums) - 1:
                print(f"  -> Can reach end, breaking")
                break
    
    return jumps


if __name__ == "__main__":
    # Test cases from examples
    assert jump([2,3,1,1,4]) == 2
    assert jump([2,3,0,1,4]) == 2
    
    # Edge cases
    assert jump([0]) == 0      # Single element
    assert jump([1]) == 0      # Single element
    assert jump([1,1]) == 1    # Two elements
    assert jump([1,2,3]) == 2  # Multiple small jumps
    assert jump([5,1,1,1,1]) == 1  # One big jump
    
    # Demonstration with verbose output
    print("=== Verbose walkthrough ===")
    result = jump_verbose([2,3,1,1,4])
    print(f"Result: {result}\n")
    
    print("Day6 jump_game_ii.py: all tests passed")