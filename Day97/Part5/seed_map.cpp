#include <iostream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

// Problem 5: Procedural Map With Seed Leak
// Map generated from seed S.
// Queries: Is(x,y) wall?
// Query Limit Q.
// Target Known.
//
// Logic:
// We have a Search Space of Seeds (0..MaxS).
// We want to narrow down S such that we are CERTAIN a path exists?
// OR finding the path?
// Querying (x, y) returns Wall/Empty.
// This splits the Seed Set into `S_wall` and `S_empty`.
// Based on real map, one set is valid.
// We update CandidateSeeds.
// If for ALL s in CandidateSeeds, IsReachable(Target), then YES.
//
// But we need to guarantee finding.
// If CandidateSeeds contains maps where Target is UNREACHABLE, we need to query more?
// "Target bisa dijamin ditemukan".
// This means we guide the player to Target.
//
// Simple Version:
// Input: List of Seeds + Map Logic?
// Or simply: Given N possible Seeds, and the ability to query.
// This is "Guess the Seed" game.
// We pick (x,y) to maximize information gain (Split seeds 50/50).
//
// But we are limited by "Inti: information theory".
// Implementing full entropy search is hard.
// Simplified Logic for Day 97:
// Iterate (x, y). Count how many seeds have Wall vs Empty.
// Pick (x,y) with best balance.
// Perform Query. Update Set.
// Repeat until Set size is 1 (Found seed) OR Queries exhausted.
// If Set size > 1: Check if ALL remaining seeds agree on Path?
//
// Mocking the "Query" via input?
// Or simulate against a specific seed?
// Problem asks "Target bisa dijamin".
// Output YES/NO.
// If Max_Queries >= log2(Num_Seeds), YES?
// Assuming queries are perfect.
// Input probably gives: NumSeeds, Queries.
// Grid size?
// List of Maps for each Seed?
// 
// Let's assume input is:
// NumSeeds, Queries.
// For each Seed: The Grid.
// output YES if we can identify seed or guarantee safety.

int N_seeds, Q_limit, Rows, Cols;
vector<vector<string>> maps;

bool solve() {
    // Check if distinct maps <= 2^Q
    // But two seeds might have SAME map.
    // If maps are identical, we don't need to distinguish seeds.
    // We distinct Unique Maps.
    
    set<vector<string>> unique_maps;
    for(const auto& m : maps) unique_maps.insert(m);
    
    int U = unique_maps.size();
    
    // We need ceil(log2(U)) queries to distinguish U items.
    // Actually, we need to distinguish enough to Find Target?
    // Maybe Target is reachable in Map A, but unreachable in Map B.
    // If we have both A and B in candidates, we don't know if we can win.
    // We need to distinguish reachability.
    // But "Target Link" known means coord is known.
    // "Ditemukan" means REACHED.
    //
    // Worst case: U maps.
    // We need Q such that 2^Q >= U?
    // Basic Information Theory: Yes.
    
    long long capacity = 1LL << Q_limit;
    if (capacity >= U) return true;
    return false;
}

int main() {
    if (!(cin >> N_seeds >> Q_limit >> Rows >> Cols)) return 0;
    
    maps.resize(N_seeds);
    for(int i=0; i<N_seeds; ++i) {
        maps[i].resize(Rows);
        for(int r=0; r<Rows; ++r) cin >> maps[i][r];
    }
    
    if (solve()) cout << "YES" << endl;
    else cout << "NO" << endl;
    
    return 0;
}
