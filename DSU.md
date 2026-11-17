## 并查集：从连通块到离线算法

## 一、这节课解决什么问题

当图中不断加入新的边，我们希望快速回答：

1. 两个节点是否属于同一个连通块？
2. 加入一条边后，两个连通块如何合并？
3. 某个连通块有多少个节点？
4. 当前一共有多少个连通块？

**并查集（Disjoint Set Union，DSU）维护的是一组互不相交的集合。**

- **并**：把两个集合合并。
- **查**：查询某个元素属于哪个集合。
- **集**：所有元素被划分为若干个不相交的集合。

放到无向图中，一个集合通常对应一个连通块。

### 1. DFS/BFS 与并查集有什么区别

| 场景 | 常用方法 | 原因 |
| --- | --- | --- |
| 一张固定的图，求所有连通块 | DFS/BFS 或并查集 | 都可以完成，遍历还能获取更多结构信息 |
| 不断加边，中间反复询问连通性 | 并查集 | 每次只需要合并，不必重新遍历 |
| 求最少走几条边 | BFS | 普通并查集不维护距离 |
| 求具体路径 | DFS/BFS 等 | 并查集的父指针不是原图中的路径 |
| 删除边或节点 | 普通并查集不能直接处理 | 可考虑倒序离线；更复杂情况需要其他技术 |
| 判断有向图中能否从一个点走到另一个点 | 有向图搜索等 | 普通并查集会忽略方向 |

**并查集擅长维护“是不是同一组”，不负责还原“具体怎样走”。**

## 二、用一个例子理解合并

有 6 个节点，最初没有边：

$$
\{1\},\{2\},\{3\},\{4\},\{5\},\{6\}
$$

依次加入边：

| 操作 | 当前集合 | 集合数量 |
| --- | --- | --- |
| 初始 | `{1}`、`{2}`、`{3}`、`{4}`、`{5}`、`{6}` | 6 |
| 加入 `(1,2)` | `{1,2}`、`{3}`、`{4}`、`{5}`、`{6}` | 5 |
| 加入 `(2,3)` | `{1,2,3}`、`{4}`、`{5}`、`{6}` | 4 |
| 加入 `(4,5)` | `{1,2,3}`、`{4,5}`、`{6}` | 3 |
| 加入 `(1,3)` | 集合不变 | 3 |
| 加入 `(3,4)` | `{1,2,3,4,5}`、`{6}` | 2 |

加入 `(1,3)` 时，1 和 3 已经连通，因此不能再次减少集合数量。

## 三、核心表示：父节点与代表元

### 1. 每个集合选一个代表

使用 `parent[x]` 表示并查集内部的父节点。

若：

```cpp
parent[x] == x
```

说明 `x` 是这个集合的根，也称为代表元。

例如：

```cpp
parent[1] = 1;
parent[2] = 1;
parent[3] = 2;
```

1、2、3 属于同一个集合，根是 1。3 的直接父节点虽然是 2，但最终根仍然是 1。

**`parent[x]` 不一定等于代表元，必须通过 `find(x)` 查找。**

### 2. 初始化

每个节点单独作为一个集合：

```cpp
for (int i = 1; i <= n; i++) {
    parent[i] = i;
    sz[i] = 1;
}
```

`sz[root]` 记录这个根所代表的集合大小。

### 3. 查找代表元

未优化的查找思路：不断沿父指针向上走，直到根。

```cpp
int find(int x) {
    if (parent[x] == x) return x;
    return find(parent[x]);
}
```

如果合并方式不好，树可能变成很长的链，单次查找最坏为 $O(N)$。

## 四、两种优化

### 1. 路径压缩

```cpp
int find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}
```

这行代码分成两步理解：

```cpp
int root = find(parent[x]);
parent[x] = root;
return root;
```

查到根以后，让经过的节点直接指向根。下次查找就会更快。

路径压缩只改变并查集内部结构，不改变集合成员关系。

### 2. 按大小合并

合并时，让小集合的根指向大集合的根：

```cpp
a = find(a);
b = find(b);
if (a == b) return false;
if (sz[a] < sz[b]) swap(a, b);
parent[b] = a;
sz[a] += sz[b];
return true;
```

注意：

