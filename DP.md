## 📚 动态规划（**Dynamic Programming**）

------

## 📘 目录

1. DP的应用场景
2. DP 五要素
3. 经典DP模型：序列 / 背包 / 区间 / 树上 / 图上 / 数位 / 状压
4. 优化技巧：滚动数组、单调队列、斜率优化、分治/四边形不等式、Bitset
5. 复杂度与调试策略

------

## 🧩 1. DP的应用场景

- **重叠子问题**：当同一个子问题在递归中被反复计算时，可以用表（数组 / 字典）缓存结果以节省时间。例Fibonacci 序列、爬楼梯问题。
- **最优子结构**：若问题的最优解可由子问题的最优解组成，则可以递推。例最短路径、背包问题、LCS。
- **子问题依赖关系**：状态之间通常构成一个有向无环图（DAG）。按照这个依赖关系排序求解，即为 Bottom-Up 动态规划。
- **DP本质**：是在搜索树上“剪枝 + 缓存”的系统化过程。
  - Top-Down（记忆化搜索）：递归 + 缓存结果。
  - Bottom-Up（迭代 DP）：按依赖顺序逐步填表。
     两种方式等价，只是方向不同。

### 🧭 适用条件（判断是否能用 DP）

1. **问题可分解成规模更小的子问题**。
2. **子问题之间有重叠**，而不是完全独立（否则分治更优）。
3. **满足最优子结构**：全局最优由局部最优构成。
4. **状态数有限且可枚举**。
5. **转移方向明确（无环依赖）**。

> ✅ 如果问题满足以上条件，就可以考虑动态规划。

### 🔧 小结要点

- DP 的关键不是“能不能写出代码”，而是找出**正确的状态定义和转移关系**。
- 一旦状态设计正确，DP 就是“**自动推理机器**”：
   只需按拓扑序填表即可得到全局最优解。

------

## 🧩 2. DP 的三要素

动态规划的关键在于“拆解问题 + 有序递推”。
 无论是**线性 DP、区间 DP、树 DP 还是状压 DP**，都遵循同样的 5 个核心环节。

------

### 🧠 1️⃣ 状态定义（State Definition）

> 决定了你在 DP 表中记录什么“信息”。

#### 🔹 原则：

- 明确“**子问题是什么**”。
- 每个状态应能唯一表示一个子问题。
- 尽量让状态“最小但充足”——即刚好能支撑转移，不冗余。

#### 🔹 示例：

- 爬楼梯：`f[i] = 到第 i 阶的方案数`
- 背包：`f[i][w] = 处理前 i 件物品，容量 w 的最大价值`
- LIS：`f[i] = 以第 i 个数结尾的 LIS 长度`

------

### ⚙️ 2️⃣ 状态转移方程（State Transition）

> 描述当前状态如何由更小的状态得到。

#### 🔹 一般形式：

```
f[i] = best( f[前置状态] + 当前决策的代价 )
```

#### 🔹 思维路径：

1. 从**最终目标**逆推需要哪些子问题；
2. 对每个状态，**枚举所有可能的前驱**；
3. 取最优 / 求和 / 计数等操作。

#### 🔹 示例：

- **爬楼梯**：`f[i] = f[i-1] + f[i-2]`

- **0-1 背包**：`f[i][w] = max(f[i-1][w], f[i-1][w-weight[i]] + value[i])`

- **LCS(最长公共子序列)**：

  ```c++
  if s1[i]==s2[j]: f[i][j]=f[i-1][j-1]+1
  else: f[i][j]=max(f[i-1][j], f[i][j-1])
  ```

------

### 🧱 3️⃣ 边界初始化（Boundary Initialization）

> 决定递推的起点，也常是 Bug 集中区。

#### 🔹 原则：

- 对于无法转移到的状态（例如空集、空区间、容量为 0），必须赋明确初值。
- 若求最大值型：初始化状态设为 `-inf`；
   若求最小值型：初始化状态设为 `+inf`。

#### 🔹 示例：

- 背包：`f[0][w]=0`
- LCS：`f[0][j]=f[i][0]=0`
- Fibonacci：`f[1]=1, f[2]=2`

