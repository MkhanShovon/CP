#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define py cout << "YES\n"
#define pn cout << "NO\n"

class DSU
{
private:
    vector<int> parent, size, minElement, maxElement;
    ll n;

public:
    DSU(int n)
    {
        parent.resize(n + 2);
        size.resize(n + 1, 1); // Each element is its own set initially, so size is 1
        minElement.resize(n + 1);
        maxElement.resize(n + 1);
        this->n = n;
        parent[n + 1] = n+1;
        for (int i = 1; i <= n; ++i)
        {
            parent[i] = i;
            minElement[i] = i;
            maxElement[i] = i;
        }
    }

    int find(int u)
    {
        if (u>=0 and u <= n and parent[u] != u)
        {
            parent[u] = find(parent[u]); // Path Compression
        }
        return parent[u];
    }

    void unite(int u, int v)
    {
        ll rootU = find(u);

        ll rootV = find(v);

        parent[rootU] = rootV;
    }

    ll get(int v)
    {
        ll rootV = find(v);
        return rootV;
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
        char c;
        cin>>c;
        if(c=='?'){
            ll a;
            cin>>a;
            ll root = dsu.get(a);
            if(root==n+1){
                cout<<-1<<endl;
            }
            else{
                cout<<root<<endl;
            }
        }
        else{
            ll a;
            cin>>a;
            dsu.unite(a, a+1);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    ll t = 1;
    // cin>>t;
    while (t--)
    {
        solve();
    }
}
