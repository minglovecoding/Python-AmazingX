## 📚 USACO常见的map、unordered_map

### 📌1、**map 和 unordered_map 的对比**

| 特性               | `map`（有序）      | `unordered_map（无序）` |
| ------------------ | ------------------ | ----------------------- |
| 底层逻辑           | 红黑树             | 哈希表                  |
| 时间复杂度         | 查找/插入 O(log n) | 查找/插入平均 O(1)      |
| key 是否自动排序？ | ✔ 有序（升序）     | ✘ 无序                  |
| 空间               | 较少               | 较多                    |

### 什么时候用 `map`？

- **需要 key 排序的题**
- 需要 lower_bound/upper_bound（比如区间查找）
- 数据量很大但不要求极限速度
- 想要结果有序（输出顺序）

```c++
map<int, int> mp;  // 自动按 key 排序
```

### 什么时候用 `unordered_map`？

- 只需要查找是否存在
- 频率统计（freq counter）
- key 是字符串、大整数、pair 等
- 希望最快的平均性能

```c++
unordered_map<string, int> freq;
```

### ✅ 1. 频率统计（frequency counting）

```c++
unordered_map<int, int> cnt;
for (int x : arr) {
    cnt[x]++;
}
```

统计字符串也一样：

```c++
unordered_map<string, int> cnt;
for (string s : arr) cnt[s]++;
```

### ✅ **2. 判断某元素是否出现**

```c++
if (cnt.count(x)) {
    // 存在 x
}
```

### ✅ **3. 遍历所有 key-value**

```c++
for (auto &p : cnt) {
    int key = p.first;
    int value = p.second;
}
```

### ✅ **4. map + 排序（对 key 排序）**

```c++
map<int, int> mp; // 有序
for (auto &p : mp) {
    // 自动按 key 从小到大
}
```

### ✅ **5. 多重映射（key → vector）**

适用于“分组统计”类题。

```c++
unordered_map<int, vector<int>> g;
g[key].push_back(val);
```

### ✅ **6. 字符串映射（非常常见）**

```c++
unordered_map<string, int> id;
id["cow"] = 5;
```

### ✅ **7. pair 映射（二维 key）**

```c++
unordered_map<long long, int> mp;
long long key = 1LL * x * 1e9 + y; // 手动哈希
mp[key]++;
```

### ✅ **8. 离散化 + map**

**离散化（coordinate compression） = 把巨大范围的值，映射成从 0 开始的小整数。**

例如原本有值：

```c++
[-2000000000, 10, 999999999]
```

范围太大，如果你做：

- 开数组 arr[1e9]：直接爆炸
- 或需要排序/统计的时候不方便

所以我们把它们压缩成：

```c++
-2000000000 → 0
10           → 1
999999999    → 2
```

**这样所有值都变成可控的小下标（0,1,2…）**

```c++
map<int, int> mp;
int id = 0;
for (int x : arr) {
    if (!mp.count(x)) mp[x] = id++;
}
```

这段代码的作用就是：

### 🔍 **如果 x 第一次出现**

→ 给它分配一个新的 ID（从 0 开始）
 → 下次遇到相同 x，就复用这个 ID。

**mp[x] = id++** 保证了每个不同的数匹配到不同的小编号。

✔ 把大范围值→换成小整数
 ✔ 自动按 key 排序
 ✔ 下标从 0 到 unique_count-1
 ✔ 用于区间、树状数组、扫描线、图论等场景

> 2016 Dec Silver_1-Counting Haybales

***

### ✅ **9. map + lower_bound/upper_bound**

因为 `map` 是 **有序（红黑树）结构**，key 自动按升序排列。

第一个 ≥ x 的 key → `lower_bound`

第一个 > x 的 key → `upper_bound`

### case 1：找到第一个 >= x 的 key（最常用场景）**

比如你有一些牛的位置，需要找到离位置 x 最近的**右侧牛**。

```c++
map<int, int> mp;  // key: 牛的位置, val: 其他信息
auto it = mp.lower_bound(x);
if (it != mp.end()) {
    cout << "第一个 >= x 的位置是 " << it->first << "\n";
}
```

### case **2：找到第一个 > x 的 key**

常用于处理严格区间，例如 (x, +∞)。

```c++
auto it = mp.upper_bound(x);
if (it != mp.end()) {
    cout << "第一个 > x 的位置是 " << it->first << "\n";
}
```

### **case 3：在有序 map 中找某个区间内的 key**

比如你有若干农场编号，想找到区间 [L, R] 内所有的农场。

```c++
auto it = mp.lower_bound(L);  // 第一个 >= L
while (it != mp.end() && it->first <= R) {
    cout << "农场: " << it->first << "\n";
    it++;
}
```

### case **4：查找最接近 x 的点（USACO 非常常考）**

例如要找距离某个位置最近的牛：

```c++
auto it = mp.lower_bound(x);
int best = 1e18;

// right side
if (it != mp.end())
    best = min(best, abs(it->first - x));

// left side
if (it != mp.begin()) {
    it--;
    best = min(best, abs(it->first - x));
}
```

***

### 📌 2、优先队列priority_queue

优先队列是一种特殊的队列：

> **取出的永远是“最优的那个元素”（最大或最小）**
>  而不是先进先出。

优先队列底层使用 **二叉堆（binary heap）** 实现。

### 🧠为什么竞赛喜欢用优先队列？

因为它速度快：

| 操作               | 时间复杂度 |
| ------------------ | ---------- |
| 插入               | O(log n)   |
| 取最值             | O(log n)   |
| 查询最值（不删除） | O(1)       |

