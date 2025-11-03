## 🎒 4. 经典模型 II：背包 DP（必会）

##### 4.1 0-1 背包

 给定容量为 `W` 的背包，n 件物品，每件有重量 `w[i]` 和价值 `v[i]`。
 要求在不超过容量的情况下，价值最大。

### ✅ 状态定义

```
dp[w] = 容量为 w 时的最大价值
```

------

### ✅ 状态转移方程

$$
dp[w] = \max(dp[w], dp[w - weight[i]] + value[i])
$$

但注意顺序要 **倒序枚举 w**，否则一个物品可能被重复使用。

------

### ✅ 为什么要倒序？

- 因为每个物品只能用一次；
- 如果正序，会导致同一个物品在一次循环内被多次使用（相当于完全背包了）。

------

### 💻 代码模板

```c++
int n, W;
cin >> n >> W;
vector<int> w(n+1), v(n+1);
for (int i = 1; i <= n; i++) cin >> w[i] >> v[i];
vector<int> dp(W + 1, 0);
for (int i = 1; i <= n; i++) {
    for (int j = W; j >= w[i]; j--) {
        dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
    }
}
cout << dp[W];
```

### 4.2 完全背包 

> 每个物品可以选无限次（类似“硬币问题”）。

### ✅ 状态定义

```c++
dp[w] = 容量为 w 时的最大价值
```

### ✅ 转移方程

$$
dp[w] = \max(dp[w], dp[w - weight[i]] + value[i])
$$

与 0-1 背包几乎相同，但**枚举顺序不同**：

> 完全背包使用 **正序** 遍历 w。

### 💻 代码模板

```c++
for (int i = 1; i <= n; i++) {
    for (int j = w[i]; j <= W; j++) { // 正序遍历
        dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
    }
}
```

### 4.3 多重背包

> 每个物品有“数量限制” `count[i]`。

### ✅ 思路一：朴素枚举（复杂度较高）

直接在内层循环中枚举数量：

```c++
for (int i = 1; i <= n; i++) {
    for (int j = W; j >= w[i]; j--) {
        for (int k = 1; k <= cnt[i] && k*w[i] <= j; k++) {
            dp[j] = max(dp[j], dp[j - k*w[i]] + k*v[i]);
        }
    }
}
```

### ✅ 思路二：二进制拆分优化（Binary Optimization）

假设有一个物品：

```c++
重量 w = 2
价值 v = 3
数量 c = 13
```

这意味着你可以选 0~13 个这样的物品。

现在我们用 **二进制拆分**：

```c++
13 = 1 + 2 + 4 + 6
```

于是我们可以生成 4 个「新物品」，把 `cnt[i]` 拆成若干个 0-1 物品。这样问题就变成了**若干个 0-1 背包问题**。

我们把这 4 件新物品放进普通 0-1 背包算法里，每件物品只能选 0 或 1 次。

### 💻 代码模板

```c++
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, W;
    cin >> n >> W;
    vector<int> w(n + 1), v(n + 1), c(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> w[i] >> v[i] >> c[i];

    // step 1: 二进制拆分
    vector<pair<int,int>> items; // (weight, value)
    for (int i = 1; i <= n; i++) {
        int num = c[i], k = 1;
        while (num > 0) {
            int use = min(k, num);
            items.push_back({w[i] * use, v[i] * use});
            num -= use;
            k <<= 1;
        }
    }

    // step 2: 0-1 背包
    vector<int> dp(W + 1, 0);
    for (auto [wt, val] : items) {
        for (int j = W; j >= wt; j--) {
            dp[j] = max(dp[j], dp[j - wt] + val);
        }
    }

    cout << dp[W] << "\n";
}

```

### 4.4、体积/费用多维背包（Multi-dimensional Knapsack）

> 有多个约束维度，比如：
>
> - 容量（重量限制）
> - 时间（加工时间）
> - 资金（成本）

### ✅ 状态定义

例如：两个限制（重量 W、时间 T）
$$
dp[w][t] = 不超过重量 w 和时间 t 时的最大价值
$$

------

### ✅ 转移方程

$$
dp[w][t] = \max(dp[w][t], dp[w - weight[i]][t - time[i]] + value[i])
$$

------

### 💻 代码模板

