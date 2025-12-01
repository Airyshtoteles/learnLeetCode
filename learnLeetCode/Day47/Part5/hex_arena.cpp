#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <set>
#include <cmath>
#include <map>

using namespace std;

struct Point {
    int x, y, z;

    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        if (y != other.y) return y < other.y;
        return z < other.z;
    }

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y && z == other.z;
    }
};

struct State {
    int cost;
    Point p;

    bool operator>(const State& other) const {
        return cost > other.cost;
    }
};

int solveHexArena(Point target, vector<Point>& blocked, vector<Point>& runes) {
    set<Point> blocked_set(blocked.begin(), blocked.end());
    set<Point> rune_set(runes.begin(), runes.end());

    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({0, {0, 0, 0}});

    map<Point, int> dist;
    dist[{0, 0, 0}] = 0;

    int limit = 50;

    int dx[] = {1, 1, 0, -1, -1, 0};
    int dy[] = {-1, 0, 1, 1, 0, -1};
    int dz[] = {0, -1, -1, 0, 1, 1};

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        int cost = current.cost;
        Point p = current.p;

        if (p == target) {
            return cost;
        }

        if (dist.count(p) && cost > dist[p]) {
            continue;
        }

        // 1. Walk
        for (int i = 0; i < 6; ++i) {
            Point next = {p.x + dx[i], p.y + dy[i], p.z + dz[i]};
            if (max(abs(next.x), max(abs(next.y), abs(next.z))) <= limit && blocked_set.find(next) == blocked_set.end()) {
                int new_cost = cost + 1;
                if (!dist.count(next) || new_cost < dist[next]) {
                    dist[next] = new_cost;
                    pq.push({new_cost, next});
                }
            }
        }

        // 2. Blink
        for (int i = 0; i < 6; ++i) {
            Point next = {p.x + dx[i], p.y + dy[i], p.z + dz[i]};
            while (max(abs(next.x), max(abs(next.y), abs(next.z))) <= limit && blocked_set.find(next) == blocked_set.end()) {
                int new_cost = cost + 2;
                if (!dist.count(next) || new_cost < dist[next]) {
                    dist[next] = new_cost;
                    pq.push({new_cost, next});
                }
                next.x += dx[i];
                next.y += dy[i];
                next.z += dz[i];
            }
        }

        // 3. Rune Teleport
        if (rune_set.count(p)) {
            for (const auto& r : runes) {
                if (r == p) continue;
                int new_cost = cost + 1;
                if (!dist.count(r) || new_cost < dist[r]) {
                    dist[r] = new_cost;
                    pq.push({new_cost, r});
                }
            }
        }
    }

    return -1;
}

int main() {
    Point Target = {0, -2, 2};
    vector<Point> Blocked = {{0, -1, 1}};
    vector<Point> Runes = {{1, -1, 0}, {0, -2, 2}};

    int result = solveHexArena(Target, Blocked, Runes);
    cout << "Minimum Cost: " << result << endl;

    return 0;
}
