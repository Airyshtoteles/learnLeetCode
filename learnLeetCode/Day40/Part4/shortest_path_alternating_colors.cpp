#include <bits/stdc++.h>
using namespace std;

static const int RED = 0;
static const int BLUE = 1;

vector<int> shortestAlternatingPaths(int n, const vector<pair<int,int>>& redEdges, const vector<pair<int,int>>& blueEdges) {
    vector<vector<int>> redAdj(n), blueAdj(n);
    for (auto &e : redEdges) redAdj[e.first].push_back(e.second);
    for (auto &e : blueEdges) blueAdj[e.first].push_back(e.second);

    const int INF = 1e9;
    vector<vector<int>> dist(n, vector<int>(2, INF));
    deque<pair<int,int>> dq;

    dist[0][RED] = 0;
    dist[0][BLUE] = 0;
    dq.emplace_back(0, RED);
    dq.emplace_back(0, BLUE);

    while (!dq.empty()) {
        auto [u, last] = dq.front(); dq.pop_front();
        int d = dist[u][last];
        if (last == RED) {
            for (int v : blueAdj[u]) {
                if (d + 1 < dist[v][BLUE]) {
                    dist[v][BLUE] = d + 1;
                    dq.emplace_back(v, BLUE);
                }
            }
        } else {
            for (int v : redAdj[u]) {
                if (d + 1 < dist[v][RED]) {
                    dist[v][RED] = d + 1;
                    dq.emplace_back(v, RED);
                }
            }
        }
    }

    vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
        int best = min(dist[i][RED], dist[i][BLUE]);
        ans[i] = (best >= INF ? -1 : best);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<pair<int,int>> red1{{0,1},{1,2}}; vector<pair<int,int>> blue1{};
    auto a1 = shortestAlternatingPaths(3, red1, blue1);
    for (int x : a1) cout << x << ' '; cout << "\n"; // 0 1 2

    vector<pair<int,int>> red2{{0,1}}; vector<pair<int,int>> blue2{{1,2}};
    auto a2 = shortestAlternatingPaths(3, red2, blue2);
    for (int x : a2) cout << x << ' '; cout << "\n"; // 0 1 2
    return 0;
}
