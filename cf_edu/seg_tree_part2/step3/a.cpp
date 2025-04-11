// f(p2s2)
#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll mod = 1e9 + 7;

struct item
{
    ll sum, pref, suf, seg;
};

struct seg_tree
{
    ll size;
    vector<item> vals, ops;

    item NEUTRAL_ELEMENT = {0, 0, 0, 0}, NO_OPERATION ={LLONG_MIN,
                                                        LLONG_MIN,
                                                        LLONG_MIN,
                                                        LLONG_MIN};

    item single(ll v){
        // cout<<v<<"\n";
        return {v, 0, 0, 0};
    }

    item merge(item a, item b){
        return {
            a.sum+b.sum,
            max(a.pref,a.sum+b.pref),
            max(b.suf,b.sum+a.suf),
            max(max(a.seg,b.seg),a.suf+b.pref)
        };
    }

    item modify_op(item a, item b, ll len)
    {
        if (b.pref == NO_OPERATION.pref and b.suf == NO_OPERATION.suf and b.sum == NO_OPERATION.sum and b.seg == NO_OPERATION.seg)
        {
            return a;
        }
        else
        {
            if(b.sum>0){
                b.pref = b.suf = b.seg = b.sum*len;
            }
            else{
                b.pref = b.suf = b.seg = 0;
            }
            b.sum*=len;
            // cout<<len<<"\n";
            return b;
        }
    }

    item calc_op(item a, item b)
    {
        return merge(a, b);
    }

    void apply_op(item &a, item b, ll len)
    {
        a = modify_op(a, b, len);
    }

    void init(ll n)
    {
        size = 1;
        while (size < n)
        {
            size *= 2;
        }
        ops.assign(2 * size, NO_OPERATION);
        vals.assign(2 * size, NEUTRAL_ELEMENT);

        // build(0,0,size);
    }

    void propagate(ll x, ll lx, ll rx)
    {
        if (rx - lx == 1)
        {
            return;
        }

        ll m = (rx + lx) / 2;
        if(ops[x].pref == NO_OPERATION.pref and ops[x].sum == NO_OPERATION.sum
        and ops[x].suf == NO_OPERATION.suf and ops[x].seg == NO_OPERATION.seg) return;
        apply_op(ops[2 * x + 1], ops[x], 1);
        apply_op(vals[2 * x + 1], ops[x], m - lx);
        apply_op(ops[2 * x + 2], ops[x], 1);
        apply_op(vals[2 * x + 2], ops[x], rx - m);
        ops[x] = NO_OPERATION;
    }

    void modify(ll l, ll r, ll v, ll x, ll lx, ll rx)
    {
        propagate(x, lx, rx);
        if (lx >= r or l >= rx)
        {
            return;
        }
        if (lx >= l and rx <= r)
        {
            item temp = single(v);
            apply_op(vals[x], temp, rx - lx);
            apply_op(ops[x], temp, 1);
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

    item calc(ll l, ll r, ll x, ll lx, ll rx)
    {
        propagate(x, lx, rx);
        if (lx >= r or l >= rx)
        {
            return NEUTRAL_ELEMENT;
        }
        if (lx >= l and rx <= r)
        {
            return vals[x];
        }

        ll m = (lx + rx) / 2;
        item m1 = calc(l, r, 2 * x + 1, lx, m);
        item m2 = calc(l, r, 2 * x + 2, m, rx);
        auto res = calc_op(m1, m2);

        return res;
    }

    item calc(ll l, ll r)
    {
        return calc(l, r, 0, 0, size);
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
        ll l,r,v;
        cin>>l>>r>>v;
        st.modify(l,r,v);
        cout<<st.calc(0,n).seg<<"\n";
    }
}