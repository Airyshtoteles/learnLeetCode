import sys
sys.setrecursionlimit(5000)

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
        
    iterator = iter(input_data)
    try:
        N = int(next(iterator))
        TargetL = int(next(iterator))
        NumBase = int(next(iterator))
        
        stability = {} # id -> bool
        for _ in range(NumBase):
            rid = int(next(iterator))
            stability[rid] = True
            
        recipes = {} # target -> list of recipe lists
        NumRecipes = int(next(iterator))
        for _ in range(NumRecipes):
            tgt = int(next(iterator))
            k = int(next(iterator))
            ings = []
            for _ in range(k):
                ings.append(int(next(iterator)))
            
            if tgt not in recipes: recipes[tgt] = []
            recipes[tgt].append(ings)
            
    except StopIteration:
        return
        
    memo = {}
    
    def check(u):
        if u in stability: return True # Base stable
        if u in memo: return memo[u]
        
        if u not in recipes:
            memo[u] = False
            return False
            
        # Is there ANY valid recipe?
        can_craft = False
        for rec in recipes[u]:
            recipe_valid = True
            for ing in rec:
                if not check(ing):
                    recipe_valid = False
                    break
            if recipe_valid:
                can_craft = True
                break
        
        memo[u] = can_craft
        return can_craft

    if check(TargetL):
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    solve()
