#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <set>
#include <tuple>

using namespace std;

const int INF = 1e9;

struct State {
    int w, r, c;
};

int main() {
    int N = 5, M = 5;
    vector<string> grid0 = {
        "S...#",
        ".###.",
        ".....",
        ".###.",
        "....E"
    };
    vector<string> grid1 = {
        ".....",
        "#...#",
        "#.R.#",
        "#...#",
        "....."
    };

    set<pair<int, int>> rifts;
    rifts.insert({0, 4});
    rifts.insert({2, 2});
    rifts.insert({4, 0});

    int startR, startC, endR, endC;
    bool foundStart = false, foundEnd = false;

    for(int r=0; r<N; ++r) {
        for(int c=0; c<M; ++c) {
            if(grid0[r][c] == 'S') {
                startR = r; startC = c;
                foundStart = true;
            }
            if(grid0[r][c] == 'E') {
                endR = r; endC = c;
                foundEnd = true;
            }
        }
    }
    
    if (!foundEnd) {
         for(int r=0; r<N; ++r) {
            for(int c=0; c<M; ++c) {
                if(grid1[r][c] == 'E') {
                    endR = r; endC = c;
                    foundEnd = true;
                }
            }
         }
    }

    if(!foundStart || !foundEnd) {
        cout << "Start or End not found" << endl;
        return 0;
    }

    // dist[world][r][c]
    vector<vector<vector<int>>> dist(2, vector<vector<int>>(N, vector<int>(M, INF)));
    deque<State> dq;

    dist[0][startR][startC] = 0;
    dq.push_back({0, startR, startC});

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while(!dq.empty()) {
        State curr = dq.front();
        dq.pop_front();

        int w = curr.w;
        int r = curr.r;
        int c = curr.c;
        int d = dist[w][r][c];

        if(r == endR && c == endC) {
            cout << "Minimum steps: " << d << endl;
            return 0;
        }

        // 1. Teleport (Cost 0)
        if(rifts.count({r, c})) {
            int nw = 1 - w;
            const vector<string>& targetGrid = (nw == 0) ? grid0 : grid1;
            
            if(targetGrid[r][c] != '#') {
                if(dist[nw][r][c] > d) {
                    dist[nw][r][c] = d;
                    dq.push_front({nw, r, c});
                }
            }
        }

        // 2. Move (Cost 1)
        const vector<string>& currentGrid = (w == 0) ? grid0 : grid1;
        for(int i=0; i<4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if(nr >= 0 && nr < N && nc >= 0 && nc < M) {
                if(currentGrid[nr][nc] != '#') {
                    if(dist[w][nr][nc] > d + 1) {
                        dist[w][nr][nc] = d + 1;
                        dq.push_back({w, nr, nc});
                    }
                }
            }
        }
    }

    cout << "Unreachable" << endl;

    return 0;
}
