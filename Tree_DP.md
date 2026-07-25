## 📚 树型DP（**Tree DP**）

### 树的定义：

##### 头节点没有父亲，其他节点只有一个父亲，直观理解为发散状在树上，从头节点出发到任何节点的路径是唯一的，不管二叉树还是多叉树都如此

## 一、什么是树形 DP

**树形 DP = 在树上做动态规划**

核心思想是：

> 先计算每个子树的答案，再利用子节点的答案计算父节点的答案。

通常使用 **DFS 后序遍历**：先递归处理儿子，再处理当前节点。

1. 数据结构：问题的模型是**树**（二叉树、多叉树、森林）；
2. DP 特点：利用树递归、父子节点的结构，先递归处理所有子树，再用子树 DP 值更新当前节点 DP 值；
3. 核心思想：一棵树的最优解，由它所有子树的最优解组合得到。

## 二、通用模板

### 1. 状态定义

设 `dp[u][...]` 表示：以节点 u 为根的子树，在某种限制条件下的最优答案。

第二维一般代表节点 u 的状态（选 / 不选、染色颜色、是否匹配等）。

### 2. 转移逻辑

对当前节点 `u`，遍历它每一个子节点 `v`：

1. 先递归 `dfs(v)`，算出子树 v 所有 dp 值；
2. 用 `dp[v]` 的结果，更新父节点 `dp[u]`；
3. 子树之间互不干扰，合并子树答案得到 u 的答案。

### 3. 答案输出

整棵树的答案就是 `dp[root][...]`（root 一般是 1 号根节点）。

## 三、例题

### 例题 1：没有上司的舞会

公司员工构成一棵树，父节点是上司；

如果邀请上司来，下属就不能来；邀请下属，上司不能来。求邀请人的最大快乐值。

#### 状态定义

- `dp[u][0]`：以 u 为根的子树，**不选 u** 的最大快乐值
- `dp[u][1]`：以 u 为根的子树，**选 u** 的最大快乐值

#### DP 转移

1. 选 \(u\) 时，所有子节点 \(v\) 都不能选：

   $$
   dp[u][1] = val[u] + \sum_{v \in child(u)} dp[v][0]
   $$

2. 不选 \(u\) 时，每个子节点 \(v\) 可选可不选，取两种状态中的最大值：

   $$
   dp[u][0] = \sum_{v \in child(u)} \max(dp[v][0], dp[v][1])
   $$

#### 最终答案

$$
\max(dp[root][0], dp[root][1])
$$

```c++
//P1352
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 6005;
int n;
long long val[MAXN];
long long dp[MAXN][2];
vector<int> children[MAXN];
bool hasParent[MAXN];

// 对以 u 为根的子树进行树形 DP
void dfs(int u) {
    // 选 u
    dp[u][1] = val[u];
    // 不选 u
    dp[u][0] = 0;
    for (int v : children[u]) {
        dfs(v);
        // 选 u，则子节点 v 不能选
        dp[u][1] += dp[v][0];
        // 不选 u，则子节点 v 可选可不选
        dp[u][0] += max(dp[v][0], dp[v][1]);
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    // 读取每名员工的快乐值
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
    }
    // 输入格式：L 是下属，K 是 L 的直接上司
    for (int i = 1; i < n; i++) {
        int L, K;
        cin >> L >> K;

        children[K].push_back(L);
        hasParent[L] = true;
    }
    // 找到没有上司的员工，即树根
    int root = 1;
    for (int i = 1; i <= n; i++) {
        if (!hasParent[i]) {
            root = i;
            break;
        }
    }
    dfs(root);
    cout << max(dp[root][0], dp[root][1]) << '\n';
    return 0;
}
```

### 例题 2：树的最小点覆盖（经典二分图树形 DP）

洛谷**P2016 战略游戏**。

题意：选最少点，使得树上每条边至少有一个端点被选中。

状态：

- `dp[u][0]`：不选 u，所有子节点必须选
- `dp[u][1]`：选 u，子节点可选可不选

这道题本质上就是**树的最小点覆盖**：

- 每条边至少有一个端点被选中；
- 求最少选择多少个节点。

它的状态转移与你写的完全一致：
$$
dp[u][0]=\sum_{v\in child(u)}dp[v][1]
$$

$$
dp[u][1]
=
1
+
\sum_{v \in child(u)}
\min(dp[v][0], dp[v][1])
$$

最终答案：
$$
\min(dp[root][0],dp[root][1])
$$

