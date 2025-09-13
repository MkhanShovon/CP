#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    int z = 0;
    for (char c : s)
        if (c == '0')
            z++;
    int ones_in_left = 0;
    for (int i = 0; i < z; i++)
        if (s[i] == '1')
            ones_in_left++;
    cout << ones_in_left << endl;
}

int main()
{
    int t;
    cin >> t;
    for (int test = 0; test < t; test++)
    {
        solve();
    }
    return 0;
}