------

### 🔄 4️⃣ 计算顺序（Computation Order）

> 即按依赖拓扑序计算，保证每个状态在使用前已知。

#### 🔹 常见顺序：

| DP 类型      | 顺序                      |
| ------------ | ------------------------- |
| 线性 DP      | i 从小到大                |
| 背包（0-1）  | i 正序，w 倒序            |
| 背包（完全） | i 正序，w 正序            |
| 区间 DP      | 按区间长度 len 从小到大   |
| 树形 DP      | DFS 后序遍历              |
| DAG DP       | 拓扑排序                  |
| 数位 DP      | 高位 → 低位（递归记忆化） |

**写法模板**（自底向上）：

```C++
# 初始化
f = [负无穷或0] * (n+1)
f[0] = 初始值

# 按依赖顺序递推
for i in range(1, n+1):
    for d in 所有可能的决策:
        f[i] = best(f[i], trans(f[前置状态], d))

# 输出答案
print(f[n] 或 max(f))
```

------

## 🧩 3. 经典模型 I：序列 DP

### 3.1 最长上升子序列（LIS）& 最长公共子序列（LCS）

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

📌 **一、DP 版（O(n²)）**

```c++
#include <bits/stdc++.h>
using namespace std;
// 求最长上升子序列长度 —— O(n^2) 动态规划写法
int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<int> dp(n, 1); // dp[i] = 以 a[i] 结尾的 LIS 长度
    int ans = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]) {              // 只有比当前小的数才能接在前面
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        ans = max(ans, dp[i]);              // 记录全局最长长度
    }
    cout << ans << endl;
    return 0;
}
```

##### 📌 二、二分优化版（O(n log n)）

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

### 🧩 什么是 LCS？

给定A = "ACDBE"，B = "ABCDE"，最长的公共子序列是 `"ACDE"`，LCS(A, B) 长度为 **4**。

### 🧠 状态定义

```
f[i][j] = A[1..i] 与 B[1..j] 的最长公共子序列长度
```

### ✅ 转移方程

```c++
if (A[i] == B[j]):
    f[i][j] = f[i-1][j-1] + 1
else:
    f[i][j] = max(f[i-1][j], f[i][j-1])
```

- 若末尾字符相等 → 可以延长公共子序列；
- 若不相等 → 必须舍弃 A[i] 或 B[j] 中的一个，取较优解。

### 🧱 边界条件：

```c++
f[0][*] = 0
f[*][0] = 0 //（空串与任何字符串的 LCS 为 0）
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

### 3.2 子序列计数 & 编辑距离

###### ✅ Case 1：统计一个字符串作为另一个字符串的子序列出现次数

**例题：** S = `"babgbag"` T = `"bag"`,问 T 在 S 中作为子序列的出现次数。

### 🧠 状态定义：

```c++
f[i][j] = S 的前 i 个字符中，T 的前 j 个字符出现为子序列的次数
```

### ⚙️ 转移方程：

```c++
if S[i] == T[j]:
    f[i][j] = f[i-1][j-1] + f[i-1][j]
else:
    f[i][j] = f[i-1][j]
