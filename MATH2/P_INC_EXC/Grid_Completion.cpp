#include <bits/stdc++.h>
using namespace std;
using int64 = long long;
const int MOD = 1000000007;

int64 addmod(int64 a, int64 b){ a += b; if(a >= MOD) a -= MOD; return a; }
int64 submod(int64 a, int64 b){ a -= b; if(a < 0) a += MOD; return a; }
int64 mulmod(int64 a, int64 b){ return (a * b) % MOD; }
int64 powmod(int64 a, int64 e){
    int64 r = 1;
    while(e){
        if(e & 1) r = mulmod(r, a);
        a = mulmod(a, a);
        e >>= 1;
    }
    return r;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if(!(cin >> n)) return 0;
    vector<string> s(n);
    for(int i = 0; i < n; ++i) cin >> s[i];

    // Build directed graph on 2n vertices:
    // 0..n-1 : rows (left part)
    // n..2n-1: cols (right part)
    vector<vector<int>> out(2*n), in(2*n);
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(s[i][j] == 'A'){
                out[i].push_back(j + n);
                in[j + n].push_back(i);
            } else if(s[i][j] == 'B'){
                out[j + n].push_back(i);
                in[i].push_back(j + n);
            }
        }
    }

    // Count component patterns used in the combinatorial formula.
    // For left part (rows) we gather three counts:
    //  cntL0 = isolated vertices (no in and no out)
    //  cntL1 = vertices with exactly one outgoing edge, no incoming, and the target has no outgoing (i.e. single-edge component starting here)
    //  cntL2 = vertices with no outgoing (used later)
    int cntL0 = 0, cntL1 = 0, cntL2 = 0;
    for(int i = 0; i < n; ++i){
        if(out[i].empty() && in[i].empty()) ++cntL0;
        if((int)out[i].size() == 1 && in[i].empty() && out[out[i][0]].empty()) ++cntL1;
        if(out[i].empty()) ++cntL2;
    }

    // Similarly for right part (columns)
    int cntR0 = 0, cntR1 = 0, cntR2 = 0;
    for(int i = n; i < 2*n; ++i){
        if(out[i].empty() && in[i].empty()) ++cntR0;
        if((int)out[i].size() == 1 && in[i].empty() && out[out[i][0]].empty()) ++cntR1;
        if(out[i].empty()) ++cntR2;
    }

    // Precompute factorials and binomials up to n.
    vector<int64> fact(n+1,1), invfact(n+1,1);
    for(int i = 1; i <= n; ++i) fact[i] = mulmod(fact[i-1], i);
    invfact[n] = powmod(fact[n], MOD-2);
    for(int i = n; i >= 1; --i) invfact[i-1] = mulmod(invfact[i], i);

    auto C = [&](int a, int b)->int64{
        if(b < 0 || b > a) return 0;
        return mulmod(fact[a], mulmod(invfact[b], invfact[a-b]));
    };

    int64 answer = 0;

    // Iterate over three parameters described below:
    // fr = number of 2-cycles we make by pairing isolated left/right vertices
    // z1 = number of 2-cycles formed by choosing some left single-edge components
    // z2 = number of 2-cycles formed by choosing some right single-edge components
    //
    // After choosing those, the remaining "free" vertices on left and right
    // (with no outgoing edges) must be permuted: factorial(l) * factorial(r).
    for(int fr = 0; fr <= min(cntL0, cntR0); ++fr){
        for(int z1 = 0; z1 <= cntL1; ++z1){
            for(int z2 = 0; z2 <= cntR1; ++z2){
                // remaining vertices with no outgoing edges
                int Lrem = cntL2 - fr - z2;
                int Rrem = cntR2 - fr - z1;
                if(Lrem < 0 || Rrem < 0) continue;

                int64 ways = 1;
                // choose fr isolated left and fr isolated right, pair them into fr cycles:
                ways = mulmod(ways, C(cntL0, fr));
                ways = mulmod(ways, C(cntR0, fr));
                ways = mulmod(ways, fact[fr]); // number of pairings (fr!)

                // choose z1 left single-edge components and z2 right single-edge components
                ways = mulmod(ways, C(cntL1, z1));
                ways = mulmod(ways, C(cntR1, z2));

                // permutations of remaining free vertices on left and right
                ways = mulmod(ways, fact[Lrem]);
                ways = mulmod(ways, fact[Rrem]);

                // sign: if number of chosen 2-cycles (fr + z1 + z2) is odd, subtract, else add.
                if(((fr + z1 + z2) & 1) == 0) answer = addmod(answer, ways);
                else answer = submod(answer, ways);
            }
        }
    }

    cout << answer % MOD << "\n";
    return 0;
}
