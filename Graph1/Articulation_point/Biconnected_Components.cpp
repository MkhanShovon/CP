#include <iostream>
#include <bits/stdc++.h>
// #include <sys/resource.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace chrono;
using namespace __gnu_pbds;
template <typename T>
using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <typename T>
using omset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <typename T, typename R>
using o_map = tree<T, R, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// Pragmas
#pragma GCC optimize("O3,unroll-loops")
// #ifndef LOCAL_PROJECT
// #pragma GCC target("avx2")
// #endif
// #pragma GCC optimize("Ofast")

// Speed
inline void FastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

// Aliases
using ll = long long;
using lld = long double;
using ull = unsigned long long;

// Constants
const lld pi = 3.141592653589793238;
const ll INF = LONG_LONG_MAX;
const ll mod = 1e9 + 7;

// TypeDEf
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<pll> vpll;
typedef vector<string> vs;
typedef unordered_map<ll, ll> umll;
typedef map<ll, ll> mll;

// Macros
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define fl(i, n) for (ll i = 0; i < n; i++)
#define fls(i, m, n) for (ll i = m; i <= n; i++)
#define rl(i, m, n) for (ll i = n; i >= m; i--)
#define py cout << "Yes\n";
#define pm cout << "-1\n";
#define pn cout << "No\n";
#define vr(v) v.begin(), v.end()
#define rv(v) v.rbegin(), v.rend()
#define edl '\n'
#define len(v) v.size()
#define nl cout << edl;

// Debug
void __print(int x) { cerr << x; }
void __print(long x) { cerr << x; }
void __print(long long x) { cerr << x; }
void __print(unsigned x) { cerr << x; }
void __print(unsigned long x) { cerr << x; }
void __print(unsigned long long x) { cerr << x; }
void __print(float x) { cerr << x; }
void __print(double x) { cerr << x; }
void __print(long double x) { cerr << x; }
void __print(char x) { cerr << '\'' << x << '\''; }
void __print(const char *x) { cerr << '"' << x << '"'; }
void __print(const string &x) { cerr << '"' << x << '"'; }
void __print(bool x) { cerr << (x ? "true" : "false"); }

template <typename T, typename V>
void __print(const pair<T, V> &x)
{
    cerr << '{';
    __print(x.first);
    cerr << ',';
    __print(x.second);
    cerr << '}';
}
template <typename T>
void __print(const T &x)
{
    int f = 0;
    cerr << '{';
    for (auto &i : x)
        cerr << (f++ ? "," : ""), __print(i);
    cerr << "}";
}
void _print() { cerr << "]\n"; }
template <typename T, typename... V>
void _print(T t, V... v)
{
    __print(t);
    if (sizeof...(v))
        cerr << ", ";
    _print(v...);
}
#ifndef ONLINE_JUDGE
#define debug(x...)               \
    cerr << "[" << #x << "] = ["; \
    _print(x)
#else
#define debug(x...)
#endif

// Operator overloads
template <typename T1, typename T2> // cin >> pair<T1, T2>
istream &operator>>(istream &istream, pair<T1, T2> &p)
{
    return (istream >> p.first >> p.second);
}
template <typename T> // cin >> vector<T>
istream &operator>>(istream &istream, vector<T> &v)
{
    for (auto &it : v)
        cin >> it;
    return istream;
}
template <typename T1, typename T2> // cout << pair<T1, T2>
ostream &operator<<(ostream &ostream, const pair<T1, T2> &p)
{
    return (ostream << p.first << " " << p.second);
}
template <typename T> // cout << vector<T>
ostream &operator<<(ostream &ostream, const vector<T> &c)
{
    for (auto &it : c)
        cout << it << " ";
    return ostream;
}

// Utility functions
#define print(x) cout << x << '\n'

template <typename T>
ll sumvec(vector<T> v)
{
    ll n = v.size();
    ll s = 0;
    fl(i, n) s += v[i];
    return s;
}

