#include <iostream>
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <typename T>
using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <typename T>
using omset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define Code ios_base::sync_with_stdio(false);
#define By cin.tie(NULL);
#define MaraKhaw cout.tie(NULL);

using ll = long long;
const ll mod = 1e9 + 7;

struct DSU {
    vector<ll> parent, size;
    
    DSU(ll n) {
        parent.resize(n + 1);
        size.resize(n + 1, 1);  // Initialize all sizes to 1

        for (ll i = 1; i <= n; ++i) {
            parent[i] = i;
        }
    }

    ll find(ll u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]); // Path Compression
        }
        return parent[u];
    }

    void unite(ll u, ll v) {
        ll rootU = find(u);
        ll rootV = find(v);

        if (rootU != rootV) {
            if (size[rootU] < size[rootV]) {
                swap(rootU, rootV);
            }
            parent[rootV] = rootU;
            size[rootU] += size[rootV];
        }
    }

    ll getSize(ll v) {
        return size[find(v)];
    }
};

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> edges(m);

    for (ll i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        edges[i] = {u, v, w};
    }

    ll ans = 0;
    for (ll i = 31; i >= 0; i--) {
        vector<vector<ll>> filtered_edges;
        DSU dsu(n);

        for (const auto &edge : edges) {
            if (!((edge[2] >> i) & 1)) {
                filtered_edges.push_back(edge);
                dsu.unite(edge[0], edge[1]);
            }
        }

        if (dsu.getSize(1) == n) {
            edges = move(filtered_edges);
        } else {
            ans |= (1 << i);
        }
    }

    cout << ans << '\n';
}

int main() {
    Code By MaraKhaw
    ll t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}