#include <bits/stdc++.h>
using namespace std;

// Part 1 — Parse the Maze
// Helper to find positions of a target character.

vector<pair<int,int>> findPositions(const vector<vector<char>>& maze, char target) {
    int n = (int)maze.size();
    vector<pair<int,int>> res;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < (int)maze[i].size(); ++j) {
            if (maze[i][j] == target) res.emplace_back(i, j);
        }
    }
    return res;
}

optional<pair<int,int>> findSingle(const vector<vector<char>>& maze, char target) {
    int n = (int)maze.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < (int)maze[i].size(); ++j) {
            if (maze[i][j] == target) return make_pair(i, j);
        }
    }
    return nullopt;
}

int main() {
    vector<vector<char>> maze = {
        {'S','E','P','W'},
        {'E','W','E','E'},
        {'E','P','W','E'},
        {'E','E','E','X'}
    };

    auto ps = findPositions(maze, 'P');
    cout << "Positions of 'P': ";
    for (auto &p : ps) cout << "(" << p.first << "," << p.second << ") ";
    cout << "\n";

    auto s = findSingle(maze, 'S');
    auto x = findSingle(maze, 'X');
    cout << "Start 'S': ";
    if (s) cout << "(" << s->first << "," << s->second << ")\n"; else cout << "None\n";
    cout << "Exit  'X': ";
    if (x) cout << "(" << x->first << "," << x->second << ")\n"; else cout << "None\n";
    return 0;
}
