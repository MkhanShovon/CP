#include <bits/stdc++.h>
using namespace std;
 
typedef pair<long long, long long> pll;
typedef vector<pll> vp;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<ll> vl;
#define pb push_back
#define len(s) (int)s.size()
#define print(x) cout << x << '\n'
#define nl cout << '\n'
#define REP(i, a, b) for (int i = a; i <= b; i++)
#define rep(i, n) for (int i = 0; i < n; i++)
#define all(a) (a).begin(), (a).end()
#define fast                          \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);
#define py print("YES")
#define pn print("NO");
#define pk print("OK");
#define mp make_pair
 
void printv(vector<ll> v)
{
    int n=v.size();
    rep(i, n)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}
 
void solve()
{
    ll n,m;
    cin>>n>>m;
    map<ll,vl>adj;
    map<ll,bool>vis;
    rep(i,m){
        ll a,b;
        cin>>a>>b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    map<ll,ll>parent;
    queue<ll>q;
    q.push(1);
    vis[1]=true;
    while(!q.empty()){
        ll node=q.front();
        q.pop();
        for(auto child:adj[node]){
            if(!vis[child]){
                vis[child]=true;
                q.push(child);
                parent[child]=node;
            }
        }
    }
    if(!vis[n]){
        print("IMPOSSIBLE");
        return;
    }
    vl ans;
    ans.pb(n);
    ll node=n;
    while(node!=1){
        node=parent[node];
        ans.pb(node);
    }
    reverse(all(ans));
    print(len(ans));
    printv(ans);
    
}
 
signed main()
{
    fast;
    ll t=1;
    //cin >> t;
    while (t--)
    {
        solve();
    }
}