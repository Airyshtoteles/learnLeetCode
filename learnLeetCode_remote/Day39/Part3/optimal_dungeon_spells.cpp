#include <bits/stdc++.h>
using namespace std;

long long min_time_to_clear(const vector<long long>& roomsHP,
                            const vector<long long>& damage,
                            const vector<int>& cd,
                            const vector<long long>& cost,
                            long long totalMana){
    int m = (int)damage.size();
    vector<long long> cd_left(m, 0);
    long long time = 0;
    long long mana = totalMana;
    for(long long hp : roomsHP){
        long long cur = hp;
        while(cur > 0){
            int best = -1; long long best_dmg = -1;
            for(int j=0;j<m;++j){
                if(cd_left[j]==0 && cost[j] <= mana && damage[j] > best_dmg){
                    best_dmg = damage[j]; best = j;
                }
            }
            if(best != -1 && best_dmg > 0){
                cur -= best_dmg;
                mana -= cost[best];
                cd_left[best] = cd[best];
                ++time;
                for(int j=0;j<m;++j) if(cd_left[j]>0) --cd_left[j];
            }else{
                long long wait = LLONG_MAX;
                bool anyAffordable = false;
                for(int j=0;j<m;++j){
                    if(cost[j] <= mana){
                        anyAffordable = true;
                        if(cd_left[j]>0) wait = min(wait, cd_left[j]);
                        else if(damage[j]>0) wait = 0;
                    }
                }
                if(!anyAffordable) return -1;
                if(wait == 0) continue;
                if(wait == LLONG_MAX) return -1;
                time += wait;
                for(int j=0;j<m;++j){ if(cd_left[j]>0){ cd_left[j] = max(0LL, cd_left[j]-wait); } }
            }
        }
    }
    return time;
}

int main(){ ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << min_time_to_clear(vector<long long>{10}, vector<long long>{6,4}, vector<int>{2,1}, vector<long long>{3,2}, 10) << "\n";
    return 0; }
