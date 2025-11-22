#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
};

struct Enemy {
    int path_idx;
    int hp;
    int speed;
};

double dist(Point p1, Point p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

bool check(const vector<Point>& towers, const vector<vector<Point>>& paths, const vector<Enemy>& enemies, int radius, int damage, int interval) {
    for(const auto& e : enemies) {
        const auto& path = paths[e.path_idx];
        int hp = e.hp;
        int speed = e.speed;
        
        int max_time = path.size() / speed; // Approx
        
        for(int t=0; t < max_time; t += interval) {
            int idx = t * speed;
            if(idx >= path.size()) break;
            
            Point pos = path[idx];
            int dmg_taken = 0;
            
            for(const auto& tower : towers) {
                if(dist(pos, tower) <= radius) {
                    dmg_taken += damage;
                }
            }
            
            hp -= dmg_taken;
            if(hp <= 0) break;
        }
        
        if(hp > 0) return false;
    }
    return true;
}

// Helper to generate combinations
void combinations(int n, int k, int offset, vector<int>& current, vector<vector<int>>& result) {
    if (k == 0) {
        result.push_back(current);
        return;
    }
    for (int i = offset; i <= n - k; ++i) {
        current.push_back(i);
        combinations(n, k, i + 1, current, result);
        current.pop_back();
    }
}

int solve() {
    // Hardcoded setup matching Python
    vector<vector<Point>> paths;
    vector<Point> p1, p2;
    for(int i=0; i<=10; ++i) p1.push_back({0, i});
    for(int i=0; i<=10; ++i) p2.push_back({5, i});
    paths.push_back(p1);
    paths.push_back(p2);
    
    vector<Enemy> enemies = {
        {0, 20, 1},
        {1, 20, 1}
    };
    
    vector<Point> candidates = {
        {2, 5}, {0, 5}, {5, 5}
    };
    
    int radius = 3;
    int damage = 5;
    int interval = 2;
    
    int n = candidates.size();
    
    for(int k=1; k<=3; ++k) {
        vector<vector<int>> combos;
        vector<int> current;
        combinations(n, k, 0, current, combos);
        
        for(const auto& indices : combos) {
            vector<Point> selected_towers;
            for(int idx : indices) selected_towers.push_back(candidates[idx]);
            
            if(check(selected_towers, paths, enemies, radius, damage, interval)) {
                return k;
            }
        }
    }
    
    return -1;
}

int main() {
    cout << "Minimum towers needed: " << solve() << endl;
    return 0;
}
