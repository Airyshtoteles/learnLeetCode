#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Skill {
    int id;
    int cast;
    int dmg;
    int cool;
    double dps;
};

bool compareSkills(const Skill& a, const Skill& b) {
    if (a.dps != b.dps)
        return a.dps > b.dps;
    return a.dmg > b.dmg;
}

int main() {
    int T = 20;
    vector<Skill> skills = {
        {0, 2, 20, 5, 0.0},   // A
        {1, 1, 8, 0, 0.0},    // B
        {2, 5, 60, 10, 0.0},  // C
        {3, 3, 30, 3, 0.0}    // D
    };
    
    for (auto& s : skills) {
        s.dps = (double)s.dmg / s.cast;
    }
    
    sort(skills.begin(), skills.end(), compareSkills);
    
    int currentTime = 0;
    long long totalDamage = 0;
    vector<int> readyTime(skills.size(), 0);
    
    while (currentTime < T) {
        int bestIdx = -1;
        
        for (int i = 0; i < skills.size(); ++i) {
            int originalId = skills[i].id;
            if (readyTime[originalId] <= currentTime) {
                if (currentTime + skills[i].cast <= T) {
                    bestIdx = i;
                    break;
                }
            }
        }
        
        if (bestIdx != -1) {
            Skill& s = skills[bestIdx];
            totalDamage += s.dmg;
            currentTime += s.cast;
            readyTime[s.id] = currentTime + s.cool;
        } else {
            int nextReady = 2e9;
            for (int i = 0; i < skills.size(); ++i) {
                int originalId = skills[i].id;
                if (readyTime[originalId] > currentTime) {
                    nextReady = min(nextReady, readyTime[originalId]);
                }
            }
            
            if (nextReady == 2e9 || nextReady >= T) {
                break;
            }
            currentTime = nextReady;
        }
    }
    
    cout << "Total Damage: " << totalDamage << endl;
    
    return 0;
}
