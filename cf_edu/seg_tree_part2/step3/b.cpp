//e(p2s2)
#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll mod=1e9+7;

struct seg_tree
{
    ll size;
    vector<ll> ops, vals;

    ll NEUTRAL_ELEMENT = 0,NO_OPERATION = 0;

    ll modify_op(ll a, ll b, ll len){
        if(b == NO_OPERATION) {
            // cout<<a<<" "<<b<<"Here\n";
            return a;
        }
        ll ans=0;
        if(len == 1){
            return b^a;
        }
        else{
            ans = len-a;
            return ans;
        }
    }

    ll calc_op(ll a, ll b){
        return a+b;
    }

    void apply_op(ll &a, ll b, ll len){
        a = modify_op(a,b,len);
    }

    void init(ll n)
    {
        size = 1;
        while (size < n)
            size *= 2;
        ops.assign(2 * size, NO_OPERATION);
        vals.assign(2 * size, 0LL);

        // build(0,0,size);
    }

    void propagate(ll x, ll lx, ll rx){
        if(rx-lx == 1){
            return;
        }

        ll m=(rx+lx)/2;
        if(ops[x] == NO_OPERATION){
            return;
        }
        apply_op(ops[2*x+1],ops[x],1);
        apply_op(vals[2*x+1],ops[x],m-lx);
        apply_op(ops[2*x+2],ops[x],1);
        apply_op(vals[2*x+2],ops[x],rx-m);
        ops[x] = NO_OPERATION;
    }

    void modify(ll l, ll r, ll x, ll lx, ll rx)
    {
        propagate(x,lx,rx);
        if (lx >= r or l >= rx)
        {
            return;
        }
        if (lx >= l and rx <= r)
        {
            ll v=1;
            apply_op(vals[x],v,rx-lx);
            apply_op(ops[x],v,1);
            return;
        }

        ll m = (lx + rx) / 2;
        modify(l, r, 2 * x + 1, lx, m);
        modify(l, r, 2 * x + 2, m, rx);
        vals[x] = calc_op(vals[2 * x + 1], vals[2 * x + 2]);
        
    }

    void modify(ll l, ll r)
    {
        modify(l, r, 0, 0, size);
    }

    ll find(ll k, ll x, ll lx, ll rx){
        propagate(x,lx,rx);
        if(rx-lx == 1){
            return lx;
        }
        ll m=(rx+lx)/2;
        ll res=0;
        if(vals[2*x+1]>k){
            res = find(k,2*x+1,lx,m);
        }
        else{
            res = find(k-vals[2*x+1],2*x+2,m,rx);
        }
        return res;
    }

    ll find(ll k){
        return find(k,0,0,size);
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
            ll l, r;
            cin >> l >> r;
            st.modify(l, r);
        }
        else
        {
            ll k;
            cin >> k;
            cout<<st.find(k)<<"\n";
        }
    }
}