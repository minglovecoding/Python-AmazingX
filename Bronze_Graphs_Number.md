## 📚USACO 铜组：图论基础与数论基础

## 1. 内容

| 模块 | 内容 | 配套真题 | 课堂重点 |
| --- | --- | --- | --- |
| 图论入门 | 点、边、方向、度数、邻接表 | 自编基础练习 | 文字中的对象与关系分别对应什么 |
| 图论基础 | 相邻约束、染色与贪心 | [The Great Revegetation，2019 February Bronze P2](https://usaco.org/index.php?page=viewproblem2&cpid=916) | 为什么四种颜色足够，为什么可以选最小合法颜色 |
| 图论基础 | 反向建图、可达性、出度 | [Milk Factory，2019 US Open Bronze P2](https://usaco.org/index.php?page=viewproblem2&cpid=940) | “所有点到终点”如何变成“一次从终点搜索” |
| 图论提高 | 每个点的唯一后继、入度、二元环 | [Hoofball，2018 February Bronze P2](https://usaco.org/index.php?page=viewproblem2&cpid=808) | 从传球规则建立有向图，找必须投球的位置 |
| 数学入门 | 排序、正数性质、代数关系 | [Do You Know Your ABCs?，2020 December Bronze P1](https://usaco.org/index.php?page=viewproblem2&cpid=1059) | 不要把排序后的第三个数直接当成 C |
| 数论基础 | 奇偶性、余数、可行性判断 | [Even More Odd Photos，2021 January Bronze P2](https://usaco.org/index.php?page=viewproblem2&cpid=1084) | 只记录奇数、偶数的数量是否足够 |
| 数论迁移 | 模 10、回文性质、必胜与必败 | [Palindrome Game，2024 February Bronze P1](https://usaco.org/index.php?page=viewproblem2&cpid=1395) | 先证明规律，再把大整数问题缩成末位判断 |
| 数学迁移 | 数轴、绝对值、倍增序列 | [The Lost Cow，2017 US Open Bronze P1](https://usaco.org/index.php?page=viewproblem2&cpid=735) | 区分“相对最初起点的目标”和“本轮移动距离” |
| 数论提高 | 十进制、进位、区间计数 | [Roundabout Rounding，2024 December Bronze P1](https://usaco.org/index.php?page=viewproblem2&cpid=1443) | 从小数据暴力发现区间，并证明边界 |
| 补充基础 | 整除、约数、gcd、lcm、质数判定 | 自编练习 | 理解适用条件与整数溢出 |

---

## 第一部分：图论基础

## 图：用点和边表示关系

**图由节点和边组成。节点表示对象，边表示对象之间的关系。**

| 题目中的对象 | 节点 | 边 |
| --- | --- | --- |
| 农场与道路 | 农场 | 两个农场之间的道路 |
| 草地种植限制 | 草地 | 两片草地必须种不同类型 |
| 奶牛传球 | 奶牛 | 一头牛把球传给另一头牛 |
| 排队相邻限制 | 奶牛 | 两头牛必须相邻 |

建图前先回答：**这条关系有没有方向？**

### 2.1 无向图与有向图

- 无向边 `(u,v)`：关系是双向的，如两块草地不能同色。
- 有向边 `u→v`：关系有方向，如牛 `u` 把球传给牛 `v`。

```mermaid
graph LR
    A["草地 1"] --- B["草地 2"]
    B --- C["草地 3"]
    C --- A
```

上图有一个环：从一个节点出发，沿不同的边绕一圈可以回到起点。

### 2.2 度数、入度与出度

| 概念 | 含义 | 代码记录 |
| --- | --- | --- |
| 无向图的度数 | 与节点相连的边数 | `degree[u]` |
| 有向图的入度 | 指向节点的边数 | `indegree[u]` |
| 有向图的出度 | 从节点出发的边数 | `outdegree[u]` |

读入一条有向边 `u→v`：

```cpp
outdegree[u]++;
indegree[v]++;
```

注意：**入度不是能到达该节点的节点总数。** 它只统计直接指向它的边。

### 2.3 路径、可达性、连通块与树

- 路径：沿边依次经过若干节点形成的路线；简单路径不重复节点。
- 可达：能沿边从一个节点走到另一个节点；有向图必须遵守方向。
- 无向连通块：彼此可以到达的一组节点。
- 树：连通且无环的无向图；`N` 个节点有 `N-1` 条边。

**有 `N-1` 条边不一定是树，还需要连通。**

树的关键性质：任意两个不同节点之间恰好有一条简单路径。

---

## 3. 图的存储

### 3.1 邻接表

假设已读入节点数 `n` 和边数 `m`：

```cpp
vector<vector<int>> adj(n + 1);
for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);  // 无向图加入两个方向
}
```

有向图只加入规定方向：

```cpp
adj[u].push_back(v);  // u -> v
```

遍历邻居：

```cpp
for (int v : adj[u]) {
    // 处理 u 的邻居 v
}
```

空间复杂度为 `O(N+M)`。

### 3.2 邻接矩阵（了解）

```cpp
vector<vector<bool>> edge(n + 1, vector<bool>(n + 1, false));
edge[u][v] = true;
edge[v][u] = true;
```

可以 `O(1)` 判断两点是否直接相连，但空间为 `O(N²)`。适合节点数较小的题。

---

## 4. 遍历：从一个点出发能到达哪里

以下两个函数均假设节点编号为 `1..N`，输入邻接表已按正确方向建立。

### 4.1 DFS：显式栈写法

```cpp
vector<int> reachableDFS(int start, const vector<vector<int>>& adj) {
    vector<int> visited(adj.size(), 0);
    stack<int> st;
    visited[start] = 1;
    st.push(start);

    while (!st.empty()) {
        int u = st.top();
        st.pop();
        for (int v : adj[u]) {
            if (visited[v]) continue;
            visited[v] = 1;
            st.push(v);
        }
    }
    return visited;
}
```

**入栈时标记**，避免同一个节点被多条边重复加入。

### 4.2 BFS：队列写法

```cpp
vector<int> reachableBFS(int start, const vector<vector<int>>& adj) {
    vector<int> visited(adj.size(), 0);
    queue<int> q;
    visited[start] = 1;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (visited[v]) continue;
            visited[v] = 1;
            q.push(v);
        }
    }
    return visited;
}
```

两种方法都能判断可达性，时间 `O(N+M)`，空间 `O(N)`，不含传入的图。

| 需求 | 可以使用 |
| --- | --- |
| 只判断能否到达 | DFS 或 BFS |
| 无权图中求最少经过几条边 | BFS，并额外记录距离 |
| 有环图防止重复访问 | 使用 `visited` |

铜组阶段先理解“哪些节点能访问到”，不必一开始就扩展到复杂最短路。

---

## 5. 真题：The Great Revegetation——相邻约束与四种颜色

- **2019 February Bronze P2**。
- [官方题目](https://usaco.org/index.php?page=viewproblem2&cpid=916)
- 数据：`N≤100，M≤150`；每个节点的度数不超过 `3`。

### 题意

每片草地选择一种编号为 `1..4` 的草。每条限制要求两片草地颜色不同。输出按草地编号排列后字典序最小的合法颜色串。

### 思路：按编号选最小可用颜色

依次处理 `u=1..N`，将已染色邻居用过的颜色标记为不可用，再选择最小的可用颜色。

```cpp
bool used[5] = {};
for (int v : adj[u]) {
    if (color[v] != 0) used[color[v]] = true;
}
for (int c = 1; c <= 4; c++) {
    if (!used[c]) {
        color[u] = c;
        break;
    }
}
```

### 为什么不会把后面逼进死路

每个节点最多有 `3` 个邻居，因此在为它染色时，最多禁用 `3` 种颜色。总有至少一种颜色可以选。

这不仅保证当前能选，还保证无论之前怎么合法选择，后面的节点都能继续完成。

### 为什么字典序最小

固定此前的选择，当前选最小合法颜色，而且后面一定能完成。任何在当前位选择更大颜色的方案，字典序都更大。

### 手算示例（自编）

限制边为 `(1,2)、(1,3)、(2,3)、(3,4)`。

| 当前草地 | 已染色邻居禁用的颜色 | 选择 |
| --- | --- | --- |
| 1 | 无 | 1 |
| 2 | 1 | 2 |
| 3 | 1、2 | 3 |
| 4 | 3 | 1 |

结果为 `1231`。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> color(n + 1, 0);
    for (int u = 1; u <= n; u++) {
        bool used[5] = {};
        for (int v : adj[u]) used[color[v]] = true;
        for (int c = 1; c <= 4; c++) {
            if (!used[c]) {
                color[u] = c;
                break;
            }
        }
    }
    for (int u = 1; u <= n; u++) cout << color[u];
    cout << '\n';
}
```

`used[0]` 可以被标记，但不参与颜色选择，效果等价于忽略尚未染色的邻居。

复杂度：时间 `O(N+M)`，空间 `O(N+M)`。

**课堂追问：**若只有三种颜色，原来的“后面一定能完成”证明还成立吗？不成立，度数不超过三仍可能出现需要四种颜色的图，例如四节点完全图。

---

## 6. 真题：Milk Factory——把所有点到终点改成反向搜索

- **2019 US Open Bronze P2**。
- [官方题目](https://usaco.org/index.php?page=viewproblem2&cpid=940)
- 数据：`N≤100`；底层无向图是一棵树，每条边被指定一个方向。

### 题意

寻找能从其他所有节点到达的节点。若不存在，输出 `-1`。

### 方法一：枚举终点，反向搜索

原图中 `u→v`，在反图存 `v→u`。

原图中存在 `x→…→target`，等价于反图中存在 `target→…→x`。

因此枚举候选终点，从它在反图中搜索，能访问全部节点就说明可行。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> rev(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        rev[v].push_back(u);
    }

    for (int target = 1; target <= n; target++) {
        vector<int> visited(n + 1, 0);
        queue<int> q;
        q.push(target);
        visited[target] = 1;
        int count = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            count++;
            for (int v : rev[u]) {
                if (visited[v]) continue;
                visited[v] = 1;
                q.push(v);
            }
        }
        if (count == n) {
            cout << target << '\n';
            return 0;
        }
    }
    cout << -1 << '\n';
}
```

正确性来自反向路径的一一对应。按编号升序枚举，第一次找到的即为最小编号答案。

复杂度：时间 `O(N²)`，空间 `O(N)`。本题只有 `N-1` 条边，单次遍历为 `O(N)`。

### 方法二：唯一零出度点（选学）

由于底层是一棵树，不可能形成有向环。

1. 从任意点沿出边前进，最终一定停在一个零出度点。
2. 若零出度点唯一，所有节点都可以到达它。
3. 若存在多个零出度点，它们之间不能到达，不存在答案。

可以只统计出度，得到 `O(N)` 解法。这里的结论依赖无有向环，一般有向图不能直接套用。

**手算：**`1→2←3` 的答案是 `2`；`1←2→3` 有两个零出度点，答案为 `-1`。

---

## 7. 真题：Hoofball——传球关系、入度和二元环

- **2018 February Bronze P2**。
- [官方题目](https://usaco.org/index.php?page=viewproblem2&cpid=808)
- 数据：`N≤100`，位置互不相同。
- 定位：图论提高题，可放在掌握入度、出度之后。

### 题意

每头牛收到球后，固定传给距离最近的另一头牛；距离相同时传给左边的牛。最初至少给多少头牛发球，才能让所有牛都持球至少一次？

### 第一步：把规则变成有向边

记 `to[u]` 为牛 `u` 的传球目标，建立边 `u→to[u]`。`N>1` 时每个节点恰好有一个出边。

不必一开始排序。由于 `N≤100`，直接枚举每头牛的所有候选目标即可，耗时 `O(N²)`。

### 第二步：入度为零的牛必须最初拿到球

没有其他牛给它传球，因此不主动给它球，它就永远不能拿到球。

每个入度为零的点都至少需要一个初始球。

### 第三步：处理没有入口的二元环

在数轴上，最近的另一头牛一定是排序后的相邻牛。有向环只能是相邻两头牛互相传球，不会出现长度大于二的环。

原因：只连接相邻位置的底层无向图是路径的一部分，不可能有长度大于二的无向环；长度大于二的有向环也就不可能出现。

如果 `u、v` 互相传球，并且两者入度都是 `1`，就没有环外的牛向它们传球，需要额外给这个环一个球。

如果环有外部节点指向它，则沿反向前驱不断寻找，最终会遇到一个入度为零的点；该点发出的球已经能够进入并覆盖这个环。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> x(n);
    for (int& v : x) cin >> v;
    if (n == 1) {
        cout << 1 << '\n';
        return 0;
    }

    vector<int> to(n, -1), indegree(n, 0);
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (u == v) continue;
            if (to[u] == -1 ||
                abs(x[u] - x[v]) < abs(x[u] - x[to[u]]) ||
                (abs(x[u] - x[v]) == abs(x[u] - x[to[u]]) &&
                 x[v] < x[to[u]])) {
                to[u] = v;
            }
        }
        indegree[to[u]]++;
    }

    int answer = 0;
    for (int u = 0; u < n; u++) {
        if (indegree[u] == 0) answer++;
    }
    for (int u = 0; u < n; u++) {
        int v = to[u];
        if (u < v && to[v] == u &&
            indegree[u] == 1 && indegree[v] == 1) {
            answer++;
        }
    }
    cout << answer << '\n';
}
```

复杂度：时间 `O(N²)`，空间 `O(N)`。

**手算示例（自编）：**位置为 `1、2、10、11`，有两个相互独立的互传对，需要 `2` 个球。

**易错点：**同距离时比较位置而不是输入编号；互传对只计算一次；`N=1` 时单独处理。

## 第二部分：数论基础与初等数学

## 8. 整数运算：先弄清楚除法和余数

### 8.1 整除与余数

对于 `a≥0，b>0`：

$$
a=b\left\lfloor\frac ab\right\rfloor+(a\bmod b),
\qquad 0\le a\bmod b<b.
$$

```cpp
int a = 17, b = 5;
cout << a / b << '\n';  // 3
cout << a % b << '\n';  // 2
```

- `a % b == 0`：`a` 能被 `b` 整除。
- `a % 2 == 0`：`a` 是偶数。
- `a % 10`：非负整数 `a` 的个位数。

C++ 对负整数除法向零截断，不能直接套非负整数的“向下取整”直觉。将负余数归一化到 `0..m-1`，其中 `m>0`：

```cpp
long long r = (a % m + m) % m;
```

### 8.2 向上取整

`a≥0，b>0` 时：

$$
\left\lceil\frac ab\right\rceil
=\left\lfloor\frac ab\right\rfloor+[a\bmod b\ne0].
$$

```cpp
long long groups = a / b + (a % b != 0);
```

例如 `17` 件物品，每箱最多 `5` 件，需要 `4` 箱。常见的 `(a+b-1)/b` 也适用，但应注意加法溢出。

### 8.3 奇偶性

| 运算 | 结果 |
| --- | --- |
| 偶数＋偶数 | 偶数 |
| 奇数＋奇数 | 偶数 |
| 奇数＋偶数 | 奇数 |
| 若干整数求和 | 只取决于其中奇数个数的奇偶性 |

**两个奇数的和可以作为一个偶数使用。** 这句话是后面分组题的关键。

---

## 9. 补充：约数、gcd、lcm 与质数

本节是整数基础补充，后面的精讲题不会强行套用这些工具。

### 9.1 枚举约数

若 `d` 是 `n` 的约数，那么 `n/d` 也是约数。两者至少有一个不超过 `sqrt(n)`。

```cpp
vector<long long> divisors(long long n) {
    vector<long long> result;
    for (long long d = 1; d <= n / d; d++) {
        if (n % d != 0) continue;
        result.push_back(d);
        if (d != n / d) result.push_back(n / d);
    }
    sort(result.begin(), result.end());
    return result;
}
```

约定 `n≥1`。枚举检查次数为 `O(sqrt(n))`，排序另计。完全平方数的平方根不要重复加入。

### 9.2 最大公约数 gcd

`gcd(a,b)` 是同时整除 `a、b` 的最大正整数，其中 `a、b` 非负且不同时为零。

辗转相除法：

$$
\gcd(a,b)=\gcd(b,a\bmod b).
$$

```cpp
long long gcdValue(long long a, long long b) {
    while (b != 0) {
        long long r = a % b;
        a = b;
        b = r;
    }
    return a;
}
```

例：`gcd(24,18)=gcd(18,6)=gcd(6,0)=6`。

时间 `O(log(max(a,b)))`。C++17 也可以直接使用 `std::gcd(a,b)`。

### 9.3 最小公倍数 lcm

对于正整数：

$$
\operatorname{lcm}(a,b)=\frac a{\gcd(a,b)}\times b.
$$

```cpp
long long lcm = a / gcd(a, b) * b;
```

先除后乘可以降低中间溢出风险，但仍需要保证最终结果能用 `long long` 表示。

**不要混淆：**“两件事周期同时发生”可能用 lcm；“最大等长切分”可能用 gcd。先确认题目条件，不能只看关键词。

### 9.4 质数判定

质数是大于 `1`、正约数只有 `1` 和自己的整数。

```cpp
bool isPrime(long long n) {
    if (n < 2) return false;
    for (long long d = 2; d <= n / d; d++) {
        if (n % d == 0) return false;
    }
    return true;
}
```

时间 `O(sqrt(n))`。若需要判断大量整数，后续再学习筛法。

---

## 10. 真题：Do You Know Your ABCs?——排序与代数关系

- **2020 December Bronze P1**。
- [官方题目](https://usaco.org/index.php?page=viewproblem2&cpid=1059)

### 题意

给出乱序的七个数：`A、B、C、A+B、A+C、B+C、A+B+C`，其中 `0<A≤B≤C`。恢复 `A、B、C`。

### 思路

将七个数从小到大排序，记为 `v[0..6]`：

- 最小值是 `A`。
- 第二小值是 `B`。所有包含正数相加的组合都不会比 `B` 更小。
- 最大值是 `A+B+C`。

因此：

$$
A=v[0],\quad B=v[1],\quad C=v[6]-v[0]-v[1].
$$

### 为什么不能直接取前三个

自编反例：`A=1，B=2，C=10`。

七个数排序后为 `1、2、3、10、11、12、13`。第三小值是 `A+B=3`，不是 `C`。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<long long> v(7);
    for (auto& x : v) cin >> x;
    sort(v.begin(), v.end());
    cout << v[0] << ' ' << v[1] << ' '
         << v[6] - v[0] - v[1] << '\n';
}
```

复杂度：输入规模固定为七个数，时间和空间均为 `O(1)`。

**易错点：**输入允许重复数，不要去重；证明依赖 `A、B、C` 都是正数。

---

## 11. 真题：Even More Odd Photos——把数值转成奇偶数量

- **2021 January Bronze P2**。
- [官方题目](https://usaco.org/index.php?page=viewproblem2&cpid=1084)
- 数据：`2≤N≤1000`。

### 题意

可以重新分组、重新排列所有牛。每头牛恰好属于一个非空组，要求各组编号和依次为“偶、奇、偶、奇……”；求最多组数。

### 11.1 哪些信息有用

只需要知道偶数数量 `even` 和奇数数量 `odd`，具体数值及原顺序都不影响分组和的奇偶性。

### 11.2 枚举最终组数

若最终分成 `k` 组，则需要：

$$
O=\left\lfloor\frac k2\right\rfloor
\quad\text{个奇数组},\qquad
E=\left\lceil\frac k2\right\rceil
\quad\text{个偶数组}.
$$

判断三个条件：

1. `odd≥O`：每个奇数组至少需要一个奇数。
2. `(odd-O)%2==0`：总和的奇偶性必须与奇数组数量一致。
3. `even+(odd-O)/2≥E`：预留 `O` 个奇数后，剩下每两个奇数可以合成一个偶数资源，加上原有偶数，足够形成 `E` 个非空偶数组。

### 为什么条件充分

先给每个奇数组放一个奇数，再将剩余奇数两两配对。每对奇数与每个原有偶数都可以充当一个“偶数资源”。

给每个偶数组至少一个偶数资源，剩余的资源任意加入已有组，都不改变该组奇偶性。这样全部元素都能用完。

因此从 `k=N` 向下枚举，第一个可行值就是最大答案。

### 手算示例（自编）

有 `2` 个偶数、`3` 个奇数。

- `k=5`：需要 `2` 个奇数组，剩下 `1` 个奇数，无法成对，不可行。
- `k=4`：仍需要 `2` 个奇数组，不可行。
- `k=3`：需要 `1` 个奇数组，剩下两个奇数可以配对；偶数资源足够，可行。

答案为 `3`。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int even = 0, odd = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (x % 2 == 0) even++;
        else odd++;
    }

    for (int k = n; k >= 1; k--) {
        int needOdd = k / 2;
        int needEven = (k + 1) / 2;
        if (odd < needOdd) continue;
        int rest = odd - needOdd;
        if (rest % 2 != 0) continue;
        if (even + rest / 2 < needEven) continue;
        cout << k << '\n';
        return 0;
    }
}
```

复杂度：时间 `O(N)`，额外空间 `O(1)`。

**易错点：**必须使用全部牛；第一组必须是偶数组；不能简单输出 `2*min(even,odd)`。

---

## 12. 真题：Palindrome Game——回文性质与模 10

- **2024 February Bronze P1**。
- [官方题目](https://usaco.org/index.php?page=viewproblem2&cpid=1395)

### 题意

初始有一个很大的正整数 `S` 个石子，双方轮流拿走一个正回文数数量的石子，不能超过剩余数量，无石子可拿的人输。Bessie 先手，双方最优，判断谁赢。

### 从小数据观察

`1..9` 都可以一次拿完。`10` 无法一次拿完，而且无论拿走 `1..9` 中哪个，对方都能一次拿完余数。

猜测：`10` 的倍数是必败态，其余是必胜态。

**观察不是证明。下面证明两个方向。**

### 12.1 10 的倍数不能走到另一个 10 的倍数

正回文数没有前导零，因此首位不是零；末位与首位相同，也不是零。

所以正回文数不能被 `10` 整除。一个 `10` 的倍数减去正回文数后，余数一定不是 `10` 的倍数。

### 12.2 非 10 的倍数总能走到 10 的倍数

设当前数的个位为 `d∈{1,...,9}`。单个数字 `d` 就是正回文数，拿走 `d` 个石子后，剩余数量成为 `10` 的倍数，可能为零。

以 `0` 为必败态，按剩余石子数归纳：

- 10 的倍数只能走向必胜态，因此是必败态。
- 非 10 的倍数至少有一步走向必败态，因此是必胜态。

### 大整数怎么办

题目允许 `S` 有多达 `10^5` 位，不能放进 `long long`。但判断能否被 `10` 整除只需末位字符。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        cout << (s.back() == '0' ? 'E' : 'B') << '\n';
    }
}
```

复杂度：每例时间 `O(L)`，主要用于读取长度为 `L` 的字符串；空间 `O(L)`。读入后判定仅需 `O(1)`。

**课堂追问：**`12021` 本身是回文数，而 `12000` 不是；但判定胜负时不需要判断整个输入是否回文。

---

## 13. 真题：The Lost Cow——数轴、绝对值与倍增

- **2017 US Open Bronze P1**。
- [官方题目](https://usaco.org/index.php?page=viewproblem2&cpid=735)
- 定位：初等数学与模拟的交叉练习。

### 题意

从 `x` 出发，目标位置依次是 `x+1、x-2、x+4、x-8……`，直到走到 `y` 为止，求总路程。输入保证 `x≠y`。

### 区分三个量

| 变量 | 含义 |
| --- | --- |
| `x` | 最初起点，始终不变 |
| `current` | 当前实际位置 |
| `offset` | 本轮目标相对最初起点的偏移量：1、-2、4、-8…… |

本轮目标是 `next=x+offset`，不是 `current+offset`。

如果 `y` 在本轮线段上，就只走到 `y`；否则走完整段。

### 手算

`x=3，y=6`：

| 路段 | 走过距离 |
| --- | --- |
| 3→4 | 1 |
| 4→1 | 3 |
| 1→6，在到达目标 7 前找到牛 | 5 |

总计 `9`。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long x, y;
    cin >> x >> y;
    long long current = x, offset = 1, answer = 0;
    while (true) {
        long long next = x + offset;
        if (min(current, next) <= y && y <= max(current, next)) {
            answer += abs(y - current);
            break;
        }
        answer += abs(next - current);
        current = next;
        offset *= -2;
    }
    cout << answer << '\n';
}
```

正确性：逐段模拟实际行走的线段，第一次包含 `y` 的线段上只累加到 `y` 的距离。

复杂度：偏移绝对值每轮翻倍，时间 `O(log(|x-y|+1))`，空间 `O(1)`。

**易错点：**目标偏移相对最初位置；路程不是当前位置的绝对值；最后一段不一定走完。

---

## 14. 真题：Roundabout Rounding——从进位模拟到区间计数

- **2024 December Bronze P1**。
- [官方题目](https://usaco.org/index.php?page=viewproblem2&cpid=1443)
- 数据：`T≤10^5，N≤10^9`。

### 14.1 题意

对每个整数 `x∈[2,N]`，令 `10^P` 是不小于 `x` 的最小十的幂。比较直接四舍五入到 `10^P` 与逐级四舍五入到十、百、千……再到 `10^P` 的结果，统计不同的个数。

### 14.2 正整数四舍五入的整数写法

`base` 为 `10、100、1000……` 时：

```cpp
long long rounded = (x + base / 2) / base * base;
```

不要用浮点数模拟整数进位。

手算：`48` 直接到百位得到 `0`；逐级为 `48→50→100`，结果不同。`44→40→0` 则结果相同。

### 14.3 先写小数据暴力（函数片段）

```cpp
bool different(long long x) {
    long long power = 10;
    while (power < x) power *= 10;

    long long direct = (x + power / 2) / power * power;
    long long chain = x;
    for (long long base = 10; base <= power; base *= 10) {
        chain = (chain + base / 2) / base * base;
    }
    return direct != chain;
}
```

适用于本题范围内的小数据实验。对所有 `2..N` 调用，耗时约 `O(N log N)`，不能直接应对最大输入。

### 14.4 找到差异区间

| 数位长度 | 最小差异数 | 最大差异数 | 区间长度 |
| --- | --- | --- | --- |
| 2 | 45 | 49 | 5 |
| 3 | 445 | 499 | 55 |
| 4 | 4445 | 4999 | 555 |
| 5 | 44445 | 49999 | 5555 |

单个数字的直接与逐级舍入相同。

### 14.5 为什么边界是这些数

对于 `d` 位数，直接舍入到 `10^d` 的进位门槛是 `5×10^(d-1)`。逐级舍入可能被较低位的进位提前推过这个门槛；舍入函数单调，因此满足条件的数构成连续区间。

设逐级舍入能进到 `10^d` 的最小 `d` 位整数为 `L_d`。两位时 `L_2=45`。

对更多位，先舍入到十位，再把末尾的零去掉，剩下就是规模小一位的同类舍入过程。要让这一步之后的数至少达到 `L_(d-1)`，必须满足：

$$
\left\lfloor\frac{x+5}{10}\right\rfloor\ge L_{d-1},
\qquad L_d=10L_{d-1}-5.
$$

于是依次得到 `45、445、4445……`。

只有直接舍入仍不进位的数会产生差异，上界为：

$$
R_d=5\times10^{d-1}-1,
\qquad R_2=49,\quad R_{d+1}=10R_d+9.
$$

### 14.6 区间与 [2,N] 的交集

每段 `[L,R]` 的贡献：

$$
\max(0,\min(N,R)-L+1).
$$

不用逐个枚举整数，只需枚举数位长度。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        ll left = 45, right = 49, answer = 0;
        while (left <= n) {
            answer += min(n, right) - left + 1;
            left = left * 10 - 5;
            right = right * 10 + 9;
        }
        cout << answer << '\n';
    }
}
```

复杂度：每例 `O(log N)` 时间、`O(1)` 空间。

**为什么使用 long long：**即使 `N≤10^9`，处理完九位区间后，下一次更新会生成十位边界，例如 `4444444445`，超过 32 位有符号整数范围。循环判断之前的更新也可能溢出。

**检查边界：**`N=44→0，45→1，49→5，100→5，444→5，445→6`。

---

## 15. 自编基础练习

本节全部为自编题，非 USACO 官方真题。

### 图论 A：统计度数

输入 `N、M` 以及 `M` 条无向边，输出每个节点的度数和孤立点数量。

自编输入：

```text
5 3
1 2
2 3
2 4
```

答案：度数依次为 `1、3、1、1、0`，孤立点 `1` 个。

**追问：**为什么度数和为 `2M`？每条边在两个端点各计算一次。

### 图论 B：可达性与反图

有向边为 `1→2、3→2、2→4、5→3`。

1. 从 `1` 能到达哪些点，包括自身？答案：`1、2、4`。
2. 哪些点能到达 `2`，包括自身？答案：`1、2、3、5`。
3. 用反图从 `2` 出发搜索，验证第二问。

### 数论 A：约数与质数

1. 输出 `36` 的全部正约数。答案：`1、2、3、4、6、9、12、18、36`。
2. 判断 `1、2、49、97` 是否为质数。答案：否、是、否、是。
3. 为什么枚举约数只需检查到平方根？为什么平方根只加入一次？

### 数论 B：gcd 与 lcm

1. 长度分别为 `24、18` 的两根绳子，要切成相同整数长度且无剩余，最长每段多长？答案：`6`。
2. 两个信号从时刻 `0` 同时开始，每隔 `12、18` 秒发出一次，下次同时发出是几秒后？答案：`36`。
3. 为什么第一问用 gcd，第二问用 lcm？请用“整除”关系说明。

### 数论 C：字符串求余

输入一个最多 `10^5` 位的非负十进制整数字符串和正整数 `m≤10^9`，求它除以 `m` 的余数。

若当前前缀余数为 `r`，加入新数字 `d`：

$$
r_{new}=(10r+d)\bmod m.
$$

```cpp
long long r = 0;
for (char c : s) r = (r * 10 + c - '0') % m;
```

输入 `123456789123456789`，`m=9`，答案为 `0`。这也是从 Palindrome Game 的“只看个位”走向一般大整数求余的练习。

### 数学 D：用小数据检验规律

写一个小程序，对 `N=1..10000` 比较 Roundabout Rounding 的暴力统计与区间统计。若不同，输出第一个反例。

**注意：**对拍能帮助发现错误，不能代替边界公式的证明。

## 16. 课后真题练习表

| 题目 | 比赛 | 考察知识点 | 课后完成要求 |
| --- | --- | --- | --- |
| [The Great Revegetation](https://usaco.org/index.php?page=viewproblem2&cpid=916) | 2019 February Bronze P2 | 无向图、邻接约束、贪心染色 | 独立写出建图和染色；解释四种颜色足够及字典序最小的原因 |
| [Milk Factory](https://usaco.org/index.php?page=viewproblem2&cpid=940) | 2019 US Open Bronze P2 | 有向图、反向建图、可达性、出度 | 先完成搜索版本，再说明唯一零出度优化依赖什么条件 |
| [Livestock Lineup](https://usaco.org/index.php?page=viewproblem2&cpid=965) | 2019 December Bronze P3 | 相邻关系、图建模、排列枚举 | 先用字典序全排列检查约束；再观察约束图为什么由链与孤立点组成 |
| [Hoofball](https://usaco.org/index.php?page=viewproblem2&cpid=808) | 2018 February Bronze P2 | 唯一后继、入度、二元环 | 画出传球图，解释零入度点与孤立互传对为什么需要初始球 |
| [Do You Know Your ABCs?](https://usaco.org/index.php?page=viewproblem2&cpid=1059) | 2020 December Bronze P1 | 正数性质、排序、代数 | 构造“排序后第三个数不是 C”的反例，并证明最小两个数的身份 |
| [Even More Odd Photos](https://usaco.org/index.php?page=viewproblem2&cpid=1084) | 2021 January Bronze P2 | 奇偶计数、枚举答案、可行性 | 不看代码重建三个可行条件；说明剩余元素如何全部分配 |
| [Palindrome Game](https://usaco.org/index.php?page=viewproblem2&cpid=1395) | 2024 February Bronze P1 | 模 10、回文性质、简单博弈 | 分别证明必败态不能到必败态、其余状态能到必败态 |
| [The Lost Cow](https://usaco.org/index.php?page=viewproblem2&cpid=735) | 2017 US Open Bronze P1 | 绝对值、区间、倍增、模拟 | 处理向左寻找和最后一段提前停止，解释目标位置相对谁计算 |
| [Roundabout Rounding](https://usaco.org/index.php?page=viewproblem2&cpid=1443) | 2024 December Bronze P1 | 进位、十进制边界、区间计数 | 先写暴力，再推导差异区间；解释 N 不超 int 为何仍使用 long long |

---