1. 连接的是两个集合的**根**。
2. 只有合并成功，才更新集合大小与集合数量。
3. 只有根节点上的 `sz` 保证有效；查询应使用 `sz[find(x)]`。

### 3. 时间复杂度

同时使用路径压缩与按大小合并：

- 初始化：$O(N)$。
- 查找、合并：均摊 $O(\alpha(N))$。
- 共 $M$ 次操作：$O(N+M\alpha(N))$。
- 空间：$O(N)$。

$\alpha(N)$ 是增长非常慢的反阿克曼函数，实际可以近似看成很小的常数，但不能说每次操作严格为 $O(1)$。

## 五、统一 C++ 模板

下面使用 `parent` 与 `sz` 两个数组，便于初学者理解。

```cpp
struct DSU {
    vector<int> parent, sz;
    int components;

    explicit DSU(int n) : parent(n + 1), sz(n + 1, 1), components(n) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]); // 路径压缩
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false; // 已在同一集合，不重复合并
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;           // 小集合的根接到大集合的根
        sz[a] += sz[b];
        components--;
        return true;
    }

    int size(int x) {
        return sz[find(x)];
    }
};
```

常用接口：

| 代码 | 含义 |
| --- | --- |
| `DSU dsu(n);` | 建立 1 到 n 的 n 个单点集合 |
| `dsu.find(x)` | 查找 x 所在集合的代表元 |
| `dsu.same(a,b)` | 判断 a、b 是否在同一集合 |
| `dsu.unite(a,b)` | 合并两个集合，返回本次是否真正发生合并 |
| `dsu.size(x)` | 查询 x 所在集合的节点数 |
| `dsu.components` | 当前集合数量，统计初始化的全部 n 个节点 |

`explicit` 用来限制隐式类型转换，不影响本课合并与查询的算法逻辑。

### 另一种写法：根节点存负数

有些代码只用一个 `parent` 数组：

- `parent[x] < 0`：x 是根，`-parent[x]` 是集合大小。
- `parent[x] >= 0`：存父节点编号。

因此你可能看到：

```cpp
int size(int x) {
    return -parent[find(x)];
}
```

这个负号来自存储约定。本课统一使用双数组版本，不混用两套初始化与判断规则。

## 六、基础练习：合并与查询

