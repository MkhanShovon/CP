#include <bits/stdc++.h>
using namespace std;
 
int main() {
    // int T=1; cin >> T;
    int T=1;
    while (T--) {
        int n1; cin >> n1;
        string s;
        cin >> s;
        string ch = "";
        for (char c: s) {
            if (c == '1')
                ch += '0';
            else
                ch += '1';
        }
        s += '#';
        s += ch;
        int n = (int) s.size();
        vector<int> pr(n);
        pr[0] = 0;
        for (int i = 1; i < n; i++) {
            int j = pr[i - 1];
            while (j > 0 && s[j] != s[i])
                j = pr[j - 1];
            if (s[i] == s[j])
                j++;
            pr[i] = j;
        }
        for (int i = n1 + 1; i < n; i++) {
            cout << pr[i] << ' ';
        }
        cout << '\n';
    }
}