#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;
    vector<int> weight(n);
    for (int i = 0; i < n; ++i) {
        cin >> weight[i];
    }

    // dp[mask] = {min_rides, last_ride_weight}
    vector<pair<int, int>> dp(1 << n, {INT_MAX, 0});
    dp[0] = {1, 0};  // Base case: 1 rides needed for 0 people

    for (int mask = 0; mask < (1 << n); ++mask) {
        for (int p = 0; p < n; ++p) {
            if (!(mask & (1 << p))) {
                int new_mask = mask | (1 << p);
                auto current = dp[mask];
                
                // Try adding to current ride
                if (current.second + weight[p] <= x) {
                    current.second += weight[p];
                } 
                // Otherwise start new ride
                else {
                    current.first++;
                    current.second = weight[p];
                }
                
                // Update if better option found
                dp[new_mask] = min(dp[new_mask], current);
            }
        }
    }

    cout << dp[(1 << n) - 1].first << endl;
    return 0;
}