[洛谷 P3367：并查集](https://www.luogu.com.cn/problem/P3367)

操作 `1 x y`：合并；操作 `2 x y`：询问，输出 `Y` 或 `N`。

### 完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, sz;
    int components;

    explicit DSU(int n) : parent(n + 1), sz(n + 1, 1), components(n) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]); // 路径压缩
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false; // 已在同一集合，不重复合并
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;           // 小集合的根接到大集合的根
        sz[a] += sz[b];
        components--;
        return true;
    }

    int size(int x) {
        return sz[find(x)];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    DSU dsu(n);
    while (m--) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1) dsu.unite(x, y);
        else cout << (dsu.same(x, y) ? "Y" : "N") << '\n';
    }
}
```

### 手动练习

```text
5 6
1 1 2
1 2 3
2 1 3
2 1 4
1 3 4
2 2 4
```

输出：

```text
Y
N
Y
```

思考：为什么比较 `parent[x] == parent[y]` 不可靠，而比较 `find(x) == find(y)` 才可靠？

## 七、真题路线图

下表标注的是题目原始组别；“可用并查集”不代表该题只有这一种解法。

| 阶段 | 往年真题 | 考查重点 |
| --- | --- | --- |
| 银组入门 | [Closing the Farm — 2016 US Open Silver](https://usaco.org/index.php?page=viewproblem2&cpid=644) | 连通性；先理解逐次搜索，再学习倒序开放 |
| 银组过渡 | [MooTube — 2018 January Silver](https://usaco.org/index.php?page=viewproblem2&cpid=788) | 阈值限制下的连通块；搜索与离线并查集的对比 |
| 银组综合 | [Wormhole Sort — 2020 January Silver](https://usaco.org/index.php?page=viewproblem2&cpid=992) | 二分答案 + 并查集判定 |
| 银组拓展 | [Cereal 2 — 2022 January Silver](https://usaco.org/index.php?page=viewproblem2&cpid=1184) | 图建模、生成森林、环与输出顺序构造 |
| 金组入门 | [Closing the Farm — 2016 US Open Gold](https://usaco.org/index.php?page=viewproblem2&cpid=646) | 逆序离线，删除变加入 |
| 金组入门 | [MooTube — 2018 January Gold](https://usaco.org/index.php?page=viewproblem2&cpid=789) | 查询排序、边排序、离线维护集合大小 |
| 金组拓展 | [Fenced In — 2016 February Gold](https://usaco.org/index.php?page=viewproblem2&cpid=623) | 几何转图、最小生成树、批量处理同权边 |

建议课堂主线：基础模板 → Closing the Farm → MooTube → Wormhole Sort。Kruskal 与 Fenced In 可作为后续一课。

## 八、真题一：Closing the Farm

### 1. 题意与组别差异

给定无向图，按指定顺序关闭节点及其关联边，询问剩余开放节点是否全部连通。

| 版本 | 数据范围 | 适合的思路 |
| --- | --- | --- |
| 银组 | $N,M\le 3000$ | 每次关闭后 DFS/BFS，$O(N(N+M))$ |
| 金组 | $N,M\le 200000$ | 逆序开放 + 并查集 |

### 2. 为什么不能直接删除

假设 1、2、3 已经合并成一个集合，删除节点 2 后，1 和 3 是否仍连通，取决于原图有没有其他路径。

普通并查集只保留合并结果，无法直接把集合重新拆开。

**改变处理顺序：正向关闭节点，反向就是开放节点。**

### 3. 解题步骤

1. 读入全部关闭顺序 `order[1..n]`。
2. 初始所有节点都未开放，从 `order[n]` 开始倒序开放。
3. 新开放一个节点，开放连通块数先加 1。
4. 与所有已开放邻居合并；每次成功合并，开放连通块数减 1。
5. 若开放连通块数等于 1，记录 `YES`，最后按原顺序输出。

### 4. 样例推演与答案位置

原图的边为 `(1,2)`、`(2,3)`、`(3,4)`，关闭顺序是 `3,4,1,2`。

| 倒序操作 | 已开放节点 | 开放连通块数 | 存入 |
| --- | --- | --- | --- |
| 开放 2 | `{2}` | 1 | `answer[4]=YES` |
| 开放 1 | `{1,2}` | 1 | `answer[3]=YES` |
| 开放 4 | `{1,2,4}` | 2 | `answer[2]=NO` |
| 开放 3 | `{1,2,3,4}` | 1 | `answer[1]=YES` |

正序输出 `YES NO YES YES`。

**`answer[i]` 表示关闭前 `i-1` 个节点后的状态。** 题目不要求输出所有节点都关闭后的空图状态。

### 5. 完整代码：银组、金组通用

```cpp
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, sz;
    int components;

    explicit DSU(int n) : parent(n + 1), sz(n + 1, 1), components(n) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]); // 路径压缩
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false; // 已在同一集合，不重复合并
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;           // 小集合的根接到大集合的根
        sz[a] += sz[b];
        components--;
        return true;
    }

    int size(int x) {
        return sz[find(x)];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> order(n + 1);
    for (int i = 1; i <= n; i++) cin >> order[i];

    DSU dsu(n);
    vector<bool> active(n + 1, false), answer(n + 1, false);
    int activeComponents = 0; // 只统计已经开放的节点
    for (int i = n; i >= 1; i--) {
        int u = order[i];
        active[u] = true;
        activeComponents++;
        for (int v : adj[u]) {
            if (active[v] && dsu.unite(u, v)) activeComponents--;
        }
        // 当前开放的节点恰好是 order[i..n]
        answer[i] = (activeComponents == 1);
    }
    for (int i = 1; i <= n; i++) {
        cout << (answer[i] ? "YES" : "NO") << '\n';
    }
}
```

复杂度：$O(N+M\alpha(N))$，空间 $O(N+M)$。

注意：模板中的 `dsu.components` 包含尚未开放的节点，不能直接拿来判断。本题另外维护 `activeComponents`。

## 九、真题二：MooTube

### 1. 题意

图是一棵树。两点的相关度等于唯一路径上的最小边权。

查询 `(k,v)`：除 v 自己外，有多少节点与 v 的相关度至少为 k？

### 2. 从路径转成连通块

路径最小边权至少为 k，等价于这条路径上的每条边权都至少为 k。

因此，只保留边权 `w >= k` 的边，答案就是：

$$
\operatorname{size}(v)-1
$$

减去 1 是为了排除 v 自己。

### 3. 为什么银组能搜索，金组需要优化

- 银组 $N,Q\le 5000$：每次 DFS/BFS，时间 $O(NQ)$，可以完成。
- 金组 $N,Q\le 10^5$：反复搜索代价过高。

所有查询提前给出，可以先排序、再计算，最后恢复输出顺序。这叫**离线处理**。

### 4. 解题步骤

1. 将边按边权从大到小排序。
2. 将查询按阈值 k 从大到小排序，记录原查询编号 `id`。
3. 处理每个查询前，把所有 `w >= k` 的边加入并查集。
4. 记录 `answer[id] = dsu.size(v) - 1`。
5. 按原查询顺序输出。

阈值不断减小，允许的边只增不减，因此并查集的合并结果可以保留。

如果阈值从小到大处理，就需要删除已经加入的边，普通并查集不适合这样做。

### 5. 小例子

边：`1—2` 权值 3，`2—3` 权值 2，`2—4` 权值 4。

| 阈值 | 已加入的边 | 查询节点 | 答案 |
| --- | --- | --- | --- |
| 4 | `(2,4)` | 1 | 0 |
| 3 | 再加入 `(1,2)` | 1 | 2 |
| 1 | 再加入 `(2,3)` | 2 | 3 |

注意同权边：回答阈值 k 前，所有权值等于 k 的边也必须加入。

### 6. 完整代码：银组、金组通用

```cpp
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, sz;
    int components;

    explicit DSU(int n) : parent(n + 1), sz(n + 1, 1), components(n) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]); // 路径压缩
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false; // 已在同一集合，不重复合并
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;           // 小集合的根接到大集合的根
        sz[a] += sz[b];
        components--;
        return true;
    }

    int size(int x) {
        return sz[find(x)];
    }
};

