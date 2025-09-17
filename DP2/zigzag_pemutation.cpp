/*
problem:
  statement: |
    Given N, calculate how many permutations of length N
    (ara[1], ara[2], …, ara[N]) exist where, for each i (1 < i < N),
    either of the following conditions is satisfied:

    1. ara[i] > ara[i + 1] and ara[i] > ara[i – 1]
    2. ara[i] < ara[i + 1] and ara[i] < ara[i – 1]

    Constraints:
    1 ≤ N ≤ 10000

tests:
  - input: 1
    output: 1

  - input: 2
    output: 2

  - input: 3
    output: 4

  - input: 4
    output: 10

  - input: 5
    output: 32

  - input: 10
    output: 50521

  - input: 20
    output: 688423210   # value modulo 1e9+7

  - input: 100
    output: 591137401   # value modulo 1e9+7

  - input: 1000
    output: 591765313   # value modulo 1e9+7

*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;
    const int MOD = 1'000'000'007;

    // up[j], down[j] for current length i (1..i). We'll 1-index for clarity.
    vector<int> up(1 + N), down(1 + N), up_next(1 + N), down_next(1 + N);
    vector<int> pref(1 + N); // prefix helper

    // base: i = 1
    up[1] = 1;
    down[1] = 1;

    for (int i = 1; i < N; ++i) {
        // up_next[j] = sum_{x=1}^{j-1} down[x]
        pref[0] = 0;
        for (int j = 1; j <= i; ++j) {
            pref[j] = pref[j - 1] + down[j];
            if (pref[j] >= MOD) pref[j] -= MOD;
        }
        // j runs 1..i+1 (new rank among i+1 items)
        for (int j = 1; j <= i + 1; ++j) {
            int val = pref[j - 1]; // sum down[1..j-1]
            up_next[j] = val;
        }

        // down_next[j] = sum_{x=j}^{i} up[x]  (suffix)
        // suffix via total - prefix(j-1)
        pref[0] = 0;
        for (int j = 1; j <= i; ++j) {
            pref[j] = pref[j - 1] + up[j];
            if (pref[j] >= MOD) pref[j] -= MOD;
        }
        int totalUp = pref[i];
        for (int j = 1; j <= i + 1; ++j) {
            // for j = i+1, sum_{x=j}^{i} is empty -> 0
            int val = 0;
            if (j <= i) {
                val = totalUp - pref[j - 1];
                if (val < 0) val += MOD;
            }
            down_next[j] = val;
        }

        // move to next length
        for (int j = 1; j <= i + 1; ++j) {
            up[j] = up_next[j];
            down[j] = down_next[j];
        }
    }

    long long ans = 0;
    for (int j = 1; j <= N; ++j) {
        ans += up[j];
        if (ans >= MOD) ans -= MOD;
        ans += down[j];
        if (ans >= MOD) ans -= MOD;
    }
    cout << ans % MOD << "\n";
    return 0;
}
