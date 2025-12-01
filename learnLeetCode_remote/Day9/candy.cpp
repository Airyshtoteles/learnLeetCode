#include <iostream>
#include <vector>
using namespace std;

int candy(const vector<int>& ratings) {
    int n = (int)ratings.size();
    if (n == 0) return 0;
    vector<int> candies(n, 1);
    for (int i = 1; i < n; ++i) {
        if (ratings[i] > ratings[i-1]) candies[i] = candies[i-1] + 1;
    }
    for (int i = n - 2; i >= 0; --i) {
        if (ratings[i] > ratings[i+1]) candies[i] = max(candies[i], candies[i+1] + 1);
    }
    long long sum = 0;
    for (int c : candies) sum += c;
    return (int)sum;
}

int main() {
    // Given examples
    if (candy({1,0,2}) != 5) return 1;
    if (candy({1,2,2}) != 4) return 1;
    // Additional checks
    if (candy({1,1,1}) != 3) return 1;
    if (candy({1,2,3,4,5}) != 15) return 1;
    if (candy({5,4,3,2,1}) != 15) return 1;
    cout << "Day9 candy.cpp: all tests passed" << endl;
    return 0;
}
