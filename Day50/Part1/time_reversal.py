def solve_time_reversal(monster, k):
    n = len(monster)
    current_monster = list(monster)
    
    for _ in range(k):
        best_reduction = 0
        best_segment = None
        
        # Heuristic: Look for significant inversions
        # We want large values at small indices.
        # Find max value at large index and min value at small index?
        
        # Simplified Greedy: Try to move the global max to position 0, then global max of remainder to pos 1, etc.
        # But we have limited K.
        
        # Let's try to find the single reversal that maximizes gain.
        # Gain from reversing [l, r]:
        # Old: sum_{x=l}^r (x+1)*A[x]
        # New: sum_{x=l}^r (x+1)*A[r-(x-l)]
        # This is O(N^2) to check all. Too slow.
        
        # Optimization: Only check reversals that move the largest misplaced element to its "correct" zone?
        # Let's try to fix the largest elements.
        # Find the largest element that is not in the first few positions.
        
        # For the purpose of this exercise, we'll implement a simplified heuristic:
        # Find the pair (i, j) with largest (A[j] - A[i]) * (j - i) and reverse [i, j].
        # This approximates the gain.
        
        max_diff = -1
        best_l, best_r = -1, -1
        
        # Check a subset of pairs to keep it fast
        # E.g., check top 20 largest values against top 20 smallest values?
        
        indexed_monster = [(val, idx) for idx, val in enumerate(current_monster)]
        indexed_monster.sort(key=lambda x: x[0]) # Sort by value
        
        # Smallest values (should be at right)
        smallest = indexed_monster[:50]
        # Largest values (should be at left)
        largest = indexed_monster[-50:]
        
        found = False
        for val_s, idx_s in smallest:
            for val_l, idx_l in largest:
                if idx_s < idx_l: # Small is left of Large (Bad!)
                    # Reversing [idx_s, idx_l] swaps them (and others).
                    # Estimate gain roughly as (val_l - val_s) * (idx_l - idx_s)
                    # This is just the gain from the endpoints.
                    gain = (val_l - val_s) * (idx_l - idx_s)
                    if gain > max_diff:
                        max_diff = gain
                        best_l, best_r = idx_s, idx_l
                        found = True
                        
        if found:
            # Apply reversal
            l, r = best_l, best_r
            while l < r:
                current_monster[l], current_monster[r] = current_monster[r], current_monster[l]
                l += 1
                r -= 1
        else:
            break
            
    total_damage = sum((i + 1) * val for i, val in enumerate(current_monster))
    return total_damage

if __name__ == "__main__":
    monster = [1, 2, 3, 4, 5] # Already sorted ascending (worst case)
    k = 1
    # Reverse whole array -> [5, 4, 3, 2, 1] -> Best
    print(solve_time_reversal(monster, k))
