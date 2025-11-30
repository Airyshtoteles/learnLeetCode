#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct Room {
    int id;
    long long net_gain; // gain - cost
    int cooldown;
};

struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n + 1);
        iota(parent.begin(), parent.end(), 0);
    }
    
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            // Always point to larger index (next available)
            if (root_i < root_j) parent[root_i] = root_j;
            else parent[root_j] = root_i;
        }
    }
};

long long solve_dungeon_energy(int N, int T, vector<int>& gain, vector<int>& cost, vector<int>& cooldown) {
    vector<Room> rooms(N);
    for (int i = 0; i < N; ++i) {
        rooms[i] = {i, (long long)gain[i] - cost[i], cooldown[i]};
    }
    
    // Sort by net gain descending
    sort(rooms.begin(), rooms.end(), [](const Room& a, const Room& b) {
        return a.net_gain > b.net_gain;
    });
    
    // DSU for time slots 0 to T-1.
    // parent[i] points to next available slot >= i.
    // If parent[i] == T, no slot available.
    DSU dsu(T);
    
    long long total_energy = 0; // Assuming initial energy E is sufficient or we just maximize gain.
    // Problem says "Dapatkan energi maksimum". "Energi awal E".
    // "Return energi maksimum... atau -1 jika energimu mati".
    // Wait, "energimu mati".
    // If at any point energy < 0, we die.
    // But we can visit rooms in any order?
    // "Satu langkah = masuk ke satu ruangan".
    // We must pick a room at each step t=0..T-1.
    // The order is fixed by time.
    // But we choose WHICH room at time t.
    // If we use Greedy strategy, we determine the schedule.
    // Then we simulate to check if energy drops below 0?
    // But we want to MAXIMIZE final energy.
    // If we just pick max net gain, we maximize sum.
    // Does the order matter for survival?
    // Yes. If we pick a room with high cost early, we might die.
    // But we can't reorder time slots freely due to cooldowns.
    // However, the Greedy strategy fills slots.
    // Does it fill them in chronological order?
    // No, it fills based on room priority.
    // So we get a schedule.
    // Then we must simulate the schedule to check survival.
    // If we die, is there a better schedule?
    // Maybe. But "Heavy DP" hint suggests maybe survival is key?
    // But "Greedy" hint suggests maximizing sum.
    // Given N=2000, T=1e6, DP is hard.
    // I will assume E is large enough or we just maximize sum.
    // If survival is strict, this is much harder (Knapsack-like).
    // But usually "Energy Balancer" with "Maximize Energy" implies maximizing sum.
    // The "die" condition might be a check.
    // I'll implement Greedy + Simulation check.
    
    vector<int> schedule(T, -1); // Store room index
    
    for (const auto& room : rooms) {
        if (room.net_gain <= 0) continue; // Don't pick bad rooms unless forced?
        // If all rooms are bad, we must pick least bad?
        // "Wajib pilih satu per langkah".
        // So we MUST fill all T slots.
        // If we have positive rooms, we fill them.
        // If we have gaps, we fill with least negative?
        // Yes.
    }
    
    // Refined Greedy:
    // 1. Fill with positive rooms using DSU.
    // 2. If slots remain, fill with least negative rooms (sorted by net_gain descending, i.e., -1 > -10).
    // Actually, just sort ALL rooms descending.
    // Fill slots.
    // Since we MUST fill T slots, we just keep going until T slots are full.
    
    int slots_filled = 0;
    for (const auto& room : rooms) {
        if (slots_filled == T) break;
        
        int t = 0;
        while (t < T) {
            int available_t = dsu.find(t);
            if (available_t >= T) break;
            
            // Use slot available_t
            schedule[available_t] = room.id;
            total_energy += room.net_gain; // Just sum for now
            slots_filled++;
            
            // Mark used
            dsu.unite(available_t, available_t + 1);
            
            // Next attempt
            t = available_t + room.cooldown + 1;
        }
    }
    
    if (slots_filled < T) {
        // Should not happen if we have enough rooms and cooldowns allow.
        // But if N is small and cooldowns large, we might not be able to fill T steps?
        // "Wajib pilih satu per langkah".
        // If we can't fill, then it's impossible?
        // Or maybe we can pick the same room multiple times ignoring cooldown? No.
        // If we can't fill, return -1.
        return -1;
    }
    
    // Check survival?
    // Problem: "Return energi maksimum... atau -1 jika energimu mati".
    // We need initial E.
    // Function signature doesn't have E.
    // I'll add E to signature.
    // Wait, prompt says "Kamu masuk dungeon dengan energi awal E".
    // I'll assume E is given.
    
    return total_energy;
}

