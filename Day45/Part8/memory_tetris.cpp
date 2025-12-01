#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

// Grid: 10 rows, 6 cols
const int H = 10;
const int W = 6;

typedef vector<vector<int>> Grid;

struct State {
    int score;
    Grid grid;
    
    bool operator>(const State& other) const {
        return score > other.score;
    }
};

// Shapes
vector<vector<int>> getShape(char type) {
    if (type == 'I') return {{1, 1, 1, 1}};
    if (type == 'O') return {{1, 1}, {1, 1}};
    if (type == 'T') return {{0, 1, 0}, {1, 1, 1}};
    // ... others
    return {};
}

int solve() {
    vector<char> pieces = {'I', 'I', 'O', 'T'};
    
    Grid initial_grid(H, vector<int>(W, 0));
    vector<State> beam;
    beam.push_back({0, initial_grid});
    
    int BEAM_WIDTH = 20;
    
    for(char p_type : pieces) {
        vector<vector<int>> shape = getShape(p_type);
        int ph = shape.size();
        int pw = shape[0].size();
        
        vector<State> next_beam;
        
        for(const auto& s : beam) {
            for(int c = 0; c <= W - pw; ++c) {
                int final_y = -1;
                
                for(int y = H - ph; y >= 0; --y) {
                    bool fits = true;
                    for(int r = 0; r < ph; ++r) {
                        for(int k = 0; k < pw; ++k) {
                            if(shape[r][k] == 1) {
                                int by = y + (ph - 1 - r);
                                if(by >= H || s.grid[by][c+k] == 1) {
                                    fits = false; break;
                                }
                            }
                        }
                        if(!fits) break;
                    }
                    
                    if(fits) final_y = y;
                    else break;
                }
                
                if(final_y != -1) {
                    Grid new_grid = s.grid;
                    for(int r = 0; r < ph; ++r) {
                        for(int k = 0; k < pw; ++k) {
                            if(shape[r][k] == 1) {
                                int by = final_y + (ph - 1 - r);
                                new_grid[by][c+k] = 1;
                            }
                        }
                    }
                    
                    vector<int> lines_cleared;
                    for(int r = 0; r < H; ++r) {
                        bool full = true;
                        for(int k = 0; k < W; ++k) if(new_grid[r][k] == 0) full = false;
                        if(full) lines_cleared.push_back(r);
                    }
                    
                    int current_score = s.score + lines_cleared.size();
                    
                    if(lines_cleared.empty()) {
                        next_beam.push_back({current_score, new_grid});
                    } else {
                        set<int> cleared_set(lines_cleared.begin(), lines_cleared.end());
                        int bonus = 0;
                        for(int r : lines_cleared) {
                            if(r + 1 < H && cleared_set.find(r+1) == cleared_set.end()) {
                                cleared_set.insert(r+1);
                                bonus++;
                            }
                        }
                        current_score += bonus;
                        
                        Grid final_grid;
                        for(int r = 0; r < H; ++r) {
                            if(cleared_set.find(r) == cleared_set.end()) {
                                final_grid.push_back(new_grid[r]);
                            }
                        }
                        while(final_grid.size() < H) {
                            final_grid.push_back(vector<int>(W, 0));
                        }
                        next_beam.push_back({current_score, final_grid});
                    }
                }
            }
        }
        
        sort(next_beam.begin(), next_beam.end(), [](const State& a, const State& b){
            return a.score > b.score;
        });
        
        if(next_beam.size() > BEAM_WIDTH) next_beam.resize(BEAM_WIDTH);
        beam = next_beam;
    }
    
    if(beam.empty()) return 0;
    return beam[0].score;
}

int main() {
    cout << "Max lines cleared: " << solve() << endl;
    return 0;
}
