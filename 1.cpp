#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> head, tail, nxt;
    vector<int> answer;
    vector<bool> relevant;

    explicit DSU(int n)
        : parent(n + 1, -1),
          head(n + 1),
          tail(n + 1),
          nxt(n + 1, 0),
          answer(n + 1, -1),
          relevant(n + 1, false) {

        // 每个集合最初只有自己，答案尚未确定
        for (int i = 1; i <= n; i++) {
            head[i] = tail[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] < 0) return x;
        return parent[x] = find(parent[x]);
    }

    // 给集合中所有待定节点赋答案，并清空待定链表
    // 参数 root 必须是根节点
    void assignPending(int root, int time) {
        for (int u = head[root]; u != 0; u = nxt[u]) {
            answer[u] = time;
        }

        head[root] = tail[root] = 0;
    }

    // 恢复农场 x 生产，让整个集合变为相关
    void activate(int x, int time) {
        int root = find(x);

        relevant[root] = true;
        assignPending(root, time);
    }

    // 加回道路，合并两个集合
    void unite(int a, int b, int time) {
        a = find(a);
        b = find(b);

        if (a == b) return;

        // 按大小合并
        if (parent[a] > parent[b]) swap(a, b);

        parent[a] += parent[b];
        parent[b] = a;

        // 将 b 的待定链表拼接到 a 后面
        if (head[b] != 0) {
            if (head[a] == 0) {
                head[a] = head[b];
            } else {
                nxt[tail[a]] = head[b];
            }

            tail[a] = tail[b];
        }

        head[b] = tail[b] = 0;

        // 任意一侧相关，合并后整个集合都相关
        relevant[a] = relevant[a] || relevant[b];

        if (relevant[a]) {
            assignPending(a, time);
        }
    }
};

struct Edge {
    int u, v;
};

struct Operation {
    char type;
    int x; // D 存农场编号，A/R 存道路编号
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    // 道路编号从 1 开始，按 A 操作出现的顺序编号
    vector<Edge> edges(1);
    vector<bool> removed(1, false);

    // 读完后，active 表示最终是否仍在生产
    vector<bool> active(N + 1, true);
    vector<Operation> operations(Q + 1);

    for (int i = 1; i <= Q; i++) {
        char type;
        cin >> type;

        if (type == 'A') {
            int u, v;
            cin >> u >> v;

            edges.push_back({u, v});
            removed.push_back(false);

            int id = int(edges.size()) - 1;
            operations[i] = {type, id};
        } else {
            int x;
            cin >> x;

            operations[i] = {type, x};

            if (type == 'D') {
                active[x] = false;
            } else {
                removed[x] = true;
            }
        }
    }

    DSU dsu(N);

    // 1. 建立最终状态中仍存在的道路
    for (int e = 1; e < int(edges.size()); e++) {
        if (!removed[e]) {
            dsu.unite(edges[e].u, edges[e].v, Q);
        }
    }

    // 2. 最终仍在生产的农场，使所在集合相关
    // 这些集合中的节点，答案都是 Q
    for (int u = 1; u <= N; u++) {
        if (active[u]) {
            dsu.activate(u, Q);
        }
    }

    // 3. 倒序处理操作
    for (int i = Q; i >= 1; i--) {
        auto [type, x] = operations[i];

        // 撤销第 i 次操作，回到第 i-1 次操作后的状态
        int time = i - 1;

        if (type == 'D') {
            dsu.activate(x, time);
        } else if (type == 'R') {
            dsu.unite(edges[x].u, edges[x].v, time);
        }

        // type == 'A'：忽略
    }

    for (int u = 1; u <= N; u++) {
        cout << dsu.answer[u] << '\n';
    }

    return 0;
}