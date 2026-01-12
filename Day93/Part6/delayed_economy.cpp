#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Problem 6: Economy With Delayed Transactions
// State: Current Money W.
// Pending Transactions: Queue of (Time, Amount).
// Rule: Money < 0 is Loss.
// Goal: Reach Target W_target.
// Input: W_init, W_target, T_delay (Global Delay T?).
// "Each transaction effects after T steps".
// Available choices: List of Deals (CostNow, GainLater).
// Usually Cost is immediate, Gain is delayed.
// Or Cost is delayed too? "Transaction takes effect after T steps".
// If Cost is delayed, checking Money < 0 is tricky.
// Usually "Buy now, pay now, receive later".
// So Money -= Cost immediately. Money += Gain at t+T.
// If so, state is (Money, Pending_Gains_At_Times).
// If T is constant, we can track Pending Gains as a simple sum or queue?
// Actually if delay is fixed T.
// We make decisions at t=0, 1, 2...
// At step k, we receive gains from step k-T.
// We choose deal d: Money -= Cost[d]. Queue Gain[d] for k+T.
// Since T is delay, we only really care about Money flow.
// If we can mix deals, this is unbounded knapsack over time?
// Simplification: "Can target be reached?"
// BFS State: (Current Money). But future matters.
// "Inti: event simulation + priority queue".
// Maybe we assume we just do one big set of transactions?
// Or we greedily pick the best ROI?
// If we have infinite time, we can just farm the best positive net deal.
// Net = Gain - Cost. If Net > 0, we can pump money to infinity.
// Constraint is not going below 0 in the dip.
// So we need `CurrentMoney >= Cost`.
// If we have a deal with Gain > Cost.
// And we can afford it. We take it.
// Then wait T steps. Receive Gain. Repeat.
// So: Check if there is ANY deal with gain > cost that we can afford (Cost <= W_init).
// If YES, we can reach infinity -> YES.
// If NO (all affordable deals have Net <= 0), we can't grow.
// Then we check if we can reach W_target with current money or with one-off limited chains?
// Usually "Economy" implies growth.
// Algorithm:
// 1. Filter deals with Gain > Cost.
// 2. Find min Cost among them (MinEntryPrice).
// 3. If Init_W >= MinEntryPrice, we can profit infinitely. YES.
// 4. If not, and Init_W >= Target, YES.
// 5. If Init_W < Target and no profitable deal affordable, NO.
// Wait, what if we can afford a bad deal that unlocks a good deal?
// E.g. Deal A: Cost 10, Gain 5. (Net -5). W=10.
// But we need W=20? No.
// Usually we want positive cycles.
// Is it possible to chain? Cost 10, Gain 20. But W=5? No.
// So simple check: Can we enter a positive cycle?
// Or can we reach Target directly?
// Also check "Overlap".
// "Some transactions can overlap".
// This implies parallel execution.
// If we have access to a profitable deal `(c, g)` with `g > c`.
// And `W >= c`.
// We do it. `W -> W - c`. Wait T. `W -> W - c + g`.
// Since `g > c`, `W_new > W_old`. We grow.
// Eventually reach Target.
// So simply check if reachable OR growable.

struct Deal {
    long long cost;
    long long gain;
};

int main() {
    long long W_init, W_target, T_delay;
    int N;
    if (!(cin >> W_init >> W_target >> T_delay >> N)) return 0;
    
    vector<Deal> deals(N);
    bool can_grow = false;
    
    for (int i = 0; i < N; ++i) {
        cin >> deals[i].cost >> deals[i].gain;
        if (deals[i].gain > deals[i].cost) {
            // High yield deal
            if (W_init >= deals[i].cost) {
                can_grow = true;
            }
        }
    }
    
    if (W_init >= W_target) {
        cout << "YES" << endl;
    } else if (can_grow) {
        cout << "YES" << endl;
    } else {
        // Can we reach target with one shot negative deals? Unlikely.
        // Or maybe combination?
        // If we only have losing deals, we consume money. W decreases.
        // We can never reach W_target > W_init.
        // Exception: A deal gives huge Gain but Gain < Cost? No.
        // The only way to go UP is Gain > Cost?
        // Wait. If Gain > Cost, W increases.
        // If Gain < Cost, W decreases (eventually).
        // Can W temporarily spike?
        // W_now = W - Cost. W_future = W - Cost + Gain.
        // If Gain < Cost, W_future < W.
        // So we can't reach higher W_target using losing deals.
        // So simple check covers it.
        cout << "NO" << endl;
    }
    
    return 0;
}
