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

template <typename T>
class SparseTable {
private:
    int n, K;
    vector<int> lg2;            // floor(log2) table
    vector<vector<T>> st;       // st[k][i] covers [i, i + 2^k - 1]
    function<T(const T&, const T&)> combine;
    T identity;
    bool idempotent;            // if true -> O(1) queries, else O(log N)

    void build(const vector<T>& a) {
        n = (int)a.size();
        if (n == 0) return;

        // precompute logs
        lg2.assign(n + 1, 0);
        for (int i = 2; i <= n; ++i) lg2[i] = lg2[i / 2] + 1;

        K = lg2[n] + 1;
        st.assign(K, vector<T>(n));
        // base layer
        for (int i = 0; i < n; ++i) st[0][i] = a[i];
        // build
        for (int k = 1; k < K; ++k) {
            int len = 1 << k;
            for (int i = 0; i + len <= n; ++i) {
                st[k][i] = combine(st[k-1][i], st[k-1][i + (len >> 1)]);
            }
        }
    }

public:
    // Constructor: (identity, combine, array, idempotent?)
    SparseTable(const T& identity_,
                function<T(const T&, const T&)> combine_,
                const vector<T>& a,
                bool idempotent_ = true)
        : combine(move(combine_)), identity(identity_), idempotent(idempotent_) {
        build(a);
    }

    // Optional ctor mirroring your SegmentTree example signature
    SparseTable(size_t /*n_unused*/,
                const T& identity_,
                function<T(const T&, const T&)> combine_,
                const vector<T>& a,
                bool idempotent_ = true)
        : combine(move(combine_)), identity(identity_), idempotent(idempotent_) {
        build(a);
    }

    // Query on inclusive range [l, r]
    T query(int l, int r) const {
        if (l > r || l < 0 || r >= n) throw out_of_range("Invalid query range");
        if (idempotent) {
            int len = r - l + 1;
            int k = lg2[len];
            // two overlapping blocks of length 2^k
            return combine(st[k][l], st[k][r - (1 << k) + 1]);
        } else {
            // disjoint power-of-two decomposition (left to right)
            T res = identity;
            int pos = l;
            int len = r - l + 1;
            for (int k = 0; len > 0; ++k) {
                if (len & 1) {
                    res = combine(res, st[k][pos]);
                    pos += (1 << k);
                }
                len >>= 1;
            }
            return res;
        }
    }

    int size() const { return n; }
};

// Code
void solve()
{

    ll n;
    cin >> n;
    ll m;
    cin >> m;
    vll v(n);
    cin >> v;

    vll dif;
    fl(i, n - 1){
        dif.pb(abs(v[i] - v[i + 1]));
    }

    SparseTable<ll> st(
        0, [](ll a, ll b) { return gcd(a, b);}, dif, true
    );
    // debug(dif);
    fl(i, m){
        ll l, r;
        cin >> l >> r;
        l--, r--;
        ll from = l, to = max(l, r - 1);
        if(l == r){
            cout<< 0 << " ";
            continue;
        }
        cout << st.query(from, to) << " ";
    }
    nl;
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
    cin >> t;
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