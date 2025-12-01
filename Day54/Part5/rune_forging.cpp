#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>

using namespace std;

struct Rule {
    string ing1;
    string ing2;
    string result;
};

string solve_rune_forging(vector<string> basic_runes, vector<Rule> recipes, string target) {
    unordered_set<string> available;
    queue<string> q;

    // Initialize with basic runes
    for (const string& r : basic_runes) {
        available.insert(r);
        q.push(r);
    }

    // Map: Ingredient -> List of Recipe Indices
    unordered_map<string, vector<int>> ingredient_usage;
    for (int i = 0; i < recipes.size(); ++i) {
        ingredient_usage[recipes[i].ing1].push_back(i);
        ingredient_usage[recipes[i].ing2].push_back(i);
    }

    // Track status of recipes
    // We need to know if a recipe is "ready".
    // A recipe is ready if both ingredients are in 'available'.
    // Since we process updates via queue, we can just check conditions when an ingredient is added.
    // But we need to avoid re-adding.
    
    // Better approach:
    // Just loop until no changes? Or use the map.
    // If I have A, check all recipes using A. If the other ingredient is also present, add Result.
    
    while (!q.empty()) {
        string curr = q.front();
        q.pop();

        if (curr == target) return "YES";

        if (ingredient_usage.find(curr) != ingredient_usage.end()) {
            for (int recipe_idx : ingredient_usage[curr]) {
                const Rule& r = recipes[recipe_idx];
                // Check if we can craft r.result
                if (available.count(r.result)) continue; // Already have it

                if (available.count(r.ing1) && available.count(r.ing2)) {
                    available.insert(r.result);
                    q.push(r.result);
                }
            }
        }
    }

    return available.count(target) ? "YES" : "NO";
}

int main() {
    // Test 1
    /*
    Basic: "Fire", "Water"
    Recipes:
    Fire + Water -> Steam
    Steam + Fire -> Energy
    Target: Energy
    */
    vector<string> basic1 = {"Fire", "Water"};
    vector<Rule> recipes1 = {
        {"Fire", "Water", "Steam"},
        {"Steam", "Fire", "Energy"}
    };
    cout << "Test 1 (Expected YES): " << solve_rune_forging(basic1, recipes1, "Energy") << endl;

    // Test 2
    /*
    Basic: "Earth"
    Recipes: Earth + Fire -> Lava
    Target: Lava
    */
    vector<string> basic2 = {"Earth"};
    vector<Rule> recipes2 = {
        {"Earth", "Fire", "Lava"}
    };
    cout << "Test 2 (Expected NO): " << solve_rune_forging(basic2, recipes2, "Lava") << endl;

    return 0;
}
