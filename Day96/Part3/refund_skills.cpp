#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>

using namespace std;

// Problem 3: Skill DAG With Partial Refund
// Logic:
// We need to check if there is a valid topological/execution order to process
// the necessary skills to unlock Target T starting with Initial Energy.
// Structure: Parent implies Dependency. "Take child of i".
// Actually, "Total Refund" happens after ALL children.
// This implies Parent wraps Children.
// Tree Structure is best fit.
// Let's implement the Tree Heuristic for Skill Tree.
//
// Function solve(u):
//   Returns {PeakRequirement, NetCost}.
//   Logic:
//     Base Req = Cost[u].
//     Effect = -Cost[u].
//     If leaf: Peak = Cost[u], Net = -Cost[u] + Refund[u].
//     If children:
//       Values = [solve(v) for v in children].
//       Sort Values:
//         Positives first (Net >= 0): Sort by Peak Ascending.
//         Negatives last (Net < 0): Sort by (Peak + Net) Descending (Recovery logic).
//       
//       Simulate u:
//         CurrentReq = Cost[u] (Paid).
//         Peak = CurrentReq.
//         CurrentBal = -Cost[u].
//         For each child (req, net):
//           Peak = max(Peak, CurrentBal + req?? No. Need relative).
//           We track "Minimum Energy Needed Before Starting u".
//           Let E be starting.
//           E >= C[u]. E -> E - C[u].
//           For child: E - C[u] >= Req_child.
//           So E >= C[u] + Req_child.
//           E -> E - C[u] + Net_child.
//           
//         Finally: E + Refund[u].
//         Net = Final - Initial.
//         Peak = Min Initial needed.
//
// If DAG, we convert to Tree by replicating or ignoring?
// Given "DAG" + "Cooldown" problem earlier, maybe this is strict tree?
// Or maybe finding T forces a specific subgraph?
// I will implement the Tree Logic on the subgraph leading to T?
// Wait, "Take children of i" implies i is parent. T is Target.
// If T is a leaf, we just take T?
// If T is root, we take T and children?
// "Target skill T". "Mengambil skill i".
// Likely we just need to take T.
// If T has no parents, cost is C[T].
// If T has children (prereqs?), we must take them.
// "Mengambil (Take/Acquire) skill i cost C. After taking ALL child, refund."
// This implies to finish "Taking i", we must take children.
// So yes, processing T means processing the subtree rooted at T.
// So we apply logic to T.

struct Result {
    long long peak;
    long long net;
};

int N;
vector<long long> Cost, Refund;
vector<vector<int>> adj;
vector<bool> visiting;

Result dfs(int u) {
    long long myPeak = Cost[u];
    long long myNet = -Cost[u];
    
    // Collect children results
    vector<Result> children_res;
    for(int v : adj[u]) {
        children_res.push_back(dfs(v));
    }
    
    // Sort
    vector<Result> pos, neg;
    for(auto r : children_res) {
        if (r.net >= 0) pos.push_back(r);
        else neg.push_back(r);
    }
    
    sort(pos.begin(), pos.end(), [](const Result& a, const Result& b){
        return a.peak < b.peak;
    });
    
    sort(neg.begin(), neg.end(), [](const Result& a, const Result& b){
        return (a.peak + a.net) > (b.peak + b.net); // Maximize recovery? Standard scheduling trick.
        // Actually: For negatives, we want biggest "return" (least drop) last?
        // Logic: if we have (Req 10, Net -5) and (Req 10, Net -2).
        // A: 10, -5. B: 10, -2.
        // Doing A then B: Need 10. End -5. Need (10 - (-5))? No.
        // Abs state: Start E.
        // A: Need E >= 10. E -> E-5.
        // B: Need E-5 >= 10 -> E >= 15.
        // Start E:
        // B: Need E >= 10. E -> E-2.
        // A: Need E-2 >= 10 -> E >= 12.
        // So B then A is better (12 < 15).
        // B has larger (Peak - |Net|) or something?
        // Wait, standard job sequencing says sort by `Peak + Net` descending?
        // Let's check:
        // A: Peak 10, Net -5. P+N = 5.
        // B: Peak 10, Net -2. P+N = 8.
        // Sorted Desc: 8 (B), 5 (A). B then A. Correct.
    });
    
    // Simulation relative to AFTER paying C[u]
    long long current_drop = 0; // Relative to (Start - C[u])
    long long max_drop_needed = 0;
    
    // Process Pos
    for(auto r : pos) {
        // Need: current_drop + r.peak <= Available?
        // Available (relative) starts at 0 (meaning we have exactly C[u] left?) No.
        // We track "Max Added Need".
        // To do child, we need `CurrentBal >= Peak`.
        // `StartRelative - Drop >= Peak`.
        // `StartRelative >= Drop + Peak`.
        max_drop_needed = max(max_drop_needed, current_drop + r.peak);
        current_drop -= r.net; // Net implies gain. r.net >= 0. So drop decreases.
        // Actually current_drop represents "Spent".
        // Net is "Change".
        // If Net is +5, we spent X, gained 5. Spent becomes X-5.
        // Wait, `net` is signed. `peak` is unsigned size.
        // `current_spent`:
        // Need `peak`. `MaxSpent` tracks max deviation.
        // After op pairwise: `current_spent -= net`.
    }
    
    // Process Neg
    for(auto r : neg) {
        max_drop_needed = max(max_drop_needed, current_drop + r.peak);
        current_drop -= r.net; // net is negative, so drop increases.
    }
    
    // Now convert to Node u context
    // We paid C[u]. So we are at state -C[u].
    // Children logic required `max_drop_needed` ABOVE the base state.
    // So Total Peak = C[u] + max_drop_needed.
    
    // Net
    myNet += (0 - current_drop); // The children net sum is sum(net). -current_drop = sum(net).
    myNet += Refund[u];
    
    return {myPeak, myNet};
}

int main() {
    long long InitialE;
    int TargetT;
    if (!(cin >> N >> InitialE >> TargetT)) return 0;
    
    Cost.resize(N);
    Refund.resize(N);
    adj.resize(N);
    
    for(int i=0; i<N; ++i) cin >> Cost[i];
    for(int i=0; i<N; ++i) cin >> Refund[i];
    
    int edges; cin >> edges;
    for(int i=0; i<edges; ++i){
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
    }
    
    // Assuming TargetT is the root of the task we want to perform.
    Result res = dfs(TargetT);
    
    if (InitialE >= res.peak) cout << "YES" << endl;
    else cout << "NO" << endl;
    
    return 0;
}
