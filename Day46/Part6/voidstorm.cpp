#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    int N = 10;
    int M = 10;
    int H = 100;
    int D = 15;
    
    // Formula
    int t_safe = (min(N, M) - 1) / 2;
    int extra_time = (H - 1) / D;
    int total_time = t_safe + extra_time;
    
    cout << "Calculated Max Survival Time: " << total_time << endl;
    
    // Simulation
    double curr_r = 0;
    double curr_c = 0;
    int curr_h = H;
    int t = 0;
    
    double center_r = (N - 1) / 2.0;
    double center_c = (M - 1) / 2.0;
    
    while (curr_h > 0) {
        t++;
        if (t > 1000) break;
        
        // Move
        if (curr_r < center_r) curr_r += 1;
        else if (curr_r > center_r) curr_r -= 1;
        
        // Snap to integer? No, grid is integer.
        // But center might be .5.
        // If center is 4.5, and we are at 4. We move to 5?
        // "Move 1 step".
        // If we are at 4, center 4.5.
        // We can move to 5.
        // If we are at 5, center 4.5. Move to 4.
        // So we oscillate 4-5. Both are "center".
        
        if (curr_c < center_c) curr_c += 1;
        else if (curr_c > center_c) curr_c -= 1;
        
        // Boundary
        int min_safe = t;
        int max_safe_r = N - 1 - t;
        int max_safe_c = M - 1 - t;
        
        bool in_safe = true;
        // Check integer coordinates
        // We need to track integer pos.
        // Let's use int for pos.
        // Logic: if curr < center, inc.
        // But if center is 4.5, and curr is 4. 4 < 4.5 -> inc to 5.
        // Next step: 5 > 4.5 -> dec to 4.
        // Correct.
        
        if ((int)curr_r < min_safe || (int)curr_r > max_safe_r) in_safe = false;
        if ((int)curr_c < min_safe || (int)curr_c > max_safe_c) in_safe = false;
        
        if (!in_safe) {
            curr_h -= D;
        }
    }
    
    cout << "Simulated Max Survival Time: " << t - 1 << endl;
    
    return 0;
}
