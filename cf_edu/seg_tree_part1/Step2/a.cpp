//similar to c(step 1)
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct item
{
    ll seg, pref, suf, sum;
};


struct seg_tree{
    ll size;
    vector<item> values;

    item neutral_el = {LLONG_MIN, LLONG_MIN, LLONG_MIN, 0};

    item single(ll v)
    {
        if (v > 0)
        {
            return {v, v, v, v};
        }
        else
        {
            return {0, 0, 0, v};
        }
    }

    item merge(item a, item b)
    {
        return {
            max({a.seg, b.seg, a.suf + b.pref}),
            max(a.pref, a.sum + b.pref),
            max(b.suf, b.sum + a.suf),
            a.sum + b.sum};
    }

    void init(ll n){
        size = 1;
        while(size < n) size *= 2;
        values.resize(2*size);
    }

    void build(vector<ll>&a,ll x,ll lx,ll rx){
        if(rx-lx == 1){
            if(lx < (ll)a.size()){
                values[x] = single(a[lx]);
            }
            return;
        }
        ll m = (lx+rx)/2;
        build(a,2*x+1,lx,m);
        build(a,2*x+2,m,rx);
        values[x] = merge(values[2*x+1] , values[2*x+2]);
    }

    void build(vector<ll>&a){
        build(a,0,0,size);
    }

    void set(ll i,ll v,ll x,ll lx,ll rx){
        if(rx-lx == 1){
            values[x] =single(v);
            return;
        }
        ll m = (lx+rx)/2;
        if(i<m){
            set(i,v,2*x+1,lx,m);
        }
        else{
            set(i,v,2*x+2,m,rx);
        }
        values[x] = merge(values[2*x+1] , values[2*x+2]);
    }

    void set(ll i,ll v){
        set(i,v,0,0,size);
    }

    item calc(ll l,ll r,ll x,ll lx,ll rx){
        if(lx >= r || l >= rx) return neutral_el;
        if(lx >= l && rx <= r) return values[x];
        ll m = (lx+rx)/2;
        item s1 = calc(l,r,2*x+1,lx,m);
        item s2 = calc(l,r,2*x+2,m,rx);
        return merge(s1,s2);
    }

    item calc(ll l,ll r){
        return calc(l,r,0,0,size);
    }

};

int main()
{
    ll n,m;
    cin>>n>>m;
    seg_tree st;
    st.init(n);
    vector<ll>a(n);
    for(ll i=0;i<n;i++){
        cin>>a[i];
    }
    st.build(a);
    cout<<st.calc(0, n).seg<<endl;
    while(m--){
        ll i,v;
        cin>>i>>v;
        st.set(i, v);
        cout<<st.calc(0, n).seg<<endl;
    }
}
