#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

// Problem 4: Procedural World With Deterministic Chaos
// Rule: Deterministic evolution.
// Unknown Start.
// Goal: Reach Target surely.
// Approach: Maintain set of ALL possible current nodes.
// Transitions: S_new = { rule(u) for u in S }.
// If S_new == {Target}, YES.
// If S_new enters cycle without collapsing to Target, NO (or keep searching if loop matches).
// If steps > Limit, NO.

int main() {
    int N, M, Target;
    if (!(cin >> N >> M >> Target)) return 0;
    
    // Graph representation
    // Edges u->v at step t? 
    // "Rule deterministik". May imply single successor?
    // "World berubah tiap langkah". 
    // Maybe Edge(u, t%P) -> v? Or Input gives transition table for T steps?
    // Let's assume standard automata: N nodes, M input symbols?
    // "Kamu tahu rule". If rule is just time-based, no input.
    // If no input, we just simulate.
    // Input: Edges. Maybe simple directed graph where out-degree=1?
    // Or time dependent? 
    // Assume functional graph u->v.
    // Start with Set = {1..N}.
    // Step repeatedly.
    // Since graph is finite and functional, we enter cycles.
    // Check if the set of possible locations becomes {Target}.
    
    // Input reading: Assume functional graph u->next(u). 
    // If multiple edges map time?
    // Let's assume u -> v.
    
    vector<int> next_node(N + 1);
    for(int i=1; i<=N; ++i) {
        int v; cin >> v; // Input next node for i
        next_node[i] = v;
    }
    
    set<int> current_possible;
    for(int i=1; i<=N; ++i) current_possible.insert(i);
    
    for(int step=0; step < 2 * N + 5; ++step) { // Run enough to enter cycles
        if (current_possible.size() == 1 && *current_possible.begin() == Target) {
            cout << "YES" << endl;
            return 0;
        }
        
        set<int> next_possible;
        for(int u : current_possible) {
            next_possible.insert(next_node[u]);
        }
        current_possible = next_possible;
    }
    
    cout << "NO" << endl;
    return 0;
}
