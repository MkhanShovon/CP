#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXA = 10000;

// compute mobius up to MAXA with a linear sieve
void mobius_sieve(vector<int>& mu) {
    mu.assign(MAXA+1, 0);
    vector<int> primes;
    vector<int> lp(MAXA+1, 0);
    mu[1] = 1;
    for (int i = 2; i <= MAXA; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            primes.push_back(i);
            mu[i] = -1;
        }
        for (int p : primes) {
            ll v = 1LL * p * i;
            if (v > MAXA) break;
            lp[v] = p;
            if (i % p == 0) {         // p^2 divides v
                mu[v] = 0;
                break;
            } else {
                mu[v] = -mu[i];
            }
        }
    }
}

// n choose 4, safe for n up to 10000 (returns 0 if n < 4)
inline ll C4(ll n) {
    if (n < 4) return 0;
    // compute as (n*(n-1)*(n-2)*(n-3))/24
    return (n * (n-1) / 2) * ((n-2) * (n-3) / 2) / 6; // rearranged to stay in ll range
    // alternative straightforward formula:
    // return n*(n-1)*(n-2)*(n-3)/24;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> mu;
    mobius_sieve(mu);

    int N;
    while ( (cin >> N) ) {
        vector<int> a(N);
        int maxval = 0;
        for (int i = 0; i < N; ++i) {
            cin >> a[i];
            maxval = max(maxval, a[i]);
        }
        if (maxval == 0) { // defensive (not really needed for given constraints)
            cout << 0 << '\n';
            continue;
        }

        // count occurrences of each exact value
        vector<int> cnt(maxval + 1, 0);
        for (int x : a) ++cnt[x];

        // for each d compute how many numbers are divisible by d
        vector<int> freq(maxval + 1, 0);
        for (int d = 1; d <= maxval; ++d) {
            for (int mult = d; mult <= maxval; mult += d) {
                freq[d] += cnt[mult];
            }
        }

        // apply mobius formula
        long long ans = 0;
        for (int d = 1; d <= maxval; ++d) {
            if (mu[d] == 0) continue;
            ll c = C4(freq[d]);
            ans += (ll)mu[d] * c;
        }

        cout << ans << '\n';
    }

    return 0;
}
