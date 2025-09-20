#include <bits/stdc++.h>
using namespace std;

const int MOD = 1'000'000'007;
using int64 = long long;

int addmod(int a, int b){ a += b; if(a>=MOD) a-=MOD; return a; }
int submod(int a, int b){ a -= b; if(a<0) a+=MOD; return a; }
int mulmod(int64 a, int64 b){ return int((a*b) % MOD); }

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = (int)s.size();

    // counts of each letter
    vector<int> cnt(26,0);
    for(char ch : s) cnt[ch-'a']++;
    // remove zeros and sort descending (optional but reduces DP states)
    vector<int> freq;
    for(int x : cnt) if(x>0) freq.push_back(x);
    sort(freq.rbegin(), freq.rend());

    // Precompute binomial coefficients up to n (n <= 5000)
    const int MAXN = n + 5;
    vector<vector<int>> C(MAXN, vector<int>(MAXN,0));
    for(int i=0;i<MAXN;i++){
        C[i][0] = C[i][i] = 1;
        for(int j=1;j<i;j++){
            C[i][j] = addmod(C[i-1][j-1], C[i-1][j]);
        }
    }

    // dp[B] = number of ways to build sequences of B runs so far
    vector<int> dp(1, 1); // dp[0] = 1 (no runs initially)

    for(int x : freq){
        // new dp size: previous dp size + x (we can add up to x new runs)
        vector<int> ndp(dp.size() + x, 0);

        // iterate over current number of blocks 'B1' and possible splits 'b' (new runs)
        for(int B1 = 0; B1 < (int)dp.size(); ++B1){
            if(dp[B1] == 0) continue;
            for(int b = 1; b <= x; ++b){
                // ways to split x identical letters into b non-empty groups
                int waysSplit = C[x-1][b-1]; // C(x-1, b-1)
                // ways to interleave the b new runs with existing B1 runs
                int waysInter = C[B1 + b][b]; // C(B1 + b, b)
                int add = mulmod(dp[B1], mulmod(waysSplit, waysInter));
                ndp[B1 + b] = addmod(ndp[B1 + b], add);
            }
        }
        dp.swap(ndp);
    }

    // Final answer: alternating sum sum_B (-1)^{n-B} dp[B]
    int ans = 0;
    for(int B = 0; B < (int)dp.size(); ++B){
        if( (n - B) % 2 == 0 ) ans = addmod(ans, dp[B]);
        else ans = submod(ans, dp[B]);
    }

    cout << ans << "\n";
    return 0;
}
