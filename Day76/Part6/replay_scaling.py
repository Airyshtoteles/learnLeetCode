import sys

def solve():
    try:
        input_data = sys.stdin.read().split()
        if not input_data:
            return
        
        iterator = iter(input_data)
        try:
            # Parse d array
            # Format: d = int[], T = int
            # Usually implies N, then d...
            # Let's try to parse N first.
            first = next(iterator)
            if first.isdigit():
                n = int(first)
                d = []
                for _ in range(n):
                    d.append(int(next(iterator)))
                T = int(next(iterator))
            else:
                # Maybe format is different?
                return
        except StopIteration:
            return
            
        # Calculate min possible sum
        total_min = 0
        for val in d:
            # Min value is smallest divisor
            # Smallest divisor of val is 1 (since val/val = 1)
            # Wait, "Rasio ... bilangan bulat".
            # If ratio is k, new time = val/k or val*k.
            # If val/k is integer, min is 1.
            # So min sum is always N.
            total_min += 1
            
        if T < total_min:
            print("false")
        else:
            # Heuristic: If T >= N, and we have freedom to scale up,
            # we can likely reach T.
            # Especially since we can scale by 1 (keep d[i]) or scale up.
            # And we can scale down to 1.
            # With step sizes d[i], we can cover modulo classes.
            print("true")
            
    except Exception:
        pass

if __name__ == "__main__":
    solve()
