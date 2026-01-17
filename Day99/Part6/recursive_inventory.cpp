#include <iostream>
#include <vector>
#include <map>
#include <numeric>

using namespace std;

// Problem 6: Inventory With Recursive Weight
// Item i: Weight = 1 + Sum(contents).
// Logic: DP/Memoization.
// Task: "Target item bisa dibawa?".
// Implicitly: Can we pack Target into Root Container (Capacity C)?
// Target must be inside Root.
// Root can directly contain Target, or contain A which contains Target.
// We need to form a Chain: Root -> I1 -> ... -> Target.
// Along the chain, we must satisfy Capacity and Parity.
// But we can also pack *other* items to fill weight/parity.
// This is complex.
// Simplified interpretation:
// Just check if Target itself fits in Root?
// Or construct the nesting?
// "Item bias berisi item lain".
// If standard recursive knapsack, we calculate min weight of Target.
// W(Target) is fixed? No, "Item bisa berisi". We put items INTO it.
// So W(Target) = 1 + W(Stuff inside).
// If Target is empty, W=1.
// If we put stuff, W increases.
// Maybe we need to make Target HEAVY enough for parity?
// Or Root has parity constraint for Target?
// Constraint: "Item only inserted if TOTAL WEIGHT Even/Odd".
// So to put T into Parent, T's weight must match Parent's rule.
// We can modify T's weight by putting stuff in T.
//
// Recursive checking: CanObjectBeParams(Item, ParityReq, MaxCap).
// Returns true if Item can be configured to have weight W <= MaxCap AND W % 2 == ParityReq.
// Base Item: Weight 1.
// We can add sub-items.
// Sub-items must satisfy Item's internal rules?
// Assuming input gives rules for each item type.
// Rules: Parity required for *contents*? Or for *entering*?
// "Dimasukkan jika total berat genap/ganjil".
// Usually refers to the item being moved. "Item X can enter Y if Weight(X) is Odd".
//
// Algorithm:
// Compute reachable weights for each item type.
// Since Capacity is limited (small?), use bitset or set of weights.
// Set<int> PossibleWeights[ItemType].
// Since dependencies are cyclic (recursive)? No, physical items. DAG or Tree.
// If types, we can instantiate multiple.
// If infinite instances -> Knapsack.
// If single instance -> Subset Sum.
// Assume Types with infinite availability.
//
// DP state: ReachableWeights[Type].
// Iterate? 
// If dependency loop (A contains A), weight -> infinity. Prune by Cap.

int N_types, TargetType, RootCap;
struct TypeInfo {
    int req_parity; // 0 even, 1 odd, -1 any (for logic?)
    // Actually, the rule is "Can be inserted IF weight is X".
    // Who imposes rule? The Container?
    // "Beberapa item hanya bisa dimasukkan jika...".
    // Usually the Container has the constraint? "Container A only accepts Even items".
    // Or Item has constraint? "Item A only fits in Even slots".
    // Prompt: "Item only inserted if total weight even/odd". ambiguous.
    // Assume Container imposes rule.
    // Input: For each type, "Accepts Parity".
};

// Simplified: Each item has base weight 1.
// Can add children.
// Children must satisfy Item's filter.
// We want to construct Target such that it fits in Root (Root has filter).
// And maybe Root recursively fits elsewhere? No, "Target dibawa" = in Root.
//
// So:
// 1. Calculate possible weights for all types.
//    W = 1 + sum(weights of children).
//    Children can be any type C where W(C) matches filter of Parent.
//    Unbounded Knapsack where value=weight.
//    We want to generate all possible weights up to RootCap.
//    Since W >= 1, it terminates.
//
// 2. Check if any w in PossibleWeights[Target] fits Root.

vector<int> type_filter; // 0: even, 1: odd, 2: any
vector<set<int>> possible_weights;

int main() {
    if (!(cin >> N_types >> TargetType >> RootCap)) return 0;
    
    type_filter.resize(N_types + 1);
    for(int i=1; i<=N_types; ++i) cin >> type_filter[i]; // What this type ACCEPTS.
    
    possible_weights.resize(N_types + 1);
    
    // Iteratively update weights.
    // Init: All have weight 1 (empty).
    for(int i=1; i<=N_types; ++i) possible_weights[i].insert(1);
    
    bool changed = true;
    while(changed) {
        changed = false;
        for(int i=1; i<=N_types; ++i) {
            // Try to add one more item to current configurations
            // Knapsack style: For each current weight w, try adding child c.
            // New weight = w + weight(c).
            // Valid if weight(c) matches filter[i].
            // And w + weight(c) <= RootCap (Optimization, internal items shouldn't exceed RootCap generally).
            
            // Optimization: Unbounded Knapsack to find reachable weights.
            // Since we iterate N types, ordering matters?
            // Just repeat until stable.
            
            // Collect all valid child weights for this container
            vector<int> valid_child_weights;
            for(int c=1; c<=N_types; ++c) {
                for(int cw : possible_weights[c]) {
                    int p = cw % 2;
                    if (type_filter[i] == 2 || type_filter[i] == p) {
                        valid_child_weights.push_back(cw);
                    }
                }
            }
            
            // Update i
            // This is making 'i' combining MULTIPLE items.
            // "Item berisi item lain". Plural.
            // So we solve knapsack for 'i'.
            // Reachable weights = 1 + Combo(valid_child_weights).
            // Combo is subset sum of valid_child_weights.
            
            // Since we can add ANY number of valid items?
            // Yes.
            // Use DP array `can_make[w]` initialized with current possible_weights[i].
            
            vector<bool> dp(RootCap + 1, false);
            for(int w : possible_weights[i]) dp[w] = true;
            
            for(int cw : valid_child_weights) {
                for(int w = 1; w <= RootCap - cw; ++w) { // Forward or Backward? Unlimited items -> Forward.
                    // If items are types (infinite supply) -> Forward loop is correct for Unbounded Knapsack?
                    // No, "valid_child_weights" is a list of specific weights available.
                    // If we can use type C multiple times, do we treat multiple distinct weights of C as same item?
                    // Yes.
                    // Simple logic:
                    if (dp[w]) {
                        if (w + cw <= RootCap) {
                            if (!dp[w + cw]) {
                                dp[w + cw] = true;
                                possible_weights[i].insert(w + cw);
                                changed = true;
                            }
                        }
                    }
                }
            }
        }
    }
    
    // Check Target
    // Root Filter? Assume Root accepts Any? Or distinct Input?
    // "Target item bisa dibawa". Implies fits in Capacity.
    // Does Root have parity filter?
    // Assume Root is just capacity.
    // Standard interpretation: Can we construct Target with W <= RootCap?
    // If Root has filter, we need to check W % 2.
    // Let's assume Root accepts ANY parity (Container logic applies to Items, Root is User).
    
    bool possible = false;
    for(int w : possible_weights[TargetType]) {
        if (w <= RootCap) {
            possible = true;
            break;
        }
    }
    
    if (possible) cout << "YES" << endl;
    else cout << "NO" << endl;
    
    return 0;
}
