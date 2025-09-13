#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define py cout << "YES\n"
#define pn cout << "NO\n"

class DSU
{
private:
    vector<ll> parent, depth, par;
    ll n;
    vector<pair<ll, ll>> vis;

public:
    DSU(ll nn)
    {
        this->n = nn + 1;
        parent.resize(n + 1);
        par.resize(n + 1);
        // size.resize(n + 1, 1); // Each element is its own set initially, so size is 1
        // minElement.resize(n + 1);
        // maxElement.resize(n + 1);
        depth.resize(n + 1);
        vis.resize(n + 1);
        par.resize(n + 1);

        for (ll i = 1; i <= n; ++i)
        {
            parent[i] = i;
            par[i] = i;
            // minElement[i] = i;
            // maxElement[i] = i;
        }
    }

    ll find(ll u, ll child)
    {
        // cout<<u<<" "<<child<<endl;
        if (parent[u] != u)
        {
            ll p = parent[u];
            parent[u] = find(parent[u], u); // Path Compression
            if(par[u] == p){ // u is direct child of p
                depth[u] = depth[p] + 1;
            }
            else{
                depth[u] += depth[p]; // u is not direct child of p
            }
            // cout << u << " " << depth[u] << " " << p << " " << depth[p] << endl;
        }
        return parent[u];
    }

    void unite(ll u, ll v)
    {
        parent[u] = v;
        par[u] = v;
        // size[v] += size[u];
    }

    ll get(ll c)
    {
        ll root = find(c, c);
        return depth[c];
    }
};

// Code
void solve()
{
#ifndef ONLINE_JUDGE
    freopen("Error.txt", "w", stderr);
#endif

    ll n, m;
    cin >> n >> m;
    DSU dsu(n);
    for (ll i = 1; i <= m; i++)
    {
        ll t;
        cin >> t;
        if (t == 1)
        {
            ll a, b;
            cin >> a >> b;
            dsu.unite(a, b);
        }
        else
        {
            ll a;
            cin >> a;
            cout << dsu.get(a) << endl;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t = 1;
    // cin>>t;
    while (t--)
    {
        solve();
    }
}
