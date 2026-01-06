#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <tuple>
#include <map>

using namespace std;

// Problem: Skill Selection With Global Constraint
// N skills, each gives vector V[i].
// Total vector = sum of selected skills (in order).
// Constraint: Prefix sums must be unique. (No returning to same state).
// Target T.
// Task: Reach T.
// Strategy: BFS from (0,0,...) to T.
// State: Current Vector Sum.
// Neighbors: Add any V[i] (can reuse skills? "Ada n skill". Usually unique or reusable? "Skill Selection" usually means subset. "Urutan skill" -> permutation? Or reusable?)
// "Menghasilkan vector sama -> gagal" implies we lose if we hit a visited state. 
// "Urutan skill" -> implies sequence.
// If skills are unique (subset), we must track used skills.
// If skills are reusable, we just track current sum.
// "Ada n skill... total vector = penjumlahan skill".
// Usually "Skill Selection" implies you pick a subset.
// Let's assume Subset (Bitmask impossible if N large). 
// But "Urutan" (Sequence) matters for prefix?
// If it's a subset, order doesn't change the final sum, but changes the path.
// If any order works, we just need a path.
// But if "prefix sums unique" is the constraint, maybe some orders are invalid while others are valid.
// However, standard BFS finds *any* valid path.
// If Skills are from a set (can't reuse), we need state = (CurrentSum, AvailableSkills).
// If N is small (e.g. <= 20), Bitmask BFS.
// If N is large, maybe skills are reusable?
// "Ada n skill". Usually means a pool.
// Let's assume Reusable for now (like Part 4 "Damage with Forbidden Prefixes" allowed repeats).
// If Subset, the state space is too big without N constraint.
// I will implement "Reusable" BFS. If N is small, it works.

struct Vector {
    vector<int> v;
    bool operator<(const Vector& other) const {
        return v < other.v;
    }
    bool operator==(const Vector& other) const {
        return v == other.v;
    }
};

int main() {
    int N, Dim;
    if (!(cin >> N >> Dim)) return 0;

    vector<Vector> skills(N);
    for (int i = 0; i < N; ++i) {
        skills[i].v.resize(Dim);
        for (int j = 0; j < Dim; ++j) {
            cin >> skills[i].v[j];
        }
    }

    Vector Target;
    Target.v.resize(Dim);
    for (int j = 0; j < Dim; ++j) {
        cin >> Target.v[j];
    }

    // BFS
    queue<Vector> q;
    Vector start;
    start.v.assign(Dim, 0);
    q.push(start);

    set<Vector> visited;
    visited.insert(start);

    while (!q.empty()) {
        Vector curr = q.front();
        q.pop();

        if (curr == Target) {
            cout << "Possible" << endl;
            return 0;
        }

        for (const auto& skill : skills) {
             Vector next = curr;
             for(int k=0; k<Dim; ++k) next.v[k] += skill.v[k];

             if (visited.find(next) == visited.end()) {
                 visited.insert(next);
                 q.push(next);
             }
        }
    }

    cout << "Impossible" << endl;
    return 0;
}
