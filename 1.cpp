#include <bits/stdc++.h>
using namespace std;

const int Nmax = 100005;

int N, M;
string milk;
vector<int> adj[Nmax];

// has：从起点到当前节点 u 的路径上，是否有喜欢的牛奶
bool dfs(int u, int parent, int target, char wanted, bool has) {
    if (milk[u] == wanted) {
        has = true;
    }

    // 到达终点，判断这条路径是否符合要求
    if (u == target) {
        return has;
    }

    for (int v : adj[u]) {
        if (v == parent) continue;

        if (dfs(v, u, target, wanted, has)) {
            return true;
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 需要文件输入输出时，取消下面两行注释。
    freopen("milkvisits.in", "r", stdin);
    freopen("milkvisits.out", "w", stdout);

    cin >> N >> M;
    cin >> milk;
    milk = " " + milk; // 编号从 1 开始

    for (int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 0; i < M; i++) {
        int a, b;
        char wanted;
        cin >> a >> b >> wanted;

        cout << (dfs(a, 0, b, wanted, false) ? '1' : '0');
    }

    cout << '\n';
    return 0;
}