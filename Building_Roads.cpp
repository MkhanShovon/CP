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
map<ll,vl>adj;
map<ll,bool>vis;
 
void dfs(ll node){
    vis[node]=true;
    for(auto child:adj[node]){
        if(!vis[child]){
            dfs(child);
        }
    }
}
 
void solve()
{
    ll n,m;
    cin>>n>>m;
    rep(i,m){
        ll a,b;
        cin>>a>>b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    ll cnt=0;
    vector<ll>ans;
    REP(i,1,n){
        if(!vis[i]){
            dfs(i);
            cnt++;
            ans.pb(i);
        }
    }
    print(cnt-1);
    rep(i,len(ans)-1){
        cout<<ans[i]<<" "<<ans[i+1]<<endl;
    }
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