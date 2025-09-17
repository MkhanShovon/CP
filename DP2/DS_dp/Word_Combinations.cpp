#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll MOD = 1'000'000'007;

struct Node {
    array<int, 26> nxt;
    bool leaf = false;
    Node() { nxt.fill(-1); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S;
    int N;
    if (!(cin >> S >> N)) return 0;

    vector<Node> trie(1); // root = 0

    auto add_word = [&](const string& w) {
        int v = 0;
        for (char ch : w) {
            int c = ch - 'a';
            if (trie[v].nxt[c] == -1) {
                trie[v].nxt[c] = (int)trie.size();
                trie.emplace_back();
            }
            v = trie[v].nxt[c];
        }
        trie[v].leaf = true;
    };

    for (int i = 0; i < N; ++i) {
        string w; 
        cin >> w;
        add_word(w);
    }

    int M = (int)S.size();
    vector<ll> dp(M + 1, 0);
    dp[M] = 1; // empty suffix

    for (int i = M - 1; i >= 0; --i) {
        int v = 0;
        for (int j = i; j < M; ++j) {
            int c = S[j] - 'a';
            if (trie[v].nxt[c] == -1) break;
            v = trie[v].nxt[c];
            if (trie[v].leaf) {
                dp[i] += dp[j + 1];
                if (dp[i] >= MOD) dp[i] -= MOD;
            }
        }
    }

    cout << dp[0] << '\n';
    return 0;
}
