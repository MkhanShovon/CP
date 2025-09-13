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
 
// Pragmas
// #pragma GCC optimize("O3,unroll-loops")
// #ifndef LOCAL_PROJECT
// #pragma GCC target("avx2")
// #endif
#pragma GCC optimize("Ofast")
 
// Speed
#define Code ios_base::sync_with_stdio(false);
#define By cin.tie(NULL);
#define MaraKhaw cout.tie(NULL);
 
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
#define py cout << "YES\n";
#define pm cout << "-1\n";
#define pn cout << "NO\n";
#define vr(v) v.begin(), v.end()
#define rv(v) v.rbegin(), v.rend()
#define edl '\n'
#define len(v) v.size()
#define nl cout<<edl;
 
// Debug
#ifndef ONLINE_JUDGE
#define debug(x)       \
    cerr << #x << " "; \
    _print(x);         \
    cerr << endl;
#else
#define debug(x)
#endif
 
// Custom hash map
struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
 
    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
template <typename T1, typename T2> // Key should be integer type
using safe_map = unordered_map<T1, T2, custom_hash>;
 
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
 
// template <typename T, typename... Args>
// void print(T &&t, Args &&...args)
// {
//     cout << t << " ";
//     print(forward<Args>(args)...);
// }
 
template <typename T>
int32_t size_i(T &container) { return static_cast<int32_t>(container.size()); }
 
void printarr(ll arr[], ll n)
{
    fl(i, n) cout << arr[i] << " ";
    cout << "\n";
}
template <typename T>
void printvec(vector<T> v)
{
    ll n = v.size();
    fl(i, n) cout << v[i] << " ";
    cout << "\n";
}
 
template <typename T>
ll sumvec(vector<T> v)
{
    ll n = v.size();
    ll s = 0;
    fl(i, n) s += v[i];
    return s;
}
 
// Mathematical functions
ll gcd(ll a, ll b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
} //__gcd
 
int GCD_extended(int a, int b, int &x, int &y)
{
    x = 1, y = 0;
    int x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1)
    {
        int q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}
 
ll lcm(ll a, ll b) { return (a / gcd(a, b) * b); }
ll moduloMultiplication(ll a, ll b, ll mod) // (a * b) % mod
{
    ll res = 0; // Initialize result
    a %= mod;  // Update a if it is more than or equal to mod
    
    while (b)
    {
        // If b is odd, add 'a' to result
        if (b & 1)
            res = (res + a) % mod;
 
        // Here we ensure 'a' does not overflow by doubling it and taking modulo
        a = (a * 2) % mod;
 
        // Right shift b by 1
        b >>= 1;
    }
    return res;
}
 
ll modpow(ll x, ll n, int m = mod)
{
    if (x == 0 && n == 0)
        return 0; // undefined case
    ll res = 1;
    while (n > 0)
    {
        if (n % 2)
            res = (res * x) % m;
        x = (x * x) % m;
        n /= 2;
    }
    return res;
}
 
int modinv(int x, int m = mod)
{
    return modpow(x, m - 2, m);
}
mt19937 rng;
int getRandomNumber(int l, int r)
{
    uniform_int_distribution<int> dist(l, r);
    return dist(rng);
}
 
// Sorting
bool sorta(const pair<int, int> &a, const pair<int, int> &b) { 
    if(a.first==b.first)
        return a.second<b.second;
    return a.first<b.first; 
}
bool sortd(const pair<int, int> &a, const pair<int, int> &b) { 
    if(a.first==b.first)
        return a.second>b.second;
    return a.first>b.first; 
}
 
bool sortad(const pair<int, int> &a, const pair<int, int> &b) { 
    if(a.first==b.first)
        return a.second>b.second;
    return a.first<b.first; 
}
 
bool sortda(const pair<int, int> &a, const pair<int, int> &b) { 
    if(a.first==b.first)
        return a.second<b.second;
    return a.first>b.first; 
}
 
// Bits
string decToBinary(int n)
{
    string s = "";
    int i = 0;
    while (n > 0)
    {
        s = to_string(n % 2) + s;
        n = n / 2;
        i++;
    }
    return s;
}
ll binaryToDecimal(string n)
{
    string num = n;
    ll dec_value = 0;
    int base = 1;
    int len = num.length();
    for (int i = len - 1; i >= 0; i--)
    {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }
    return dec_value;
}
 
// Check
bool isPrime(ll n)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    for (int i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    return true;
}
bool isPowerOfTwo(int n)
{
    if (n == 0)
        return false;
    return (ceil(log2(n)) == floor(log2(n)));
}
bool isPerfectSquare(ll x)
{
    if (x >= 0)
    {
        ll sr = sqrt(x);
        return (sr * sr == x);
    }
    return false;
}
 
// void allocateStackMax()
// {
//     rlimit R;
//     getrlimit(RLIMIT_STACK, &R);
//     R.rlim_cur = R.rlim_max;
//     setrlimit(RLIMIT_STACK, &R);
// }
 
void preSolve()
{
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
    // allocateStackMax();
}
 
ll mex1(vll v)
{
    ll n = v.size();
    sort(vr(v));
    if(v[0]!=0)
        return 0;
    fl(i, n - 1)
    {
        if (v[i + 1] - v[i] > 1)
            return v[i] + 1;
    }
    return v[n - 1] + 1;
}
 
