#include <bits/stdc++.h>
using namespace std;

static const string GOAL_STR = "123456789ABCDEF0";

static const vector<vector<int>> NEI = {
    {1,4}, {0,2,5}, {1,3,6}, {2,7},
    {0,5,8}, {1,4,6,9}, {2,5,7,10}, {3,6,11},
    {4,9,12}, {5,8,10,13}, {6,9,11,14}, {7,10,15},
    {8,13}, {9,12,14}, {10,13,15}, {11,14}
};

string serialize(const vector<vector<int>>& board){
    string s; s.reserve(16);
    for(auto &row: board){
        for(int x: row){
            if(x < 10) s.push_back('0' + x);
            else s.push_back('A' + (x-10));
        }
    }
    return s;
}

vector<int> deserialize(const string& s){
    vector<int> a(16);
    for(int i=0;i<16;i++){
        char c = s[i];
        if('0'<=c && c<='9') a[i] = c - '0';
        else a[i] = 10 + (c - 'A');
    }
    return a;
}

int inversion_count(const vector<int>& arr){
    vector<int> a; a.reserve(16);
    for(int x: arr) if(x!=0) a.push_back(x);
    int inv=0;
    for(int i=0;i<(int)a.size();++i){
        for(int j=i+1;j<(int)a.size();++j){
            if(a[i] > a[j]) ++inv;
        }
    }
    return inv;
}

bool solvable(const string& key){
    auto arr = deserialize(key);
    int inv = inversion_count(arr);
    int zi = find(arr.begin(), arr.end(), 0) - arr.begin();
    int row_from_bottom = 4 - (zi/4); // 1..4
    return ((inv + row_from_bottom) % 2) == 1;
}

int min_moves(const vector<vector<int>>& board){
    string start = serialize(board);
    if(start == GOAL_STR) return 0;
    if(!solvable(start)) return -1;
    queue<string> q; q.push(start);
    unordered_map<string,int> dist; dist.reserve(100000); dist[start]=0;
    while(!q.empty()){
        string s = q.front(); q.pop();
        int d = dist[s];
        auto arr = deserialize(s);
        int z = find(arr.begin(), arr.end(), 0) - arr.begin();
        for(int nz: NEI[z]){
            auto b = arr;
            swap(b[z], b[nz]);
            string ns; ns.reserve(16);
            for(int x: b){
                if(x<10) ns.push_back('0'+x);
                else ns.push_back('A'+(x-10));
            }
            if(!dist.count(ns)){
                dist[ns] = d+1;
                if(ns == GOAL_STR) return d+1;
                q.push(ns);
            }
        }
    }
    return -1;
}

int main(){
    vector<vector<int>> board = {
        {1,2,3,4},
        {5,6,7,8},
        {9,10,11,12},
        {13,15,14,0}
    };
    cout << min_moves(board) << "\n"; // Expected 2
    return 0;
}