```

- 当字符相等：可选择“匹配”或“跳过”；
- 当字符不等：只能跳过 S[i]。

### 🧱 初始化：

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

###### ✅ Case 2：统计不同子序列个数

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

### 💻 C++ 模板：

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

###### ✅ Case 3：经典最短编辑距离（Levenshtein Distance）

题意：最少需要多少次插入 / 删除 / 替换操作，把字符串 A 变成 B。

例如：A = `"horse"`, B = `"ros"`
 输出：`3`
 （操作：`horse → rorse → rose → ros`）

### 🧠 状态定义：

```c++
f[i][j] = 把 A[1..i] 变成 B[1..j] 的最小编辑次数
```

### ⚙️ 转移方程：

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

### 🧱 边界条件：

```c++
f[0][j] = j  // 把空串变成前 j 个字符（全插入）
f[i][0] = i  // 把前 i 个字符删光
```

### 💻 C++ 模板：

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

### 3.3 分组与前缀优化（Grouped DP & Prefix Optimization）

这类题的共同特征是：

> 转移形如
> $$
> f[i] = \min_{j<i}(f[j] + \text{cost}(j+1, i))
> $$
> 或有分组、分段、划分等结构。

### 🧩 一、分组 DP（Grouped / Partition DP）

### 🧠 概念

当问题要求将序列或集合**划分成若干组**、**若干段**时，就可以用分组 DP。
 常见转移式：
$$
f[i][k] = \min_{j < i} (f[j][k-1] + \text{cost}(j+1, i))
$$
意思是：

> 把前 i 个元素划成 k 段时，最后一段是 (j+1..i)。

------

### ✅ case 1：分割数组的最小代价

**题意：**
 给定序列 `a[1..n]`，把它划分为 k 段，使得每段的“平方和”或“方差”最小。

```C++
a = [1, 2, 3, 4], k = 2
可以分成 [1,2,3] | [4]
代价 = (1+2+3)^2 + (4)^2 = 36 + 16 = 52
```

##### 🧠 状态设计

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

### ✅ case 2：USACO Gold 题 “Cow Poetry”（2019年2月）

将若干单词分组形成押韵诗行。
 转移类似：

```
dp[i] = ∑ dp[j] （若 j 到 i 的 syllable sum == K）
```

这是分组 DP + 模板匹配问题。

------

### ✅ case 3：最优分割问题（Optimal Partition / K Segments）

> LeetCode 410. Split Array Largest Sum
>  给定数组，将其分成 m 段，使每段和的最大值最小。

虽然常用二分+贪心求解，也可用分组 DP：

```
dp[i][k] = min_{j<i} max(dp[j][k-1], sum(j+1, i))
```

------

### ✅ case 4：打包与任务调度（分组背包类）

> 有 N 个任务分成若干组，每组内只能选一个任务。
>  每组相当于一个“组内背包”，这就是“分组背包 DP”。

```
for each group g:
    for w = W .. 0:
        for each item i in group g:
            dp[w] = max(dp[w], dp[w - weight[i]] + value[i])
```

### 📘 二、前缀优化（Prefix / Convex Optimization）

### 🧠 概念

当转移形如
$$
f[i] = \min_{j < i} (f[j] + C(j, i))
$$
并且 `C(j, i)` 满足**单调性**或**凸性**时，可以利用**前缀最优决策**进行优化。

核心思想：

- 用“决策点单调性”优化枚举；
- 或用前缀最小值数组、单调队列、斜率优化（CHT）来加速。

### ✅ case 1：前缀最小值优化（Prefix Min）

> **题型：**
>  形如 `f[i] = min_{j < i} (f[j] + cost[j])` 且 `cost[j]` 单调。

可以维护一个滚动前缀最小值：

```c++
min_pref = INF;
for (int i = 1; i <= n; i++) {
    f[i] = min_pref + cost[i];
    min_pref = min(min_pref, f[i] - something[i]);
}
```

**例题：**USACO “Rental Service” 或 “Loan Repayment” 中的收益最大化问题。

### ✅ case 2：决策单调性优化（Divide & Conquer Optimization）

我们考虑一类 DP：
$$
f[i] = \min_{j < i} \{ f[j] + w(j, i) \}
$$
这种 DP 朴素是 **O(n²)**，因为每个 i 都要枚举所有 j。
 如果“最优决策点（opt[i]）” 满足单调性：
$$
opt[i-1] \le opt[i]
$$
那我们就可以用 **分治算法** 优化转移过程，从而把复杂度降到 **O(n log n)**。

🧩假设我们要把数组 `a = [1, 2, 3, 4, 5]` 分成两段，使得每段的代价是**区间和的平方**：
$$
dp[i] = \min_{j<i} \big(dp[j] + (sum[i]-sum[j])^2\big)
$$
代价函数：
$$
cost(j+1, i) = (prefix[i] - prefix[j])^2
$$

```c++
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n = 5;
    vector<ll> a = {0, 1, 2, 3, 4, 5};
    vector<ll> prefix(6);
    for (int i = 1; i <= n; i++) prefix[i] = prefix[i - 1] + a[i];

    auto cost = [&](int l, int r) {
        ll s = prefix[r] - prefix[l - 1];
        return s * s;
    };

    vector<ll> dp(n + 1, 1e18);
    vector<int> opt(n + 1, 0);
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        int start = opt[i - 1];   // 从上一个最优点开始
        for (int j = start; j < i; j++) {
            ll val = dp[j] + cost(j + 1, i);
            if (val < dp[i]) {
                dp[i] = val;
                opt[i] = j;
            }
        }
    }

    for (int i = 1; i <= n; i++)
        cout << "i=" << i << " dp=" << dp[i] << " opt=" << opt[i] << "\n";
}

