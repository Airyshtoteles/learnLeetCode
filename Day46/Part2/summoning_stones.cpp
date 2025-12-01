#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <tuple>

using namespace std;

struct Action {
    int exitTime;
    int enemyId;
    int towerIdx;
    
    bool operator<(const Action& other) const {
        if (exitTime != other.exitTime)
            return exitTime < other.exitTime;
        return enemyId < other.enemyId;
    }
};

int N = 15;
int R = 2;
int K = 2;
vector<int> enemiesSpawn = {0, 1, 2, 5, 6, 7, 10, 12};

int simulate(const vector<int>& positions) {
    int kills = 0;
    set<int> aliveEnemies;
    for(int i=0; i<enemiesSpawn.size(); ++i) aliveEnemies.insert(i);
    
    vector<int> towerReadyAt(K, 0);
    
    int maxTime = 0;
    for(int t : enemiesSpawn) maxTime = max(maxTime, t);
    maxTime += N + R + 5;
    
    for (int t = 0; t < maxTime; ++t) {
        vector<Action> actions;
        
        for (int i = 0; i < K; ++i) {
            if (towerReadyAt[i] > t) continue;
            
            int p = positions[i];
            
            for (int eId : aliveEnemies) {
                int spawn = enemiesSpawn[eId];
                int ePos = t - spawn;
                
                if (ePos >= p - R && ePos <= p + R) {
                    int exitTime = p + R + spawn;
                    actions.push_back({exitTime, eId, i});
                }
            }
        }
        
        sort(actions.begin(), actions.end());
        
        set<int> usedTowers;
        for (const auto& act : actions) {
            if (aliveEnemies.count(act.enemyId) && usedTowers.find(act.towerIdx) == usedTowers.end()) {
                aliveEnemies.erase(act.enemyId);
                usedTowers.insert(act.towerIdx);
                towerReadyAt[act.towerIdx] = t + 3;
                kills++;
            }
        }
    }
    return kills;
}

void generateCombinations(vector<int>& current, int start, int k, int n, int& maxKills, vector<int>& bestPos) {
    if (k == 0) {
        int kls = simulate(current);
        if (kls > maxKills) {
            maxKills = kls;
            bestPos = current;
        }
        return;
    }
    
    for (int i = start; i <= n; ++i) {
        current.push_back(i);
        generateCombinations(current, i + 1, k - 1, n, maxKills, bestPos);
        current.pop_back();
    }
}

int main() {
    int maxKills = 0;
    vector<int> bestPos;
    vector<int> current;
    
    generateCombinations(current, 0, K, N, maxKills, bestPos);
    
    cout << "Max Kills: " << maxKills << endl;
    cout << "Best Positions: ";
    for (int p : bestPos) cout << p << " ";
    cout << endl;
    
    return 0;
}
