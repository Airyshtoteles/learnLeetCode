import sys

def solve():
    try:
        input_data = sys.stdin.read().split()
        if not input_data:
            return
        
        iterator = iter(input_data)
        try:
            n = int(next(iterator))
            H = int(next(iterator))
        except StopIteration:
            return
            
        d = []
        for _ in range(n):
            d.append(int(next(iterator)))
            
        H_rev = H // 2
        d.sort(reverse=True)
        
        current_subset = []
        current_total = 0
        
        for k in range(1, n + 1):
            val = d[k-1]
            current_subset.append(val)
            current_total += val
            
            if current_total < H + H_rev:
                continue
                
            # Check partition
            # Need subset sum S in [H, current_total - H_rev]
            min_s = H
            max_s = current_total - H_rev
            
            if max_s < min_s:
                continue
                
            # Subset sum using set
            reachable = {0}
            found = False
            
            # Optimization: If range is large, maybe we can find it easily?
            # Just run DP.
            for x in current_subset:
                new_sums = set()
                for s in reachable:
                    ns = s + x
                    if ns <= max_s: # Optimization: Don't store sums > max_s if we only care about <= max_s?
                        # Wait, we need to reach [min_s, max_s].
                        # If we discard sums > max_s, we might miss a path?
                        # No, because we add positive numbers.
                        # If s > max_s, s + x > max_s.
                        # So we can prune sums > max_s.
                        new_sums.add(ns)
                    elif ns >= min_s:
                         # If ns > max_s, but we might need it?
                         # No, we are looking for a FINAL sum in [min_s, max_s].
                         # But intermediate sums can be anything.
                         # However, since we only add positive numbers, if we exceed max_s, we can never come back to <= max_s.
                         # So we can safely ignore sums > max_s.
                         pass
                         
                reachable.update(new_sums)
                
                # Check if any reachable is in range
                # We can check during update
                # But let's check after update or during
                # Actually, checking during is faster.
                
            for s in reachable:
                if min_s <= s <= max_s:
                    found = True
                    break
            
            if found:
                print(k)
                return
                
        print(-1)
        
    except Exception:
        pass

if __name__ == "__main__":
    solve()
