## 📚LCA（Lowest Common Ancestor）

### 1. 什么是 LCA？

假设有一棵有根树，对于两个节点 `u` 和 `v`：

> **LCA(u, v)** = 同时是 `u` 和 `v` 的祖先，并且距离 `u、v` 最近的那个祖先。

这里的“最近”，可以理解成：

> 在所有公共祖先里，深度最大的那个节点。

例如：

```
        1
       / \
      2   3
     / \   \
    4   5   6
       / \
      7   8
```

以 `1` 为根。

```
LCA(4, 7) = 2
```

### 2. 如果一个节点本身就是另一个节点的祖先呢？

```java
LCA(2, 7) = 2  //一个节点也算自己的祖先
```

### 3. 为什么 LCA 很重要？

LCA 最大的用途：求树上两个节点之间的距离。

假设：

```java
depth[u]
```

表示节点 `u` 到根节点的距离（边数）。

那么：

```java
dist(u, v)=depth[u] + depth[v] - 2 * depth[LCA(u,v)]
```

例如：

```java
        1
       /
      2
     / \
    4   5
       /
      7
```

求：

```java
dist(4, 7)
```

我们知道：

```java
depth[4] = 2
depth[7] = 3
LCA(4,7) = 2
depth[2] = 1
```

于是：

```java
dist(4,7)
= 2 + 3 - 2 × 1
= 3
```

实际路径：

```
4 → 2 → 5 → 7
```

确实有 `3` 条边。

因此可以记住一个非常重要的公式：

```java
dist(u, v)=depth[u] + depth[v] - 2 * depth[LCA(u,v)]
```

### 4. 最暴力的 LCA 怎么求？

最简单的方法就是先让两个节点处于相同深度，再让 `u` 不断找父亲：

```
u = parent[u]
```

直到：

```c++
depth[u] == depth[v]
```

然后两个人一起往上：

```c++
while (u != v) {
    u = parent[u];
    v = parent[v];
}
```

最后相遇的位置就是 LCA。

```c++
int lca(int u, int v) {
    while (depth[u] > depth[v])
        u = parent[u];
    while (depth[v] > depth[u])
        v = parent[v];
    while (u != v) {
        u = parent[u];
        v = parent[v];
    }
    return u;
}
```

如果树是一条链，每次查询可能都要往上走 `N` 次，如果有`Q`次查询，时间复杂度是`O(NQ)`。

### 5. LCA通常使用Binary Lifting（二进制倍增）

```java
up[u][j]  //u 向上跳 2^j 层之后的祖先。
  
up[u][j] = up[up[u][j-1]][j-1]; //2^j = 2^(j-1) + 2^(j-1)
//可以先跳 2^(j-1)，再跳 2^(j-1)
  
//例如原本要往上跳 1000 层，现在只要跳6层。
//1000= 2^9 + 2^8 + 2^7 + 2^6 + 2^5 + 2^3= 512 + 256 + 128 + 64 + 32 + 8
//现在时间复杂度是O(log N)
for (int j = LOG - 1; j >= 0; j--) {
    if ((diff >> j) & 1) {
        u = up[u][j];  //逐级跳
}
```

例如求：

```
u 的 8 层祖先
```

可以：

```java
先找到 u 的 4 层祖先 x
再找到 x 的 4 层祖先
```

```java
const int MAXN = 200005;
const int LOG = 20;

vector<int> adj[MAXN];

int depth[MAXN];
int up[MAXN][LOG];

//从根节点开始遍历整棵树，同时计算每个节点的深度 depth，以及它的 1、2、4... 层祖先 up[u][j]
void dfs(int u, int parent) {
    up[u][0] = parent;
//预处理2层祖先、4层祖先、8层祖先、16层祖先……
    for (int j = 1; j < LOG; j++) {
        up[u][j] = up[up[u][j - 1]][j - 1];
    }
    for (int v : adj[u]) {
        if (v == parent)
            continue; //如果这个邻居就是我父亲，就不要再回去了。
        depth[v] = depth[u] + 1;
        dfs(v, u);
    }
}
```

