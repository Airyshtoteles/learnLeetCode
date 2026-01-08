#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Problem: Economy With State Oblivion
// Description:
// You have prices for N days.
// You can make infinite transactions (Buy then Sell).
// BUT, after Selling, you must wait K days (Oblivion/Cooldown) before Buying again.
// Find Max Profit.
// Constraints: N <= 10^5, K <= N.
// DP Approach:
// dp_sold[i] = max profit on day i where we hold NO stock (just sold or did nothing).
// dp_held[i] = max profit on day i where we HOLD stock (just bought or kept holding).
// Transitions:
// dp_held[i] = max(dp_held[i-1], dp_sold[i-1] - prices[i] ? NO).
//              If we buy on day i, we must have sold at least K+1 days ago?
//              No, if we sold on day j, we enter cooldown for days j+1...j+K.
//              We can buy on day j+K+1.
//              So if we buy on day i, the previous state must be "No Stock" from day i-1.
//              AND the last sell must be <= i-1-K? No.
//              Let's rephrase:
//              If we buy on day i, we transition from a state where we were allowed to buy.
//              We are allowed to buy if we are not in cooldown.
//              The "Solves" state is usually:
//              S0: Rest/Ready (Can Buy)
//              S1: Held (Can Sell)
//              S2: Cooldown (Can Rest)
//
//              Refined State:
//              buy[i]: Max profit ending day i with stock held.
//              sell[i]: Max profit ending day i having JUST sold.
//              rest[i]: Max profit ending day i empty handed (cooldown or resting).
// 
//              buy[i] = max(buy[i-1], rest[i-1] - prices[i])
//              sell[i] = buy[i-1] + prices[i]
//              rest[i] = max(rest[i-1], sell[i-1]?? NO).
//              If we sell at i-1, i is Cooldown.
//              So rest has TWO sources: 
//                  1. rest[i-1] (continued resting)
//                  2. sell[i-K-1]? NO.
//              Let's handle K directly.
//              If we sell at i, we can't buy until i+K+1.
//              So buy[i] can come from:
//                  1. buy[i-1] (holding)
//                  2. (Max profit having sold <= day i-1 AND cooldown finished) - prices[i].
//                     This means we need max(sell[0...i-K-1], rest[0...i-K-1]).
//              Let `clean[i]` be max profit on day i where we have NO stock and NO cooldown (Ready to buy).
//              clean[i] = max(clean[i-1], sell[i-K-1] if i-K-1 >= 0 else 0) ??
//              Let's use just 2 arrays:
//              held[i]: Max profit at end of i, holding stock.
//              sold[i]: Max profit at end of i, not holding (sold or resting).
//              
//              held[i] = max(held[i-1], sold[i-1]? No, sold implies we might have cooldown restriction.
//              Let's go back to: We can BUY on day i if we didn't sell in [i-K, i-1].
//              So to compute held[i] (buying action part): 
//                 Profit = sold[i-1] - P[i] is VALID only if last sell was long ago?
//                 Actually, easier:
//                 held[i] = max(held[i-1],  (i-K-1 >= 0 ? sold[i-K-1] : 0) - prices[i]).
//                 Here `sold[x]` means "Max profit at end of day x with 0 stock".
//                 Wait, if sold[x] accounts for selling AT x.
//                 Let's redefine `sold[i]` = Max profit up to day i with 0 stock.
//                 Then sold[i] = max(sold[i-1], held[i-1] + prices[i]).
//                 And held[i] = max(held[i-1], sold[i-K-1] - prices[i]).
//                 (If K=1, needs sell at i-2. Indices work out).
//                 Base case: sold[-1] = 0.
//                 held[-1] = -inf. 
//                 But wait, can we buy at day 0? Yes. `sold[-K-1]` is 0.
//                 So `held[0] = -prices[0]`.
//                 What if K=0? Cooldown 0. `held[i] = max(h, sold[i-1] - p)`. Correct.
//
// Implementation:
// Use long long for profit.
// Initialize held = -1e18 (impossible).
// sold array size N.

int main() {
    int N, K;
    if (!(cin >> N >> K)) return 0;
    
    vector<long long> P(N);
    for(int i=0; i<N; ++i) cin >> P[i];

    vector<long long> sold(N, 0);
    vector<long long> held(N, -2e18); // Large negative

    for (int i = 0; i < N; ++i) {
        // Update held[i]
        long long prev_held = (i > 0) ? held[i-1] : -2e18;
        
        // Buy option: Need state from i-K-1
        long long prev_sold_valid = 0;
        int lookback = i - K - 1;
        if (lookback >= 0) prev_sold_valid = sold[lookback];
        else if (lookback < -1) {
            // Cannot buy if lookback implies before start?
            // Actually, if i=0, lookback = -K-1.
            // If K=1, i=0 => -2. i=1 => -1.
            // We can always buy at start.
            // If i < K+1, we can buy effectively using 0 base.
            // No, the restriction is "After selling". If we haven't sold, we can buy.
            prev_sold_valid = 0; 
        } else {
             // lookback == -1 case (e.g. i=K)
             prev_sold_valid = 0;
        }

        // Wait, if i < K, can we buy? Yes. Because we haven't sold.
        // The only restriction is IF we sold at t, we can't buy in [t+1, t+K].
        // If we buy at i, we assume we didn't sell in [i-K, i-1].
        // So we take max profit from i-K-1.
        // If i-K-1 < 0, it means we didn't sell before. Base profit 0.
        // So yes, `prev_sold_valid` is effectively `(lookback >= 0 ? sold[lookback] : 0)`.
        
        held[i] = max(prev_held, prev_sold_valid - P[i]);

        // Update sold[i]
        long long prev_sold = (i > 0) ? sold[i-1] : 0;
        sold[i] = max(prev_sold, held[i] + P[i]); 
        // Note: We use held[i] here? That allows Buy then Sell same day.
        // Usually allowed (profit 0). Or we can use held[i-1].
        // "Transaction" usually different times?
        // If same day buy/sell allowed, doesn't hurt (profit 0).
        // If strictly day passes, use held[i-1].
        // Standard problem "infinite transactions" allows same day usually (net 0).
        // Let's stick to using held[i] (which includes held[i-1]).
    }

    cout << sold[N-1] << endl;

    return 0;
}
