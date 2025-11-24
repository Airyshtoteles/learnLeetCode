#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

const int INF = 1e9;

struct Node {
    int cost;
    int r;
    int c;
    
    bool operator>(const Node& other) const {
        return cost > other.cost;
    }
};

int N, M;
vector<vector<int>> costs;
vector<vector<int>> traps;

vector<vector<int>> dijkstra(int startR, int startC) {
    vector<vector<int>> dist(N, vector<int>(M, INF));
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    
    dist[startR][startC] = 0;
    pq.push({0, startR, startC});
    
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    
    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();
        
        int r = current.r;
        int c = current.c;
        int d = current.cost;
        
        if (d > dist[r][c]) continue;
        
        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                int newCost = d + costs[nr][nc];
                if (newCost < dist[nr][nc]) {
                    dist[nr][nc] = newCost;
                    pq.push({newCost, nr, nc});
                }
            }
        }
    }
    return dist;
}

int main() {
    // Hardcoded Example
    costs = {
        {1, 5, 1, 1},
        {1, 5, 1, 5},
        {1, 1, 1, 5},
        {5, 5, 5, 1}
    };
    traps = {
        {0, 0, 0, 0},
        {0, 0, 1, 0}, // Trap at (1, 2)
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    
    N = costs.size();
    M = costs[0].size();
    
    // 1. From Start
    vector<vector<int>> distStart = dijkstra(0, 0);
    
    if (distStart[N-1][M-1] == INF) {
        cout << -1 << endl;
        return 0;
    }
    
    int minEnergy = distStart[N-1][M-1];
    cout << "Cost from Start: " << minEnergy << endl;
    
    // 2. From Traps
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < M; ++c) {
            if (traps[r][c] == 1) {
                // Check reachability
                if (distStart[r][c] != INF) {
                    cout << "Trap at (" << r << "," << c << ") is reachable." << endl;
                    vector<vector<int>> distTrap = dijkstra(r, c);
                    if (distTrap[N-1][M-1] != INF) {
                        int trapCost = distTrap[N-1][M-1];
                        cout << "Cost from Trap: " << trapCost << endl;
                        if (trapCost < minEnergy) {
                            minEnergy = trapCost;
                        }
                    }
                }
            }
        }
    }
    
    cout << "Minimum Energy: " << minEnergy << endl;
    
    return 0;
}
