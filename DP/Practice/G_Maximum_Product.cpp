#include <bits/stdc++.h>
using namespace std;

struct Node {
    bool zero;          // true if the product is 0 (some zero after start)
    long double val;    // sum of logs for digits > 0
    string s;           // built number (with padding)
};

const long double EPS = 1e-18L;

string A, B;
int n;
int vis[20][2][2][2];
Node dp[20][2][2][2];
int cs = 1;

inline Node better(const Node& a, const Node& b) {
    // Prefer non-zero product
    if (a.zero != b.zero) return a.zero ? b : a;
    // If both positive products, compare by sum of logs
    if (!a.zero) {
        if (a.val > b.val + EPS) return a;
        if (b.val > a.val + EPS) return b;
    }
    // Tie (both zero-product or equal log-sum): prefer the one that is actually built
    // Using longer length ensures we don't keep the initial empty candidate.
    if (a.s.size() != b.s.size()) return (a.s.size() > b.s.size()) ? a : b;
    // Any is fine
    return a;
}

Node go(int pos, int tightL, int tightR, int started) {
    if (pos == n) return {false, 0.0L, ""};
    int &mark = vis[pos][tightL][tightR][started];
    if (mark == cs) return dp[pos][tightL][tightR][started];
    mark = cs;

    int lo = tightL ? (A[pos]-'0') : 0;
    int hi = tightR ? (B[pos]-'0') : 9;

    Node ans = {true, 0.0L, ""}; // a dummy "worst": zero=true and empty string

    for (int d = lo; d <= hi; ++d) {
        int ns = started || (d != 0);
        int nL = tightL && (d == (A[pos]-'0'));
        int nR = tightR && (d == (B[pos]-'0'));

        Node sub = go(pos+1, nL, nR, ns);

        Node cand;
        cand.s = string(1, char('0' + d)) + sub.s;
        cand.zero = sub.zero || (ns && d == 0);
        cand.val  = sub.val + ((ns && d > 0) ? log((long double)d) : 0.0L);

        ans = better(ans, cand);
    }

    return dp[pos][tightL][tightR][started] = ans;
}

string stripLeadingZeros(const string& s) {
    size_t p = s.find_first_not_of('0');
    return (p == string::npos) ? string("0") : s.substr(p);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string a, b;
    if (!(cin >> a >> b)) return 0;

    // Pad a to the length of b on the left with zeros
    if (a.size() < b.size()) a = string(b.size() - a.size(), '0') + a;
    A = a; B = b; n = (int)B.size();

    ++cs;
    Node res = go(0, 1, 1, 0);

    // Remove padding zeros for printing
    cout << stripLeadingZeros(res.s) << "\n";
    return 0;
}
