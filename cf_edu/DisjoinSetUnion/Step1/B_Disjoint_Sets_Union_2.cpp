#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define py cout<<"YES\n"
#define pn cout<<"NO\n"

class DSU {
private:
    vector<int> parent, size, minElement, maxElement;
    
public:
    DSU(int n) {
        parent.resize(n + 1);
        size.resize(n + 1, 1);  // Each element is its own set initially, so size is 1
        minElement.resize(n + 1);
        maxElement.resize(n + 1);
        
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
            minElement[i] = i;
            maxElement[i] = i;
        }
    }

    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]); // Path Compression
        }
        return parent[u];
    }

    void unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        
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

    vector<ll> get(int v) {
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
    
    ll n,m;
    cin>>n>>m;
    DSU dsu(n);
    for(ll i=1;i<=m;i++){
        string s;
        cin>>s;
        if(s=="union"){
            ll a,b;
            cin>>a>>b;
            dsu.unite(a, b);
        }
        else{
            ll a;
            cin>>a;
            vector<ll> info = dsu.get(a);
            cout<<info[0]<<" "<< info[1]<<" "<< info[2]<<endl;
        }
    }
}

int main(){
    ll t=1;
    // cin>>t;
    while(t--){
        solve();
    }
}
