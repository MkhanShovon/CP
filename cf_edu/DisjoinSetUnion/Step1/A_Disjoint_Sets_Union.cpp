#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define py cout<<"YES\n"
#define pn cout<<"NO\n"

map<ll,ll> par,sz;

void make(ll n){
    par[n]=n;
    sz[n]=1;

}

ll find(ll n){
    if(par[n]==n) return n;
    return par[n]=find(par[n]);
}

void Union(ll a,ll b){
    a=find(a);
    b=find(b);
    if(a==b) return;
    if(sz[a]<sz[b]) swap(a,b);
    par[b]=a;
    sz[a]+=sz[b];
}



// Code
void solve()
{
#ifndef ONLINE_JUDGE
    freopen("Error.txt", "w", stderr);
#endif
    
    ll n,m;
    cin>>n>>m;
    for(ll i=1;i<=n;i++){
        make(i);
    }
    for(ll i=1;i<=m;i++){
        string s;
        cin>>s;
        if(s=="union"){
            ll a,b;
            cin>>a>>b;
            Union(a,b);
        }
        else{
            ll a,b;
            cin>>a>>b;
            if(find(a)==find(b)){
                py;
            }
            else{
                pn;
            }
        }
    }
}

int main(){
    ll t=1;
    // cin>>t;
    while(t--){
        solve();
    }
}