ll mex2(vll v){
    sort(vr(v));
    ll mx=0;
    fl(i,v.size()){
        if(v[i]==mx){
            mx++;
        }
    }
    return mx;
}
 
// Comparator for the priority_queue
struct Compare {
    bool operator()(const pll& a, const pll& b) {
        // First sort by the first element in descending order
        if (a.first != b.first)
            return a.first < b.first;
        // If first elements are equal, sort by the second element in ascending order
        return a.second > b.second;
    }
};
 
struct seg_tree {
    ll size;
    vector<ll> op1s, vals, operations2;
    vector<bool> has_op1;
 
    ll NEUTRAL_ELEMENT = 0, NO_OPERATION = 0;
 
    void init(ll n) {
        size = 1;
        while (size < n)
            size *= 2;
        op1s.assign(2 * size, 0LL);
        vals.assign(2 * size, 0LL);
        operations2.assign(2 * size, 0LL);
        has_op1.assign(2 * size, false);
    }
 
    void apply_op1(ll &a, ll b, ll len) {
        a = b * len;
    }
 
    void apply_operations2(ll &a, ll b, ll len) {
        a += b * len;
    }
 
    void propagate(ll x, ll lx, ll rx) {
        if (rx - lx == 1) return;
 
        ll m = (lx + rx) / 2;
 
        if (has_op1[x]) {
            apply_op1(vals[2 * x + 1], op1s[x], m - lx);
            apply_op1(op1s[2 * x + 1], op1s[x], 1);
            operations2[2 * x + 1] = 0;
            has_op1[2 * x + 1] = true;
 
            apply_op1(vals[2 * x + 2], op1s[x], rx - m);
            apply_op1(op1s[2 * x + 2], op1s[x], 1);
            operations2[2 * x + 2] = 0;
            has_op1[2 * x + 2] = true;
 
            has_op1[x] = false;
            op1s[x] = NO_OPERATION;
        }
 
        if (operations2[x] != NO_OPERATION) {
            apply_operations2(vals[2 * x + 1], operations2[x], m - lx);
            apply_operations2(operations2[2 * x + 1], operations2[x], 1);
 
            apply_operations2(vals[2 * x + 2], operations2[x], rx - m);
            apply_operations2(operations2[2 * x + 2], operations2[x], 1);
 
            operations2[x] = NO_OPERATION;
        }
    }
 
    void modify1(ll l, ll r, ll v, ll x, ll lx, ll rx) {
        propagate(x, lx, rx);
        if (lx >= r or l >= rx) return;
        if (lx >= l and rx <= r) {
            apply_op1(vals[x], v, rx - lx);
            op1s[x] = v;
            has_op1[x] = true;
            operations2[x] = 0;
            return;
        }
        ll m = (lx + rx) / 2;
        modify1(l, r, v, 2 * x + 1, lx, m);
        modify1(l, r, v, 2 * x + 2, m, rx);
        vals[x] = vals[2 * x + 1] + vals[2 * x + 2];
    }
 
    void modify1(ll l, ll r, ll v) {
        modify1(l, r, v, 0, 0, size);
    }
 
    void modify2(ll l, ll r, ll v, ll x, ll lx, ll rx) {
        propagate(x, lx, rx);
        if (lx >= r or l >= rx) return;
        if (lx >= l and rx <= r) {
            apply_operations2(vals[x], v, rx - lx);
            operations2[x] += v;
            return;
        }
        ll m = (lx + rx) / 2;
        modify2(l, r, v, 2 * x + 1, lx, m);
        modify2(l, r, v, 2 * x + 2, m, rx);
        vals[x] = vals[2 * x + 1] + vals[2 * x + 2];
    }
 
    void modify2(ll l, ll r, ll v) {
        modify2(l, r, v, 0, 0, size);
    }
 
    ll calc(ll l, ll r, ll x, ll lx, ll rx) {
        propagate(x, lx, rx);
        if (lx >= r or l >= rx) return NEUTRAL_ELEMENT;
        if (lx >= l and rx <= r) return vals[x];
        ll m = (lx + rx) / 2;
        ll m1 = calc(l, r, 2 * x + 1, lx, m);
        ll m2 = calc(l, r, 2 * x + 2, m, rx);
        return m1 + m2;
    }
 
    ll calc(ll l, ll r) {
        return calc(l, r, 0, 0, size);
    }
};
 
 
 
// Code
void solve()
{
#ifndef ONLINE_JUDGE
    freopen("Error.txt", "w", stderr);
#endif
    
    ll n,q;
    cin>>n>>q;
    seg_tree st;
    st.init(n);
    fl(i,n){
        ll x;
        cin>>x;
        st.modify1(i,i+1,x);
    }
    fl(i,q){
        ll t;
        cin>>t;
        if(t==1){
            ll l,r,v;
            cin>>l>>r>>v;
            st.modify2(l-1,r,v);
        }
        else if(t==2){
            ll l,r,v;
            cin>>l>>r>>v;
            st.modify1(l-1,r,v);
        }
        else{
            ll l,r;
            cin>>l>>r;
            print(st.calc(l-1,r));
        }
    }
}
// Main
signed main()
{
    Code By MaraKhaw
    preSolve();
    ll t=1;
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
