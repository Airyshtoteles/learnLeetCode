def solve_arcane_forge(t, machines):
    total_value = 0
    
    for craft, cd, value in machines:
        cycle_time = craft + cd
        
        # Full cycles
        count = t // cycle_time
        
        # Remaining time
        rem = t % cycle_time
        
        # Can we finish one last item?
        # We only need 'craft' time to finish the item.
        # The cooldown happens after, but if T ends during cooldown, the item is already done.
        if rem >= craft:
            count += 1
            
        total_value += count * value
        
    return total_value

if __name__ == "__main__":
    T = 10
    # craft, cd, value
    Machines = [
        [2, 1, 5],
        [5, 2, 20]
    ]
    
    result = solve_arcane_forge(T, Machines)
    print(f"Maximum Value: {result}")