```

### **例题：**

- USACO Gold “Array Partition”
- POJ 1180 “Batch Processing”

------

### ✅ 例 3：斜率优化（Convex Hull Trick, CHT）

> 当转移形如：
> $$
> f[i] = \min_{j<i} (f[j] + m_j \times x_i + b_j)
> $$
> 可用“凸包”维护最优决策。

**应用：**

- 数组分段最小平方误差（拟合问题）
- “滑动窗口 + 线性 DP” 问题（如“Chorus Line”, “Line Fitting”）

------

### ✅ 例 4：单调队列优化（Monotone Queue DP）

> 转移中带有限窗口：
> $$
> f[i] = \min_{j \in [i-L, i-1]} (f[j] + cost(j, i))
> $$
> 可用双端队列维护最优 `j`。

**例题：**

- USACO “Cow Jog”
- LeetCode 1696 “Jump Game VI”

------

### ✅ 例 5：Knuth 优化（四边形不等式）

> 当 DP 形如区间合并：
> $$
> f[l][r] = \min_{k\in(l,r)} (f[l][k] + f[k+1][r] + w(l, r))
> $$
> 且满足四边形不等式时，可优化为 O(n²)。

**例题：**

- 石子合并（Merge Stones）
- 最优二叉搜索树（Optimal BST）

------

### ⚙️ 三、常见转移形式总表

| DP 类型        | 转移形式                                       | 典型优化          | 常见题目         |
| -------------- | ---------------------------------------------- | ----------------- | ---------------- |
| 分段划分       | `f[i][k] = min_j f[j][k-1] + cost(j+1,i)`      | 决策单调性 / 分治 | 数组分段最小代价 |
| 区间合并       | `f[l][r] = min_k f[l][k] + f[k+1][r] + w(l,r)` | Knuth 优化        | 石子合并         |
| 线性式         | `f[i] = min_j (f[j] + m_j*x_i + b_j)`          | 斜率优化（CHT）   | Line Fitting     |
| 滑动窗口       | `f[i] = min_{j∈[i-L,i-1]} (...)`               | 单调队列          | Jump Game VI     |
| 简单前缀最小值 | `f[i] = min_j (f[j] + c[j])`                   | 前缀优化          | 最大子段和变体   |

------

### 🧠 四、可视化理解

可以把 “f[i] = min(f[j] + cost(j,i))” 理解为：

> 从状态 j 向 i 连一条边，代价是 cost(j,i)，
>  DP 就是求一条最短路径。

如果 cost 满足单调性（如 j 越大越不优），
 那我们可以用各种几何或数据结构优化（凸包、队列、前缀最小等）。

------

### 📘 五、练习题推荐（难度递增）

| 类型       | 题目                            | 来源                       |
| ---------- | ------------------------------- | -------------------------- |
| 分组 DP    | Split Array Largest Sum         | LeetCode 410               |
| 分组 DP    | Partition Array for Maximum Sum | LeetCode 1043              |
| 前缀优化   | Minimum Cost For Tickets        | LeetCode 983               |
| 决策单调性 | Batch Processing                | POJ 1180                   |
| Knuth 优化 | Merge Stones                    | LeetCode 1000 / USACO Gold |
| 斜率优化   | Line Fitting                    | 洛谷 P3628                 |
| 单调队列   | Jump Game VI                    | LeetCode 1696              |
