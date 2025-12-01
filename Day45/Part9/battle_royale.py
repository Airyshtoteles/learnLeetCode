import math

def dist(p1, p2):
    return math.sqrt((p1[0]-p2[0])**2 + (p1[1]-p2[1])**2)

def solve():
    # Hardcoded Input
    # 3 Players
    # P0: (0,0), HP 50, Atk 10, Rng 2, Spd 1
    # P1: (5,0), HP 50, Atk 10, Rng 2, Spd 1
    # P2: (2,5), HP 60, Atk 5, Rng 5, Spd 0 (Sniper)
    
    players = [
        {'id': 0, 'hp': 50, 'atk': 10, 'rng': 2, 'spd': 1, 'pos': [0.0, 0.0], 'alive': True},
        {'id': 1, 'hp': 50, 'atk': 10, 'rng': 2, 'spd': 1, 'pos': [5.0, 0.0], 'alive': True},
        {'id': 2, 'hp': 60, 'atk': 5,  'rng': 5, 'spd': 0, 'pos': [2.5, 5.0], 'alive': True}
    ]
    
    # Seed Cycle (Permutations of 0, 1, 2)
    # Let's say cycle length 2
    cycle = [
        [0, 1, 2],
        [2, 1, 0]
    ]
    
    turn = 0
    max_turns = 100
    
    while turn < max_turns:
        # Check winner
        alive_ids = [p['id'] for p in players if p['alive']]
        if len(alive_ids) <= 1:
            return alive_ids[0] if alive_ids else -1
            
        # 1. Move
        # All move simultaneously towards nearest enemy
        new_positions = []
        for p in players:
            if not p['alive']:
                new_positions.append(p['pos'])
                continue
                
            # Find nearest enemy
            nearest = None
            min_d = float('inf')
            for other in players:
                if p['id'] != other['id'] and other['alive']:
                    d = dist(p['pos'], other['pos'])
                    if d < min_d:
                        min_d = d
                        nearest = other
            
            if nearest:
                # Move towards nearest
                # Direction
                dx = nearest['pos'][0] - p['pos'][0]
                dy = nearest['pos'][1] - p['pos'][1]
                length = math.sqrt(dx*dx + dy*dy)
                
                if length > 0:
                    move_dist = min(p['spd'], length) # Don't overshoot? Or stop at range?
                    # Simple: Move full speed
                    # But if already in range?
                    # "Bergerak mendekati pemain terdekat. Jika dalam range, mereka menyerang."
                    # Usually move then attack.
                    # If in range, maybe stop?
                    # Let's assume they move to minimize distance.
                    
                    # If dist > range, move.
                    # If dist <= range, maybe stay?
                    # Let's assume aggressive: Always move closer until collision (dist=0).
                    
                    nx = p['pos'][0] + (dx/length) * move_dist
                    ny = p['pos'][1] + (dy/length) * move_dist
                    new_positions.append([nx, ny])
                else:
                    new_positions.append(p['pos'])
            else:
                new_positions.append(p['pos'])
        
        # Update positions
        for i, pos in enumerate(new_positions):
            players[i]['pos'] = pos
            
        # 2. Attack
        # Get permutation
        perm = cycle[turn % len(cycle)]
        
        for pid in perm:
            attacker = players[pid]
            if not attacker['alive']: continue
            
            # Find target in range
            # Nearest in range
            target = None
            min_d = float('inf')
            
            for other in players:
                if attacker['id'] != other['id'] and other['alive']:
                    d = dist(attacker['pos'], other['pos'])
                    if d <= attacker['rng']:
                        if d < min_d:
                            min_d = d
                            target = other
            
            if target:
                target['hp'] -= attacker['atk']
                if target['hp'] <= 0:
                    target['alive'] = False
                    
        turn += 1
        
    return -1 # Timeout

if __name__ == "__main__":
    result = solve()
    print(f"Survivor ID: {result}")
