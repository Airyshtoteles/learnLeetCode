#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <map>

using namespace std;

// Problem: Economy With Conservation Violation
// State: (a, b) wealth.
// Error accumulates.
// Max Error E_limit.
// Goal: Reach (a, b) such that a >= W or b >= W? Or a+b >= W?
// Usually "Reach wealth W" implies total wealth or one component?
// "Target wealth W". I'll assume Total Wealth a+b >= W, or specifically A >= W.
// Usually simplest is "Total Wealth >= W".
// Transactions: rules.
// Logic: BFS to find min error to reach state (a, b).
// Since E_limit can be large? No, error accumulates.
// If (a,b) state space is large, BFS might be slow.
// But Day 87... usually conceptual.
// BFS State: (a,b). Value: min_error.
// Priority Queue (Dijkstra) if different error costs.
// If error can be float, we definitely need Dijkstra.
// "Floating error" -> yes.

struct State {
    int a, b;
    bool operator<(const State& other) const {
        return tie(a, b) < tie(other.a, other.b);
    }
};

struct Transition {
    int da, db;
    double err;
};

int main() {
    int A, B, W;
    double E_limit;
    if (!(cin >> A >> B >> W >> E_limit)) return 0;

    int M;
    cin >> M;
    vector<Transition> trans(M);
    for (int i = 0; i < M; ++i) {
        cin >> trans[i].da >> trans[i].db >> trans[i].err;
    }

    priority_queue<pair<double, State>, vector<pair<double, State>>, greater<pair<double, State>>> pq;
    map<State, double> min_error;

    // Use pair<double, State> for PQ. C++ pair comparison compares first, then second.
    // We want min error.
    // Wait, greater behavior on pair works? Yes.

    // BUT `greater` needs `operator>`? Or `operator<` reversed?
    // Standard `greater` uses `>`. So we need to put `(error, state)` in PQ.

    // How to handle State in PQ?
    // We need to define `operator>` for pair?
    // Actually, `greater<pair<double, State>>` just needs `operator>` for types.
    // `pair` has lexicographical compare.
    // Just ensure State has compare.

    // Wait, map lookup is O(log N).
    
    pq.push({0.0, {A, B}});
    min_error[{A, B}] = 0.0;

    while (!pq.empty()) {
        double cur_err = pq.top().first;
        State s = pq.top().second;
        pq.pop();

        if (cur_err > min_error[s]) continue;
        if (s.a + s.b >= W) { // Assumption: Total wealth >= W
            cout << "Possible" << endl;
            return 0;
        }

        for (const auto& t : trans) {
            State next = {s.a + t.da, s.b + t.db};
            double n_err = cur_err + t.err;

            if (n_err <= E_limit) {
                if (min_error.find(next) == min_error.end() || n_err < min_error[next]) {
                    min_error[next] = n_err;
                    pq.push({n_err, next});
                }
            }
        }
    }

    cout << "Impossible" << endl;

    return 0;
}