```c++
int W, T, n;
cin >> n >> W >> T;
vector<int> w(n+1), t(n+1), v(n+1);
for (int i = 1; i <= n; i++) cin >> w[i] >> t[i] >> v[i];

vector<vector<int>> dp(W+1, vector<int>(T+1, 0));

for (int i = 1; i <= n; i++) {
    for (int ww = W; ww >= w[i]; ww--) {
        for (int tt = T; tt >= t[i]; tt--) {
            dp[ww][tt] = max(dp[ww][tt],
                             dp[ww - w[i]][tt - t[i]] + v[i]);
        }
    }
}
cout << dp[W][T];
```

------

## 🧩 5. 经典模型 III：区间 DP

### 🧩 一、区间 DP 的本质

### 🧠 定义：

> 对于一段区间 `[l, r]`，你要求某种最优值（或可行性），
>  并且可以通过划分子区间 `[l, k]` 和 `[k+1, r]` 来合并子问题。

因此它的状态表示通常是：
$$
dp[l][r] = \text{区间 [l,r] 的最优结果}
$$

### 🧩 转移通式：

$$
dp[l][r] = \min_{k \in [l,r-1]} \{ dp[l][k] + dp[k+1][r] + \text{cost}(l, r, k) \}
$$

- `dp[l][k]`：左半段的最优代价
- `dp[k+1][r]`：右半段的最优代价
- `cost(l, r, k)`：合并 `[l,k]` 与 `[k+1,r]` 所需的额外代价（如两堆石头合并）

### 🧩 计算顺序：

必须保证子区间已计算完再计算大区间
 → 按「区间长度」递增遍历：

```c++
for (int len = 2; len <= n; len++)
  for (int l = 1; l + len - 1 <= n; l++) {
      int r = l + len - 1;
      dp[l][r] = INF;
      for (int k = l; k < r; k++)
          dp[l][r] = min(dp[l][r], dp[l][k] + dp[k+1][r] + cost(l,r,k));
  }
```

经典模版，时间复杂度：**O(n³)**。

### 🪨 典型例题

| 问题                 | 状态定义               | cost(l,r,k)      | 说明                   |
| -------------------- | ---------------------- | ---------------- | ---------------------- |
| **石子合并**         | 合并 [l,r] 的最小代价  | 区间和           | 每次合并代价为区间总和 |
| **矩阵连乘**         | 计算矩阵链乘法最少次数 | p[l-1]*p[k]*p[r] | 括号化顺序             |
| **括号匹配**         | 最少删除/修改次数      | 特殊规则         | 子区间是否能配对       |
| **凸多边形三角剖分** | 最小三角形权和         | w(l,k,r)         | 多边形 DP 模型         |

------

### 🧮 石子合并示例

有 `n` 堆石子排成一行，第 `i` 堆有 `a[i]` 个。每次你可以合并相邻两堆石子，代价是它们的石子总数。
 合并后这两堆变成一堆。
 问：把所有石子合并成一堆的最小总代价。

### 🧠 思路分析

我们要求「区间 `[l, r]` 合并成一堆的最小代价」。

### ✅ 状态定义：

$$
dp[l][r] = \text{合并 [l,r] 区间成一堆的最小代价}
$$

### ✅ 状态转移：

考虑最后一次合并前，区间 `[l,r]` 被分成两部分 `[l,k]` 和 `[k+1,r]`：
$$
dp[l][r] = \min_{l \le k < r} \big( dp[l][k] + dp[k+1][r] + \text{sum}(l,r) \big)
$$
其中：
$$
\text{sum}(l,r) = \sum_{i=l}^r a[i] = \text{前缀和差：} pre[r] - pre[l-1]
$$

### ✅ 初始化：

单个石堆不需要合并：
$$
dp[i][i] = 0
$$

### 🧮 实现细节

- 预处理前缀和 `pre[i]`；
- 按区间长度 `len` 从小到大枚举；
- 三重循环（O(n³)）计算最小代价。

------

### 💻 完整代码（C++）

