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

struct SqrtRangeAddRangeQuery {
    int n, B, numBlocks;
    std::vector<long long> a;      // base values
    std::vector<long long> lazy;   // lazy add per block
    std::vector<long long> blockSum; // sum of each block (excluding lazy)

    SqrtRangeAddRangeQuery(const std::vector<long long>& arr) {
        n = (int)arr.size();
        B = (int)std::floor(std::sqrt(std::max(1, n))) + 1; // block size
        numBlocks = (n + B - 1) / B;
        a = arr;
        lazy.assign(numBlocks, 0);
        blockSum.assign(numBlocks, 0);

        // Initialize block sums
        for (int i = 0; i < n; ++i) {
            blockSum[i / B] += a[i];
        }
    }

    // Add u to [l, r] (0-indexed)
    void add(int l, int r, long long u) {
        int bl = l / B, br = r / B;
        if (bl == br) {
            for (int i = l; i <= r && i < n; ++i) {
                a[i] += u;
                blockSum[bl] += u;
            }
            return;
        }

        // Left tail
        int leftEnd = (bl + 1) * B - 1;
        for (int i = l; i <= leftEnd && i < n; ++i) {
            a[i] += u;
            blockSum[bl] += u;
        }

        // Whole blocks
        for (int b = bl + 1; b <= br - 1; ++b) {
            lazy[b] += u;
            blockSum[b] += u * (std::min(n, (b + 1) * B) - b * B);
        }

        // Right tail
        for (int i = br * B; i <= r && i < n; ++i) {
            a[i] += u;
            blockSum[br] += u;
        }
    }

    // Get value at position k (0-indexed)
    long long getPoint(int k) const {
        return a[k] + lazy[k / B];
    }

    // Get sum of range [l, r] (0-indexed)
    long long getRange(int l, int r) const {
        long long sum = 0;
        int bl = l / B, br = r / B;

        if (bl == br) {
            for (int i = l; i <= r && i < n; ++i) {
                sum += a[i] + lazy[bl];
            }
            return sum;
        }

        // Left tail
        int leftEnd = (bl + 1) * B - 1;
        for (int i = l; i <= leftEnd && i < n; ++i) {
            sum += a[i] + lazy[bl];
        }

        // Whole blocks
        for (int b = bl + 1; b <= br - 1; ++b) {
            sum += blockSum[b] + lazy[b] * (std::min(n, (b + 1) * B) - b * B);
        }

        // Right tail
        for (int i = br * B; i <= r && i < n; ++i) {
            sum += a[i] + lazy[br];
        }

        return sum;
    }
};

// Code
void solve()
{
    ll n;
    ll q;
    cin >> n >> q;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    // debug(a);
    ll len = (ll)sqrt(n + .0) + 1; // size of the block and the number of blocks
    vector<ll> b(len);
    // for (ll i = 0; i < n; ++i)
    //     b[i / len] += a[i];

    SqrtRangeAddRangeQuery sq(a);
    // answering the queries
    while (q--)
    {
        ll t;
        cin >> t;
        if(t == 1){
            ll l, r, val;
            cin >> l >> r >> val;
            l--, r--;
            sq.add(l, r, val);
        }
        else{
            ll k;
            cin >> k;
            print(sq.getPoint(k - 1));
        }
        
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