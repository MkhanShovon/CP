#include<bits/stdc++.h>
using namespace std;

#define ll long long

struct item
{
    /* data */
    ll m,c;
};


struct seg_tree{
    ll size;
    vector<item> values;

    item merge(item a,item b){
        if(a.m<b.m) return a;
        else if(a.m>b.m) return b;
        else return {a.m,a.c+b.c};
    }
    item single(ll v){
        return {v,1};
    }

    item neutral_el= {LLONG_MAX,0};

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

int main(){
    ll n,m;
    cin>>n>>m;

    seg_tree st;
    st.init(n);
    vector<ll> a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    st.build(a);

    while(m--){
        ll op;
        cin>>op;
        if(op == 1){
            ll i,v;
            cin>>i>>v;
            st.set(i,v);
        }
        else{
            ll l,r;
            cin>>l>>r;
            auto res= st.calc(l,r);
            cout<<res.m<<" "<<res.c<<"\n";
        }
        
    }
}