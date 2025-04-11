#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define py cout << "YES\n"
#define pn cout << "NO\n"

class DSU
{
private:
    vector<ll> parent, size, minElement, maxElement;
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
            parent[i] = i;
            minElement[i] = i;
            maxElement[i] = i;
        }
    }

    ll find(ll u)
    {
        if (parent[u] != u)
        {
            parent[u] = find(parent[u]); // Path Compression
        }
        return parent[u];
    }

    void unite(ll u, ll v)
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
            minElement[rootU] = min(minElement[rootU], minElement[rootV]);
            maxElement[rootU] = max(maxElement[rootU], maxElement[rootV]);
        }
    }

    tuple<int, int, int> get(int v)
    {
        int rootV = find(v);
        return {minElement[rootV], maxElement[rootV], size[rootV]};
    }
};

// Code
void solve()
{
#ifndef ONLINE_JUDGE
    freopen("Error.txt", "w", stderr);
#endif

    ll n, m, k;
    cin >> n >> m >> k;
    DSU dsu(n);

    for (ll i = 0; i < m; i++)
    {
        ll u, v;
        cin >> u >> v;
    }

    vector<vector<ll>> d;

    for (ll i = 0; i < k; i++)
    {
        string s;
        ll l, r;
        cin >> s >> l >> r;
        if (s == "cut")
        {
            d.push_back({1, l, r});
        }
        else
        {
            d.push_back({0, l, r});
        }
    }

    reverse(d.begin(), d.end());
    vector<ll>ans;
    for (ll i = 0; i < k; i++)
    {
        if(d[i][0] == 1){
            dsu.unite(d[i][1],d[i][2]);
        }
        else{
            ans.push_back(dsu.find(d[i][1]) == dsu.find(d[i][2]));
        }
    }
    reverse(ans.begin(), ans.end());

    for(ll i = 0; i < ans.size(); i++)
    {
        if(ans[i]){
            cout<<"YES\n";
        }
        else{
            cout<<"NO\n";
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
