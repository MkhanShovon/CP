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

    void set(ll i,ll v,ll x,ll lx,ll rx){
        if(rx-lx == 1){
            sums[x] = v;
            return;
        }
        ll m = (lx+rx)/2;
        if(i<m){
            set(i,v,2*x+1,lx,m);
        }
        else{
            set(i,v,2*x+2,m,rx);
        }
        sums[x] = sums[2*x+1] + sums[2*x+2];
    }

    void set(ll i,ll v){
        set(i,v,0,0,size);
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

    ll findId(ll sm,ll x,ll lx,ll rx){
        if(rx-lx == 1){
            return lx;
        }
        ll m = (lx+rx)/2;
        ll s2 = sums[2*x+2];
        if(sm <= s2){
            return findId(sm, 2*x+2, m, rx);
        }
        else{
            return findId(sm-s2, 2*x+1, lx, m);
        }
    }

    ll findId(ll sm){
        return findId(sm, 0, 0, size);
    }

};

int main(){
    ll n;
    cin>>n;
    vector<ll> a(n),ans(n);
    for(ll i=0;i<n;i++){
        cin>>a[i];
    }
    seg_tree st;
    st.init(n+1);
    for(ll i=1;i<=n;i++){
        st.set(i,1);
    }
    for(ll i=n-1;i>=0;i--){
        ll id = st.findId(a[i]+1);
        ans[i] = id;
        st.set(id,0);
    }
    for(ll i=0;i<n;i++){
        cout<<ans[i]<<" ";
    }
    cout<<"\n";
}