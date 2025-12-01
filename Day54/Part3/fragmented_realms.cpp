#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

string solve_fragmented_realms(string s) {
    int n = s.length();
    map<char, int> even_counts;
    map<char, int> odd_counts;

    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0) even_counts[s[i]]++;
        else odd_counts[s[i]]++;
    }

    if (n % 2 == 0) {
        // Even length: 0 matches N-1 (Odd). Even set must equal Odd set.
        if (even_counts == odd_counts) return "YES";
        else return "NO";
    } else {
        // Odd length:
        int center = n / 2;
        int odd_set_odd_counts = 0;
        for (auto const& [key, val] : odd_counts) {
            if (val % 2 != 0) odd_set_odd_counts++;
        }
        int even_set_odd_counts = 0;
        for (auto const& [key, val] : even_counts) {
            if (val % 2 != 0) even_set_odd_counts++;
        }

        if (center % 2 == 0) {
            // Center is at Even index. Even set has the center char.
            // Even set: 1 odd count. Odd set: 0 odd counts.
            if (even_set_odd_counts == 1 && odd_set_odd_counts == 0) return "YES";
            else return "NO";
        } else {
            // Center is at Odd index. Odd set has the center char.
            // Odd set: 1 odd count. Even set: 0 odd counts.
            if (odd_set_odd_counts == 1 && even_set_odd_counts == 0) return "YES";
            else return "NO";
        }
    }
}

int main() {
    // Test 1: "aabb" -> N=4. Even: a,b. Odd: a,b. Equal? Yes. "abba" is palindrome.
    cout << "Test 1 (aabb) Expected YES: " << solve_fragmented_realms("aabb") << endl;

    // Test 2: "abc" -> N=3. Even: a,c. Odd: b.
    // Odd set: {b:1}. Count is odd. Fail.
    // Palindrome must be "acbca"? No.
    // Indices: 0,1,2. Pairs (0,2). Center 1.
    // Wait. My logic for N odd was:
    // 0 matches N-1.
    // If N=3. 0 matches 2. (Even, Even).
    // 1 is center. (Odd).
    // So Odd set has center. Even set has pairs.
    // Let's re-verify N=3.
    // Indices: 0, 1, 2.
    // 0 and 2 are Even. They must match. So Even set must have pairs.
    // 1 is Odd. It is center. So Odd set must have 1 odd count.
    // My code logic:
    // "Odd set must have all even counts" -> This was for N=5 where center was 2 (Even).
    // Let's generalize.
    // Center index is N/2.
    // If N/2 is Even: Center comes from Even set. Even set has 1 odd count. Odd set has 0 odd counts.
    // If N/2 is Odd: Center comes from Odd set. Odd set has 1 odd count. Even set has 0 odd counts.
    
    // Let's fix the code logic.
    cout << "Test 2 (abc) Expected NO: " << solve_fragmented_realms("abc") << endl;
    
    // Test 3: "aaabb" -> N=5. Indices 0,1,2,3,4.
    // Pairs (0,4) Even-Even. (1,3) Odd-Odd. Center 2 (Even).
    // Even set: a,a,b (from 0,2,4). Odd set: a,b (from 1,3).
    // Even set needs 1 odd count. Odd set needs 0 odd counts.
    // Input "aaabb".
    // Even indices (0,2,4): a,a,b. Counts: a:2, b:1. (1 odd count). OK.
    // Odd indices (1,3): a,b. Counts: a:1, b:1. (2 odd counts). Fail.
    // Can we rearrange?
    // We can swap 0,2,4 freely. We can swap 1,3 freely.
    // We need to form palindrome.
    // Palindrome structure: X Y Z Y X
    // 0=X, 4=X. (Even set needs 2 X's).
    // 1=Y, 3=Y. (Odd set needs 2 Y's).
    // 2=Z. (Even set needs 1 Z).
    // So Even set needs pairs + 1 single. Odd set needs pairs.
    // My manual trace says "aaabb" fails.
    cout << "Test 3 (aaabb) Expected NO: " << solve_fragmented_realms("aaabb") << endl;

    // Test 4: "ababa" -> N=5.
    // Even (0,2,4): a,a,a. Odd (1,3): b,b.
    // Even: a:3. (1 odd count). OK.
    // Odd: b:2. (0 odd count). OK.
    // Result YES.
    cout << "Test 4 (ababa) Expected YES: " << solve_fragmented_realms("ababa") << endl;

    return 0;
}
