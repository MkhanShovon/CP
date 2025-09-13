#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define py cout << "YES\n"
#define pn cout << "NO\n"

class DSU
{
private:
    vector<ll> parent, size, minElement, maxElement, points;
    ll n;

public:
    DSU(ll nn)
    {
        n = nn + 1;
        parent.resize(n + 1);
        size.resize(n + 1, 1); // Each element is its own set initially, so size is 1
        minElement.resize(n + 1);
        maxElement.resize(n + 1);
        points.resize(n + 1);

        for (ll i = 1; i <= n; ++i)
        {
            parent[i] = i;
            minElement[i] = i;
            maxElement[i] = i;
        }
    }

    ll find(ll u)
    {
        return (parent[u] == u ? u : find(parent[u]));
    }

    void unite(ll u,ll  v)
    {
        ll rootU = find(u);
        ll rootV = find(v);

        if (rootU != rootV)
        {
            // Union by Size
            if (size[rootU] < size[rootV])
            {
                swap(rootU, rootV); // Ensure rootU is always the larger set
            }

            parent[rootV] = rootU; // Merge the smaller set into the larger set
            size[rootU] += size[rootV];
            points[rootV] -= points[rootU];
            minElement[rootU] = min(minElement[rootU], minElement[rootV]);
            maxElement[rootU] = max(maxElement[rootU], maxElement[rootV]);
        }
    }

    ll get(ll v)
    {
        ll p = points[v];

        while (v != parent[v])
        {
            v = parent[v];
            p += points[v];
        }
        return p;
    }

    void add(ll x, ll v)
    {
        ll p = find(x);
        points[p] += v;
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
        string s;
        cin >> s;
        if (s == "join")
        {
            ll a, b;
            cin >> a >> b;
            dsu.unite(a, b);
        }
        else if (s == "add")
        {
            ll a, v;
            cin >> a >> v;
            dsu.add(a, v);
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
