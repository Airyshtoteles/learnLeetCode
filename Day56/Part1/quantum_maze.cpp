#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

struct State {
    long long time;
    int r, c;
    
    bool operator>(const State& other) const {
        return time > other.time;
    }
};

int N, M;
long long K;
// grid[r][c][0] = is path in phase 0?
// grid[r][c][1] = is path in phase 1?
int grid[305][305][2];
long long dist[305][305];

const long long INF = 1e18;

long long get_next_arrival(long long current_time, int r, int c) {
    long long arrival = current_time + 1;
    
    // Check if accessible in current phase
    int phase = (arrival / K) % 2;
    if (grid[r][c][phase]) return arrival;
    
    // If not, we need the other phase
    int required_phase = 1 - phase;
    
    // Find start of next block with required_phase
    // Current block is [ (arrival/K)*K, (arrival/K + 1)*K - 1 ]
    // Next block starts at (arrival/K + 1)*K
    long long next_block_start = (arrival / K + 1) * K;
    
    // We need T >= next_block_start such that T % 2 == arrival % 2
    long long T;
    if (next_block_start % 2 == arrival % 2) {
        T = next_block_start;
    } else {
        T = next_block_start + 1;
    }
    
    // Check if T is within the block
    // Block ends at next_block_start + K
    if (T < next_block_start + K) {
        return T;
    }
    
    // If not valid (only happens if K=1 and parity mismatch), impossible
    return INF;
}

int main() {
    // if (fopen("input.txt", "r")) {
    //     freopen("input.txt", "r", stdin);
    // }

    if (!(cin >> N >> M >> K)) return 0;
    
    for (int i = 0; i < N; ++i) {
        string row;
        cin >> row;
        for (int j = 0; j < M; ++j) {
            grid[i][j][0] = (row[j] == '.');
        }
    }
    
    for (int i = 0; i < N; ++i) {
        string row;
        cin >> row;
        for (int j = 0; j < M; ++j) {
            grid[i][j][1] = (row[j] == '.');
        }
    }
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            dist[i][j] = INF;
        }
    }
    
    priority_queue<State, vector<State>, greater<State>> pq;
    
    dist[0][0] = 0;
    pq.push({0, 0, 0});
    
    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};
    
    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();
        
        long long t = current.time;
        int r = current.r;
        int c = current.c;
        
        if (t > dist[r][c]) continue;
        if (r == N - 1 && c == M - 1) {
            cout << t << endl;
            return 0;
        }
        
        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                long long next_time = get_next_arrival(t, nr, nc);
                if (next_time != INF && next_time < dist[nr][nc]) {
                    dist[nr][nc] = next_time;
                    pq.push({next_time, nr, nc});
                }
            }
        }
    }
    
    cout << -1 << endl;
    return 0;
}
