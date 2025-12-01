#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>
#include <map>
#include <algorithm>

using namespace std;

struct Spell {
    int power;
    int cooldown;
    int tagId;
};

const int INF = 1e9;

int solve() {
    int H;
    int N;
    
    // Hardcoded input for demonstration matching Python
    H = 100;
    N = 4;
    vector<tuple<int, int, string>> raw_spells = {
        {10, 3, "fire"},
        {8, 2, "ice"},
        {4, 1, "fire"},
        {20, 5, "storm"}
    };

    map<string, int> tagToId;
    int tagCounter = 0;
    vector<Spell> spells;

    for(auto& s : raw_spells) {
        string t = get<2>(s);
        if(tagToId.find(t) == tagToId.end()) {
            tagToId[t] = tagCounter++;
        }
        spells.push_back({get<0>(s), get<1>(s), tagToId[t]});
    }

    // dist[damage][last_tag]
    // damage: 0 to H
    // last_tag: 0 to tagCounter-1. 
    // We also need a state for "no tag" (start). Let's use tagCounter as "None".
    int numTags = tagCounter;
    int noneTag = numTags; 
    
    // Dimensions: (H + 1) x (numTags + 1)
    vector<vector<int>> dist(H + 1, vector<int>(numTags + 1, INF));

    // PQ stores: {time, damage, last_tag}
    // Min-heap
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;

    // Start state
    dist[0][noneTag] = 0;
    pq.push({0, 0, noneTag});

    while(!pq.empty()) {
        auto [time, dmg, lastTag] = pq.top();
        pq.pop();

        if (dmg >= H) return time;
        if (time > dist[dmg][lastTag]) continue;

        for(const auto& spell : spells) {
            int p = spell.power;
            if (spell.tagId == lastTag) {
                p *= 2;
            }
            
            int nextDmg = min(H, dmg + p);
            int nextTime = time + spell.cooldown;
            int nextTag = spell.tagId;

            if (nextTime < dist[nextDmg][nextTag]) {
                dist[nextDmg][nextTag] = nextTime;
                pq.push({nextTime, nextDmg, nextTag});
            }
        }
    }

    return -1;
}

int main() {
    cout << "Minimum time to reach target damage: " << solve() << endl;
    return 0;
}
