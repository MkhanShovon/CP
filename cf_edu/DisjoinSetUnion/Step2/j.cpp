#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define py cout << "YES\n"
#define pn cout << "NO\n"

class DSU
{
private:
    vector<ll> size, minElement, maxElement, len;
    vector<pair<ll, ll>> parent;
    ll n;

public:
    DSU(ll nn)
    {
        this->n = nn + 1;
        parent.resize(n + 1);
        size.resize(n + 1, 1); // Each element is its own set initially, so size is 1
        minElement.resize(n + 1);
        maxElement.resize(n + 1);

        for (ll i = 1; i <= n; ++i)
        {
            parent[i] = {i, -1};
            minElement[i] = i;
            maxElement[i] = i;
        }
    }

    pair<ll, ll> find(ll u)
    {
        if (parent[u].first == u)
        {
            return parent[u];
        }
        auto p = find(parent[u].first);
        parent[u].first = p.first;
        parent[u].second = (parent[u].second + p.second) % 2;
        return parent[u];
    }

    void unite(ll u, ll v)
    {
        auto pu = find(u), pv = find(v);
        if (pu.first != pv.first)
        {
            if (size[pu.first] < size[pv.first])
            {
                swap(pu, pv);
            }
            parent[pv.first] = {pu.first, (pu.second + pv.second + 1) % 2};
            size[pu.first] += size[pv.first];
        }
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
    ll shift = 0;
    vector<pair<ll, ll>> edges;
    for (ll i = 0; i < m; i++)
    {
        ll a, b;
        cin >> a >> b;
        edges.push_back({a, b});
    }
    // cout<<" ok"<<endl;
    for (ll i = 1; i <= m; i++)
    {
        ll a, b;
        a = edges[i - 1].first, b = edges[i - 1].second;
        auto pa = dsu.find(a), pb = dsu.find(b);
        if (pa.second == pb.second)
        {
            cout << i << endl;
            cout << pa.first << " " << pb.first << endl;
            return;
        }
        else
        {
            dsu.unite(a, b);
        }
    }
    cout << -1 << endl;
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
