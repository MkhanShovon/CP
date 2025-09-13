/*
Given a 2D N×M (N, M ≤ 2000) array.
You will be given Q (1e5) queries such that you will be given two A×B non-overlapping sub-rectangles and have to swap them.
After all these queries print the array
*/

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val = 0;
    Node *right = nullptr, *down = nullptr;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    if (!(cin >> N >> M)) return 0;

    // Build (N+1) x (M+1) grid with dummy row/col at index 0
    vector<vector<Node>> g(N + 1, vector<Node>(M + 1));
    for (int i = 0; i <= N; ++i)
        for (int j = 0; j <= M; ++j) {
            if (j < M) g[i][j].right = &g[i][j + 1];
            if (i < N) g[i][j].down  = &g[i + 1][j];
        }

    // Fill values at (1..N, 1..M)
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= M; ++j)
            cin >> g[i][j].val;

    auto jumpDown  = [](Node* p, int k){ while (k--) p = p->down;  return p; };
    auto jumpRight = [](Node* p, int k){ while (k--) p = p->right; return p; };

    auto get = [&](int i, int j) { // node at (i, j)
        Node* p = &g[0][0];
        p = jumpDown(p, i);
        p = jumpRight(p, j);
        return p;
    };

    int Q; cin >> Q;
    while (Q--) {
        int x1, y1, x2, y2, A, B;
        cin >> x1 >> y1 >> x2 >> y2 >> A >> B; // rectangles are non-overlapping

        // Swap top edges (down pointers from row x-1 across B columns)
        Node *p = get(x1 - 1, y1 - 1), *q = get(x2 - 1, y2 - 1);
        for (int k = 0; k < B; ++k) { swap(p->down, q->down); p = p->right; q = q->right; }

        // Swap bottom edges (down pointers from row x+A-1 across B columns)
        p = get(x1 + A - 1, y1 - 1); q = get(x2 + A - 1, y2 - 1);
        for (int k = 0; k < B; ++k) { swap(p->down, q->down); p = p->right; q = q->right; }

        // Swap left edges (right pointers from col y-1 down A rows)
        p = get(x1 - 1, y1 - 1); q = get(x2 - 1, y2 - 1);
        for (int k = 0; k < A; ++k) { swap(p->right, q->right); p = p->down; q = q->down; }

        // Swap right edges (right pointers from col y+B-1 down A rows)
        p = get(x1 - 1, y1 + B - 1); q = get(x2 - 1, y2 + B - 1);
        for (int k = 0; k < A; ++k) { swap(p->right, q->right); p = p->down; q = q->down; }
    }

    // Output by traversing pointers
    Node* row = &g[0][0];
    for (int i = 1; i <= N; ++i) {
        row = row->down;
        Node* cur = row;
        for (int j = 1; j <= M; ++j) {
            cur = cur->right;
            cout << cur->val << (j == M ? '\n' : ' ');
        }
    }
    return 0;
}
