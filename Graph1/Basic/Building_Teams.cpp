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
 
void solve()
{
    ll n, m;
    cin >> n >> m;
    map<ll, vl> adj;
    map<ll, bool> vis;
    rep(i, m)
    {
        ll a, b;
        cin >> a >> b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    map<ll, ll> color;
    bool flag = true;
    function<void(ll, ll)> dfs = [&](ll node, ll c)
    {
        vis[node] = true;
        color[node] = c;
        for (auto child : adj[node])
        {
            if (!vis[child])
            {
                {
                    dfs(child, c ^ 1);
                }
            }
            else
            {
                if (color[child] == color[node])
                {
                    flag = false;
                }
            }
        }
    };
    REP(i, 1, n)
    {
        if (!vis[i])
        {
            dfs(i, 0);
        }
    }
    if (!flag)
    {
        print("IMPOSSIBLE");
        return;
    }
    REP(i, 1, n)
    {
        cout << color[i] + 1 << " ";
    }
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