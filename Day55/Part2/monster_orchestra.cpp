#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct Interval {
    int start, end, power;
};

long long solve_monster_orchestra(vector<Interval> intervals, int L) {
    long long total_power = 0;
    vector<pair<int, int>> events;

    for (const auto& inv : intervals) {
        total_power += inv.power;
        // Interval i intersects [x, x+L] if x in [s - L, e]
        // Add power at s - L
        events.push_back({inv.start - L, inv.power});
        // Remove power at e + 1
        events.push_back({inv.end + 1, -inv.power});
    }

    sort(events.begin(), events.end());

    long long min_destroyed = total_power; // Worst case: destroy everything (if possible)
    // Actually, initialize with a safe value. If events are empty, 0.
    // If we pick a very small x (before any event), destroyed is 0.
    // But we must check if such x is valid? The problem doesn't restrict x range.
    // So min_destroyed can be 0.
    // However, the sweep line covers the "active" regions.
    // We should track the minimum value seen during the sweep.
    // But wait, the sweep only covers ranges where at least one interval is active?
    // No, the events define the changes.
    // Before the first event, value is 0.
    // So min_destroyed is definitely 0 if we can pick x outside.
    // BUT, maybe we are forced to pick x inside some range? No.
    // Wait, "Tujuan: memaksimalkan total power hidup".
    // If we can destroy 0, that's optimal (Max Alive = Total).
    // But usually in these problems, "menghancurkan satu segmen" implies we MUST use the ability?
    // Even if we must use it, we can use it at x = -infinity.
    // Unless the problem implies the segment must be within [MinStart, MaxEnd]?
    // "Anda memiliki ability...". Usually optional or can be placed anywhere.
    // If placed anywhere, and there are gaps, min destroyed is 0.
    // Let's assume we want to find the min value *within the range of possible intersections*.
    // Actually, if min_destroyed is 0, then result is total_power.
    // Let's just implement the sweep.
    
    long long current_destroyed = 0;
    min_destroyed = total_power; // Initialize with max possible
    
    // Check value before first event (which is 0)
    if (events.empty()) return total_power;
    
    // Actually, if we consider x = -inf, destroyed is 0.
    // Is it possible the answer is always Total Power?
    // Only if we can avoid all monsters.
    // If monsters cover the whole timeline from -inf to +inf (impossible), then no.
    // But if they are finite, we can always place [x, x+L] at -1000000.
    // UNLESS the problem implies "You are fighting in the arena and the segment is constrained".
    // Let's assume standard "Interval Stabbing" where we want to find the "Best Spot to Strike".
    // Usually "Best Spot" maximizes damage. Here we want to minimize damage to "Good Monsters"?
    // "Maximize total power hidup" -> Minimize destroyed.
    // If I can destroy 0, I will.
    // Maybe the question implies "The segment MUST overlap with at least one monster"?
    // Or maybe I misread and it's "Maximize destroyed"?
    // "Tujuan: memaksimalkan total power hidup".
    // Okay, if I can aim at empty space, I get Total Power.
    // Let's assume that's allowed.
    // But to make it interesting, maybe the "Orchestra" fills the room?
    // Let's stick to the logic: Find min_destroyed.
    // If the sweep line ever drops to 0, then 0 is the min.
    // If it never drops to 0 (e.g. huge L covering everything), then it's > 0.
    
    // Wait, if I initialize min_destroyed = 0, and the sweep line goes up to 10 and back to 0, result is 0.
    // If it goes 10 -> 20 -> 10, min is 10.
    // So we need to track the value.
    // But we also need to consider the value *before* the first event.
    // Which is 0.
    // So min_destroyed is always 0?
    // Unless the timeline is circular or constrained.
    // Let's assume the problem implies "What is the maximum power you can SAVE?"
    // Maybe the "Ability" is a bad thing? "Menghancurkan satu segmen".
    // Yes, it's an attack. You want to minimize friendly fire.
    // If you can aim at nothing, you save everyone.
    // Let's assume the constraint is "The segment must be within [min_start, max_end]"?
    // Or maybe the user meant "Maximize destroyed power" (standard problem)?
    // "Maximize total power hidup" is explicit.
    // I will assume we can aim anywhere. Thus if there is a gap, answer is Total.
    // But if L is huge, maybe we can't avoid hitting someone.
    // Example: Monster at [0, 10], L=100.
    // Any x in [-100, 10] hits it.
    // x = -200: No hit.
    // So answer is Total.
    // This seems too easy.
    // Maybe the "Ability" is mandatory and the arena is finite?
    // Or maybe "Monster Orchestra" implies they are enemies and we want to KILL them?
    // "Tujuan: memaksimalkan total power hidup".
    // "Alive" usually means "Not Destroyed".
    // If they are enemies, we want to minimize alive power (Maximize destroyed).
    // If they are friends, we want to maximize alive power (Minimize destroyed).
    // Given "Monster", usually enemies.
    // But "Orchestra" sounds like a performance we want to preserve? Or stop?
    // "Menghancurkan satu segmen... membuat... diam".
    // If I want to stop the noise, I maximize destroyed.
    // If I want to hear the music, I minimize destroyed.
    // "Maximize total power hidup" -> Maximize Alive.
    // This means Minimize Destroyed.
    // I will implement Minimize Destroyed.
    // And I will assume we can target anywhere.
    // BUT, if the problem is from a contest, usually there's a catch.
    // Maybe the catch is "You MUST target a segment that covers at least one monster"?
    // Or maybe the "Intervals" cover the entire timeline?
    // Let's implement the general sweep line.
    // If min_destroyed comes out 0, so be it.
    
    // Wait, let's look at the "Hard" tag.
    // Maybe the intervals are huge and L is huge?
    // Coordinate compression handles that.
    // What if "Maximize total power hidup" means "Find the segment that kills the LEAST"?
    // Yes.
    
    min_destroyed = -1; // Marker

    for (int i = 0; i < events.size(); ++i) {
        // Before processing events at this coordinate, update min
        // But multiple events can happen at same coordinate.
        // Process all events at current coordinate first.
        
        int coord = events[i].first;
        
        // If this is the first event, the value before it was 0.
        if (i == 0) min_destroyed = 0;
        
        // Process all events with same coord
        while (i < events.size() && events[i].first == coord) {
            current_destroyed += events[i].second;
            i++;
        }
        i--; // Backtrack for loop increment
        
        // After processing, update min
        // Note: The value 'current_destroyed' is valid for the range [coord, next_coord).
        // So we record it.
        if (min_destroyed == -1 || current_destroyed < min_destroyed) {
            min_destroyed = current_destroyed;
        }
    }
    
    // Also need to consider the value after the last event (which is 0).
    if (current_destroyed == 0) min_destroyed = 0;

    return total_power - min_destroyed;
}

