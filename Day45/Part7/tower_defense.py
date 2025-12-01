import itertools
import math

def solve():
    # Hardcoded Input
    # 2 Paths
    # Path 1: (0,0) -> (0,5) -> (0,10)
    # Path 2: (5,0) -> (5,5) -> (5,10)
    # Enemy 1: HP 20, Speed 1 unit/s. Path 1.
    # Enemy 2: HP 20, Speed 1 unit/s. Path 2.
    
    # Candidates:
    # 1. (2, 5) - Between paths
    # 2. (0, 5) - On Path 1
    # 3. (5, 5) - On Path 2
    
    # Tower Stats: Radius 3, Damage 5.
    # Fire Rate: Every 2s (t=0, 2, 4...)
    
    paths = [
        [(0,0), (0,1), (0,2), (0,3), (0,4), (0,5), (0,6), (0,7), (0,8), (0,9), (0,10)],
        [(5,0), (5,1), (5,2), (5,3), (5,4), (5,5), (5,6), (5,7), (5,8), (5,9), (5,10)]
    ]
    
    enemies = [
        {'path_idx': 0, 'hp': 20, 'speed': 1},
        {'path_idx': 1, 'hp': 20, 'speed': 1}
    ]
    
    candidates = [
        (2, 5),
        (0, 5),
        (5, 5)
    ]
    
    tower_radius = 3
    tower_damage = 5
    fire_interval = 2
    
    # Try k = 1, 2, 3
    for k in range(1, 4):
        for combo in itertools.combinations(candidates, k):
            # Simulate
            all_dead = True
            
            for enemy in enemies:
                path = paths[enemy['path_idx']]
                hp = enemy['hp']
                speed = enemy['speed']
                
                # Simulation
                # Time t=0, 2, 4...
                # Max time = len(path) / speed
                max_time = len(path) / speed
                
                current_hp = hp
                
                # Check damage at t=0, 2, 4...
                t = 0
                while t < max_time:
                    # Position at time t
                    # Assuming path is discrete points and speed is 1 point/s
                    # index = int(t * speed)
                    # If speed is 1, index = t
                    
                    idx = int(t * speed)
                    if idx >= len(path):
                        break # Reached end
                        
                    pos = path[idx]
                    
                    # Check towers
                    damage_taken = 0
                    for tower_pos in combo:
                        dist = math.sqrt((pos[0]-tower_pos[0])**2 + (pos[1]-tower_pos[1])**2)
                        if dist <= tower_radius:
                            damage_taken += tower_damage
                            
                    current_hp -= damage_taken
                    if current_hp <= 0:
                        break
                        
                    t += fire_interval
                
                if current_hp > 0:
                    all_dead = False
                    break
            
            if all_dead:
                return k
                
    return -1

if __name__ == "__main__":
    result = solve()
    print(f"Minimum towers needed: {result}")
