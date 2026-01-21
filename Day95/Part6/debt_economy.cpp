#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// Problem 6: Economy With Debt Ceiling
// State: Current Money M.
// Constraints: M > -D.
// Dynamic: M_new = M_old + Interest? "Bunga hutang bertambah setiap langkah".
// If M < 0: M gets worse.
// Goal: Reach W.
// Strategy: Maximize M at every step.
// Transactions: Cost C, Gain G. Net = G - C.
// To maximize M, do we just pick max(G-C)?
// Or max(G) if C is large?
// Usually: If M >= C, we can execute. New M = M - C + G.
// So effectively M += (G-C).
// If G-C > 0, we want to do this ASAP.
// Priority:
// 1. Projects with G > C (Profitable).
//    - To maximize ability to execute, do lowest Cost first?
//    - Case: M=10. Deals (5, 10), (10, 20).
//      (5, 10): M -> 10-5+10 = 15. Then (10, 20): M -> 15-10+20 = 25.
//      (10, 20): M -> 10-10+20 = 20. Then (5, 10): M -> 20-5+10 = 25.
//      Both work.
//    - Case: M=10. Deals (10, 20), (15, 30).
//      (10, 20): M->20. Then (15, 30): M->35.
//      (15, 30): Impossible.
//    - So Cost Ascending is best for unlocking.
// 2. Projects with G <= C (Lossy).
//    - Avoid unless necessary? Usually avoided in pure "Reach W" unless W is low and we just burn money?
//    - Exception: If Lossy deal unlocks huge Profitable deal? No dependencies mentioned.
//    - So Ignore Lossy deals.
// 3. Interest?
//    - If M < 0, Interest hurts.
//    - Need to escape Debt ASAP.
//    - Profitable deals increase M.
//    - Does Order matter for interest?
//    - Step 1: M0. Deal 1. M1 = M0 + Net1. Interest(M1) -> M1'.
//    - Step 2: M1'. Deal 2. M2 = M1' + Net2. Interest(M2) -> M2'.
//    - Doing Deal 1 reduces debt (if Net > 0). Interest is applied on smaller debt.
//    - So we save money.
//    - Thus, do Highest Net first? Or Lowest Cost?
//    - Conflicts: Lowest Cost might have small Net. Highest Net might have High Cost.
//    - If M < 0 (Debt), we can take deals if M >= Cost - D? "Boleh berhutang hingga -D".
//    - Actually, feasibility condition: `Current M >= Cost - D`? No.
//    - Condition: `M - Cost >= -D`.
//    - So yes.
//    - If in debt, maximizing Net gain per step reduces interest penalty most.
//    - But we must satisfy `M - Cost >= -D`.
//    - So: Iterate through deals. Pick Best Net that is Affordable.
//    - Heuristic: Sort by Net Descending. Check affordability.
//    - Or Sort by Cost Ascending?
//    - Since usually Debt implies we are desperate, maybe Cost Ascending allows *more* deals?
//    - If Interest is huge, 1 big deal is better than 10 small ones.
//    - If Interest is small, quantity works.
//    - Common approach: Sort by Cost Ascending (to unlock chain).
//      Because if we can't afford High Net/High Cost, we do Low Cost/Med Net to reach it.
//      The gain from doing High Net *early* vs *late* (interest savings) is usually strictly less important than *feasibility*.
//      So unlocking is primary.
//      Sort Profitable Deals by Cost Ascending.
//      Simulate. Apply interest every step?
//      "Bunga hutang bertambah setiap langkah". (Interest adds every step).
//      Assume 1 step = 1 deal.
//      If M < 0, M += M * Rate (Rate is negative? Or M becomes more negative). Use `M *= (1+Rate)`.
//      Assume simple compounded debt.

struct Deal {
    double cost, gain;
};

int main() {
    double W_init, W_target, DebtLimit, Rate;
    int N;
    if (!(cin >> W_init >> W_target >> DebtLimit >> Rate >> N)) return 0;
    
    vector<Deal> profitable;
    for(int i=0; i<N; ++i){
        double c, g;
        cin >> c >> g;
        if (g > c) {
            profitable.push_back({c, g});
        }
    }
    
    // Sort by Cost Ascending
    sort(profitable.begin(), profitable.end(), [](const Deal& a, const Deal& b){
        return a.cost < b.cost;
    });
    
    double current_W = W_init;
    bool reached = (current_W >= W_target);
    
    // Apply Interest only if Debt?
    // "Bunga hutang". Only applies if W < 0.
    // Assuming Rate is given as positive decimal e.g. 0.05 for 5%.
    // M_new = M + M*Rate = M(1+Rate) is wrong for negative numbers if Rate > 0.
    // If M = -100, Rate = 0.1. M_new should be -110.
    // So M_new = M * (1 + Rate). Yes.
    
    for(const auto& deal : profitable) {
        if (reached) break;
        
        // Check affordability (Can dip to -D)
        // M - Cost >= -DebtLimit
        if (current_W - deal.cost >= -DebtLimit - 1e-9) {
            // Apply Deal
            current_W -= deal.cost;
            current_W += deal.gain;
            
            // Check Win
            if (current_W >= W_target) {
                reached = true;
                break;
            }
            
            // Apply Time/Interest
            // Assuming 1 deal = 1 step
            if (current_W < 0) {
                current_W *= (1.0 + Rate);
            }
            
            // Check Fail
            // If interest pushes us below limit
            if (current_W < -DebtLimit - 1e-9) {
                // Failed path?
                // But we sorted by cost. Maybe skipping this deal helps?
                // But this deal was profitable (Net > 0).
                // Doing it IMPROVED our position relative to not doing it (except for 1 step of time).
                // Usually Net Gain > Interest of 1 step unless Debt is huge.
                // If debt is huge, we die anyway.
                // Assuming Profitable deals help.
                break; 
            }
        }
    }
    
    if (reached || current_W >= W_target) cout << "YES" << endl;
    else cout << "NO" << endl;
    
    return 0;
}