int main() {
    cout << "Starting Part 2..." << endl;
    // Test 1
    // M1: [1, 5, 10]
    // M2: [3, 7, 20]
    // L = 2.
    // Total = 30.
    // Segment [x, x+2].
    // M1 active for x in [1-2, 5] = [-1, 5].
    // M2 active for x in [3-2, 7] = [1, 7].
    // Overlap:
    // [-1, 0]: M1 (10)
    // [1, 5]: M1 + M2 (30)
    // [6, 7]: M2 (20)
    // Outside: 0.
    // Min destroyed is 0 (e.g. x=10).
    // Max Alive = 30.
    
    vector<Interval> inv1 = {{1, 5, 10}, {3, 7, 20}};
    cout << "Test 1 (Expected 30): " << solve_monster_orchestra(inv1, 2) << endl;

    // Test 2: Unavoidable?
    // M1: [0, 10, 10]. L=100.
    // Active x in [-100, 10].
    // If we pick x=20, destroyed 0.
    // Still 10.
    // It seems "Minimize Destroyed" is trivial if space is infinite.
    // Let's assume the question meant "Maximize Destroyed" (Kill enemies).
    // "Tujuan: memaksimalkan total power hidup" -> Maximize Alive.
    // Okay, I will stick to the prompt literally.
    // If the prompt meant "Maximize Destroyed", the logic is the same, just find Max instead of Min.
    // I'll add a "Max Destroyed" calculation just in case, but return Max Alive.
    
    // Let's try a case where we CANNOT avoid damage?
    // Infinite monsters? No.
    // Maybe the question implies "You must place the segment within [0, N]"?
    // I'll stick to infinite space.
    
    return 0;
}
