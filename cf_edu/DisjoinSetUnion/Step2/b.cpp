#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define py cout << "YES\n"
#define pn cout << "NO\n"

class DSU {
private:
    vector<ll> parent, size, minElement, maxElement;
    ll n;
    
public:
    DSU(ll nn) {
        this->n = nn+1;
        parent.resize(n + 1);
        size.resize(n + 1, 1);  // Each element is its own set initially, so size is 1
        minElement.resize(n + 1);
        maxElement.resize(n + 1);
        
        for (ll i = 1; i <= n; ++i) {
            parent[i] = i;
            minElement[i] = i;
            maxElement[i] = i;
        }
    }

    ll find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]); // Path Compression
        }
        return parent[u];
    }

    void unite(int u, int v) {
        ll rootU = find(u);
        ll rootV = find(v);
        
        if (rootU != rootV) {
            // Union by Size
            if (size[rootU] < size[rootV]) {
                swap(rootU, rootV);  // Ensure rootU is always the larger set
            }

            parent[rootV] = rootU;  // Merge the smaller set into the larger set
            size[rootU] += size[rootV];
            minElement[rootU] = min(minElement[rootU], minElement[rootV]);
            maxElement[rootU] = max(maxElement[rootU], maxElement[rootV]);
        }
    }

    tuple<int, int, int> get(int v) {
        int rootV = find(v);
        return {minElement[rootV], maxElement[rootV], size[rootV]};
    }

    ll getmax(int v) {
        int rootV = find(v);
        return maxElement[rootV];
    }
};

// Code
void solve()
{
#ifndef ONLINE_JUDGE
    freopen("Error.txt", "w", stderr);
#endif

    ll n;
    cin >> n;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    DSU dsu(n);
    // cout << "why\n";
    for (ll i = 0; i < n; i++)
    {
        ll x = dsu.getmax(a[i]);
        if(x == n+1){
            x = dsu.getmax(1);
        }
        cout << x << " ";
        dsu.unite(x, x+1);
    }
    cout<<endl;
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