```c++
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> a(n + 1), pre(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pre[i] = pre[i - 1] + a[i];
    }

    vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, 0));

    for (int len = 2; len <= n; len++) {     // 区间长度
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            dp[l][r] = LLONG_MAX;
            for (int k = l; k < r; k++) {
                long long cost = dp[l][k] + dp[k + 1][r] + pre[r] - pre[l - 1];
                dp[l][r] = min(dp[l][r], cost);
            }
        }
    }
    cout << dp[1][n] << "\n";
    return 0;
}
```

### ⚙️ 复杂度优化思想

`O(n³)` 的枚举太慢，可以用数学性质加速。

### 1️⃣ **四边形不等式优化 (Quadrangle Inequality)**

若代价函数满足：
$$
\text{opt}(l,r-1) \le \text{opt}(l,r) \le \text{opt}(l+1,r)
$$
即最优划分点 **单调不减**，
 可用 **Knuth Optimization** 将枚举 `k` 降为常数范围。

复杂度降为：**O(n²)**。

**适用条件：**

- 代价函数满足“单调性 + 四边形不等式”；
- 常见如：石子合并、矩阵连乘。

### 2️⃣ **Divide & Conquer Optimization**

若转移方程为：
$$
dp[i][j] = \min_{k \le j} \{ dp[i-1][k] + C(k,j) \}
$$
且最优决策点单调（`opt[i][j-1] ≤ opt[i][j]`），
 可用分治法优化为 **O(n log n)** 或 **O(n²)**。

> 用在多阶段分组型问题（如分割数组最小代价）。

***

### 🧩 6. 经典模型 IV：树上 DP

### 1️⃣ 基本定义

> **树上 DP** 是指在树结构上进行动态规划，通过递归遍历（通常用 DFS）在子树间传递状态。

核心思想是：

- 通过 `dfs(u, fa)` 计算以节点 `u` 为根的子树信息；
- 根据子节点的 `dp[v]` 值，合并到父节点；
- 通常状态间存在「选 / 不选」、「删 / 留」、「包含 / 不包含」等二元关系。

### 2️⃣ 常用结构

```c++
void dfs(int u, int fa) {
    for (int v : adj[u]) {
        if (v == fa) continue;
        dfs(v, u);
        // 根据 dp[v] 更新 dp[u]
    }
}
```

注意点：

- `fa`（父节点）防止回到上层。
- 子树信息合并时，可以使用「临时数组」「前后缀 DP」等技巧。

### 3️⃣ 常见模型与转移

| 模型               | 状态设计                                 | 状态转移                                                     | 备注             |
| ------------------ | ---------------------------------------- | ------------------------------------------------------------ | ---------------- |
| **树的最大独立集** | `dp[u][0/1]`：u 不选 / 选                | `dp[u][1] = val[u] + Σ dp[v][0]` `dp[u][0] = Σ max(dp[v][0], dp[v][1])` | 无相邻点同时选   |
| **树的直径**       | `dp[u]`：以 u 为根的最长下行路径         | 取子树最大两条路径相加更新答案                               | 经典双 DFS       |
| **树形背包**       | `dp[u][k]`：子树 u 中选 k 个节点的最优值 | 枚举子节点合并：多重背包式转移                               | O(n·K²) 或优化版 |
| **树的重心**       | `sz[u]` 子树大小，`max_sub` 最大子树     | `max(max_sub, n - sz[u])` 最小者为重心                       | 结构分析类 DP    |
| **树的路径和**     | `dp[u]`：从 u 出发的最大路径             | 合并所有子树的下行最大路径更新全局                           | 与直径类似       |

### 🌳 示例：树的最大独立集

> 题意：在一棵树中选点，使得没有相邻点同时被选，求点权和最大。

### ✅ 状态定义

```c++
dp[u][0] = 子树u中，u不选时的最大权和
dp[u][1] = 子树u中，u选时的最大权和
```

### ✅ 状态转移

```c++
dp[u][1] = val[u] + Σ dp[v][0]
dp[u][0] = Σ max(dp[v][0], dp[v][1])
```

### ✅ 实现代码

```c++
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
vector<int> g[N];
int n;
long long val[N], dp[N][2];

void dfs(int u, int fa) {
    dp[u][1] = val[u];
    dp[u][0] = 0;
    for (int v : g[u]) {
        if (v == fa) continue;
        dfs(v, u);
        dp[u][1] += dp[v][0]; // 选u -> 子节点不能选
        dp[u][0] += max(dp[v][0], dp[v][1]); // 不选u -> 子节点可选可不选
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> val[i];
    for (int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(1, 0);
    cout << max(dp[1][0], dp[1][1]) << "\n";
}
```

