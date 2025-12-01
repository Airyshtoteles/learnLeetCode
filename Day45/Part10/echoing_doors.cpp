#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>
#include <map>

using namespace std;

struct State {
    int cost;
    int x, y, z;
    int mask;
    
    bool operator>(const State& other) const {
        return cost > other.cost;
    }
};

struct Door {
    int initial;
    int effect;
};

int solve() {
    int X = 3, Y = 3, Z = 1;
    vector<string> grid = {
        "S.0",
        ".#.",
        "1.G"
    };
    
    map<int, Door> doors;
    doors[0] = {1, (1 << 1)};
    doors[1] = {0, 0};
    
    int sx, sy, sz, gx, gy, gz;
    map<tuple<int,int,int>, int> door_locs;
    
    for(int z=0; z<Z; ++z) {
        for(int y=0; y<Y; ++y) {
            for(int x=0; x<X; ++x) {
                char c = grid[y][x]; // Z=1, so just y,x
                if(c == 'S') { sx=x; sy=y; sz=z; }
                else if(c == 'G') { gx=x; gy=y; gz=z; }
                else if(isdigit(c)) {
                    door_locs[{x,y,z}] = c - '0';
                }
            }
        }
    }
    
    int initial_mask = 0;
    for(auto const& [id, d] : doors) {
        if(d.initial) initial_mask |= (1 << id);
    }
    
    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({0, sx, sy, sz, initial_mask});
    
    map<tuple<int,int,int,int>, int> dist;
    dist[{sx, sy, sz, initial_mask}] = 0;
    
    int dx[] = {1, -1, 0, 0, 0, 0};
    int dy[] = {0, 0, 1, -1, 0, 0};
    int dz[] = {0, 0, 0, 0, 1, -1};
    
    while(!pq.empty()) {
        State curr = pq.top();
        pq.pop();
        
        if(curr.x == gx && curr.y == gy && curr.z == gz) return curr.cost;
        
        if(dist.count({curr.x, curr.y, curr.z, curr.mask}) && dist[{curr.x, curr.y, curr.z, curr.mask}] < curr.cost) continue;
        
        for(int i=0; i<6; ++i) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];
            int nz = curr.z + dz[i];
            
            if(nx >= 0 && nx < X && ny >= 0 && ny < Y && nz >= 0 && nz < Z) {
                char c = grid[ny][nx];
                if(c == '#') continue;
                
                int new_cost = curr.cost;
                int new_mask = curr.mask;
                
                if(door_locs.count({nx, ny, nz})) {
                    int id = door_locs[{nx, ny, nz}];
                    if((curr.mask >> id) & 1) {
                        new_cost += 1;
                        new_mask ^= doors[id].effect;
                    } else {
                        continue; // Closed
                    }
                }
                
                if(!dist.count({nx, ny, nz, new_mask}) || new_cost < dist[{nx, ny, nz, new_mask}]) {
                    dist[{nx, ny, nz, new_mask}] = new_cost;
                    pq.push({new_cost, nx, ny, nz, new_mask});
                }
            }
        }
    }
    
    return -1;
}

int main() {
    cout << "Minimum doors passed: " << solve() << endl;
    return 0;
}