### 6. Binary Lifting 求 LCA 的核心过程

第一步：让两个节点深度相同，如果 depth[u] > depth[v]，让 `u` 按 2^j 方式往上跳。

第二步：一起往上跳，直到跳到LCA 的两个直接孩子位置，最后返回其父节点位置即是LCA位置。

> 两个人跳完之后相同”只能说明你已经到达了某个公共祖先，但不保证它是最近的公共祖先。

深度一样以后，我们从最大的 `j` 开始检查：

```java
if (up[u][j] != up[v][j]) {
    u = up[u][j];
    v = up[v][j];
}
```

意思是：

> 如果两个人向上跳 `2^j` 层之后还不是同一个节点，那么可以放心一起跳上去。

直到：

```java
u 和 v 已经站在 LCA 的两个直接孩子位置
```

这时候：

```java
return up[u][0];
```

就是 LCA。

```java
int lca(int u, int v) {
    // 保证 u 更深
    if (depth[u] < depth[v])
        swap(u, v);
    // 先让 u 和 v 到相同深度
    int diff = depth[u] - depth[v];
    for (int j = LOG - 1; j >= 0; j--) {
        if ((diff >> j) & 1) {
            u = up[u][j];
        }
    }
    // 如果此时已经相等
    if (u == v)
        return u;
    // 一起往上跳
    for (int j = LOG - 1; j >= 0; j--) {
        if (up[u][j] != up[v][j]) {
            u = up[u][j];
            v = up[v][j];
        }
    }
    return up[u][0]; //不是直接跳到 LCA,而是尽可能靠近,最终up[u][0]是共同的父节点。
}
```

### 7. Case

```java
                 1
              /     \
             2       3
           /   \    / \
          4     5  6   7
         /     / \
        8     9  10
       /
      11
```

求 LCA (11,10)，很显然等于LCA=2，观察Binary Lifting 是怎么找到这个 `2` 的。

### 第一步：记录 depth

假设根节点 `1` 的深度是 `0`：

```
节点      depth

1           0
2,3         1
4,5,6,7     2
8,9,10      3
11          4
```

所以：

```
depth[11] = 4
depth[10] = 3
```

两个节点深度不一样。

### 第二步：先让它们到同一深度

当前：

```
11   depth = 4
10   depth = 3
```

差：

```
diff = 4 - 3 = 1
```

所以把 `11` 向上跳 `1` 层：

```
11
 ↑
 8
```

于是：

```
u = 8
v = 10
```

现在：

```
depth[8] = 3
depth[10] = 3
```

终于在同一层了。

树上现在相当于：

```
                 1
              /     \
             2       3
           /   \
          4     5
         /     / \
        8     9  10
        ↑        ↑
        u        v
```

现在真正开始找 LCA。

### 第三步：为什么不能直接一直往上？

如果普通方法，可以：

```
8 → 4 → 2
10 → 5 → 2
```

两个人一层一层走：

第一次：

```
8 → 4
10 → 5
```

还不一样。

第二次：

```
4 → 2
5 → 2
```

相遇：

```
2
```

所以 LCA 是 `2`。

Binary Lifting 的目标就是：

> 不要一层一层走，而是尝试一次跳 1、2、4、8……层。

### 第四步：先看看祖先表

对于节点 `8`：

```
8 的 1 层祖先 = 4
8 的 2 层祖先 = 2
8 的 4 层祖先 = 不存在/根以上
```

所以：

```
up[8][0] = 4     // 2^0 = 1
up[8][1] = 2     // 2^1 = 2
```

对于节点 `10`：

```
10 的 1 层祖先 = 5
10 的 2 层祖先 = 2
```

所以：

```
up[10][0] = 5
up[10][1] = 2
```

整理一下：