```c++
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1505;

int n;
int dp[MAXN][2];
vector<int> graph[MAXN];

void dfs(int u, int parent) {
    dp[u][0] = 0;
    dp[u][1] = 1;
    for (int v : graph[u]) {
        if (v == parent) continue;
        dfs(v, u);
        dp[u][0] += dp[v][1];
        dp[u][1] += min(dp[v][0], dp[v][1]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int u, k;
        char ch;
        cin >> u >> ch >> ch >> k >> ch;
        for (int j = 0; j < k; j++) {
            int v;
            cin >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
    }

    dfs(0, -1);
    cout << min(dp[0][0], dp[0][1]) << '\n';
    return 0;
}
```

## 四、树形 DP 分类

1. ### 树上选课 / 树上背包

   给定一棵以节点 1 为根的树，每个节点有一个权值 `val[i]`。

   要求选择恰好 k 个节点，并满足：

   - 根节点必须选择；
   - 选择一个节点前，必须选择它的父节点；
   - 求所选节点的最大权值和。

   #### 状态定义

   ```
   dp[u][j]：在以 u 为根的子树中选择 j 个节点，
             并且必须选择 u 时的最大权值
   ```

   #### 状态初始化

   节点 `u` 自己被选择：

   ```
   dp[u][1] = val[u];
   ```

   #### 状态转移

   合并子节点 `v` 时：

   - 原来在已经处理的部分选择 `i` 个节点；
   - 在子树 `v` 中选择 `j` 个节点；
   - 合并后的状态为：

   $$
   dp[u][i+j]
   =
   \max(dp[u][i+j],dp[u][i]+dp[v][j])
   $$

   其中 `j = 0` 表示不从子树 `v` 中选择节点。

   例题：**洛谷P2014**

   ```c++
   #include <bits/stdc++.h>
   using namespace std;
   const int MAXN = 305;
   int n, m;
   int score[MAXN];
   int dp[MAXN][MAXN];
   int sz[MAXN];
   vector<int> tree[MAXN];
   void dfs(int u) {
       sz[u] = 1;
       dp[u][1] = score[u];
       for (int v : tree[u]) {
           dfs(v);
           for (int i = min(sz[u], m + 1); i >= 1; i--) {
               for (int j = 1; j <= sz[v] && i + j <= m + 1; j++) {
                   dp[u][i + j] = max(
                       dp[u][i + j],
                       dp[u][i] + dp[v][j]
                   );
               }
           }
           sz[u] += sz[v];
       }
   }
   
   int main() {
       ios::sync_with_stdio(false);
       cin.tie(nullptr);
       cin >> n >> m;
       for (int i = 1; i <= n; i++) {
           int parent;
           cin >> parent >> score[i];
           tree[parent].push_back(i);
       }
       dfs(0);
       cout << dp[0][m + 1] << '\n';
       return 0;
   }
   ```

2. **树上状态 DP（选 / 不选、染色）**

   每个节点两种 / 多种状态，子树独立合并（舞会P1352、点覆盖、独立集）。

3. **换根 DP（二次树形 DP）**

   先一遍 dfs 算根节点答案，再第二遍 dfs 换根，求出所有节点作为根的答案。

   ### 第一次 DFS

   以节点 `1` 为根，计算：

   - `size[u]`：以 `u` 为根的子树节点数量；
   - `ans[1]`：节点 `1` 到所有节点的距离之和。

   设 `depth[u]` 是节点 `u` 的深度，则：
   $$
   ans[1]=\sum_{u=1}^{n} depth[u]
   $$
   子树大小：
   $$
   size[u]=1+\sum_{v\in child(u)}size[v]
   $$

   ### 第二次 DFS

   假设当前根从父节点 `u` 移动到子节点 `v`。例洛谷**P1122**。

   对于 `v` 子树中的 `size[v]` 个节点，距离全部减少 `1`；对于子树外的 `n-size[v]` 个节点，距离全部增加 `1`。

   因此：
   $$
   ans[v]
   =
   ans[u]-size[v]+(n-size[v])
   $$
   化简为：
   $$
   ans[v]=ans[u]+n-2\times size[v]
   $$
   这就是换根 DP 的核心转移。

   > 例：洛谷Distance Sums 2求树上每个点到所有点距离之和。 