struct Edge { int u, v, w; };
struct Query { int k, v, id; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<Edge> edges(n - 1);
    for (auto &e : edges) cin >> e.u >> e.v >> e.w;
    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].k >> queries[i].v;
        queries[i].id = i;
    }
    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
        return a.w > b.w;
    });
    sort(queries.begin(), queries.end(), [](const Query &a, const Query &b) {
        return a.k > b.k;
    });
    DSU dsu(n);
    vector<int> answer(q);
    int p = 0;
    for (const auto &query : queries) {
        while (p < n - 1 && edges[p].w >= query.k) {
            dsu.unite(edges[p].u, edges[p].v);
            p++;
        }
        answer[query.id] = dsu.size(query.v) - 1;
    }
    for (int value : answer) cout << value << '\n';
}
```

时间复杂度：

$$
O(N\log N+Q\log Q+(N+Q)\alpha(N))
$$

空间复杂度：$O(N+Q)$。

## 十、真题三：Wormhole Sort

### 1. 如何建模

位置 i 上的奶牛编号为 `p[i]`，目标是让每个位置上的编号等于自身编号。

若只使用宽度至少为 W 的虫洞，那么允许交换的边构成一张无向图。

能够完成排序，当且仅当对所有 i：

$$
\operatorname{find}(i)=\operatorname{find}(p[i])
$$

这里使用“位置 i 上是奶牛 p[i]”的排列记法；它与题面“奶牛 i 位于 p[i]”的记法互为逆排列，对所有 i 的连通块判定完全等价。

### 2. 为什么“同一连通块”就够了

必要性：奶牛无法离开当前连通块，因此目标位置必须在同一块内。

充分性：沿连通图中的边交换，可以实现连通块内任意排列。可以取一棵生成树，把某个叶子需要的奶牛沿路径交换到叶子，再固定该叶子，递归处理剩余树。

因此不需要真的模拟每一次交换。

### 3. 为什么可以二分

- W 越大，保留的边越少，条件越严格。
- 若 W 可行，更小的阈值也可行。
- 可行性形如 `真 真 真 假 假`，求最后一个真。

### 4. 解题步骤

1. 若原排列已经有序，输出 `-1`。
2. 二分最小允许宽度 W。
3. 每次新建并查集，只合并 `w >= W` 的边。
4. 检查全部 `same(i,p[i])`；满足则尝试更大阈值。

### 5. 完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, sz;
    int components;

    explicit DSU(int n) : parent(n + 1), sz(n + 1, 1), components(n) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]); // 路径压缩
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false; // 已在同一集合，不重复合并
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;           // 小集合的根接到大集合的根
        sz[a] += sz[b];
        components--;
        return true;
    }

    int size(int x) {
        return sz[find(x)];
    }
};

struct Edge { int u, v, w; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> p(n + 1);
    bool sorted = true;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        if (p[i] != i) sorted = false;
    }
    vector<Edge> edges(m);
    int maxWidth = 0;
    for (auto &e : edges) {
        cin >> e.u >> e.v >> e.w;
        maxWidth = max(maxWidth, e.w);
    }
    if (sorted) {
        cout << -1 << '\n';
        return 0;
    }
    auto check = [&](int width) {
        DSU dsu(n); // 每次判定都重新建立，不能沿用上一次的合并
        for (const auto &e : edges) {
            if (e.w >= width) dsu.unite(e.u, e.v);
        }
        for (int i = 1; i <= n; i++) {
            if (!dsu.same(i, p[i])) return false;
        }
        return true;
    };
    int low = 0, high = maxWidth;
    while (low < high) {
        int mid = low + (high - low + 1) / 2;
        if (check(mid)) low = mid;
        else high = mid - 1;
    }
    cout << low << '\n';
}
```

