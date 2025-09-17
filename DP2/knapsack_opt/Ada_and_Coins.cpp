#include <bits/stdc++.h>
using namespace std;

#define ll long long int
const int maxN = 1e5 + 5;
/*
    how to solve this problem: (proof of correctness)
*/

bitset<maxN> bit;
int pref[maxN];

void dowork() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto &x : a) cin >> x;

    bit[0] = 1;

    sort(a.begin(), a.end());
    for (int i = 0; i < n; ++i) {
        bit |= (bit << a[i]);
    }

    for (int i = 0; i < maxN; ++i) {
        pref[i] = bit[i];
        if (i) pref[i] += pref[i - 1];
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << pref[r] - pref[l - 1] << '\n';
    }
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tt = 1;
    // cin >> tt;
    while (tt--) dowork();
    return 0;
}
