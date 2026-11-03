## 📚动态规划：基础建模、序列 DP 与分段 DP

## 1. 内容

| 阶段 | 内容 | 配套练习 | 课堂重点 |
| --- | --- | --- | --- |
| 入门DP | 从递归到记忆化、递推 | 爬楼梯；[P1216 数字三角形](https://www.luogu.com.cn/problem/P1216) | 同一子问题为什么只算一次 |
| 基础 | LIS、LCS、子序列计数、编辑距离 | [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)；[P1140 相似基因](https://www.luogu.com.cn/problem/P1140) | 状态描述的是前缀，还是必须以某元素结尾 |
| 迁移 | 双序列进度 DP | [Radio Contact，2016 January Gold](https://usaco.org/index.php?page=viewproblem2&cpid=598) | 两条序列的消费进度构成二维状态 |
| 迁移 | 连续分段 DP | [P5124 Teamwork，2018 December Gold](https://www.luogu.com.cn/problem/P5124) | 枚举最后一段；边扩展边维护段内最大值 |
| 进阶 | 增加有限状态 | [P3609 Hoof, Paper, Scissors，2017 January Gold](https://www.luogu.com.cn/problem/P3609) | 把切换次数与当前手势加入状态 |
| 进阶 | 有序计数与组合 | [P5196 Cow Poetry，2019 January Gold](https://www.luogu.com.cn/problem/P5196) | 顺序敏感的完全背包式计数；按韵部汇总 |
| 拓展 | 进一步的分段代价 | [Snakes，2019 US Open Gold](https://usaco.org/index.php?page=viewproblem2&cpid=945)；[Taming the Herd，2018 February Gold](https://usaco.org/index.php?page=viewproblem2&cpid=815) | 在相同分段框架下替换 cost(l,r) |
| 选学 | 证明条件后的优化 | 前缀和；单调队列；分治优化 | 先写正确的朴素 DP，再分析瓶颈 |

## DP适用条件

1. 问题可分解成规模更小的子问题，例Fibonacci 序列、爬楼梯问题。
2. 子问题之间有重叠，而不是完全独立（否则分治更优），例最短路径、背包问题、LCS。
3. 满足最优子结构：全局最优由局部最优构成。
4. 状态数有限且可枚举。
5. 转移方向明确（无环依赖）。

**DP本质**：是在搜索树上“剪枝 + 缓存”的系统化过程。

## DP几大要素：

- 状态定义：决定了你在 DP 表中记录什么“信息”。
- 状态转移方程：当前状态如何由更小的状态得到。
- 边界初始化：决定状态计算的起点。
- 计算顺序。

| DP 类型      | 顺序                      |
| ------------ | ------------------------- |
| 线性 DP      | i 从小到大                |
| 背包（0-1）  | i 正序，w 倒序            |
| 背包（完全） | i 正序，w 正序            |
| 区间 DP      | 按区间长度 len 从小到大   |
| 树形 DP      | DFS 后序遍历              |
| DAG DP       | 拓扑排序                  |
| 数位 DP      | 高位 → 低位（递归记忆化） |

## 1、递推与记忆化搜索

约定有 n 阶楼梯，每次走 1 阶或 2 阶，求到第 n 阶的走法数。n=0 时，什么都不做算一种方案。本例限定 0≤n≤90，答案能用 long long 保存。

定义 f[i] 为到第 i 阶的方案数。最后一步只能从 i−1 或 i−2 到达，因此：

$$
f[i]=f[i-1]+f[i-2],\qquad f[0]=1,\quad f[1]=1.
$$


```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll memo[91];
ll solve(int n) {
    if (n <= 1) return 1;
    if (memo[n] != -1) return memo[n];
    return memo[n] = solve(n - 1) + solve(n - 2);
}
int main() {
    int n; cin >> n; // 教学约定：0 <= n <= 90。
    fill(memo, memo + 91, -1);
    //递推
    vector<ll> dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; ++i) {
        dp[i] += dp[i - 1];
        if (i >= 2) dp[i] += dp[i - 2];
    }
    cout << solve(n) << '\n' << dp[n] << '\n';
}
```

## 2. 序列 DP

### LIS：状态必须以当前元素结尾

给定一个序列 `a_1, a_2, ..., a_n`，求其中最长的 **严格递增子序列** 的长度。

```c++
输入:
8
10 9 2 5 3 7 101 18
输出:
4
```

- 状态：`dp[i] = 以 a[i] 结尾的 LIS 长度`
- 转移方程：`dp[i] = 1 + max{ dp[j] | j<i 且 a[j]<a[i] }`

**一、DP 版（O(n²)）**

```c++
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; cin >> n;
    vector<int> a(n), dp(n, 1);
    for (int &x : a) cin >> x;
    int answer = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j)
            if (a[j] < a[i]) dp[i] = max(dp[i], dp[j] + 1);
        answer = max(answer, dp[i]);
    }
    cout << answer << '\n';
}
```

##### 二、二分优化版（O(n log n)）

```c++
#include <bits/stdc++.h>
using namespace std;
// 求最长上升子序列长度 —— O(n log n) 二分优化写法
int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<int> tails;  // tails[k] = 长度为 k+1 的上升子序列的最小结尾值
    for (int x : a) { // lower_bound 查找第一个 ≥ x 的位置
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end())
            tails.push_back(x);     // 如果 x 比所有结尾都大，延长序列
        else
            *it = x;                // 否则替换（更优的结尾）
    }
    cout << tails.size() << endl;
    return 0;
}
```

### LCS：最长的公共子序列

给定字符串 A、B，求最长公共子序列长度。定义 dp[i][j]为 A 的前 i 个字符与 B 的前 j 个字符的 LCS 长度。

$$
dp[i][j]=
\begin{cases}
dp[i-1][j-1]+1,&A[i-1]=B[j-1],\\
\max(dp[i-1][j],dp[i][j-1]),&A[i-1]\ne B[j-1].
\end{cases}
$$

例如：给定A = "ACDBE"，B = "ABCDE"，最长的公共子序列是 `"ACDE"`，LCS(A, B) 长度为 **4**。

### 状态定义

```
f[i][j] = A[1..i] 与 B[1..j] 的最长公共子序列长度
```

### 转移方程

```c++
if (A[i] == B[j]):
    dp[i][j] = dp[i-1][j-1] + 1
else:
    dp[i][j] = max(dp[i-1][j], dp[i][j-1])
```

- 若末尾字符相等 → 可以延长公共子序列；
- 若不相等 → 必须舍弃 A[i] 或 B[j] 中的一个，取较优解。

### 边界条件：

```c++
dp[0][*] = 0
dp[*][0] = 0 //（空串与任何字符串的 LCS 为 0）
```

```c++
#include <bits/stdc++.h>
using namespace std;
int main() {
    string A, B;
    cin >> A >> B;
    int n = A.size(), m = B.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (A[i - 1] == B[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    cout << "LCS length = " << dp[n][m] << endl;
    return 0;
}
```

### 子序列计数 & 编辑距离

###### Case 1：统计一个字符串作为另一个字符串的子序列出现次数

**例题：** S = `"babgbag"` T = `"bag"`,问 T 在 S 中作为子序列的出现次数。

### 状态定义：

```c++
f[i][j] = S 的前 i 个字符中，T 的前 j 个字符出现为子序列的次数
```

### 转移方程：

```c++
if S[i] == T[j]:
    f[i][j] = f[i-1][j-1] + f[i-1][j]
else:
    f[i][j] = f[i-1][j]
```

- 当字符相等：可选择“匹配”或“跳过”；
- 当字符不等：只能跳过 S[i]。

### 初始化：

- `f[i][0] = 1` （空串是任何字符串的子序列）
- `f[0][j>0] = 0`

```c++
int numDistinct(string s, string t) {
    int n = s.size(), m = t.size();
    vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, 0));
    for (int i = 0; i <= n; i++) dp[i][0] = 1; // 空串子序列

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] = dp[i-1][j];
            if (s[i-1] == t[j-1]) dp[i][j] += dp[i-1][j-1];
        }
    }
    return dp[n][m];
}
```

###### Case 2：统计不同子序列个数

**题意：**给定字符串 S，求它有多少个不同的子序列。

例如：S = `"abc"` → 子序列：`a,b,c,ab,ac,bc,abc` + 空串 = 8

**DP 思路：**

- `f[i]` = 前 i 个字符能组成的不同子序列数。

- 若当前字符 `S[i]` 首次出现，则：

  ```
  f[i] = 2 * f[i-1]
  ```

- 若 `S[i]` 曾出现过，则减去重复贡献：

  ```
  f[i] = 2 * f[i-1] - f[last[S[i]] - 1]
  ```

### C++ 模板：

```c++
int distinctSubseq(string s) {
    int n = s.size(), mod = 1e9+7;
    vector<long long> dp(n + 1);
    vector<int> last(256, -1);
    dp[0] = 1; // 空串
    for (int i = 1; i <= n; i++) {
        dp[i] = (2 * dp[i - 1]) % mod;
        if (last[s[i - 1]] != -1)
            dp[i] = (dp[i] - dp[last[s[i - 1]] - 1] + mod) % mod;
        last[s[i - 1]] = i;
    }
    return (dp[n] - 1 + mod) % mod; //减去空串
}
```

###### Case 3：经典最短编辑距离（Levenshtein Distance）

题意：最少需要多少次插入 / 删除 / 替换操作，把字符串 A 变成 B。

例如：A = `"horse"`, B = `"ros"`
 输出：`3`
 （操作：`horse → rorse → rose → ros`）

### 状态定义：

```c++
f[i][j] = 把 A[1..i] 变成 B[1..j] 的最小编辑次数
```

### 转移方程：

```c++
if A[i] == B[j]:
    f[i][j] = f[i-1][j-1]
else:
    f[i][j] = min(
        f[i-1][j] + 1,     // 删除 A[i]
        f[i][j-1] + 1,     // 插入 B[j]
        f[i-1][j-1] + 1    // 替换
    )
```

### 边界条件：

```c++
f[0][j] = j  // 把空串变成前 j 个字符（全插入）
f[i][0] = i  // 把前 i 个字符删光
```

### C++ 模板：

```c++
int minDistance(string a, string b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
        }
    }
    return dp[n][m];
}
```

### 分组与前缀优化（Grouped DP & Prefix Optimization）

这类题的共同特征是：

> $$
> f[i] = \min_{j<i}(f[j] + \text{cost}(j+1, i))
> $$

### 一、分组 DP（Grouped / Partition DP）

概念: 当问题要求将序列或集合划分成若干组、若干段时，就可以用分组 DP。意思是把前 i 个元素划成 k 段时，最后一段是 (j+1..i)。
$$
f[i][k] = \min_{j < i} (f[j][k-1] + \text{cost}(j+1, i))
$$
### case 1：分割数组的最小代价

给定序列 `a[1..n]`，把它划分为 k 段，使得每段的“平方和”或“方差”最小。

```C++
a = [1, 2, 3, 4], k = 2
可以分成 [1,2,3] | [4]
代价 = (1+2+3)^2 + (4)^2 = 36 + 16 = 52
```

##### 状态设计

- `dp[i][t]` = 将前 `i` 个数划成 `t` 段的最小代价
- `cost(l, r)` = `(prefix[r] - prefix[l-1])^2`

**转移方程：**
$$
dp[i][t] = \min_{j < i} (dp[j][t-1] + cost(j+1, i))
$$
通过 前缀和数组 可在 O(1) 时间计算 cost。

```c++
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<ll> a(n + 1), prefix(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        prefix[i] = prefix[i - 1] + a[i];
    }
    const ll INF = 1e18;
    vector<vector<ll>> dp(k + 1, vector<ll>(n + 1, INF));
    dp[0][0] = 0;
    // 计算 cost(j+1, i)
    auto cost = [&](int l, int r) {
        ll sum = prefix[r] - prefix[l - 1];
        return sum * sum;
    };
    for (int t = 1; t <= k; t++) {          // 分段数
        for (int i = 1; i <= n; i++) {      // 前 i 个元素
            for (int j = 0; j < i; j++) {   // 上一个分割点
                dp[t][i] = min(dp[t][i], dp[t - 1][j] + cost(j + 1, i));
            }
        }
    }
    cout << dp[k][n] << "\n";
    return 0;
}
```

***

## 连续分段 DP：枚举最后一段

### 三种“分组”不要混淆

| 模型 | 每次决策 | 主要状态 |
| --- | --- | --- |
| 连续分段 DP | 原序列的最后一段从哪里开始 | 已处理前缀、已分段数 |
| 分组背包 | 每个已知物品组中选哪一件 | 已处理物品组、容量 |
| 子集划分 DP | 哪些元素组成同一组 | 已处理元素集合 mask |

下面讨论第一类。分组背包和子集划分放在第二篇。

### 恰好分 k 段，最小化“段和的平方之和”

给定数组，划成恰好 k 个非空连续段，代价：

$$
\sum_{\text{每一段 }[l,r]}\left(\sum_{i=l}^{r}a_i\right)^2.
$$

这是“段内和再平方”，不同于“每个数平方后求和”，也不同于方差。

定义 dp[t][i] 为前 i 个元素恰好分成 t 段的最小代价。最后一段为 [cut+1,i]：

$$
dp[t][i]=\min_{t-1\le cut<i}
\left(dp[t-1][cut]+(pre[i]-pre[cut])^2\right).
$$

初始化只有 dp[0][0]=0，其余 INF。t≥1 时 i≥t，防止出现空段。

例 [1,2,3,4]、k=2：

| 划分 | 代价 |
| --- | --- |
| [1] / [2,3,4] | 1+81=82 |
| [1,2] / [3,4] | 9+49=58 |
| [1,2,3] / [4] | 36+16=52 |

最优值 52。以下程序时间 O(kn²)，空间 O(kn)。课堂输入应保证中间平方及答案小于 1LL<<60；例如 n≤500、0≤a[i]≤10^4。


```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = (1LL << 60);
int main() {
    int n, k; cin >> n >> k;
    vector<ll> pre(n + 1, 0);
    for (int i = 1; i <= n; ++i) { ll x; cin >> x; pre[i] = pre[i - 1] + x; }
    if (k < 1 || k > n) { cout << -1 << '\n'; return 0; }
    vector<vector<ll>> dp(k + 1, vector<ll>(n + 1, INF));
    dp[0][0] = 0;
    for (int groups = 1; groups <= k; ++groups) {
        for (int i = groups; i <= n; ++i) {
            for (int cut = groups - 1; cut < i; ++cut) {
                if (dp[groups - 1][cut] == INF) continue;
                ll sum = pre[i] - pre[cut];
                dp[groups][i] = min(dp[groups][i], dp[groups - 1][cut] + sum * sum);
            }
        }
    }
    cout << dp[k][n] << '\n';
}
```

### **2016 January Gold** · [官方题目](https://usaco.org/index.php?page=viewproblem2&cpid=598)

### 1 从“两个人何时移动”建模成两个进度

两个人各有一条固定路线，每个时刻可以仅第一人移动、仅第二人移动，或两人同时移动。消耗为移动后的两人欧氏距离平方，最初位置不计费用。

预处理 F[i]、B[j]，表示分别走完 i、j 步后的坐标。定义 dp[i][j] 为到达这两个进度的最小总能耗：

$$
dp[i][j]=\min(dp[i-1][j],dp[i][j-1],dp[i-1][j-1])
+\|F[i]-B[j]\|^2.
$$

不存在的前驱不参与比较，dp[0][0]=0，其余 INF。两人都不动不会推进过程，费用非负，因此无需加入“原地等待”的自环转移。

### 2 手推

F 从 (0,0) 向东走一步，B 从 (0,1) 向东走一步：同时移动后距离平方为 1，答案为 1。若分别移动，至少会多计算一次中间状态的能耗。

N,M≤1000，时间 O(NM)，空间 O(NM)。它和 LCS 的状态网格相似，但每个格子的含义与合并操作不同。


```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = (1LL << 60);
vector<pair<ll,ll>> positions(int length, ll x, ll y, const string &moves) {
    vector<pair<ll,ll>> result(length + 1);
    result[0] = {x, y};
    for (int i = 1; i <= length; ++i) {
        char c = moves[i - 1];
        if (c == 'N') ++y;
        if (c == 'S') --y;
        if (c == 'E') ++x;
        if (c == 'W') --x;
        result[i] = {x, y};
    }
    return result;
}
int main() {
    int n, m; cin >> n >> m;
    ll fx, fy, bx, by; cin >> fx >> fy >> bx >> by;
    string a, b; cin >> a >> b;
    auto f = positions(n, fx, fy, a), g = positions(m, bx, by, b);
    vector<vector<ll>> dp(n + 1, vector<ll>(m + 1, INF));
    dp[0][0] = 0; // 初始位置不计能耗。
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (i == 0 && j == 0) continue;
            ll best = INF;
            if (i > 0) best = min(best, dp[i - 1][j]);
            if (j > 0) best = min(best, dp[i][j - 1]);
            if (i > 0 && j > 0) best = min(best, dp[i - 1][j - 1]);
            ll dx = f[i].first - g[j].first, dy = f[i].second - g[j].second;
            dp[i][j] = best + dx * dx + dy * dy;
        }
    }
    cout << dp[n][m] << '\n';
}
```

**2018 December Gold** · [洛谷 P5124](https://www.luogu.com.cn/problem/P5124) · [官方题目](https://usaco.org/index.php?page=viewproblem2&cpid=863)

N 头牛按顺序分成若干连续组，每组长度不超过 K。同组内每头牛的能力都变成组内最大值，求总能力最大值。

### 1 状态与转移

定义 dp[i] 为前 i 头牛分组后的最大总能力。若最后一组长度为 len，贡献为 len×这一段最大值：

$$
dp[i]=\max_{1\le len\le\min(K,i)}
\{dp[i-len]+len\cdot\max(a[i-len+1..i])\}.
$$

从 i 向左枚举 len，顺便维护当前段最大值，单次扩展 O(1)。不能在每个 len 下再重新扫描整段。

### 2 手推

[1,15,7]、K=2，dp 依次为 0、1、30、37。最后一步比较：

- 最后一组只有 [7]：30+7=37。
- 最后一组是 [15,7]：1+2×15=31。

因此 dp[3]=37。这里选择长度为 1 的最后一组更优，说明“最后一组尽量长”并不是正确的贪心。

官方样例 [1,15,7,9,2,5,10]、K=3，答案 84。

N≤10^4、K≤1000，时间 O(NK)，空间 O(N)。初始 dp 全为 0 在这里可用，是因为每个前缀都能合法分组且能力为正；不应直接推广到“恰好 t 段且存在不可达状态”的问题。


```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, k; cin >> n >> k;
    vector<int> skill(n + 1);
    for (int i = 1; i <= n; ++i) cin >> skill[i];
    vector<ll> dp(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        int maximum = 0;
        for (int length = 1; length <= k && length <= i; ++length) {
            maximum = max(maximum, skill[i - length + 1]);
            dp[i] = max(dp[i], dp[i - length] + 1LL * maximum * length);
        }
    }
    cout << dp[n] << '\n';
}
```

**2017 January Gold** · [洛谷 P3609](https://www.luogu.com.cn/problem/P3609) · [官方题目](https://usaco.org/index.php?page=viewproblem2&cpid=694)

已知对手 N 轮手势，最多切换 K 次自己的手势，求最多胜场。初始手势任意，选择初始手势不算切换。

### 1 为什么只记录 dp[i] 不够

即使前 i 轮的胜场相同，剩余切换次数不同、当前手势不同，未来能赢的轮数也可能不同。

定义 dp[i][used][g] 为打完前 i 轮、恰好切换 used 次、当前手势 g 时的最大胜场。初始只有 used=0 合法，三种初始手势的胜场都为 0。

转移：保持手势不增加 used；换成另一个手势增加一次 used；再加当前这一轮是否获胜。

只依赖上一轮，所以用 dp 与 next 两层数组。每轮先清空 next，所有转移都读取 dp，避免同一轮结果互相污染。

### 2 小例子

对手 H、H、P、P，最多切换一次。前两轮出 P，后两轮出 S，赢 4 次。若 K=0，只能选择某一种固定手势，最多赢 2 次。

N≤10^5、K≤20，时间 O(NK)，空间 O(K)，手势维度为常数。


```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, k; cin >> n >> k;
    const int NEG = -1000000000;
    vector<array<int, 3>> dp(k + 1), next(k + 1);
    for (auto &row : dp) row.fill(NEG);
    dp[0].fill(0); // 第一轮之前免费选择初始手势，没有发生切换。
    auto wins = [](int gesture, char opponent) {
        return (gesture == 0 && opponent == 'S')
            || (gesture == 1 && opponent == 'H')
            || (gesture == 2 && opponent == 'P'); // 0:H, 1:P, 2:S
    };
    for (int i = 0; i < n; ++i) {
        char opponent; cin >> opponent;
        for (auto &row : next) row.fill(NEG);
        for (int used = 0; used <= k; ++used) {
            for (int oldGesture = 0; oldGesture < 3; ++oldGesture) {
                if (dp[used][oldGesture] == NEG) continue;
                for (int gesture = 0; gesture < 3; ++gesture) {
                    // 第一轮可直接选 gesture，不应消耗一次切换。
                    int newUsed = used + (i > 0 && gesture != oldGesture);
                    if (newUsed <= k)
                        next[newUsed][gesture] = max(next[newUsed][gesture],
                            dp[used][oldGesture] + int(wins(gesture, opponent)));
                }
            }
        }
        dp.swap(next);
    }
    int answer = 0;
    for (const auto &row : dp) for (int value : row) answer = max(answer, value);
    cout << answer << '\n';
}
```

**2019 January Gold** · [洛谷 P5196](https://www.luogu.com.cn/problem/P5196) · [官方题目](https://usaco.org/index.php?page=viewproblem2&cpid=897)

### 1 先数一行，再组合整首诗

单词可以重复使用，每个有音节数 s[i] 和韵部 c[i]。一行音节数恰好 K，整首诗有 M 行；同一押韵字母的行必须使用同一韵部，其他字母不要求使用不同韵部。

这不是“将固定单词序列切成若干段”，而是允许重复选词的有序计数。

定义 dp[t] 为组成恰好 t 个音节的单词序列数：

$$
dp[0]=1,\qquad dp[t]=\sum_{s_i\le t}dp[t-s_i].
$$

音节总数在外层、最后一个单词在内层，保证不同词序分别计数。

### 2 按最后一个词的韵部汇总

定义 ending[c] 为一行恰好 K 个音节，并且最后一个词属于韵部 c 的方案数：

$$
ending[c]=\sum_{i:c_i=c}dp[K-s_i].
$$

若押韵模式中字母 X 出现 q 次：先选一个韵部 c，这 q 行各自有 ending[c] 种写法，因此它的贡献为：

$$
\sum_c ending[c]^q.
$$

不同模式字母的贡献相乘即可。这里不是给模式字母分配互不相同的韵部。

### 3 手推

有三个单词：(1音节,韵部1)、(1音节,韵部2)、(2音节,韵部1)，每行 K=2。

dp[0]=1，dp[1]=2，dp[2]=5。ending[1]=2+1=3，ending[2]=2。

若押韵模式是 AA，答案为 3²+2²=13；若是 AB，则为 (3+2)²=25。

时间 O(NK+M+26N log M)，空间 O(N+K)，结果取模 10^9+7。单词相同音节、相同韵部不表示是同一个单词，不能把输入项随意去重。


```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1000000007;
ll power(ll a, int exponent) {
    ll answer = 1;
    while (exponent) {
        if (exponent & 1) answer = answer * a % MOD;
        a = a * a % MOD; exponent >>= 1;
    }
    return answer;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m, k; cin >> n >> m >> k;
    vector<int> syllables(n), rhyme(n);
    for (int i = 0; i < n; ++i) cin >> syllables[i] >> rhyme[i];
    array<int, 26> frequency{};
    for (int i = 0; i < m; ++i) { char c; cin >> c; ++frequency[c - 'A']; }
    vector<ll> dp(k + 1, 0), ending(n + 1, 0);
    dp[0] = 1;
    // 总音节数在外：计算有顺序的单词序列。
    for (int total = 1; total <= k; ++total) {
        for (int i = 0; i < n; ++i) {
            if (syllables[i] <= total)
                dp[total] = (dp[total] + dp[total - syllables[i]]) % MOD;
        }
    }
    for (int i = 0; i < n; ++i)
        ending[rhyme[i]] = (ending[rhyme[i]] + dp[k - syllables[i]]) % MOD;
    ll answer = 1;
    for (int count : frequency) {
        if (count == 0) continue;
        ll choices = 0;
        for (int c = 1; c <= n; ++c)
            choices = (choices + power(ending[c], count)) % MOD;
        answer = answer * choices % MOD;
    }
    cout << answer << '\n';
}
```
