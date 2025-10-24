#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;
const int LOG = 21;

int N;
int p[MAXN];
vector<int> g[MAXN];
int depth[MAXN];
int up[MAXN][LOG];
int tin[MAXN], tout[MAXN], timer = 0;

// DFS to compute tin/tout and depth
void dfs(int v) {
    tin[v] = ++timer;
    for (int u : g[v]) {
        depth[u] = depth[v] + 1;
        up[u][0] = v;
        for (int j = 1; j < LOG; j++)
            up[u][j] = up[up[u][j - 1]][j - 1];
        dfs(u);
    }
    tout[v] = ++timer;
}

// Check ancestor
bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

// LCA
int lca(int u, int v) {
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;
    for (int j = LOG - 1; j >= 0; j--) {
        if (!is_ancestor(up[u][j], v))
            u = up[u][j];
    }
    return up[u][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> p[i];
        g[p[i]].push_back(i);
    }

    depth[0] = 0;
    up[0][0] = 0;
    dfs(0);

    // find all leaves
    vector<int> leaves;
    for (int i = 0; i <= N; i++) {
        if (g[i].empty()) leaves.push_back(i);
    }

    int M = leaves.size();
    vector<int> order(M);
    for (int i = 0; i < M; i++) cin >> order[i];

    // store (tin, node) for alive leaves
    set<pair<int,int>> alive;
    for (int x : leaves) alive.insert({tin[x], x});

    vector<int> ans(M);

    for (int i = 0; i < M; i++) {
        int x = order[i];
        auto it = alive.find({tin[x], x});

        int bestLCAdepth = 0;
        // check predecessor
        if (it != alive.begin()) {
            auto pre = prev(it);
            int y = pre->second;
            int L = lca(x, y);
            bestLCAdepth = max(bestLCAdepth, depth[L]);
        }
        // check successor
        auto nxt = next(it);
        if (nxt != alive.end()) {
            int y = nxt->second;
            int L = lca(x, y);
            bestLCAdepth = max(bestLCAdepth, depth[L]);
        }

        ans[i] = depth[x] - bestLCAdepth;

        alive.erase(it);
        if (alive.size() == 0)
            ans[i] = 0;  // only one word left => 0
    }

    for (int x : ans) cout << x << "\n";
    return 0;
}