4. 子树计数类 DP

   统计合法子树数量、路径数量。

   1. **状态必须“固定一个连接点”**

   $$
   dp[u]
   $$

   表示以 `u` 为最高点，并且必须包含 `u` 的合法方案数量。

   “必须包含 `u`”非常重要，因为这样各个子树中的方案才能通过边 (u,v) 与 u 连起来，保证整体连通。

   ##### 2. 每个子树通常有“选或不选”两种决策

   对于子节点 `v`：

   - 不从 `v` 的子树中选择节点：`1` 种；
   - 选择一个包含 `v` 的合法结构：`dp[v]` 种。

   因此子节点 `v` 一共提供：
   $$
   dp[v]+1
   $$
   种选择。

   例如统计包含 `u` 的连通子树：
   $$
   dp[u]=\prod_{v\in child(u)}(dp[v]+1)
   $$
   之所以是乘法，是因为不同子树之间的选择互相独立。

## 五、树形 DP 和普通线性 DP 区别

1. 线性 DP：顺序遍历数组，从前向后转移；
2. 树形 DP：**后序遍历树**，先算完所有孩子，再算父亲；依赖关系是子→父。

## 六、总结

树形 DP 依托树的递归结构，**后序遍历先求解所有子树的 DP 状态，再合并子树结果得到当前节点最优解**，是解决树上最优、计数、选点类问题的标准算法。

***

2025 January Gold — Median Heap

#### **题意：**有一棵固定形状的完全二叉树，节点编号是 1 到 N。

对于每个节点 i：

- 初始值是 a_i
- 你可以花费 c_i，把这个节点的值改成任意整数

然后 Farmer John 会执行一个自底向上的算法：

- 从编号最大的节点开始往前处理
- 对每个内部节点，看它自己和两个孩子的三个值
- 如果当前节点的值不是这三个数的中位数，就把当前节点的值和“中位数所在的那个孩子”交换
- 最后根节点 1 上的值，就是算法输出

现在有很多个独立查询，每次给一个目标值 m。

对每个查询，你可以先修改任意多个节点的初始值，每修改一个节点就付对应的 c_i。然后再运行上面的中位数算法。

要求：
$$
\text{最小修改总成本}
$$
使得最后根节点输出恰好等于 m。

#### **核心思路：**

> **把“具体数值”压缩成相对目标 m 的三种关系，再用树形 DP 维护根节点变成 m 的最小代价。**

### 1. 不关心具体值，只关心和 m 的关系

对于一个查询目标 m，每个节点的值只需要分成三类：
$$
0:\ x<m,\qquad 1:\ x=m,\qquad 2:\ x>m
$$
因为三个数取中位数时，结果与 m 的关系，只由这三个关系决定。

例如：

- 两个数小于 m，中位数一定小于 m；
- 一个小于、一个等于、一个大于，中位数等于 m；
- 两个数大于 m，中位数一定大于 m。

所以不用记录真实数值。

### 2. 树形 DP：每个节点只维护 3 个状态

定义：
$$
dp[u][s]
$$
表示通过修改 u 子树中的节点，使节点 $u$ 最终传到父亲的值处于状态 s 的最小成本。

三种状态分别是：

```
0：小于 m
1：等于 m
2：大于 m
```

最终答案就是：
$$
dp[1][1]
$$
因为要求根节点最终等于 m。

### 3. 当前节点本身有两种代价

假设节点 u 原值 a_u 相对 m 的状态是 t。

那么：

- 保持原状态，代价为 0；
- 改成其他任意状态，代价为 c_u。

因为题目允许花一次 c_u，把值改成任意整数。

因此：
$$
cost_u[s]=
\begin{cases}
0,&s=t\\
c_u,&s\ne t
\end{cases}
$$

### 4. 内部节点枚举三个状态

设节点 u 的两个孩子是 l,r。

枚举：

- 当前节点自身修改后的状态 x；
- 左孩子最终状态 y；
- 右孩子最终状态 z。

处理后，节点 u 的状态就是三者的中位数：
$$
s=\operatorname{median}(x,y,z)
$$
转移为：
$$
dp[u][s]
=
\min\left(
dp[u][s],
cost_u[x]+dp[l][y]+dp[r][z]
\right)
$$
每个变量只有 3 种状态，所以每个节点只枚举：
$$
3^3=27
$$
种情况。

### 5. 真正的难点：不能每个查询重新做一次 DP

如果每个查询都重新跑整棵树：
$$
O(NQ)
$$
会超时。

关键观察是：随着查询目标 m 从小到大变化，一个固定节点 a_i 的状态只会变化两次：
$$
a_i>m
\longrightarrow
a_i=m
\longrightarrow
a_i<m
$$
也就是：

```
大于 → 等于 → 小于
```

因此可以把所有查询按 m 排序，离线扫描。

2023 US Open Gold — Tree Merging
