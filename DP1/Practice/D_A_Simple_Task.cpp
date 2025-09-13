#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<unsigned int> adj(n, 0);
    for (int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        --a; --b;
        adj[a] |= (1u << b);
        adj[b] |= (1u << a);
    }

    const int Nmask = 1 << n;
    // dp[mask][v]: paths starting at s, ending at v, using exactly 'mask'
    // We'll reuse the table for each s by zeroing it.
    static long long dp[1 << 19][19]; // n <= 19
    long long ans = 0;

    for (int s = 0; s < n; ++s) {
        // Clear only masks that might be used (optimization optional).
        int lowmask = (1 << s) - 1; // bits < s
        // Zero the whole dp (still fine for constraints)
        for (int mask = 0; mask < (1 << n); ++mask)
            for (int v = 0; v < n; ++v)
                dp[mask][v] = 0;

        // Initialize paths of length 2 (s -> v), v > s and edge exists
        unsigned int nb = adj[s] & ~((1u << (s + 1)) - 1u); // neighbors with index > s
        while (nb) {
            int v = __builtin_ctz(nb);
            nb &= nb - 1;
            int mask = (1 << s) | (1 << v);
            dp[mask][v] = 1;
        }

        // Iterate over masks that contain s and have no bits < s
        for (int mask = 0; mask < (1 << n); ++mask) {
            if (((mask >> s) & 1) == 0) continue;                // must include s
            if (mask & lowmask) continue;                        // no vertex < s
            int bits = __builtin_popcount((unsigned)mask);
            if (bits < 2) continue;

            for (int v = 0; v < n; ++v) {
                long long ways = dp[mask][v];
                if (!ways) continue;

                // Option 1: close a cycle back to s (only if we have at least 3 vertices)
                if (bits >= 3 && (adj[v] & (1u << s))) {
                    ans += ways;
                }

                // Option 2: extend to a new neighbor u (u >= s), u not in mask
                unsigned int cand = adj[v] & ~((unsigned)mask);
                cand &= ~((1u << s) - 1u); // keep only u >= s
                while (cand) {
                    int u = __builtin_ctz(cand);
                    cand &= cand - 1;
                    dp[mask | (1 << u)][u] += ways;
                }
            }
        }
    }

    // Each undirected cycle counted twice (two orientations)
    cout << (ans / 2) << "\n";
    return 0;
}
