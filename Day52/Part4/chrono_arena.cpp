#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

struct Skill {
    string name;
    int damage;
    double cast_time;
    double cooldown;
    int cp_change;
};

struct State {
    double time;
    int damage;
    int cp;
    vector<double> cooldowns;
    
    bool operator>(const State& other) const {
        return time > other.time; // Min-heap by time
    }
};

int solve_chrono_arena(double speed, double t_limit, vector<Skill>& skills) {
    int N = skills.size();
    double fill_time = 100.0 / speed;
    
    priority_queue<State, vector<State>, greater<State>> pq;
    
    vector<double> initial_cds(N, 0.0);
    pq.push({fill_time, 0, 0, initial_cds});
    
    int max_damage = 0;
    int count = 0;
    int LIMIT = 100000;
    
    while (!pq.empty() && count < LIMIT) {
        State current = pq.top();
        pq.pop();
        
        if (current.damage > max_damage) {
            max_damage = current.damage;
        }
        
        if (current.time > t_limit) continue;
        
        bool can_act = false;
        for (int i = 0; i < N; ++i) {
            if (current.cooldowns[i] <= current.time) {
                if (skills[i].cp_change < 0 && current.cp < -skills[i].cp_change) {
                    continue;
                }
                
                can_act = true;
                
                int new_cp = current.cp + skills[i].cp_change;
                if (new_cp > 5) new_cp = 5;
                if (new_cp < 0) new_cp = 0;
                
                double finish_time = current.time + skills[i].cast_time;
                
                if (finish_time <= t_limit) {
                    double next_ready = finish_time + fill_time;
                    
                    vector<double> new_cds = current.cooldowns;
                    new_cds[i] = finish_time + skills[i].cooldown;
                    
                    pq.push({next_ready, current.damage + skills[i].damage, new_cp, new_cds});
                }
            }
        }
        
        count++;
    }
    
    return max_damage;
}

int main() {
    // Example 1
    double speed = 50;
    double t_limit = 10.0;
    vector<Skill> skills = {
        {"Slash", 100, 1.0, 0.0, 1},
        {"Finisher", 300, 2.0, 5.0, -2}
    };
    
    cout << "Max Damage (Ex 1): " << solve_chrono_arena(speed, t_limit, skills) << endl;
    
    // Example 2
    double speed2 = 100;
    double t_limit2 = 5.0;
    vector<Skill> skills2 = {
        {"Basic", 10, 0.5, 0.0, 0}
    };
    
    cout << "Max Damage (Ex 2): " << solve_chrono_arena(speed2, t_limit2, skills2) << endl;
    
    return 0;
}
