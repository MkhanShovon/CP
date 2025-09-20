#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
// linear sieve to compute mobius up to M (inclusive)
vector<int> mobius_sieve(int M) {
    vector<int> mu(M+1, 0), lp(M+1, 0), primes;
    if (M >= 1) mu[1] = 1;
    for (int i = 2; i <= M; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            primes.push_back(i);
            mu[i] = -1;
        }
        for (int p : primes) {
            long long v = 1LL * p * i;
            if (v > M) break;
            lp[v] = p;
            if (i % p == 0) {    // p^2 divides v
                mu[v] = 0;
                break;
            } else {
                mu[v] = -mu[i];
            }
        }
    }
    return mu;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n;
    if (!(cin >> n)) return 0;
    vector<int> a(n);
    int maxval = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        maxval = max(maxval, a[i]);
    }
 
    // compute mu up to maxval
    vector<int> mu = mobius_sieve(maxval);
 
    // count occurrences of each value
    vector<int> cnt(maxval + 1, 0);
    for (int x : a) ++cnt[x];
 
    // for each d compute how many numbers are divisible by d
    vector<int> freq(maxval + 1, 0);
    for (int d = 1; d <= maxval; ++d) {
        for (int j = d; j <= maxval; j += d) {
            freq[d] += cnt[j];
        }
    }
 
    // use mobius inversion: number of coprime pairs = sum_{d>=1} mu[d] * C(freq[d], 2)
    ll ans = 0;
    for (int d = 1; d <= maxval; ++d) {
        if (mu[d] == 0) continue;
        ll f = freq[d];
        ans += (ll)mu[d] * (f * (f - 1) / 2);
    }
 
    cout << ans << '\n';
    return 0;
}