适用于：

- 找当前最大的 / 最小的
- 动态加入、动态删除
- 不断取最优解（贪心）

属于 **USACO 银组常用的数据结构**。

### ① 默认：最大堆（取最大值）

```c++
priority_queue<int> pq;

pq.push(5);
pq.push(1);
pq.push(10);

cout << pq.top();   // 10
pq.pop();           // 删除 10
```

### ② 最小堆（USACO 更常用）

要写比较器：

```c++
priority_queue<int, vector<int>, greater<int>> pq;
//创建一个以 vector 为底层容器、存 int、并按照小的优先级在上面的“最小堆”。
```

现在 `top()` 就是**最小值**。

### ③ 存 pair（按第一个排序）

```c++
priority_queue<pair<int,int>> pq;  // 默认最大堆
//比较 first, 若相同，再比较 second
```

### ④ 最小堆 + pair（竞赛常用）

```c++
priority_queue<
    pair<int,int>,
    vector<pair<int,int>>,
    greater<pair<int,int>>
> pq;
```

### 👉 优先队列在 USACO 银组的典型用途

### ① 贪心（频率 or 权重最大/最小）

例如：

- 选当前“最紧急”的任务
- 选当前“最小代价”的操作
- 选当前“最大产量”
- 堆模拟调度（schedule simulation）

### ② K 小 / K 大元素

#### 情况一：**已经有全部数据，只是想拿出 K 个最小 / 最大**

这时候最简单的想法就是：

- **K 个最小**：用**最小堆**，弹 K 次
- **K 个最大**：用**最大堆**，弹 K 次

对应代码：

```c++
// 找 K 个最小元素：
priority_queue<int, vector<int>, greater<int>> pq; // 最小堆
for (int x : arr) pq.push(x);
for (int i = 0; i < K; i++) {
    cout << pq.top() << "\n"; // 从小到大
    pq.pop();
}

// 找 K 个最大元素：
priority_queue<int> pq2; // 最大堆
for (int x : arr) pq2.push(x);
for (int i = 0; i < K; i++) {
    cout << pq2.top() << "\n"; // 从大到小
    pq2.pop();
}
```

#### 情况二：**在线维护“前 K 大 / 前 K 小”（数据流/只留 K 个）**

但在算法题里，更常见的是这种模式：

> 数据很多，只想**保留 K 个最优的**，不想存全部。

这时候常用的技巧是：

### ⭐ 保留 K 个**最大**值（Top K largest）

用 **“最小堆 + 只存 K 个”**：

```c++
priority_queue<int, vector<int>, greater<int>> pq; // 最小堆

for (int x : arr) {
    if ((int)pq.size() < K) pq.push(x);         // 先填满
    else if (x > pq.top()) {                    // 比堆顶（当前第 K 大）更大
        pq.pop();
        pq.push(x);
    }
}
// 最后 pq 里是“前 K 大”，堆顶是“第 K 大（最小的那个）”
```

### ⭐ 保留 K 个**最小**值（Top K smallest）

用 **“最大堆 + 只存 K 个”**：

```c++
priority_queue<int> pq; // 最大堆

for (int x : arr) {
    if ((int)pq.size() < K) pq.push(x);
    else if (x < pq.top()) {   // 比当前最大的小
        pq.pop();
        pq.push(x);
    }
}
// 最后 pq 里是“前 K 小”，堆顶是“第 K 小里最大的那个”
```

在**这种“只维护前 K 个”的套路**里：

- **前 K 大** → 用最小堆（我之前写的是这个思路）
- **前 K 小** → 用最大堆

### ③ 多路合并（k-way merge）

例如有多条升序序列，要合并成一个序列
 → 把每一条的第一个放入最小堆 → 每次取最小 → 推入下一项
 （和合并 k 个有序链表一个思路）

### ④ 动态维护最优值（典型银组套路）

例如“每次取最大值，做一些操作，再放回去”。

```
push → top → pop → push → top → pop → …
```

优先队列特别适合这种循环。

***

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

每个集合像一棵小树，每棵树有一个根（root）
 `find(x)` 就是找到这棵树的根。

合并两个集合（union）就是：
 让一个树的根指向另一个树的根。

为了更快，它会做两件优化：

1. **路径压缩（Path Compression）**
2. **按秩合并（Union by Rank / Size）**

这保证效率非常快，几乎是 O(1)。

<img src="/Users/mingoo/Desktop/Python-AmazingX/images/10.png" alt="10" style="zoom:50%;" />

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

让每一次 find 都顺便把节点直接连到根。
 这样树的深度越来越平，查找几乎变成 O(1)。

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

```

### **2. 连通块统计（Connected Components）**

统计一共有多少个集合，或者每个集合大小是多少。

### 场景：

- 统计有多少个独立的组
- 统计每组的大小（size 数组）
- 牧场里有几群牛
- 有几个连通子图

### 使用方法：

每次 union 合并
 最后统计根节点数量即可。

### 为什么 DSU 很强？

- 自动维护集合合并
- 直接统计根节点数量 → O(n)

> USACO 2016 US Open Silver Problem 3-Closing the Farm

### **3. 等价关系处理（Equivalence Classes）— 分组问题**

USACO 很喜欢这种题：

> A 和 B 要放在一组
>  C 和 D 要放在一组
>  他们是否会冲突？

比如：

- “这两头牛必须在一起”
- “这些编号属于同一类型”
- “某些条件让两个人必须等价”

### 典型例子（抽象）：

```
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
