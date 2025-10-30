#include <bits/stdc++.h>
using namespace std;

// Detective's Timeline
// Return suspects who have any timestamp within [t_start, t_end].

vector<string> innocent_suspects(map<string, vector<int>> suspects, int t_start, int t_end){
    vector<string> res;
    for(auto &p: suspects){
        const string &name = p.first; auto times = p.second; sort(times.begin(), times.end());
        auto i = lower_bound(times.begin(), times.end(), t_start);
        auto j = upper_bound(times.begin(), times.end(), t_end);
        if(i < j) res.push_back(name);
    }
    sort(res.begin(), res.end());
    return res;
}

int main(){
    map<string, vector<int>> suspects{{"A",{1,5,9}}, {"B",{3,8}}, {"C",{2,4,6}}};
    auto res = innocent_suspects(suspects, 3, 7);
    for(auto &s: res) cout << s << " "; cout << "\n"; // A
    return 0;
}
