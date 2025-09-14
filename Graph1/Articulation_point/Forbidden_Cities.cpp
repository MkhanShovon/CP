#include <bits/stdc++.h>
using namespace std;

// Build BCCs and block–cut tree.
// id[v] = node index in block–cut tree (C-node for cutpoint v, B-node for non-cutpoint v)
// is_cutpoint[v] marks articulation vertices.
vector<vector<int>> biconnected_components(const vector<vector<int>>& g,
                                           vector<bool>& is_cutpoint, vector<int>& id) {
    int n = (int)g.size();
    vector<int> num(n, 0), low(n, 0), stk;
    vector<vector<int>> comps;
    is_cutpoint.assign(n, false);

    int timer = 0;

    function<void(int,int)> dfs = [&](int u, int p) {
        num[u] = low[u] = ++timer;
        stk.push_back(u);
        int child_cnt = 0;

        for (int v : g[u]) {
            if (v == p) continue;
            if (num[v]) {
                low[u] = min(low[u], num[v]);
            } else {
                ++child_cnt;
                dfs(v, u);
                low[u] = min(low[u], low[v]);

                if (low[v] >= num[u]) {
                    if (p != -1) is_cutpoint[u] = true;
                    // pop one BCC containing u..v side
                    vector<int> comp;
                    comp.push_back(u);
                    while (!stk.empty()) {
                        int w = stk.back(); stk.pop_back();
                        comp.push_back(w);
                        if (w == v) break;
                    }
                    comps.push_back(move(comp));
                }
            }
        }
        if (p == -1 && child_cnt >= 2) is_cutpoint[u] = true;
    };

    for (int u = 0; u < n; ++u)
        if (!num[u]) dfs(u, -1);

    // Build block–cut tree
    // Node order: (dummy 0), then all cutpoints, then all components
    vector<vector<int>> T(1);
    id.assign(n, -1);
    int node_id = 0;

    // Assign C-nodes
    for (int u = 0; u < n; ++u) if (is_cutpoint[u]) {
        id[u] = ++node_id;
        T.push_back({});
    }

    // Assign B-nodes and connect
    for (auto& comp : comps) {
        int b = ++node_id;
        T.push_back({});
        for (int u : comp) {
            if (is_cutpoint[u]) {
                T[b].push_back(id[u]);
                T[id[u]].push_back(b);
            } else {
                id[u] = b;
            }
        }
    }
    return T;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int x, y; cin >> x >> y; --x; --y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    vector<bool> is_cutpoint;
    vector<int> id;
    auto T = biconnected_components(g, is_cutpoint, id);

    int V = (int)T.size();
    // Build LCA (forest-safe)
    int LOG = 1;
    while ((1<<LOG) <= V) ++LOG;

    vector<int> depth(V, 0), vis(V, 0);
    vector<vector<int>> up(V, vector<int>(LOG, 0));

    function<void(int,int)> dfs2 = [&](int u, int p) {
        vis[u] = 1;
        up[u][0] = (p == -1 ? u : p);
        for (int j = 1; j < LOG; ++j)
            up[u][j] = up[ up[u][j-1] ][j-1];
        for (int v : T[u]) if (v != p) {
            depth[v] = depth[u] + 1;
            dfs2(v, u);
        }
    };

    for (int u = 0; u < V; ++u) if (!vis[u] && !T[u].empty()) dfs2(u, -1);

    auto lca = [&](int a, int b) {
        if (a == -1 || b == -1) return -1;
        if (depth[a] < depth[b]) swap(a, b);
        int diff = depth[a] - depth[b];
        for (int j = LOG - 1; j >= 0; --j)
            if (diff & (1<<j)) a = up[a][j];
        if (a == b) return a;
        for (int j = LOG - 1; j >= 0; --j) {
            if (up[a][j] != up[b][j]) {
                a = up[a][j];
                b = up[b][j];
            }
        }
        return up[a][0];
    };

    auto on_path = [&](int x, int y, int z) {
        int r = lca(x, y);
        int rx = lca(x, z);
        int ry = lca(y, z);
        if (z == r) return true;
        return (rx == z && ry == r) || (ry == z && rx == r);
    };

    while (q--) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b; --c;

        if (a == c || b == c) { cout << "NO\n"; continue; }
        if (!is_cutpoint[c]) { cout << "YES\n"; continue; }

        int A = id[a], B = id[b], C = id[c];
        // If A or B is -1 (isolated vertex), fallback: only same vertex reachable.
        if (A == -1 || B == -1) { cout << (a == b ? "YES\n" : "NO\n"); continue; }

        cout << (on_path(A, B, C) ? "NO\n" : "YES\n");
    }
}