| 节点 | 1层祖先 `2^0` | 2层祖先 `2^1` |
| ---- | ------------- | ------------- |
| 8    | 4             | 2             |
| 10   | 5             | 2             |

现在关键来了。

### 第五步：从大步开始尝试

当前：

```
u = 8
v = 10
```

我们先尝试：

```
跳 2 层
```

看看：

```
up[8][1]  = 2
up[10][1] = 2
```

发现：

```
一样！
```

这意味着什么？

如果我们直接让两个人都跳 2 层：

```
8  → 2
10 → 2
```

那么直接就跳到了 LCA。

但 Binary Lifting 的第二阶段**故意不这么做**。

因为我们的目标是：

> 先找到 LCA 下面的两个孩子。

所以当：

```
up[u][j] == up[v][j]
```

时：

```
不要跳！
```

因为说明：

> 跳这么远会碰到一起，有可能直接越过我们想找的边界。

所以 `j = 1` 时不跳。

仍然：

```java
u = 8
v = 10
```

### 第六步：尝试小一点，跳 1 层

现在：

```
j = 0
```

也就是尝试跳：

```
2^0 = 1 层
```

看：

```
up[8][0] = 4
up[10][0] = 5
```

发现：

```
4 != 5
```

说明：

> 两个人跳一层以后依然不会相遇。

所以这个跳跃是安全的。

于是：

```
u = 4
v = 5
```

现在变成：

```java
       2
      / \
     4   5
     ↑   ↑
     u   v
```

### 第七步：循环结束

现在：

```
u = 4
v = 5
```

它们已经是 LCA 的两个孩子。

因为：

```
parent[4] = 2
parent[5] = 2
```

所以：

```
return up[u][0];
```

也就是：

```
up[4][0] = 2
```

最终：

```
LCA(11,10) = 2
```

```c++
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;
const int LOG = 5;

vector<int> adj[MAXN];

int depth[MAXN];
int up[MAXN][LOG];

// DFS 预处理 depth 和 up 数组
void dfs(int u, int parent) {
    up[u][0] = parent;
    // 计算 2^j 层祖先
    for (int j = 1; j < LOG; j++) {
        up[u][j] = up[ up[u][j - 1] ][j - 1];
    }
    for (int v : adj[u]) {
        if (v == parent)
            continue;
        depth[v] = depth[u] + 1;
        dfs(v, u);
    }
}

int lca(int u, int v) {
    // -------------------------
    // 第一步：让 u 和 v 深度相同
    // -------------------------
    if (depth[u] < depth[v])
        swap(u, v);
    int diff = depth[u] - depth[v];
    for (int j = LOG - 1; j >= 0; j--) {
        if ((diff >> j) & 1) {
            u = up[u][j];
        }
    }
    // 如果调平之后已经相同
    if (u == v)
        return u;

    // -------------------------
    // 第二步：一起往上跳
    // -------------------------

    for (int j = LOG - 1; j >= 0; j--) {
        if (up[u][j] != up[v][j]) {
            u = up[u][j];
            v = up[v][j];
        }
    }
    // 此时 u 和 v 是 LCA 的两个孩子
    return up[u][0];
}

void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

int main() {
    // 建树
    addEdge(1, 2);
    addEdge(1, 3);
    addEdge(2, 4);
    addEdge(2, 5);
    addEdge(3, 6);
    addEdge(3, 7);
    addEdge(4, 8);
    addEdge(5, 9);
    addEdge(5, 10);
    addEdge(8, 11);
    // 以 1 为根
    depth[1] = 0;
    // 根节点的祖先设为自己
    dfs(1, 1);
    cout << "LCA(11, 10) = " << lca(11, 10) << '\n';
    return 0;
}
```

### 一句话理解 LCA

你可以直接记成：

> **LCA 就是两个节点向根走时，第一次汇合的节点。**

而 Binary Lifting 的核心思想是通过空间换时间：

> **把“一层一层找祖先”，优化成按 1、2、4、8、16……层跳祖先。**