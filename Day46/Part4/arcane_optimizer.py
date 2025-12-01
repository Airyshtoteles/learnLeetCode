def solve():
    # Hardcoded Input
    T = 20
    # Skills: (cast_time, damage, cooldown)
    skills = [
        (2, 20, 5),   # Skill A: 10 DPS, 7s cycle
        (1, 8, 0),    # Skill B: 8 DPS, 1s cycle (Spam)
        (5, 60, 10),  # Skill C: 12 DPS, 15s cycle (Big nuke)
        (3, 30, 3)    # Skill D: 10 DPS, 6s cycle
    ]
    
    # Sort by DPS (Damage / CastTime) descending
    # If DPS equal, sort by Damage descending
    sorted_skills = []
    for i, (cast, dmg, cool) in enumerate(skills):
        dps = dmg / cast
        sorted_skills.append({
            'id': i,
            'cast': cast,
            'dmg': dmg,
            'cool': cool,
            'dps': dps
        })
        
    sorted_skills.sort(key=lambda x: (-x['dps'], -x['dmg']))
    
    current_time = 0
    total_damage = 0
    ready_time = [0] * len(skills)
    
    history = []
    
    while current_time < T:
        best_skill = None
        
        # Find best available skill
        for skill in sorted_skills:
            idx = skill['id']
            if ready_time[idx] <= current_time:
                # Check if it fits in remaining time
                if current_time + skill['cast'] <= T:
                    best_skill = skill
                    break
        
        if best_skill:
            idx = best_skill['id']
            cast = best_skill['cast']
            dmg = best_skill['dmg']
            cool = best_skill['cool']
            
            # Cast it
            history.append(f"Time {current_time}: Cast Skill {idx} (Dmg {dmg})")
            total_damage += dmg
            current_time += cast
            ready_time[idx] = current_time + cool
        else:
            # No skill ready or fits
            # Advance time to next ready event
            next_ready = float('inf')
            can_fit_any = False
            
            for skill in sorted_skills:
                idx = skill['id']
                r_time = ready_time[idx]
                if r_time < next_ready:
                    next_ready = r_time
                
                # Check if this skill could ever fit
                # Actually, if we are here, it means either:
                # 1. All skills are on cooldown.
                # 2. Some skills are ready but don't fit in remaining T.
                
                # If a skill is ready but doesn't fit, we can't use it ever.
                # If a skill is on cooldown, we might use it later.
            
            if next_ready == float('inf'):
                break
                
            if next_ready > current_time:
                # Jump
                # But wait, if next_ready + cast > T for ALL skills, we are done.
                # We need to check if jumping helps.
                if next_ready >= T:
                    break
                current_time = next_ready
            else:
                # If next_ready <= current_time, it means we have ready skills but they don't fit.
                # And since we iterated all sorted skills and found none that fit,
                # we are effectively done because time only moves forward.
                break
                
    print(f"Total Damage: {total_damage}")
    # for h in history:
    #     print(h)

if __name__ == "__main__":
    solve()
