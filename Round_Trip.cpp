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
    int n = v.size();
    rep(i, n)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}
map<ll, vl> adj;
map<ll, ll> vis, par;
 
void dfs(ll node)
{
    vis[node] = 1;
    for (auto child : adj[node])
    {
        if (!vis[child])
        {
            par[child] = node;
            dfs(child);
        }
        else if (vis[child] == 1 && child != par[node])
        {
            vector<ll> ans;
            ans.pb(child);
            ll cur = node;
            while (cur != child)
            {
                ans.pb(cur);
                cur = par[cur];
            }
            ans.pb(child);
            reverse(all(ans));
            print(len(ans));
            printv(ans);
            exit(0);
        }
    }
}
 
void solve()
{
    ll n, m;
    cin >> n >> m;
    rep(i, m)
    {
        ll a, b;
        cin >> a >> b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    REP(i, 1, n)
    {
        if (!vis[i])
        {
            dfs(i);
        }
    }
    print("IMPOSSIBLE");
}
 
signed main()
{
    fast;
    ll t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
}