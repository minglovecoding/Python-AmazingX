## 🌲 什么是图论（Graph Theory）？

**图论 = 研究“点 + 边”之间关系的数学和算法学科。**

一个图包含：

- **点（nodes / vertices）**
- **边（edges）**：连接点与点

就像你在地图、社交网络、电路图上看到的一样。

例如：

```
A -- B -- C
|         |
D ------- E
```

这是一个图，5 个节点、5 条边。

## 🧠 图论能解决什么问题？

图论用来解决各种“连接关系”的问题，例如：

- 两点之间能否到达？
- 到达需要几步？最短路径？
- 有哪些连通区域？
- 网络是否有环？
- 哪些节点之间必须在同一个集合？
- 树形结构如何遍历？

## 📊 图论中的常见图类型

### **① 无向图（undirected graph）**

A-B 和 B-A 是一样的（双向）。

### **② 有向图（directed graph）**

A → B 和 B → A 不一样。

### **③ 加权图（weighted graph）**

每条边有权重，例如距离、时间。

### **④ 树（tree）**

- 没有环
- N 个点有 N-1 条边
- 任意两点只有唯一一条路径

树是图的一种特殊情况。

## 🎯 图常用的建图方式

USACO 中最常用的是 **邻接表（adj list）**：

```c++
vector<vector<int>> g(n);
g[u].push_back(v);
g[v].push_back(u);   // 如果是无向图
```

另一种领接矩阵，**用一个 N×N 的矩阵表示点与点之间是否有边。**

如果图中有 N 个点（编号 0~N-1），那么邻接矩阵 `adj` 是一个二维数组：

```C++
adj[i][j] = 1  表示 i 与 j 有边  
adj[i][j] = 0  表示 i 与 j 没有边
```

如果是有权图，可以写成：

```c++
adj[i][j] = 边的权重
adj[i][j] = 0 或 INF → 没有边
```

## 🧩 图论的核心算法

🟢 **1. BFS（广度优先搜索）**

🟢 **2. DFS（深度优先搜索）**

🟢 **3. Flood Fill（染色）**

- 计算岛屿数量
- 标记一片区域
- 统计连通块面积

🟢 **4. Union-Find（并查集）**

- 判断两点是否在同一集合
- 合并集合
- 统计连通数量

🟡 **5. 简单树论**

### 📌 **Flood Fill 的核心逻辑**

Flood Fill = 通过 DFS/BFS 从起点把整块连通区域全部访问。

假设地图如下所示，想找所有 “#” 的连通块数量。

```c++
....#.
...##.
.#....
.###..
```

从每个未访问的 "#" 开始：

1. DFS/BFS 遍历整块区域
2. 把所有属于这块的点标记为 visited
3. 计数 +1（代表发现新的区域）

```c++
int n, m;
vector<string> grid;
bool vis[1005][1005];

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

void dfs(int x, int y) {
    vis[x][y] = true;

    for (int k = 0; k < 4; k++) {
        int nx = x + dx[k];
        int ny = y + dy[k];

        if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
        if (vis[nx][ny]) continue;
        if (grid[nx][ny] != '#') continue;

        dfs(nx, ny);
    }
}
//
int cnt = 0;
for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
        if (grid[i][j] == '#' && !vis[i][j]) {
            dfs(i, j);  // 标记整块区域
            cnt++;      // 找到一块新的
        }
    }
}
```

### 📌 Union-Find / Disjoint Set Union，DSU（并查集）

##### **并查集是一种用来管理“多个不相交集合”的数据结构。**

它支持两个核心操作：

1. **Find（查找）**
   找到某个元素所属集合的“代表”（也叫根 root）
2. **Union（合并）**
   把两个集合合并成一个集合

##### 简单理解：

> **并查集 = 动态管理“谁和谁在一组”的神器**

在图论里它最常用于：

- 判断两个点是否连通
- 动态加边
- 连通块数量统计
- Kruskal（最小生成树，Gold 中更常见）

##### 并查集的核心思想

每个集合像一棵小树，每棵树有一个根（root）`find(x)` 就是找到这棵树的根。

合并两个集合（union）就是： 让一个树的根指向另一个树的根。

为了更快，它会做两件优化：

1. **路径压缩（Path Compression）**
2. **按秩合并（Union by Rank / Size）**

这保证效率非常快，几乎是 O(1)。

<img src="./images/10.png" alt="10" style="zoom:50%;" />

### 🧩 并查集的三大操作

### ① initianize **初始化**

一开始，每个元素自己是一个集合。

```c++
for (int i = 0; i < n; i++)
    parent[i] = i;    // 每个点都是自己的父亲
    size[i] = 1;      // 每个集合大小为 1
```

### ② **Find（查根）**

```C++
int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);    // 路径压缩
    return parent[x];
}
```

### 路径压缩是什么？

让每一次 find 都顺便把节点直接连到根。这样树的深度越来越平，查找几乎变成 O(1)。

### ③ **Union（合并两个集合）**

把 A 所属的集合 和 B 所属的集合连接起来：

```c++
void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return; // 已经在同一个集合

    if (size[a] < size[b]) swap(a, b); // 按大小合并，让更小的树连到更大的树
    parent[b] = a;
    size[a] += size[b];
}
```

### 如何判断两点是否连通？

