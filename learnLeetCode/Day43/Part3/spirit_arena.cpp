#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

class SpiritArena {
    int n;
    vector<int> parent;
    vector<long long> power;
    vector<int> jump; // Points to the next index
    int num_clans;

public:
    SpiritArena(int n, const vector<int>& powers) : n(n), num_clans(n) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
        
        power.resize(n);
        for(int i=0; i<n; ++i) power[i] = powers[i];
        
        jump.resize(n);
        for(int i=0; i<n; ++i) jump[i] = (i + 1) % n;
    }

    int find_clan(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find_clan(parent[i]);
    }

    void union_clans(int i, int j) {
        int root_i = find_clan(i);
        int root_j = find_clan(j);
        if (root_i != root_j) {
            parent[root_j] = root_i;
            power[root_i] += power[root_j];
            num_clans--;
        }
    }

    int get_next_different_clan_spirit(int start_node) {
        int root_start = find_clan(start_node);
        int curr = jump[start_node];
        
        vector<int> path;
        int target = -1;

        while (true) {
            int root_curr = find_clan(curr);
            if (root_curr != root_start) {
                target = curr;
                break;
            }
            
            path.push_back(curr);
            curr = jump[curr];

            // If we circled back to start, only 1 clan remains
            if (curr == start_node) {
                return -1;
            }
        }

        // Path compression for jump pointers
        jump[start_node] = target;
        for (int p : path) {
            jump[p] = target;
        }

        return target;
    }

    void process_link(int u, int v) {
        union_clans(u, v);
    }

    void process_battle(int u) {
        int root_u = find_clan(u);
        int target = get_next_different_clan_spirit(u);

        if (target == -1) return; // Only 1 clan left

        int root_target = find_clan(target);
        
        if (power[root_u] > power[root_target]) {
            union_clans(u, target);
        } else {
            union_clans(target, u);
        }
    }

    int get_num_clans() {
        return num_clans;
    }
};

int main() {
    // Simple test case
    int n = 5;
    vector<int> powers = {10, 20, 30, 40, 50};
    SpiritArena arena(n, powers);

    // Link 0 and 2
    arena.process_link(0, 2);
    
    // Battle 0
    arena.process_battle(0);
    
    // Battle 2
    arena.process_battle(2);

    cout << "Remaining clans: " << arena.get_num_clans() << endl;

    return 0;
}
