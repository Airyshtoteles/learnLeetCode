#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

// Problem 5: Multiplayer Resource Desync
// Goal: Craft "Legendary".
// Rules: 
// Rollback can partially remove resources.
// "Consistent" crafting requires using Stable (or eventually stable) resources.
// We assume Input defines:
// Resources 1..N.
// Recipes: Target <- Ingredients.
// Stability: Each Resource is Stable or Unstable.
// Derived Stability:
// A resource is Stable IIF all its ingredients are Stable.
// AND the Server doesn't randomly rollback the Crafting Action?
// "Server bisa rollback state" implies Unstable Environment.
// BUT "Resource dikonsumsi lokal dulu".
// Usually, base resources (gathered) have stability flags.
// Crafted items inherit stability.
//
// Task: Check if Legendary Item (ID L) is Stable.
//
// Input:
// N resources, L target.
// List of Base Stability (0/1).
// Recipes. (DAG).
//
// Logic:
// Recursive Check.
// Memoize stability.

int N, TargetL;
vector<int> stability; // 0 unknown, 1 stable, 2 unstable
struct Recipe {
    vector<int> ingredients;
};
map<int, vector<Recipe>> recipes; // Item -> ways to craft

int is_stable(int u) {
    if (stability[u] != 0) return stability[u];
    
    // Check recipes.
    // If ANY recipe allows stability?
    // Or MUST all ingredients be stable?
    // Usually crafting requires ALL ingredients.
    // If we have multiple ways to craft `u`, do we effectively "Have" u if ONE way is stable?
    // Yes.
    
    if (!recipes.count(u)) {
        // No recipe and not base stable -> Unstable (Impossible to get?)
        return stability[u] = 2; // Unstable
    }
    
    for(const auto& rec : recipes[u]) {
        bool possible = true;
        for(int ing : rec.ingredients) {
            if (is_stable(ing) == 2) {
                possible = false;
                break;
            }
        }
        if (possible) return stability[u] = 1;
    }
    
    return stability[u] = 2;
}

int main() {
    int NumBase;
    if (!(cin >> N >> TargetL >> NumBase)) return 0;
    
    stability.resize(N + 1, 0); // 1 based
    for(int i=0; i<NumBase; ++i) {
        int id; cin >> id;
        stability[id] = 1; // Base Stable
    }
    
    int NumRecipes; cin >> NumRecipes;
    for(int i=0; i<NumRecipes; ++i) {
        int target, k; cin >> target >> k;
        Recipe r;
        for(int j=0; j<k; ++j) {
            int ing; cin >> ing;
            r.ingredients.push_back(ing);
        }
        recipes[target].push_back(r);
    }
    
    if (is_stable(TargetL) == 1) cout << "YES" << endl;
    else cout << "NO" << endl;
    
    return 0;
}
