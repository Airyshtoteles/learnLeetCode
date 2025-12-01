#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>

using namespace std;

struct Player {
    int id;
    double hp;
    double atk;
    double rng;
    double spd;
    double x, y;
    bool alive;
};

double dist(const Player& a, const Player& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int solve() {
    vector<Player> players = {
        {0, 50, 10, 2, 1, 0.0, 0.0, true},
        {1, 50, 10, 2, 1, 5.0, 0.0, true},
        {2, 60, 5, 5, 0, 2.5, 5.0, true}
    };
    
    vector<vector<int>> cycle = {
        {0, 1, 2},
        {2, 1, 0}
    };
    
    int turn = 0;
    int max_turns = 100;
    
    while(turn < max_turns) {
        int alive_count = 0;
        int survivor = -1;
        for(const auto& p : players) if(p.alive) { alive_count++; survivor = p.id; }
        
        if(alive_count <= 1) return survivor;
        
        // 1. Move
        vector<pair<double, double>> new_pos(players.size());
        for(int i=0; i<players.size(); ++i) {
            if(!players[i].alive) {
                new_pos[i] = {players[i].x, players[i].y};
                continue;
            }
            
            int nearest_idx = -1;
            double min_d = 1e9;
            
            for(int j=0; j<players.size(); ++j) {
                if(i != j && players[j].alive) {
                    double d = dist(players[i], players[j]);
                    if(d < min_d) {
                        min_d = d;
                        nearest_idx = j;
                    }
                }
            }
            
            if(nearest_idx != -1) {
                double dx = players[nearest_idx].x - players[i].x;
                double dy = players[nearest_idx].y - players[i].y;
                double len = sqrt(dx*dx + dy*dy);
                
                if(len > 0) {
                    double move = min(players[i].spd, len);
                    new_pos[i] = {players[i].x + (dx/len)*move, players[i].y + (dy/len)*move};
                } else {
                    new_pos[i] = {players[i].x, players[i].y};
                }
            } else {
                new_pos[i] = {players[i].x, players[i].y};
            }
        }
        
        for(int i=0; i<players.size(); ++i) {
            players[i].x = new_pos[i].first;
            players[i].y = new_pos[i].second;
        }
        
        // 2. Attack
        const vector<int>& perm = cycle[turn % cycle.size()];
        for(int pid : perm) {
            if(!players[pid].alive) continue;
            
            int target_idx = -1;
            double min_d = 1e9;
            
            for(int j=0; j<players.size(); ++j) {
                if(pid != j && players[j].alive) {
                    double d = dist(players[pid], players[j]);
                    if(d <= players[pid].rng) {
                        if(d < min_d) {
                            min_d = d;
                            target_idx = j;
                        }
                    }
                }
            }
            
            if(target_idx != -1) {
                players[target_idx].hp -= players[pid].atk;
                if(players[target_idx].hp <= 0) {
                    players[target_idx].alive = false;
                }
            }
        }
        
        turn++;
    }
    
    return -1;
}

int main() {
    cout << "Survivor ID: " << solve() << endl;
    return 0;
}
