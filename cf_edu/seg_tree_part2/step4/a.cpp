// e(p2s2)
#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll mod = 1e9 + 7;

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

int main()
{
    ll n, m;
    cin >> n >> m;

    seg_tree st;
    st.init(n+1);

    while (m--)
    {
        ll op;
        cin >> op;
        if (op == 1)
        {
            ll l, r, v;
            cin >> l >> r >> v;
            st.modify1(l, r, v);
        }
        else if (op == 2)
        {
            ll l, r, v;
            cin >> l >> r >> v;
            st.modify2(l, r, v);
        }
        else
        {
            ll l, r;
            cin >> l >> r;
            cout << st.calc(l, r) << "\n";
        }

        // cout<<"Vals: ";
        // for(auto i:st.vals){
        //     cout<<i<<" ";
        // }
        // cout<<"\n";
    }
}