设最大边权为 $W_{\max}$，时间复杂度：

$$
O\left((N+M)\alpha(N)\log(W_{\max}+1)\right)
$$

另有每次初始化的 $O(N)$，已被上式覆盖。空间 $O(N+M)$。题目保证存在可行排序方案。

**常见误区：二分阈值会时大时小，所以每次 `check` 都重新初始化并查集，不能无条件复用上次结果。**

## 十一、应用拓展：Kruskal 最小生成树

### 1. 最小生成树是什么

在一个连通无向带权图中，选择 $N-1$ 条边，使所有节点连通，并使总边权最小。

这不是最短路：最短路优化某些路径的长度，最小生成树优化连接全部节点的总成本。

### 2. Kruskal 的步骤

1. 按边权从小到大排序。
2. 依次考虑每条边 `(u,v,w)`。
3. 若 u、v 不连通，选这条边并合并两个集合。
4. 若已经连通，加入会形成环，跳过。
5. 选满 $N-1$ 条边后结束；若选不满，原图不连通。

并查集负责快速判断“这条边会不会成环”；排序与贪心决定“先考虑哪些边”。

### 3. 为什么便宜的跨集合边可以选

当前森林可以扩展为某棵最小生成树。若下一条最便宜的跨集合边 e 不在那棵树里，加入 e 会形成环；环上必有另一条跨越相应切分的边 f。

因为 e 是当前可用的最便宜跨集合边，$w(e)\le w(f)$。用 e 替换 f，不增加总权值，因此仍可得到一棵最小生成树。

### 4. 模板练习与完整代码

