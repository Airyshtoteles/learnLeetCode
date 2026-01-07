#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <queue>
#include <map>

using namespace std;

// Problem: Economy With Self-Describing Inflation
// State: Money.
// Inflation = Function of History.
// Constraint: Unique History (History -> Inflation).
// If two histories produce same inflation -> Collapse.
// This effectively means "Inflation" acts as a hash of the history.
// And we cannot revisit an "Inflation State".
// Inflation computation isn't fully specified, but "function of entire history"
// usually means `CurrentInflation = F(PrevInflation, Transaction)`.
// We need to reach Money >= W.
// BFS State: (Money, Inflation).
// Transitions: Apply transaction rules.
// Update rules: M_new = M + dM, I_new = Update(I, dM).
// "Update" function needs to be known.
// Assuming simple hash-like update or given rules.
// Let's assume input gives rules like:
// "If move i, dMoney = X, dInflation = Y (or I_new = (I + Y) % Mod)".
// Problem says "fungsi dari seluruh histori".
// Let's assume standard problem input format: M transactions available.
// Each transaction: Cost, InflationChange (or NextStep).
// BFS to reach W.

struct State {
    long long money;
    long long inflation;
    bool operator<(const State& other) const {
        if (money != other.money) return money < other.money;
        return inflation < other.inflation;
    }
};

int main() {
    long long InitialMoney, TargetW;
    long long InitialInflation = 0;
    int N_Trans;

    if (!(cin >> InitialMoney >> TargetW >> N_Trans)) return 0;

    // Transaction: dMoney, dInflation
    struct Trans {
        long long dM;
        long long dI;
    };
    vector<Trans> options(N_Trans);
    for (int i = 0; i < N_Trans; ++i) {
        cin >> options[i].dM >> options[i].dI;
    }

    queue<State> q;
    q.push({InitialMoney, InitialInflation});
    
    set<State> visited;
    visited.insert({InitialMoney, InitialInflation});

    // Check strict history constraint
    // "Jika dua histori berbeda menghasilkan inflasi sama -> collapse"
    // This implies Inflation value MUST be unique for every visited node *in the path*?
    // Or globally?
    // If globally, it means we can never reach the same Inflation value twice via different paths.
    // This is equivalent to "visited check on Inflation".
    // If we reach an Inflation I that was already visited (with diff history/money), we collapse.
    // So `visited` set should key on `inflation` alone?
    // "Jika dua histori berbeda menghasilkan inflasi sama".
    // Yes, Inflation implies unique history. So we cannot enable two states with same inflation.
    // So visited set should store `inflation`. If seen, die.
    // UNLESS the money state is the same, in valid merge?
    // "Different history". Same path leading to same state is same history logic?
    // Usually in search, reaching same state via diff path is optimization.
    // But here "Inflation" captures history.
    // If I same, History same?
    // If I same but paths diff -> Collision -> Collapse.
    // So we can only visit each I once.
    
    set<long long> seen_inflation;
    seen_inflation.insert(InitialInflation);

    while (!q.empty()) {
        State curr = q.front();
        q.pop();

        if (curr.money >= TargetW) {
            cout << "Possible" << endl;
            return 0;
        }

        for (const auto& opt : options) {
            long long next_M = curr.money + opt.dM;
            long long next_I = curr.inflation + opt.dI; // Assume additive for hash-like behavior

            // Constraint: Inflation uniqueness
            if (seen_inflation.count(next_I)) {
                // Collision!
                continue; 
            }

            // Also check money bounds? usually non-negative?
            if (next_M < 0) continue; 

            seen_inflation.insert(next_I);
            q.push({next_M, next_I});
        }
    }

    cout << "Impossible" << endl;

    return 0;
}
