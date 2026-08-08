### 🧩 状压 DP（Bitmask）

> 用一个二进制整数 `mask` 表示哪些元素已经被使用，然后在所有子集上做 DP，通常 N ≤ 20。

例如：现在只有4头牛0 1 2 3，用4个二进制位可以表示它们是否被选择，比如mask=0101

表示：

```c++
牛0：选了
牛1：没选
牛2：选了
牛3：没选
```

也就是集合：

```c++
{0, 2} // 0-index
```

1. 判断第 `i` 个元素是否存在：

```c++
//例5个元素 0 1 2 3 4
//mask=01101 表示当前集合有{0, 2, 3}
//例如判断 i = 2，1 << 2（00100）
//01101 & 00100 = 00100
if (mask & (1 << i)) 
```

```c++
#include <bits/stdc++.h>
using namespace std;
int main() {
    int mask = 13; // 01101
    for (int i = 0; i < 5; i++) {
        if (mask & (1 << i)) {
            cout << i << " 存在\n";
        } else {
            cout << i << " 不存在\n";
        }
    }
}
```

2. 加入元素 `i`：

```c++
//元素编号: 4 3 2 1 0
//mask:    0 1 1 0 1
//当前集合是 {0, 2, 3}
//现在想加入元素 1
//int newMask = mask | (1 << 1);
//1 << 1 = 00010 然后做OR newMask=01111
//新集合: {0, 1, 2, 3}
mask | (1 << i)
```

```c++
for (int i = 0; i < N; i++) {
    if (!(mask & (1 << i))) { // i 还没有被选择
        int newMask = mask | (1 << i); // 加入 i
    }
}
```

3. 删除元素 `i`：

```c++
//原集合: {0, 1, 2, 3} Mask=01111
//删除元素2
//1 << 2 = 00100 然后做XOR=01011
//新集合：{0, 1, 3}
mask ^ (1 << i)   // 前提是 i 已经存在
```

### 🧠 状态定义

有 N 个任务，每个任务只能做一次。

可以定义dp[mask] ：已经完成 `mask` 里面这些任务时的最优答案。例如：

```c++
mask = 10101
```

表示任务：

```c++
0, 2, 4
```

已经完成。

然后我们尝试加入一个还没完成的任务 `j`：

```c++
if (!(mask & (1 << j))) {
    int newMask = mask | (1 << j);

    dp[newMask] = ...
}
```

这就是**状态转移**。

### 💻 经典模版

> 有 N 个任务，每个任务做完之后会产生一定收益，求最大收益。

```c++
for (int mask = 0; mask < (1 << N); mask++) {
    for (int i = 0; i < N; i++) {
        if (mask & (1 << i)) continue;
        int newMask = mask | (1 << i);
        dp[newMask] = max(
            dp[newMask],
            dp[mask] + gain
        );
    }
}
```

 例：

```c++
N = 3
A = [5, 8, 3]
```

从：

```
000
```

可以选择牛 0：

```c++
001
dp[001] = 5
```

选择牛 1：

```c++
010
dp[010] = 8
```

选择牛 2：

```c++
100
dp[100] = 3
```

选择牛0+牛1+牛 2：

```c++
dp[111] = 16
```

***

### 📌 Hamiltonian Path / TSP （Traveling Salesman Problem）

> 给定 n 个城市以及城市之间的距离，要求从某个城市出发，**每个城市恰好访问一次**，最后回到起点，使总路程最短。

例如4个城市：A → B → D → C → A，需要在所有可能的访问顺序中找总距离最小的路线。

这是 Bitmask DP 最经典的模型之一。

定义：

```
dp[mask][i]
```

访问了 `mask` 中所有点，最后停在 `i` 的最小成本。

转移：

```c++
for (int mask = 0; mask < (1 << N); mask++) { //1左移N位
    for (int i = 0; i < N; i++) {
        if (!(mask & (1 << i)))
            continue;
        for (int j = 0; j < N; j++) {
            if (mask & (1 << j))
                continue;
            int newMask = mask | (1 << j);
            dp[newMask][j] =
                min(dp[newMask][j],
                    dp[mask][i] + cost[i][j]);
        }
    }
}
```

### 📌 popcount

> mask 里面选了几个东西。

```c++
int cnt = __builtin_popcount(mask);
```

例如：mask=101101 有4个1，**__builtin_popcount(mask) == 4**。

### 📌 Matching DP

> 有 N 个左边的人和 N 个右边的任务，每个人只能匹配一个任务，每个任务也只能被匹配一次。求合法匹配的方案数，或者最小/最大匹配代价。

### 1. 先看一个例子

有 3 个人：

```
人：   A  B  C
任务： 0  1  2
```

允许匹配关系：

```
A -> 0, 1
B -> 0, 2
C -> 1, 2
```

可以写成矩阵：

```c++
can[3][3] = {
    {1, 1, 0},
    {1, 0, 1},
    {0, 1, 1}
};
```

其中：

```c++
can[i][j] = 1
```

表示第 `i` 个人可以匹配第 `j` 个任务。

我们的目标是让：

```
A、B、C
```

分别获得一个不同的任务。

### 2. 最关键的状态设计

定义：dp[mask]

> 已经使用了 `mask` 中这些任务时，匹配前 `popcount(mask)` 个人的方案数。

这里有一个非常漂亮的地方：

**我们甚至不用额外记录现在处理到第几个人。**

因为：

```c++
i = __builtin_popcount(mask);
```

就能知道当前应该给第 `i` 个人匹配任务。

例如：

```
mask = 101
```

表示：

```
任务0：用了
任务1：没用
任务2：用了
```

所以：

```
popcount(101) = 2
```

说明已经安排好了前 2 个人：

```
A
B
```

现在轮到：

```
C
```

```c++
i = popcount(mask) //代表我们接下来处理第i个人
```

```c++
#include <bits/stdc++.h>
using namespace std;
int main() {
    int N = 3;
    int can[3][3] = {
        {1, 1, 0},
        {1, 0, 1},
        {0, 1, 1}
    };
    vector<long long> dp(1 << N);
    dp[0] = 1;
    for (int mask = 0; mask < (1 << N); mask++) {
        int i = __builtin_popcount((unsigned)mask);
        //现在要给第 i 个人选任务。
        if (i == N) continue;
        for (int j = 0; j < N; j++) {
            // j已经被使用
            if (mask & (1 << j))
                continue;
            // i不能匹配j
            if (!can[i][j])
                continue;
            int newMask = mask | (1 << j);
            dp[newMask] += dp[mask];
        }
    }
    cout << dp[(1 << N) - 1] << '\n'; //意味着所有任务都已经使用。
}
```

***

2025 Feb Gold - Friendship Editing

2023 Jan Gold - Lights Off

2021 Jan Gold - Uddered but not Herd