[洛谷 P3366：最小生成树](https://www.luogu.com.cn/problem/P3366)

```cpp
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, sz;
    int components;

    explicit DSU(int n) : parent(n + 1), sz(n + 1, 1), components(n) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]); // 路径压缩
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false; // 已在同一集合，不重复合并
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;           // 小集合的根接到大集合的根
        sz[a] += sz[b];
        components--;
        return true;
    }

    int size(int x) {
        return sz[find(x)];
    }
};

struct Edge { int u, v, w; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    for (auto &e : edges) cin >> e.u >> e.v >> e.w;
    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
        return a.w < b.w;
    });
    DSU dsu(n);
    long long answer = 0;
    int chosen = 0;
    for (const auto &e : edges) {
        if (dsu.unite(e.u, e.v)) {
            answer += e.w;
            chosen++;
        }
        if (chosen == n - 1) break;
    }
    if (chosen != n - 1) cout << "orz\n";
    else cout << answer << '\n';
}
```

时间 $O(M\log M+(N+M)\alpha(N))$，空间 $O(N+M)$。边权总和用 `long long`。

若要求最大生成树，改为边权从大到小排序，仍由并查集判断是否成环。

## 十二、金组拓展：Fenced In

[USACO 2016 February Gold — Fenced In](https://usaco.org/index.php?page=viewproblem2&cpid=623)

### 1. 图如何构造

1. 围栏把大矩形分成若干小区域，把每个**区域**作为节点。
2. 两个区域共用一段围栏，就在它们之间建立一条边。
3. 边权等于拆掉这段围栏的长度。
4. 要让所有区域互通且拆除总长度最小，就是最小生成树。

注意节点代表区域，不是围栏交点。

### 2. 边权容易弄反

若某区域宽为 `dx`、高为 `dy`：

- 向左右相邻区域打通：拆掉竖直围栏，长度是 `dy`。
- 向上下相邻区域打通：拆掉水平围栏，长度是 `dx`。

### 3. 从模板到本题

补入外边界坐标后排序，求相邻坐标差；对区域编号，例如：

```cpp
int id(int row, int col, int columns) {
    return row * columns + col;
}
```

可以显式建立区域相邻边后执行 Kruskal。但最大规模有约 400 万个区域、800 万条边，显式存储与全量边排序开销较大。

更适合本题的实现方式是：分别将宽度、高度排序，归并处理下一组最便宜的水平边或竖直边，同一组内逐条尝试并查集合并。这利用了网格最小生成树的特殊结构，无需显式存下全部边。它是对普通 Kruskal 的进一步优化，不能理解成任意带权图都可以随意重排节点对应的边权。

这个金组做法用并查集处理 $O((n+1)(m+1))$ 次相邻合并，排序只针对两组间距。时间为

$$
O\left((n+1)\log(n+1)+(m+1)\log(m+1)
 +(n+1)(m+1)\alpha((n+1)(m+1))\right).
$$

建议先掌握建模与 Kruskal，再学习这种按同权边成组生成的实现；本课不附该题完整程序，避免与模板入门混在一起。

## 十三、银组综合拓展：Cereal 2

[USACO 2022 January Silver — Cereal 2](https://usaco.org/index.php?page=viewproblem2&cpid=1184)

### 1. 建模上的转变

- 节点代表谷物。
- 每头奶牛连接它的第一选择与第二选择，对应一条边。
- 需要选择出场顺序，让尽可能多的奶牛吃到谷物。

这张图可能有重边；每条边都对应不同奶牛，不能简单去重。

### 2. 并查集能帮助什么

逐条加入边：

- 若 `unite(u,v)` 成功，这条边可以成为生成森林中的树边。
- 若失败，这条边连接的两点已经连通，是一条非树边。

对于一个有 V 个谷物节点、E 头奶牛的连通分量，最多能满足 $\min(V,E)$ 头牛：树形分量有 $E=V-1$；含环分量可以利用一个环，让 V 头牛分别占据 V 个谷物。

### 3. 为什么不能只写并查集就结束

题目还要求输出具体出场顺序，第一、第二选择也有优先关系。

因此还需要：

1. 对树形分量选择根，按合适顺序安排树边对应奶牛。
2. 对含环分量保留一个环，利用它确定起始安排。
3. 再遍历连接在环上的树，输出其余安排。

**并查集用于识别结构，DFS 与构造用于完成答案。** 这是一道综合题，适合作为课后挑战，不建议第一次学并查集就从它开始。

## 课后必做题

| 顺序 | 题目 | 本题要练会什么 |
| --- | --- | --- |
| 1 | [洛谷 P3367 并查集](https://www.luogu.com.cn/problem/P3367) | 独立完成初始化、find、unite |
| 2 | [Closing the Farm 银组](https://usaco.org/index.php?page=viewproblem2&cpid=644) | 用 DFS/BFS 做一遍，理解连通性判定 |
| 3 | [Closing the Farm 金组](https://usaco.org/index.php?page=viewproblem2&cpid=646) | 把删除转成倒序添加 |
| 4 | [MooTube 银组](https://usaco.org/index.php?page=viewproblem2&cpid=788) | 将路径最小边权限制转成连通块 |
| 5 | [MooTube 金组](https://usaco.org/index.php?page=viewproblem2&cpid=789) | 离线排序与集合大小 |
| 6 | [Wormhole Sort 银组](https://usaco.org/index.php?page=viewproblem2&cpid=992) | 二分答案中的并查集判定 |
| 7 | [洛谷 P3366 最小生成树](https://www.luogu.com.cn/problem/P3366) | 用并查集服务 Kruskal |

***
