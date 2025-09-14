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
 
void dfs(ll i, ll j, ll n, ll m, vector<string> &v)
{
    if (i < 0 || j < 0 || i >= n || j >= m || v[i][j] == '#')
    {
        return;
    }
    v[i][j] = '#';
    dfs(i + 1, j, n, m, v);
    dfs(i - 1, j, n, m, v);
    dfs(i, j + 1, n, m, v);
    dfs(i, j - 1, n, m, v);
}
 
void solve()
{
    ll n, m;
    cin >> n >> m;
    vector<string> v(n);
    rep(i, n)
    {
        cin >> v[i];
    }
    ll ans = 0;
 
    rep(i, n)
    {
        rep(j, m)
        {
            if(v[i][j]=='.') {
                ans++;
                dfs(i, j, n, m, v);
            }
        }
    }
    print(ans);
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