### 🌲 示例二：树的直径

> 树的直径 = 任意两点之间的最长路径长度。

### ✅ 两种写法

1️⃣ **两次 DFS：**

- 先从任意点出发，找最远的点 X；
- 再从 X 出发，找最远的点 Y；
- 距离 X-Y 即为直径。

2️⃣ **树 DP：**

```c++
int dp[u] = 以u为根的最长下行路径
ans = max(ans, dp[v1] + dp[v2])
```

### ✅ 实现

```c++
int ans = 0;
int dfs(int u, int fa) {
    int best1 = 0, best2 = 0;
    for (int v : g[u]) if (v != fa) {
        int d = dfs(v, u) + 1;
        if (d > best1) { best2 = best1; best1 = d; }
        else if (d > best2) best2 = d;
    }
    ans = max(ans, best1 + best2);
    return best1;
}
```

### 🎒 示例三：树形背包（Tree Knapsack）

> 给一棵树，每个节点有“价值”和“代价”，要在子树中选出不超过 K 个节点使价值最大。

### ✅ 状态：

$$
dp[u][k] = 在以u为根的子树中选k个节点的最大价值
$$

### ✅ 转移：

- 类似多重背包，逐个子节点合并；
- 每次合并都用临时数组。

### ✅ 实现思路（伪码）：

```C++
void dfs(int u, int fa) {
    dp[u][1] = val[u];
    sz[u] = 1;
    for (int v : g[u]) if (v != fa) {
        dfs(v, u);
        for (int i = sz[u]; i >= 1; i--)
            for (int j = 1; j <= sz[v]; j++)
                dp[u][i + j] = max(dp[u][i + j], dp[u][i] + dp[v][j]);
        sz[u] += sz[v];
    }
}
```

> 23-24_Jan Silver:  Potion Farming

------

## 🧩 7. 经典模型 V：图上 DP（DAG）

- 在 DAG 上按拓扑序进行转移（最长路/计数路径）。
- 也可作为“序列 DP 的广义版”。

------

## 🧩 8. 经典模型 VI：数位 DP（Digit DP）

- 问题：统计区间 [0..N] 中满足某性质的整数个数。
- 状态：`f[pos][tight][lead][...属性...]`
- 细节：处理**前导零**与**上界约束 tight**；通常 `O(位数 * 状态数 * 备选数字)`。

------

## 🧩 9. 经典模型 VII：状压 DP（Bitmask）

- 适用：`n ≤ 20~25` 的子集枚举类，如**TSP**、**分配问题**、**最大团近似**。
- 例（TSP 最短路）：`dp[mask][u] = 访问过 mask，当前在 u 的最短路`，转移枚举下一个点。

------

## 🧩 10. 常见优化

### 10.1 空间优化（滚动数组）

- 条件：`f[i]` 仅依赖 `f[i-1]`；注意遍历方向防止“新值污染旧值”。

### 10.2 单调队列优化（Convex/Monotone Queue）

- 例：`dp[i] = min(dp[i-1]) + cost(i)` + **窗口限制**；或**斜率优化**对应 `w[i]` 单调。

### 10.3 斜率优化（Convex Hull Trick, CHT）

- 形式：`dp[i] = min_j (m_j * x_i + b_j)`，维护下凸包；在线/离线两种实现。

### 10.4 分治优化

- 形式：`dp[l..r]` 的决策点 `opt[l..r]` 单调，递归分治求最优决策，复杂度从 `O(n^2)` 降至 `O(n log n)`。

### 10.5 四边形不等式（Knuth 优化）

- 适用形如区间合并的 DP，需满足 `opt[l][r-1] ≤ opt[l][r] ≤ opt[l+1][r]`。

### 10.6 Bitset 加速

- 如 0-1 背包可用位运算将 `O(nW)` 降为 `O(W/word_size * n)`，或求可达和集合。

------

## 🧩 11. 复杂度评估 & 迁移思维

