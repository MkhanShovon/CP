//a(step 1)
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

};

int main(){
    ll n;
    cin>>n;
    vector<ll> a(2*n),vis(n+1,-1);
    for(ll i=0;i<2*n;i++){
        cin>>a[i];
    }

    seg_tree st;
    st.init(2*n);
    vector<ll> ans(n);
    for(ll i=0;i<2*n;i++){
        if(vis[a[i]] == -1){
            vis[a[i]] = i;
            st.set(i,1);
        }
        else{
            ans[a[i]-1] += st.sum(vis[a[i]]+1,i);
            st.set(vis[a[i]],0);
        }
    }

    // for(ll i=0;i<n;i++){
    //     cout<<ans[i]<<" ";
    // }
    // cout<<"\n";

    seg_tree st2;
    st2.init(2*n);
    vis.clear();
    vis.resize(n+1,-1);
    for(ll i=2*n-1;i>=0;i--){
        if(vis[a[i]] == -1){
            vis[a[i]] = i;
            // cout<<a[i]<<" "<<i<<"\n";
            st2.set(i,1);
        }
        else{
            st2.set(vis[a[i]],0);
            ans[a[i]-1] += st2.sum(i,vis[a[i]]);
        }
    }
    for(ll i=0;i<n;i++){
        cout<<ans[i]<<" ";
    }
    cout<<"\n";
}