只需 check 根是否一样：

```c++
if (find(a) == find(b)) {
    // 连通
}
```

### 🧱 模板代码（C++）

```c++
struct DSU {
    vector<int> parent, sz;
    DSU(int n) {
        parent.resize(n);
        sz.resize(n, 1);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }
};
```

### 🎯 USACO 并查集最常用的 **5 种题型**

1. ### 动态连通性（Dynamic Connectivity）— 判断是否连通

> 不断 union(a, b)，然后问你 x 和 y 是否属于同一个集合。

### 典型任务：

- 判断道路两点是否可达
- 判断两头牛是否在同一群
- 判断两个牧场是否连接
- 判断两条路径是否等价

### 为什么用 DSU？

- 因为 **find(x)==find(y)** 判断连通最快
- 比 DFS / BFS 更快（O(α(n)) ≈ O(1)）

### 示例：

```c++
union(1,2)
union(2,3)
query: 1 和 3 连通吗？ → YES
```

> USACO 2020 January Silver Problem 3-Wormhole Sort

```C++
//牛 i 现在在哪个位置” 和 “它最终要站的位置 i” 是否属于同一连通块
//找一个值 X，使得 只允许使用宽度 ≥ X 的虫洞时，仍然能把所有牛排好；并且这个 X 要尽可能大。
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, sz;
    DSU(int n = 0) {
        init(n);
    }
    void init(int n) {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    if (!(cin >> N >> M)) return 0;
    vector<int> p(N + 1);
    bool sorted = true;
    for (int i = 1; i <= N; i++) {
        cin >> p[i];
        if (p[i] != i) sorted = false;
    }

    vector<tuple<int,int,int>> edges; // (w, a, b)
    edges.reserve(M);
    int a, b, w;
    int maxW = 0;
    for (int i = 0; i < M; i++) {
        cin >> a >> b >> w;
        edges.push_back({w, a, b});
        maxW = max(maxW, w);
    }

    if (sorted) {
        cout << -1 << "\n";
        return 0;
    }

    DSU dsu(N);

    auto check = [&](int X) -> bool {
        dsu.init(N);
        for (auto &e : edges) {
            int ww, x, y;
            ww = get<0>(e);
            x  = get<1>(e);
            y  = get<2>(e);
            if (ww >= X) dsu.unite(x, y);
        }
        for (int i = 1; i <= N; i++) {
            if (dsu.find(i) != dsu.find(p[i]))
                return false;
        }
        return true;
    };

    int lo = 1, hi = maxW, ans = 0;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (check(mid)) {
            ans = mid;      // mid 可行，想要更大
            lo = mid + 1;
        } else {
            hi = mid - 1;   // mid 太大，缩小
        }
    }

    cout << ans << "\n";
    return 0;
}

//并查集
//二分查找
//tuple、vector用法
```

### **2. 连通块统计（Connected Components）**

统计一共有多少个集合，或者每个集合大小是多少。

### 场景：

- 统计有多少个独立的组
- 统计每组的大小（size 数组）
- 牧场里有几群牛
- 有几个连通子图

### 使用方法：

每次 union 合并, 最后统计根节点数量即可。

### 为什么 DSU 很强？

- 自动维护集合合并
- 直接统计根节点数量 → O(n)

> USACO 2016 US Open Silver Problem 3-Closing the Farm

### **3. 等价关系处理（Equivalence Classes）— 分组问题**

USACO 很喜欢这种题：

> A 和 B 要放在一组
> C 和 D 要放在一组
> 他们是否会冲突？

比如：

- “这两头牛必须在一起”
- “这些编号属于同一类型”
- “某些条件让两个人必须等价”

### 典型例子（抽象）：

```c++
1 ~ 3   (1 和 3 同组)
3 ~ 5
问：1 和 5 是否同组？（YES）
```

> USACO 2016 December Gold Problem 1-Moocast

### **4. Kruskal / 最小生成树的简化版本**

虽然完整的 MST 通常是 **Gold 级**，但 Silver 会出现：

### 场景：

- 给一堆边，按某种顺序排序
- 按顺序加入边
- 用 DSU 判断是否形成环
- 或统计某个结构

比如：

```
如果边 (u,v) 已经连通，则跳过（否则成环）
否则合并
```

完全就是 Kruskal 的核心思想。

### 为什么用 DSU？

因为你需要快速判断：

- **加入一条边后是否会产生环**？
  → find(u)==find(v) 就会产生环
- 如果不会，就合并集合

USACO Silver 很喜欢这种轻度 MST 判断题。

> USACO 2015 February Silver Problem 3-Superbull（ MST + DSU 的代表题）

### **5. 离线查询（Offline Queries）— 倒序处理问题**

### 场景：

- 边被“删除 / 塌陷 / 关闭”
- 问你随着时间倒退，什么时候变得连通
- 许多条件下的“先删后问”

处理方法：

> **正向难 → 倒序变成 union**

比如：

- 原问题：不断删除道路，询问是否连通
- 倒序处理：从全部断开开始，倒着加道路

这是 DSU 非常强的技巧，竞赛常用。

### 为什么是 DSU？

因为：

- 正向删除很难维护连通性
- 反向加入非常简单（union）

> USACO 2016 US Open Silver Problem 3-Closing the Farm