//d(p2s2)
#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll mod=1e9+7;

struct seg_tree
{
    ll size;
    vector<ll> ops, vals;

    ll NEUTRAL_ELEMENT = LLONG_MAX,NO_OPERATION = LLONG_MAX-1;

    ll modify_op(ll a, ll b, ll len){
        if(b == NO_OPERATION) return a;
        return b;
    }

    ll calc_op(ll a, ll b){
        return min(a,b);
    }

    void apply_op(ll &a, ll b, ll len){
        a = modify_op(a,b,len);
    }

    void init(ll n)
    {
        size = 1;
        while (size < n)
            size *= 2;
        ops.assign(2 * size, 0LL);
        vals.assign(2 * size, 0LL);

        // build(0,0,size);
    }

    void propagate(ll x, ll lx, ll rx){
        if(rx-lx == 1){
            return;
        }
        ll m=(rx+lx)/2;
        apply_op(ops[2*x+1],ops[x],1);
        apply_op(vals[2*x+1],ops[x],m-lx);
        apply_op(ops[2*x+2],ops[x],1);
        apply_op(vals[2*x+2],ops[x],rx-m);
        ops[x] = NO_OPERATION;
    }

    void modify(ll l, ll r, ll v, ll x, ll lx, ll rx)
    {
        propagate(x,lx,rx);
        if (lx >= r or l >= rx)
        {
            return;
        }
        if (lx >= l and rx <= r)
        {
            apply_op(vals[x],v,rx-lx);
            apply_op(ops[x],v,1);
            return;
        }

        ll m = (lx + rx) / 2;
        modify(l, r, v, 2 * x + 1, lx, m);
        modify(l, r, v, 2 * x + 2, m, rx);
        vals[x] = calc_op(vals[2 * x + 1], vals[2 * x + 2]);
        
    }

    void modify(ll l, ll r, ll v)
    {
        modify(l, r, v, 0, 0, size);
    }

    ll calc(ll l, ll r, ll x, ll lx, ll rx){
        propagate(x,lx,rx);
        if(lx >= r or l >= rx){
            return NEUTRAL_ELEMENT;
        }
        if(lx >= l and rx <= r){
            return vals[x];
        }

        ll m = (lx+rx)/2;
        ll m1= calc(l,r,2*x+1,lx,m);
        ll m2 = calc(l,r,2*x+2,m,rx);
        auto res = calc_op(m1,m2);
        
        return res;
    }

    ll calc(ll l, ll r){
        return calc(l,r,0,0,size);
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
            st.modify(l, r, v);
        }
        else
        {
            ll l,r;
            cin >> l>>r;
            cout << st.calc(l,r) << "\n";
        }
    }
}