import math

def gcd(a, b):
    while b:
        a, b = b, a % b
    return a

def solve():
    # Hardcoded Input
    # List of (x, y)
    monsters = [
        (3, 0),
        (0, 5),
        (2, 0),
        (-1, 0),
        (0.5, 0.5) # Angle (1, 1) approx. Dist sqrt(0.5) ~ 0.707. Deadline 1.
    ]
    
    # Map: angle_key -> min_deadline
    angle_deadlines = {}
    
    for x, y in monsters:
        dist = math.sqrt(x*x + y*y)
        deadline = math.ceil(dist)
        
        # Angle Key
        # Handle float coordinates by scaling? 
        # Problem says "posisi awal (x,y)". Usually integers in CP.
        # If floats, we might need atan2 with epsilon.
        # Let's assume integers for the key logic, or use atan2.
        # Using atan2 is safer for floats.
        angle = math.atan2(y, x)
        
        # Discretize angle to handle precision
        # Round to 5 decimal places
        angle_key = round(angle, 5)
        
        if angle_key not in angle_deadlines:
            angle_deadlines[angle_key] = deadline
        else:
            angle_deadlines[angle_key] = min(angle_deadlines[angle_key], deadline)
            
    # Collect deadlines
    deadlines = sorted(angle_deadlines.values())
    
    # Check schedule
    for i, d in enumerate(deadlines):
        if i >= d:
            print("-1")
            return
            
    print(f"Minimum barriers: {len(deadlines)}")

if __name__ == "__main__":
    solve()
