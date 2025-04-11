//similar to a(step 1)
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
    vector<ll> sums;
    void init(ll n){
        size = 1;
        while(size < n) size *= 2;
        sums.assign(2*size, 0LL);
    }

    //x is the index of the current node
    void build(vector<ll>&a,ll x,ll lx,ll rx){
        if(rx-lx == 1){
            if(lx < (ll)a.size()){
                sums[x] = sumofdigits(a[lx]);
            }
            return;
        }
        ll m = (lx+rx)/2;
        build(a,2*x+1,lx,m);
        build(a,2*x+2,m,rx);
        sums[x] = sums[2*x+1] + sums[2*x+2];
    }

    void build(vector<ll>&a){
        build(a,0,0,size);
    }

    void set(ll i,ll x,ll lx,ll rx){
        if(rx-lx == 1){
            sums[x] = 1-sums[x];
            return;
        }
        ll m = (lx+rx)/2;
        if(i<m){
            set(i,2*x+1,lx,m);
        }
        else{
            set(i,2*x+2,m,rx);
        }
        sums[x] = sums[2*x+1] + sums[2*x+2];
    }

    void set(ll i){
        set(i,0,0,size);
    }

    ll sum(ll l,ll r,ll x,ll lx,ll rx){
        if(lx >= r || l >= rx) return 0;
        if(lx >= l && rx <= r) return sums[x];
        ll m = (lx+rx)/2;
        ll s1 = sum(l,r,2*x+1,lx,m);
        ll s2 = sum(l,r,2*x+2,m,rx);
        return s1+s2;
    }

    ll sum(ll l,ll r){
        return sum(l,r,0,0,size);
    }

    ll find(ll k, ll x, ll lx, ll rx){
        if(rx-lx == 1){
            return lx;
        }
        ll m = (lx+rx)/2;
        ll s1 = sums[2*x+1];
        if(k<s1){
            return find(k,2*x+1,lx,m);
        }
        else{
            return find(k-s1,2*x+2,m,rx);
        }
    }

    ll find(ll k){
        return find(k,0,0,size);
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
            ll i;
            cin>>i;
            st.set(i);
        }
        else{
            ll k;
            cin>>k;
            cout<<st.find(k)<<"\n";
        }
        
    }
}