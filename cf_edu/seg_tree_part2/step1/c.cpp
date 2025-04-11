//similar to b(p2s1) : just added propagate and apply func ,and add=>modify,get first line propagate
#include<bits/stdc++.h>
using namespace std;

#define ll long long

struct seg_tree{
    ll size;
    vector<ll> ops;

    ll NO_OPERATION = LLONG_MAX;

    ll operation(ll a, ll b){//b is the operation to be performed first
        if(b == NO_OPERATION) return a;
        return b;
    }

    void init(ll n){
        size = 1;
        while(size < n) size *= 2;
        ops.assign(2*size, 0LL);
    }

    //x is the index of the current node

    void apply_op(ll &a, ll b){
        a = operation(a,b);
    }

    void propagate(ll x, ll lx, ll rx){
        if(rx-lx == 1){
            return;
        }
        apply_op(ops[2*x+1],ops[x]);
        apply_op(ops[2*x+2],ops[x]);
        ops[x] = NO_OPERATION;
    }

    void modify(ll l, ll r, ll v, ll x, ll lx, ll rx){
        propagate(x,lx,rx);
        if(lx>=r or l>=rx){
            return;
        }
        if(lx>=l and rx<=r){
            ops[x] = operation(ops[x],v);
            return;
        }

        ll m = (lx+rx)/2;
        modify(l,r,v,2*x+1,lx,m);
        modify(l,r,v,2*x+2,m,rx);
    }

    void modify(ll l, ll r, ll v){
        modify(l,r,v,0,0,size);
    }

    ll get(ll i, ll x, ll lx, ll rx){
        propagate(x,lx,rx);
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
        return res;
    }

    ll get(ll i){
        return get(i,0,0,size);
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
            st.modify(l,r,v);
        }
        else{
            ll i;
            cin>>i;
            cout<<st.get(i)<<"\n";
        }
        
    }
}