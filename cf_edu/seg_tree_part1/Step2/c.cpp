// similar to b(step 2)
#include <bits/stdc++.h>
using namespace std;

#define ll long long
struct seg_tree
{
    ll size;
    vector<ll> values;
    void init(ll n)
    {
        size = 1;
        while (size < n)
            size *= 2;
        values.assign(2 * size, 0LL);
    }

    void build(vector<ll> &a, ll x, ll lx, ll rx)
    {
        if (rx - lx == 1)
        {
            if (lx < (ll)a.size())
            {
                values[x] = a[lx];
            }
            return;
        }
        ll m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        values[x] = max(values[2 * x + 1], values[2 * x + 2]);
    }

    void build(vector<ll> &a)
    {
        build(a, 0, 0, size);
    }

    void set(ll i, ll v, ll x, ll lx, ll rx)
    {
        if (rx - lx == 1)
        {
            values[x] = v;
            return;
        }
        ll m = (lx + rx) / 2;
        if (i < m)
        {
            set(i, v, 2 * x + 1, lx, m);
        }
        else
        {
            set(i, v, 2 * x + 2, m, rx);
        }
        values[x] = max(values[2 * x + 1], values[2 * x + 2]);
    }

    void set(ll i, ll v)
    {
        set(i, v, 0, 0, size);
    }

    ll calc(ll v, ll x, ll lx, ll rx)
    {
        if(values[x]<v) return -1;
        if(rx-lx == 1){
            return lx;
        }
        ll m = (lx+rx)/2;
        ll res = calc(v, 2*x+1, lx, m);
        if(res == -1){
            res = calc(v, 2*x+2, m, rx);
        }
        return res;
    }

    ll calc(ll v)
    {
        return calc(v, 0, 0, size);
    }
};

int main()
{
    ll n, m;
    cin >> n >> m;

    seg_tree st;
    st.init(n);
    vector<ll> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    st.build(a);

    while (m--)
    {
        ll op;
        cin >> op;
        if (op == 1)
        {
            ll i, v;
            cin >> i >> v;
            st.set(i, v);
        }
        else
        {
            ll x;
            cin >> x;
            cout<<st.calc(x)<<"\n";
        }
    }
}