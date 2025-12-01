#include <bits/stdc++.h>
using namespace std;

// Part 3 — Portal Mapping
// Deterministic teleport: from current portal to the next portal in the vector order.

optional<pair<int,int>> teleportRandom(const vector<pair<int,int>>& portals, pair<int,int> current){
    if (portals.size() <= 1) return nullopt;
    for (size_t i = 0; i < portals.size(); ++i){
        if (portals[i] == current){
            size_t j = (i + 1) % portals.size();
            if (portals[j] == current) return nullopt;
            return portals[j];
        }
    }
    return nullopt;
}

int main(){
    vector<pair<int,int>> portals = {{0,2},{2,1},{3,0}};
    auto a = teleportRandom(portals, {0,2});
    auto b = teleportRandom(portals, {2,1});
    auto c = teleportRandom(portals, {3,0});
    auto pr = [](optional<pair<int,int>> p){ if(p) cout << "("<<p->first<<","<<p->second<<")\n"; else cout << "None\n"; };
    pr(a); pr(b); pr(c);
    return 0;
}
