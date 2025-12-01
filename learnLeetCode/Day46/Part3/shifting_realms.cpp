#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

const int INF = 1e9;

struct Node {
    int cost;
    int r;
    int c;
    int k; // Realm index
    
    bool operator>(const Node& other) const {
        return cost > other.cost;
    }
};

int main() {
    // Hardcoded Input
    int N = 4;
    int M = 4;
    
    vector<vector<vector<int>>> realms(3, vector<vector<int>>(N, vector<int>(M)));
    
    // Realm A
    realms[0] = {
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 1}
    };
    
    // Realm B
    realms[1] = {
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {1, 0, 0, 1},
        {1, 1, 1, 1}
    };
    
    // Realm C
    realms[2] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 1, 1, 1},
        {0, 1, 0, 1}
    };
    
    // Dist array: [realm][r][c]
    vector<vector<vector<int>>> dist(3, vector<vector<int>>(N, vector<int>(M, INF)));
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    
    dist[0][0][0] = 0;
    pq.push({0, 0, 0, 0});
    
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    
    int minCost = -1;
    
    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();
        
        int d = current.cost;
        int r = current.r;
        int c = current.c;
        int k = current.k;
        
        if (d > dist[k][r][c]) continue;
        
        if (r == N-1 && c == M-1 && k == 2) {
            minCost = d;
            break;
        }
        
        // 1. Move within realm
        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                if (realms[k][nr][nc] == 1) {
                    int newCost = d + 1;
                    if (newCost < dist[k][nr][nc]) {
                        dist[k][nr][nc] = newCost;
                        pq.push({newCost, nr, nc, k});
                    }
                }
            }
        }
        
        // 2. Shift Realm
        int nk = (k + 1) % 3;
        if (realms[nk][r][c] == 1) {
            int newCost = d + 3;
            if (newCost < dist[nk][r][c]) {
                dist[nk][r][c] = newCost;
                pq.push({newCost, r, c, nk});
            }
        }
    }
    
    cout << "Minimum Cost: " << minCost << endl;
    
    return 0;
}
