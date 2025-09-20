#include <iostream>
#include <bits/stdc++.h>
// #include <sys/resource.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;

using ll = long long;
const ll VALMAX = 1e7;
ll mobius[VALMAX];

void mob_init()
{
    mobius[1] = -1;
    for (ll i = 1; i < VALMAX; i++)
    {
        if (mobius[i])
        {
            mobius[i] = -mobius[i];
            for (ll j = 2 * i; j < VALMAX; j += i)
            {
                mobius[j] += mobius[i];
            }
        }
    }
}

// Code
void solve()
{

    ll n;
    cin >> n;
    
    ll ans = 0;
    for(ll i = 1; i * i <= n; i++){
        ans += mobius[i] * n / (i * i);
    }

    cout << ans << endl;
}
// Main
signed main()
{
    
    mob_init();
    ll t = 1;
    cin >> t;
    while(t--)
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