- **状态数 × 转移代价 = 总复杂度**；先减状态，再减转移。
- 当 `n, m, W` 较大：考虑**近似/期望 DP**、**分层图**、**混合贪心**、**启发式搜索**。



------

## 13. 课堂示例 A：0-1 背包（滚动一维）

**题意**：容量 `W`，`n` 件物品 `(w_i, v_i)`，求最大价值。
 **状态**：`dp[w]`
 **初始化**：`dp[0]=0，其余 -inf`（或 0 取“不能超过容量”的意义）
 **转移**：`for i in items: for w=W..w_i: dp[w] = max(dp[w], dp[w-w_i]+v_i)`
 **注意**：倒序遍历 `w`，防重复使用。

------

## 14. 课堂示例 B：区间石子合并（Knuth 条件）

**题意**：n 堆石子环/链合并成一堆，费用为区间和。
 **状态**：`dp[l][r]`
 **转移**：`dp[l][r] = min_k dp[l][k]+dp[k+1][r]+sum(l,r)`
 **优化**：若满足四边形不等式，`O(n^2)` 实现；否则 `O(n^3)`。

------

## 15. 课堂示例 C：树的最大独立集

**状态**：`dp[u][0/1]`
 **转移**见上一节；注意**树上背包**时子树合并顺序。

------

## 16. 课堂示例 D：数位 DP（无相邻重复数字计数）

**状态**：`f[pos][last_digit][tight][lead]`
 **转移**：枚举当前位 `d`，若 `tight` 则 `d ≤ limit[pos]`；若 `lead` 则可放 0 且不受相邻约束。

------

## 17. 课堂示例 E：TSP 状压 DP

**状态**：`dp[mask][u]`
 **转移**：从 `u` 走到 `v`：`dp[mask|1<<v][v] = min(...)`
 **复杂度**：`O(n^2 · 2^n)`，`n≤20` 以内可做。

------

## 18. 竞赛常见题型映射

- USACO/NOIP：背包族、区间石子、树独立集/直径、DAG 路径计数、数位 DP。
- LeetCode 高频：打家劫舍、零钱兑换、不同路径、编辑距离、LCS/LIS 变体、正则匹配。

------

## 19. 训练题单（由易到难）

1. **入门**：爬楼梯、斐波那契、不同路径、0-1 背包、LCS
2. **进阶**：石子合并、编辑距离、树的最大独立集、完全背包、多重背包
3. **提高**：区间 DP 优化（Knuth/分治）、TSP、数位 DP（不含某数位）、DAG 最长路
4. **挑战**：CHT 斜率优化类、树上背包、分组背包 + 单调队列、期望 DP

> 作业建议：每类至少 2 题；写出**状态定义与转移式**，并在代码顶部注释。

------

## 20. 一页速查表（可打印）

- **套路**：定义状态 → 写转移 → 定边界 → 定顺序 → 找答案。
- **常用初始化**：`max` 型置 `-inf`，`min` 型置 `+inf`；`dp[0]=0/1` 视语义。
- **顺序要诀**：
  - 线性依赖：小到大/大到小（背包）
  - 区间：按长度
  - 树上：后序 DFS
  - DAG：拓扑序
- **优化指针**：滚动数组 / 单调队列 / CHT / 分治 / Knuth / bitset
- **调试清单**：边界、方向、覆盖、污染、越界、取模、答案位置。

------

## 21. 附：黑板化推导范式（讲解用）

1. 画依赖图：节点=状态，边=转移。
2. 写原问题的“分解等式”。
3. 根据约束抉择**维度与下标**。
4. 写伪代码并手算一个小样例验证。
5. 再考虑是否可优化（单调性、凸性、分治）。

------

## 22. 参考代码片段（C++/Python）

> 课堂仅展示关键片段；完整代码建议课后自练。

**0-1 背包（C++，滚动一维）**

```cpp
for (int i=1;i<=n;i++){
  for (int w=W; w>=wi[i]; --w)
    dp[w]=max(dp[w], dp[w-wi[i]]+vi[i]);
}
```

**区间 DP 顺序**

```python
for length in range(2, n+1):
    for l in range(1, n-length+2):
        r = l + length - 1
        for k in range(l, r):
            dp[l][r] = min(dp[l][r], dp[l][k]+dp[k+1][r]+cost(l,r))
```

------

