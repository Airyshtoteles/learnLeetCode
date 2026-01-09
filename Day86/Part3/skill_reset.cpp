#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

// Problem: Skill Graph With Global Reset
// DAG. Taking a leaf resets graph. Skills taken are kept.
// Goal: Reach Target T.
// Strategy:
// We maintain a set of "Acquired Skills" (Inventory).
// Initially empty.
// In each "Run", we can traverse the graph starting from Roots (nodes with in-degree 0).
// We can also use any skill in Inventory as a starting point (or satisfy prereqs).
// Actually, if we have a skill in Inventory, we satisfy its dependency for children.
// So, effectively, nodes in Inventory act as "Roots" for the traversal.
// In a Run, we can acquire a set of new skills.
// BUT, to keep them, we must reach a Leaf.
// If we reach a Leaf, the run ends, and all skills visited in this run are added to Inventory.
// If we cannot reach a Leaf, we cannot complete the run?
// "Setiap kali kamu mengambil skill leaf, seluruh graph reset".
// This implies the reset is the mechanism to "save" and "restart".
// If we don't reset, we are stuck in a depleted graph.
// So, a skill S can be acquired if:
// 1. It is reachable from (Roots U Inventory) in the current graph.
// 2. From S, we can reach a Leaf (to trigger reset).
// If S == Target, we don't need to reach a leaf (we win immediately).
// Algorithm:
// Loop until no new skills added:
//   Compute Reachable from (Roots U Inventory).
//   Compute CanReachLeaf (Reverse reachability from Leaves).
//   NewSkills = (Reachable AND CanReachLeaf) - Inventory.
//   If T is Reachable, return Possible.
//   If NewSkills is empty, return Impossible.
//   Inventory += NewSkills.

int main() {
    int N, M;
    if (!(cin >> N >> M)) return 0;

    vector<vector<int>> adj(N + 1);
    vector<vector<int>> rev_adj(N + 1);
    vector<int> in_degree(N + 1, 0);
    vector<int> out_degree(N + 1, 0);

    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        rev_adj[v].push_back(u);
        out_degree[u]++;
        in_degree[v]++;
    }

    int Target;
    cin >> Target;

    set<int> inventory;
    vector<int> roots;
    vector<int> leaves;

    for (int i = 1; i <= N; ++i) {
        if (in_degree[i] == 0) roots.push_back(i);
        if (out_degree[i] == 0) leaves.push_back(i);
    }

    while (true) {
        // 1. BFS from Roots U Inventory to find Reachable
        vector<bool> reachable(N + 1, false);
        queue<int> q;
        
        for (int r : roots) {
            reachable[r] = true;
            q.push(r);
        }
        for (int i : inventory) {
            if (!reachable[i]) {
                reachable[i] = true;
                q.push(i);
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (!reachable[v]) {
                    reachable[v] = true;
                    q.push(v);
                }
            }
        }

        if (reachable[Target]) {
            cout << "Possible" << endl;
            return 0;
        }

        // 2. BFS from Leaves (Reverse) to find CanReachLeaf
        vector<bool> can_reach_leaf(N + 1, false);
        queue<int> rq;
        
        for (int l : leaves) {
            can_reach_leaf[l] = true;
            rq.push(l);
        }

        while (!rq.empty()) {
            int u = rq.front();
            rq.pop();
            for (int v : rev_adj[u]) {
                if (!can_reach_leaf[v]) {
                    can_reach_leaf[v] = true;
                    rq.push(v);
                }
            }
        }

        // 3. Identify new securable skills
        vector<int> new_skills;
        for (int i = 1; i <= N; ++i) {
            if (!inventory.count(i) && reachable[i] && can_reach_leaf[i]) {
                new_skills.push_back(i);
            }
        }

        if (new_skills.empty()) {
            cout << "Impossible" << endl;
            return 0;
        }

        for (int s : new_skills) {
            inventory.insert(s);
        }
    }

    return 0;
}