long long solve_with_survival(int N, int T, int E, vector<int>& gain, vector<int>& cost, vector<int>& cooldown) {
    // Re-run logic with E check
    vector<Room> rooms(N);
    for (int i = 0; i < N; ++i) {
        rooms[i] = {i, (long long)gain[i] - cost[i], cooldown[i]};
    }
    
    sort(rooms.begin(), rooms.end(), [](const Room& a, const Room& b) {
        return a.net_gain > b.net_gain;
    });
    
    DSU dsu(T);
    vector<int> schedule(T, -1);
    int slots_filled = 0;
    
    for (const auto& room : rooms) {
        if (slots_filled == T) break;
        int t = 0;
        while (t < T) {
            int available_t = dsu.find(t);
            if (available_t >= T) break;
            schedule[available_t] = room.id;
            slots_filled++;
            dsu.unite(available_t, available_t + 1);
            t = available_t + room.cooldown + 1;
        }
    }
    
    if (slots_filled < T) return -1;
    
    long long current_E = E;
    // We need to map ID back to cost/gain
    // Or just store in schedule?
    // schedule stores ID.
    // We need original arrays.
    
    for (int t = 0; t < T; ++t) {
        int id = schedule[t];
        current_E -= cost[id];
        if (current_E <= 0) return -1; // Die if E <= 0? "Mati sebelum mencapai langkah T".
        current_E += gain[id];
    }
    
    return current_E;
}

int main() {
    // Example 1
    // Room 0: Gain 10, Cost 5 (Net 5), CD 1.
    // Room 1: Gain 20, Cost 10 (Net 10), CD 2.
    // T = 5. E = 100.
    // Sort: Room 1 (10), Room 0 (5).
    // Fill Room 1:
    // t=0: Use Room 1. Next t = 0+2+1 = 3.
    // t=3: Use Room 1. Next t = 3+2+1 = 6 (Out).
    // Schedule: [1, _, _, 1, _]
    // Fill Room 0:
    // t=0: Occupied. Find(0) -> 1.
    // t=1: Use Room 0. Next t = 1+1+1 = 3.
    // t=3: Occupied. Find(3) -> 4.
    // t=4: Use Room 0. Next t = 4+1+1 = 6.
    // Schedule: [1, 0, _, 1, 0]
    // Gap at 2.
    // Fill Room 0 again?
    // Wait, we iterate rooms ONCE.
    // But we can use a room multiple times.
    // The loop `while (t < T)` does that.
    // Ah, Room 0 logic:
    // t=0 (occupied) -> 1. Use at 1.
    // Next valid for Room 0 is 1 + 1 + 1 = 3.
    // At 3 (occupied) -> 4. Use at 4.
    // Next valid 4 + 1 + 1 = 6.
    // So Room 0 used at 1, 4.
    // Slot 2 is empty.
    // If we have no more rooms, return -1.
    // Let's add Room 2: Net 1, CD 0.
    // Fill Room 2:
    // t=0..1 occupied. t=2 empty. Use at 2.
    // Schedule: [1, 0, 2, 1, 0].
    // Total Net: 10 + 5 + 1 + 10 + 5 = 31.
    // Final E = 100 + 31 = 131.
    
    vector<int> gain = {10, 20, 5};
    vector<int> cost = {5, 10, 4};
    vector<int> cd = {1, 2, 0};
    
    cout << "Test 1: " << solve_with_survival(3, 5, 100, gain, cost, cd) << endl;
    
    return 0;
}
