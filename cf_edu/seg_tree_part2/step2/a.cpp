// copied from a(p2s1)
#include <bits/stdc++.h>
using namespace std;

#define ll long long

struct seg_tree
{
    ll size;
    vector<ll> ops, mins;
    void init(ll n)
    {
        size = 1;
        while (size < n)
            size *= 2;
        ops.assign(2 * size, 0LL);
        mins.assign(2 * size, 0LL);
    }

    void add(ll l, ll r, ll v, ll x, ll lx, ll rx)
    {
        if (lx >= r or l >= rx)
        {
            return;
        }
        if (lx >= l and rx <= r)
        {
            ops[x] += v;
            mins[x] += v;
            return;
        }

        ll m = (lx + rx) / 2;
        add(l, r, v, 2 * x + 1, lx, m);
        add(l, r, v, 2 * x + 2, m, rx);
        mins[x] = min(mins[2 * x + 1], mins[2 * x + 2]) + ops[x];
    }

    void add(ll l, ll r, ll v)
    {
        add(l, r, v, 0, 0, size);
    }

    ll getmin(ll l, ll r, ll x, ll lx, ll rx){
        if(lx >= r or l >= rx){
            return LLONG_MAX;
        }
        if(lx >= l and rx <= r){
            return mins[x];
        }

        ll m = (lx+rx)/2;
        ll m1= getmin(l,r,2*x+1,lx,m);
        ll m2 = getmin(l,r,2*x+2,m,rx);
        return min(m1,m2)+ops[x];
    }

    ll getmin(ll l, ll r){
        return getmin(l,r,0,0,size);
    }
};

int main()
{
    ll n, m;
    cin >> n >> m;

    seg_tree st;
    st.init(n);

    while (m--)
    {
        ll op;
        cin >> op;
        if (op == 1)
        {
            ll l, r, v;
            cin >> l >> r >> v;
            st.add(l, r, v);
        }
        else
        {
            ll l,r;
            cin >> l>>r;
            cout << st.getmin(l,r) << "\n";
        }
    }
}