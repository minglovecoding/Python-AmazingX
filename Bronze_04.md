##  USACO 铜组：条件转化、排序查询与模拟优化

## 📌 学习目标

| 顺序 | 内容 | 对应例题 |
|---|---|---|
| 1 | 条件转化、排序后的门槛查询 | 2024 February Bronze：Maximizing Productivity |
| 2 | 有限状态模拟、方向编码、联合状态判重 | Training：The Tamworth Two / P1518 |
| 3 | 同步传递、环形数组、连续段汇总 | 2024 February Bronze：Milk Exchange |

## 一、条件转化：把变化的查询与固定数据分开

### 从规则写出不等式

某个农场在 `c[i]` 时关闭，从起床到计划访问该农场需要 `t[i]` 时间。起床时间为 `S`，要求严格提前到达：

$$
S+t_i<c_i
$$

移项后：

$$
S<c_i-t_i
$$

定义：

```cpp
deadline[i] = c[i] - t[i];
```

`deadline[i]` 只由农场数据决定，所有询问都可以重复使用。查询变为统计：

```cpp
deadline[i] > S
```

### 特别注意“严格小于”

如果 `deadline[i] = 5`：

| 起床时间 `S` | 能否按时访问 |
|---|---|
| 4 | 可以 |
| 5 | 不可以，恰好在关闭时到达 |
| 6 | 不可以 |

不要因为使用整数，就把严格不等号随意改成 `<=`。

###  什么时候值得做这种转化？

- 查询很多，而原始数据不变。
- 每次查询都重复计算同一种差值、和或门槛。
- 移项后可以让数据排序，使满足条件的元素聚集在一段连续区间。

这是**预处理复用**，不需要每次查询重新计算所有差值。

## 二、排序与二分：查找边界，不是只查找相等元素

### ✔️ 两个函数的区别

对升序数组 `a`：

| 函数 | 返回的位置 |
|---|---|
| `lower_bound(a.begin(), a.end(), x)` | 第一个 `>= x` 的位置 |
| `upper_bound(a.begin(), a.end(), x)` | 第一个 `> x` 的位置 |

如果没有符合条件的元素，返回 `a.end()`。**可以用它计算位置或数量，但不能直接解引用。**

```cpp
vector<int> a{1, 3, 3, 5, 8};

int left = lower_bound(a.begin(), a.end(), 3) - a.begin(); // 1
int right = upper_bound(a.begin(), a.end(), 3) - a.begin(); // 3

int equalCount = right - left; // 等于 3 的数量：2
int greaterCount = (int)a.size() - right; // 大于 3 的数量：2
```

### ✔️ 常见计数公式

设 `L` 是 `lower_bound(x)` 的下标，`U` 是 `upper_bound(x)` 的下标，数组长度为 `n`：

| 统计目标 | 数量 |
|---|---|
| `< x` | `L` |
| `<= x` | `U` |
| `== x` | `U - L` |
| `>= x` | `n - L` |
| `> x` | `n - U` |

**前提：数组按相应规则有序。** 在本章使用升序排序和默认比较规则。

### 完整演示

```cpp
// program: bounds_demo
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> a{1, 3, 3, 5, 8};
    int n = (int)a.size();

    for (int x : {0, 3, 9}) {
        int L = lower_bound(a.begin(), a.end(), x) - a.begin();
        int U = upper_bound(a.begin(), a.end(), x) - a.begin();
        cout << x << ' ' << L << ' ' << U - L << ' ' << n - U << '\n';
    }
    return 0;
}
```

```text
输出：每行依次为 x、小于 x 的数量、等于 x 的数量、大于 x 的数量
0 0 0 5
3 1 2 2
9 5 0 0
```

### ✔️ 预处理不等于离线查询

- **预处理后逐条回答**：先整理固定数据，每次读入一个查询就能回答，不依赖后面的查询。
- **离线处理**：先保存查询，再按查询内容排序、分组或调整处理顺序，最后恢复原顺序输出。

本章 Maximizing Productivity 的“差值排序 + 二分”属于前者。仅仅给数据排序，不足以称为离线查询。

## 三、真题：Maximizing Productivity

📌 **USACO 2024 February，Bronze，Problem 3。**