long long rng()
{
    static std::mt19937 gen(
        std::chrono::steady_clock::now().time_since_epoch().count());
    return std::uniform_int_distribution<long long>(0, INT64_MAX)(gen);
}

void preSolve()
{
    // rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
    // allocateStackMax();
}

const int N = 5e5 + 9;

int T, low[N], dis[N], art[N], sz;
vector<int> g[N], bcc[N], st;
void dfs(int u, int pre = 0)
{
    low[u] = dis[u] = ++T;
    st.push_back(u);
    for (auto v : g[u])
    {
        if (!dis[v])
        {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dis[u])
            {
                sz++;
                int x;
                do
                {
                    x = st.back();
                    st.pop_back();
                    bcc[x].push_back(sz);
                } while (x ^ v);
                bcc[u].push_back(sz);
            }
        }
        else if (v != pre)
            low[u] = min(low[u], dis[v]);
    }
}

int dep[N], par[N][20], cnt[N], id[N];
vector<int> bt[N];
void dfs1(int u, int pre = 0)
{
    dep[u] = dep[pre] + 1;
    cnt[u] = cnt[pre] + art[u];
    par[u][0] = pre;
    for (int k = 1; k <= 18; k++)
        par[u][k] = par[par[u][k - 1]][k - 1];
    for (auto v : bt[u])
        if (v != pre)
            dfs1(v, u);
}

int lca(int u, int v)
{
    if (dep[u] < dep[v])
        swap(u, v);
    for (int k = 18; k >= 0; k--)
        if (dep[par[u][k]] >= dep[v])
            u = par[u][k];
    if (u == v)
        return u;
    for (int k = 18; k >= 0; k--)
        if (par[u][k] != par[v][k])
            u = par[u][k], v = par[v][k];
    return par[u][0];
}

int dist(int u, int v)
{
    int lc = lca(u, v);
    return cnt[u] + cnt[v] - 2 * cnt[lc] + art[lc];
}

// Code
void solve() {
    int n, m;
    cin >> n >> m;

    // reset only what's needed for this test
    T = 0;
    for (int i = 1; i <= n; ++i) {
        g[i].clear();
        low[i] = dis[i] = 0;
        bcc[i].clear();
    }
    sz = 0; // will count ONLY biconnected components

    // read edges (0-indexed in input) -> make them 1-indexed
    while (m--) {
        int u, v; cin >> u >> v;
        ++u; ++v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // run Tarjan (vertex-BCC) on every component
    for (int i = 1; i <= n; ++i) {
        if (!dis[i]) {
            dfs(i);
            // optional: if you prefer to flush singleton root-leftovers,
            // you could handle here; but we'll handle singletons after DFS.
        }
    }

    // Build component lists from bcc[u]
    // 1..sz are component IDs created during dfs()
    vector<vector<int>> comps(sz + 1);

    for (int u = 1; u <= n; ++u) {
        if (bcc[u].empty()) {
            // isolated vertex (or never assigned): create a singleton component
            comps.push_back(vector<int>{u - 1});
            ++sz;
        } else {
            for (int c : bcc[u]) comps[c].push_back(u - 1); // back to 0-index for output
        }
    }

    cout << sz << '\n';
    for (int c = 1; c <= sz; ++c) {
        if (comps[c].empty()) continue; // guard
        cout << (int)comps[c].size();
        for (int v : comps[c]) cout << ' ' << v;
        cout << '\n';
    }
}

// Main
signed main()
{
    // #ifndef ONLINE_JUDGE
    //     freopen("Error.txt", "w", stderr);
    // #endif
    FastIO();
    preSolve();
    ll t = 1;
    // cin >> t;
    fl(i, t)
    {
        solve();
    }
    // solve();
    // fl(i,t) //Kickstart
    // {
    //     cout<<"Case #"<<i+1<<": ";
    //     solve();
    //     cout<<"\n";
    // }
    return 0;
}
// End