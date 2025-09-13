#include <iostream>
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define fl(i, n) for (ll i = 0; i < n; i++)
void solve()
{

    ll n;
    cin >> n;
    
    list<ll> dll;
    fl(i, n){
        string cmd;
        cin >> cmd;
        if(cmd == "insert"){
            ll x;
            cin >> x;
            dll.push_front(x);
        }
        else if(cmd == "delete"){
            ll x;
            cin >> x;
            for(auto it = dll.begin(); it != dll.end(); it++){
                if(*it == x){
                    dll.erase(it);
                    break;
                }
            }
        }
        else if(cmd == "deleteFirst"){
            dll.pop_front();
        }
        else if(cmd == "deleteLast"){
            dll.pop_back();
        }
    }
    ll sz = dll.size();
    for (auto it = dll.begin(); it != dll.end(); ) {
        cout << *it;
        if (++it != dll.end()) cout << ' ';
    }
    cout << '\n';
}
// Main
signed main()
{
    // #ifndef ONLINE_JUDGE
    //     freopen("Error.txt", "w", stderr);
    // #endif
    // FastIO();
    // preSolve();
    ll t = 1;
    // cin >> t;
    fl(i, t)
    {
        solve();
    }
    // solve();
    // fl(i,t) //Kickstart
    // {
    //     cout<<"Case #"<<i+1<<": ";
    //     solve();
    //     cout<<"\n";
    // }
    return 0;
}
// End