- [官方题面](https://usaco.org/index.php?page=viewproblem2&cpid=1397)
- [官方题解](https://usaco.org/current/data/sol_prob3_bronze_feb24.html)

### 问题概括

给出 `N` 个农场的关闭时间 `c[i]` 与计划访问偏移 `t[i]`。每个查询问：起床时间为 `S`，能否访问至少 `V` 个农场？

题目为每个农场给出独立的计划到达时间 `S + t[i]`，**不需要在农场之间再规划一条访问路线**。

### 1. 先写出朴素方法

每个查询扫描所有农场，检查 `S + t[i] < c[i]`，时间为 `O(NQ)`。

小规模可以接受；完整数据 `N,Q ≤ 2×10^5`，不能反复扫描全部农场。

### 2. 方法 A：差值排序 + upper_bound

1. 计算 `deadline[i] = c[i] - t[i]`，升序排列。
2. 找出第一个 `deadline[i] > S` 的下标 `pos`。
3. 满足条件的农场数为 `N - pos`。
4. 判断数量是否至少为 `V`。

例如：

```text
deadline：-1 3 4 4 6
S = 3：满足条件的是 4、4、6，共 3 个
```

#### 参考代码 A

```cpp
// program: productivity_binary
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    vector<ll> c(N), t(N), deadline(N);
    for (ll &value : c) cin >> value;
    for (ll &value : t) cin >> value;

    for (int i = 0; i < N; i++) deadline[i] = c[i] - t[i];
    sort(deadline.begin(), deadline.end());

    while (Q--) {
        int V;
        ll S;
        cin >> V >> S; // 实际输入顺序是 V、S

        int pos = upper_bound(deadline.begin(), deadline.end(), S)
                  - deadline.begin();
        int count = N - pos;
        cout << (count >= V ? "YES" : "NO") << '\n';
    }
    return 0;
}
```

时间为 `O(N log N + Q log N)`，保存数据空间为 `O(N)`。

### 3. 方法 B：直接检查第 V 大门槛

题目只问“是否至少有 `V` 个”，并不要求输出准确数量。

升序数组中，第 `V` 大元素的下标为：

```cpp
N - V
```

因此只需要判断：

```cpp
deadline[N - V] > S
```

**正确性：**如果第 `V` 大都大于 `S`，前 `V` 大全部满足；如果第 `V` 大不大于 `S`，则严格大于 `S` 的最多只有 `V-1` 个。

例如：

```text
升序：-1 3 4 4 6
第 3 大：4，所以下标为 5 - 3 = 2
V = 3，S = 3：4 > 3，YES
V = 4，S = 3：3 > 3 不成立，NO
```

#### 参考代码 B

```cpp
// program: productivity_kth
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    vector<ll> deadline(N);
    for (ll &value : deadline) cin >> value; // 暂时保存 c[i]
    for (int i = 0; i < N; i++) {
        ll travel;
        cin >> travel;
        deadline[i] -= travel;
    }
    sort(deadline.begin(), deadline.end());

    while (Q--) {
        int V;
        ll S;
        cin >> V >> S;
        cout << (deadline[N - V] > S ? "YES" : "NO") << '\n';
    }
    return 0;
}
```

题目保证 `1 ≤ V ≤ N`，所以这里的下标合法。时间为 `O(N log N + Q)`，保存数据空间为 `O(N)`。

### 官方样例：两个版本都适用

```text
输入：
5 5
3 5 7 9 12
4 2 3 3 8
1 5
1 6
3 3
4 2
5 1

输出：
YES
NO
YES
YES
NO
```

## 四、模拟进阶：完整状态、同步与结束条件

### ✔️ 模拟仍然要分析复杂度

模拟考查读题、状态建模和实现，但**不是不考复杂度**。同样的规则，可能要执行 `100` 次，也可能执行 `10^9` 次；后者通常需要规律或结构优化。

| 模型 | 先考虑的方法 | 需要进一步注意 |
|---|---|---|
| 操作次数很小 | 按规则逐步执行 | 更新顺序与边界 |
| 状态有限、下一步唯一 | 模拟并记录完整状态 | 重复状态说明进入循环 |
| 每分钟多个对象同时更新 | 保留旧状态，计算新状态 | 不能让先更新的对象影响同一分钟其他对象 |
| 时间极大、存在结构规律 | 按段、按事件或按周期汇总 | 先证明规律，不能随意跳步骤 |

### ✔️ 三个需要分清的问题

1. **状态与答案不同**：想知道是否相遇，仍可能必须记录双方方向，而不只是位置。
2. **没有变化与循环不同**：状态可以在多个时刻间循环，并不一定停在原地。
3. **同步与顺序不同**：一次操作内产生的结果，是否能被同一步的其他对象立即使用？由题意决定。

### ✔️ 正确的模拟框架

```text
初始化状态
循环：
    检查是否达到目标
    检查是否出现重复状态（若此模型适用）
    根据当前状态计算下一步
    完成一次统一更新
    时间增加
```

只有在“记录的状态足以决定全部后续行为、规则不随遗漏的时间信息变化”时，重复状态才能推出之后重复。

## 五、经典题：The Tamworth Two（两只塔姆沃斯牛）

📌 **USACO Training Section 2.4。**

[洛谷 P1518](https://www.luogu.com.cn/problem/P1518)

### 规则概括

在固定 `10 × 10` 地图中，农夫与牛都从朝北开始：

- 每分钟，前方可走就前进一步。
- 前方为墙或地图外，就用这一分钟原地顺时针转 `90°`，**转弯后不立即再走一步**。
- 两者同时行动，在一分钟结束时同格才算相遇；交换位置、途中交错不算。
- 永远不相遇则输出 `0`。

### 1. 方向编码

```cpp
// 0 北、1 东、2 南、3 西
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

direction = (direction + 1) % 4; // 顺时针转向
```

坐标统一从 `0` 开始：行、列均为 `0 ~ 9`。先判断是否在地图内，再访问地图。

### 2. 为什么必须记录六个量？

联合状态为：

```text
农夫行、农夫列、农夫方向、牛行、牛列、牛方向
```

位置相同但方向不同，下一步可能不同。只记录双方位置，或发现某一方单独重复，就提前判定无解，都不充分。

### 3. 联合状态只有 160000 种

每个对象有：

$$
10\times10\times4=400
$$

种状态，双方联合起来共有：

$$
400\times400=160000
$$

种。如果没有相遇却重复了相同联合状态，因为之后的变化完全确定，就会永久循环。

### 4. 安全的零下标编码

```cpp
int code = (x * 10 + y) * 4 + direction; // 0 ~ 399
```

用：

```cpp
seen[farmerCode][cowCode]
```

记录联合状态，不必把六个量写成容易混淆的十进制权重公式。

### 参考代码

```cpp
// program: tamworth_two
#include <bits/stdc++.h>
using namespace std;

string grid[10];
bool seen[400][400]; // 放在全局，初始为 false

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

void advance(int &x, int &y, int &direction) {
    int nx = x + dx[direction];
    int ny = y + dy[direction];

    if (nx < 0 || nx >= 10 || ny < 0 || ny >= 10 || grid[nx][ny] == '*') {
        direction = (direction + 1) % 4;
    } else {
        x = nx;
        y = ny;
    }
}

int encode(int x, int y, int direction) {
    return (x * 10 + y) * 4 + direction;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int fx = -1, fy = -1, cx = -1, cy = -1;
    for (int x = 0; x < 10; x++) {
        cin >> grid[x];
        for (int y = 0; y < 10; y++) {
            if (grid[x][y] == 'F') fx = x, fy = y;
            if (grid[x][y] == 'C') cx = x, cy = y;
        }
    }

    int fd = 0, cd = 0;
    int minutes = 0;

    while (true) {
        if (fx == cx && fy == cy) {
            cout << minutes << '\n';
            return 0;
        }

        int fCode = encode(fx, fy, fd);
        int cCode = encode(cx, cy, cd);
        if (seen[fCode][cCode]) {
            cout << 0 << '\n';
            return 0;
        }
        seen[fCode][cCode] = true;

        advance(fx, fy, fd);
        advance(cx, cy, cd);
        minutes++;
    }
}
```

### 为什么代码依次调用，仍然表示同时行动？

两次 `advance` 都只看固定的墙和各自状态，不会读取另一方刚更新的位置，也不会修改地图。两次调用完成后才进入下一次相遇判断，因此等价于同步推进一分钟。

题目中的 `F`、`C` 字符只用于读入初始位置；之后不把它们当作墙，不需要在地图上反复擦除和重画。

### 自测：先转弯，再相遇

```text
输入：
**********
*FC*******
**********
**********
**********
**********
**********
**********
**********
**********

输出：
2
```

第一分钟都被北面的墙挡住，转向东；第二分钟农夫右移，牛因东侧为墙原地转向南，此时同格相遇。

**复杂度：**地图固定时最多处理 `160000` 个不同联合状态，每步为常数操作；访问标记空间同为 `160000` 个布尔值。不需要自行猜测一个“模拟足够久”的时间上限。

### ❗ 对原代码编码的修正

原稿坐标采用 `1 ~ 10`，却按十进制位权累加，最大联合编码可达到 `161110`，超出 `bool zt[160005]`。现在统一零下标，并把每个对象编码为 `0 ~ 399`，联合状态直接用二维数组记录。

## 六、环形数组与同步传递

### ✔️ 环形下标

下标 `i` 在 `0 ~ N-1` 中：

```cpp
int left = (i - 1 + N) % N;
int right = (i + 1) % N;
```

不能直接写 `(i - 1) % N` 后用于下标，因为 C++ 的负数取余结果可能为负。

### ✔️ 同步传递使用新数组

一轮中，所有对象是否能发送，必须根据**这一轮开始时**的奶量判断，不能让某头牛把这一分钟刚收到的奶又继续发送。

```text
old：这一分钟开始时的状态
next：统一记录发送和接收后的结果
```

另外，应该先完成所有发送和接收，再处理容量溢出。不能在接收时立刻截断，因为接收者在同一分钟也可能送出一单位，从而腾出空间。

这一点将在下一道题的朴素代码中体现。

## 七、真题：Milk Exchange——从同步模拟到连续段汇总

📌 **USACO 2024 February，Bronze，Problem 2。**

- [官方题面](https://usaco.org/index.php?page=viewproblem2&cpid=1396)
- [官方题解](https://usaco.org/current/data/sol_prob2_bronze_feb24.html)

> 本章只讨论铜组版本。同场金组也有一道同名题，不能混淆；本题不是银组题。

### 问题概括

奶牛围成一圈，每头牛有容量为 `a[i]` 的桶，初始全部装满。每分钟，当前有奶的牛按固定方向 `L` 或 `R` 发送一升，所有传递同步发生，超过容量的部分丢失。求 `M` 分钟后的总奶量。

完整范围中 `N ≤ 2×10^5`、`M ≤ 10^9`、`a[i] ≤ 10^9`。总奶量需要 `long long`。

### 1. 朴素方法：逐分钟模拟（部分解）

1. 复制当前奶量到 `next`。
2. 根据当前旧奶量，决定每头牛是否发送，并在 `next` 上一减一加。
3. 所有传递完成后，将 `next[i]` 截断到容量以内。
4. 用 `next` 作为下一分钟状态。

#### 参考代码：只用于小数据与理解规则

```cpp
// program: milk_exchange_direct
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    ll M;
    cin >> N >> M;
    string direction;
    cin >> direction;
    vector<ll> capacity(N);
    for (ll &value : capacity) cin >> value;
    vector<ll> milk = capacity;

    for (ll minute = 0; minute < M; minute++) {
        vector<ll> next = milk;

        for (int i = 0; i < N; i++) {
            if (milk[i] == 0) continue;
            int destination = (direction[i] == 'R')
                              ? (i + 1) % N : (i - 1 + N) % N;
            next[i]--;
            next[destination]++;
        }

        for (int i = 0; i < N; i++) {
            next[i] = min(next[i], capacity[i]);
        }
        milk = next;
    }

    cout << accumulate(milk.begin(), milk.end(), 0LL) << '\n';
    return 0;
}
```

**复杂度：**时间 `O(NM)`，空间 `O(N)`。题面有 `N,M ≤ 1000` 的部分数据；这份代码不适合直接跑完整范围。

### 2. 先看全部方向相同的情况

如果全部为 `R` 或全部为 `L`，每个满桶同时送出一升、接收一升，奶量不变。

对 `N = 1` 也成立：发送给自己，不产生损失。

### 3. 找相向的 RL 桶对

假设相邻的两个位置满足：

```text
方向：…… R | L ……
          i   j
```

这两头牛每分钟互相交换一升，所以它们始终保留自己的满桶奶量。如果还从外侧收到额外奶，就会溢出。

**不能理解为 RL 两桶之间的互相交换本身就会损失奶。真正丢失的是外侧额外流入的部分。** 只有 RL 桶对而没有外侧供应时，可以完全不损失。

### 4. 统计外侧供应链，排除 RL 自身

对一对 `R | L`：

- 从 `R` 的左邻居开始，向左收集连续的 `R`，容量和记为 `sumR`。
- 从 `L` 的右邻居开始，向右收集连续的 `L`，容量和记为 `sumL`。
- **相向的 `R`、`L` 两个端点自身都不加入容量和。**

例如：

```text
位置：  0  1  2  3  4
方向：  R  R  R  L  L
容量：  2  3  4  5  6
```

相向桶对是位置 `2、3`：

```text
sumR = a[0] + a[1] = 5
sumL = a[4] = 6
```

位置 `2` 的容量 `4` 和位置 `3` 的容量 `5` 必须保留，不能算入供应链损失。

### 5. 为什么单侧损失为 min(供应链容量和, M)？

1. 每侧每分钟最多有一升从外侧进入对应的满桶，因此损失最多 `M`。
2. 外侧连续同向链的初始奶量总和有限，因此损失最多为链容量和。
3. 初始各桶非空且装满，链上的奶逐步向相向桶对推进；在链耗尽之前，其末端持续每分钟提供一升。

所以这对桶产生的总损失为：

$$
\min(sumR,M)+\min(sumL,M)
$$

不能写成 `min(sumR + sumL, M)`：左右两侧可能在同一分钟各损失一升。

上例若 `M = 4`：初始总量 `20`，损失 `min(5,4) + min(6,4) = 8`，最终剩 `12`。

### 6. 所有供应链会不会重复统计？

不会。每段连续 `R` 只会供应它右端的相向 `R`；每段连续 `L` 只会供应它左端的相向 `L`。

各段按方向分别处理，环形下标让跨数组首尾的同向段也能正确连接。没有 RL 时不进行任何向外扫描，也就不会在同向整圈中无限循环。

### 参考代码：完整数据解法

```cpp
// program: milk_exchange_fast
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    ll M;
    cin >> N >> M;
    string direction;
    cin >> direction;
    vector<ll> capacity(N);
    for (ll &value : capacity) cin >> value;

    ll answer = accumulate(capacity.begin(), capacity.end(), 0LL);

    for (int i = 0; i < N; i++) {
        int next = (i + 1) % N;
        if (direction[i] != 'R' || direction[next] != 'L') continue;

        // 当前相向桶对：i 是 R，next 是 L
        // 左侧供应链：不包括 i
        ll sumR = 0;
        int j = (i - 1 + N) % N;
        while (direction[j] == 'R') {
            sumR += capacity[j];
            j = (j - 1 + N) % N;
        }

        // 右侧供应链：不包括 next
        ll sumL = 0;
        j = (next + 1) % N;
        while (direction[j] == 'L') {
            sumL += capacity[j];
            j = (j + 1) % N;
        }

        answer -= min(sumR, M);
        answer -= min(sumL, M);
    }

    cout << answer << '\n';
    return 0;
}
```

**复杂度：**外层扫描 `N` 个位置，各供应链只在对应桶对处处理一次，所有 `while` 的累计扫描量为 `O(N)`。因此总时间 `O(N)`，空间 `O(N)`，不能因为存在嵌套循环就直接判断为 `O(N²)`。

### 官方样例

```text
输入 1：
3 1
RRL
1 1 1

输出 1：
2
```

```text
输入 2：
5 20
LLLLL
3 3 2 3 3

输出 2：
14
```

```text
输入 3：
9 5
RRRLRRLLR
5 8 4 9 3 4 9 5 4

输出 3：
38
```
