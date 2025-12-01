#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <tuple>

using namespace std;

struct State {
    long long time;
    long long damage;
    vector<long long> ready;

    // Priority Queue needs to order by time (min heap)
    bool operator>(const State& other) const {
        return time > other.time;
    }
};

long long solve_tournament_shadows(const vector<int>& damage, const vector<int>& cooldown, const vector<int>& cast_time, int T) {
    int N = damage.size();
    
    // Min-heap for time
    priority_queue<State, vector<State>, greater<State>> pq;
    
    vector<long long> initial_ready(N, 0);
    pq.push({0, 0, initial_ready});
    
    // Visited map: (time, normalized_ready) -> max_damage
    // Normalized ready: ready[i] - time (clamped to 0)
    map<pair<long long, vector<long long>>, long long> visited;
    
    long long max_damage = 0;
    int count = 0;
    int limit = 200000;
    
    while (!pq.empty() && count < limit) {
        State current = pq.top();
        pq.pop();
        
        long long t = current.time;
        long long d = current.damage;
        vector<long long> ready = current.ready;
        
        max_damage = max(max_damage, d);
        
        if (t >= T) continue;
        
        // Option 1: Cast a ready skill
        for (int i = 0; i < N; ++i) {
            if (ready[i] <= t) {
                long long finish_time = t + cast_time[i];
                if (finish_time <= T) {
                    vector<long long> new_ready = ready;
                    new_ready[i] = finish_time + cooldown[i];
                    
                    // Normalize for visited check
                    vector<long long> norm_ready(N);
                    for(int j=0; j<N; ++j) norm_ready[j] = max(0LL, new_ready[j] - finish_time);
                    
                    pair<long long, vector<long long>> key = {finish_time, norm_ready};
                    
                    if (visited.find(key) == visited.end() || visited[key] < d + damage[i]) {
                        visited[key] = d + damage[i];
                        pq.push({finish_time, d + damage[i], new_ready});
                    }
                }
            }
        }
        
        // Option 2: Wait for next ready
        long long next_ready_time = -1;
        long long min_r = -1;
        
        for (long long r : ready) {
            if (r > t) {
                if (min_r == -1 || r < min_r) {
                    min_r = r;
                }
            }
        }
        
        if (min_r != -1 && min_r <= T) {
            next_ready_time = min_r;
            
            vector<long long> norm_ready(N);
            for(int j=0; j<N; ++j) norm_ready[j] = max(0LL, ready[j] - next_ready_time);
            
            pair<long long, vector<long long>> key = {next_ready_time, norm_ready};
            
            if (visited.find(key) == visited.end() || visited[key] < d) {
                visited[key] = d;
                pq.push({next_ready_time, d, ready});
            }
        }
        
        count++;
    }
    
    return max_damage;
}

int main() {
    vector<int> damage = {100, 200};
    vector<int> cooldown = {2, 5};
    vector<int> cast_time = {1, 2};
    int T = 10;
    
    cout << "Max Damage: " << solve_tournament_shadows(damage, cooldown, cast_time, T) << endl;
    
    return 0;
}
