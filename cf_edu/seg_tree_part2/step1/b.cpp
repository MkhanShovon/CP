//similar to a(p2s1) : +=>max
#include<bits/stdc++.h>
using namespace std;

#define ll long long

ll sumofdigits(ll n){
    ll sum = 0;
    while(n){
        sum += n%10;
        n /= 10;
    }
    return sum;
}

struct seg_tree{
    ll size;
    vector<ll> ops;

    ll operation(ll a, ll b){
        return max(a,b);
    }

    void init(ll n){
        size = 1;
        while(size < n) size *= 2;
        ops.assign(2*size, 0LL);
    }

    //x is the index of the current node
    void build(vector<ll>&a,ll x,ll lx,ll rx){
        if(rx-lx == 1){
            if(lx < (ll)a.size()){
                ops[x] = sumofdigits(a[lx]);
            }
            return;
        }
        ll m = (lx+rx)/2;
        build(a,2*x+1,lx,m);
        build(a,2*x+2,m,rx);
        ops[x] = ops[2*x+1] + ops[2*x+2];
    }

    void build(vector<ll>&a){
        build(a,0,0,size);
    }

    ll get(ll i, ll x, ll lx, ll rx){
        if(rx-lx==1){
            return ops[x];
        }

        ll m = (lx+rx)/2;
        ll res;
        if(i<m){
            res= get(i,2*x+1,lx,m);
        }
        else{
            res = get(i,2*x+2,m,rx);
        }
        return operation(res,ops[x]);
    }

    ll get(ll i){
        return get(i,0,0,size);
    }

    void set(ll i,ll v,ll x,ll lx,ll rx){
        if(rx-lx == 1){
            ops[x] = v;
            return;
        }
        ll m = (lx+rx)/2;
        if(i<m){
            set(i,v,2*x+1,lx,m);
        }
        else{
            set(i,v,2*x+2,m,rx);
        }
        ops[x] = ops[2*x+1] + ops[2*x+2];
    }

    void set(ll i,ll v){
        set(i,v,0,0,size);
    }

    void add(ll l, ll r, ll v, ll x, ll lx, ll rx){
        if(lx>=r or l>=rx){
            return;
        }
        if(lx>=l and rx<=r){
            ops[x] = operation(ops[x],v);
            return;
        }

        ll m = (lx+rx)/2;
        add(l,r,v,2*x+1,lx,m);
        add(l,r,v,2*x+2,m,rx);
    }

    void add(ll l, ll r, ll v){
        add(l,r,v,0,0,size);
    }

    ll sum(ll l,ll r,ll x,ll lx,ll rx){
        if(lx >= r || l >= rx) return 0;
        if(lx >= l && rx <= r) return ops[x];
        ll m = (lx+rx)/2;
        ll s1 = sum(l,r,2*x+1,lx,m);
        ll s2 = sum(l,r,2*x+2,m,rx);
        return s1+s2;
    }

    ll sum(ll l,ll r){// l to r-1
        return sum(l,r,0,0,size);
    }

};

int main(){
    ll n,m;
    cin>>n>>m;

    seg_tree st;
    st.init(n);
    
    while(m--){
        ll op;
        cin>>op;
        if(op == 1){
            ll l,r,v;
            cin>>l>>r>>v;
            st.add(l,r,v);
        }
        else{
            ll i;
            cin>>i;
            cout<<st.get(i)<<"\n";
        }
        
    }
}