## 📚前缀和、差分

## 一、一维前缀和：先累加，再相减

### 1. 定义

对于数组 
$$
a_1,a_2,\ldots,a_N
$$

$$
pre[0]=0,\qquad pre[i]=pre[i-1]+a[i]
$$

也就是 `pre[i]` 保存前 `i` 个元素的总和。

| 下标 i | 0 | 1 | 2 | 3 | 4 | 5 |
|---|---:|---:|---:|---:|---:|---:|
| a[i] | — | 2 | 5 | 3 | 6 | 4 |
| pre[i] | 0 | 2 | 7 | 10 | 16 | 20 |

求闭区间 `[2,4]`：

$$
\operatorname{sum}(2,4)=pre[4]-pre[1]=16-2=14
$$

减掉的是第 `l` 个元素之前的部分，所以应当减 `pre[l-1]`，而不是 `pre[l]`。

### 2. 基础模板

```cpp
vector<long long> pre(n + 1, 0);

for (int i = 1; i <= n; i++) {
    long long x; 
    cin >> x;
    pre[i] = pre[i - 1] + x;
}

// 查询 1 <= l <= r <= n。
long long sum = pre[r] - pre[l - 1];
```

构建 `O(N)`，单次查询 `O(1)`，共 `Q` 次查询为 `O(N+Q)`，空间 `O(N)`。负数不会破坏前缀和公式。

若单个元素最大为 10^9、数量为 10^5，总和可达 10^{14}，必须使用 `long long`。

### 3. 铜组真题：Daisy Chains

**2020 December Bronze，Problem 2**  
[官方题面](https://usaco.org/index.php?page=viewproblem2&cpid=1060)

**题意概括：** 枚举连续的一段花朵，若这段中存在一朵花，其花瓣数恰好等于整段的平均数，则这段照片合法。统计合法照片数。

先用前缀和计算：

$$
sum=pre[r]-pre[l-1],\qquad len=r-l+1
$$

平均数必须是整数，即 `sum % len == 0`；随后还要检查这段中是否真的存在花瓣数为 `sum / len` 的花。

例如区间花瓣数为 `{1,3}`，平均数为 2，但区间中没有 2，因此不合法。

**做法层次：**

1. 枚举 `[l,r]`，用前缀和 $O(1)$ 求和，再扫描区间查找平均数，总时间仍是 O(N^3)；本题 N\le100，可以通过。
2. 固定 `l`，向右移动 `r`，维护当前区间各花瓣数的频次，就能 O(1) 判断平均数是否出现，将总复杂度降为 O(N^2)。

本题说明：前缀和只优化“求和”这一步，不能自动消除其他枚举。

### 4. 银组真题：Breed Counting

**2015 December Silver，Problem 3**  
[官方题面](https://usaco.org/index.php?page=viewproblem2&cpid=572)

**题意概括：** 奶牛品种为 1、2、3，多次询问 `[l,r]` 内三种奶牛分别有多少头。

把每个位置对每个品种的贡献看成 0 或 1：

$$
pre[i][c]=\text{前 i 头牛中，品种 c 的数量}
$$

查询品种 `c` 的数量就是 `pre[r][c] - pre[l-1][c]`。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<array<int, 4>> pre(n + 1, array<int, 4>{});

    for (int i = 1; i <= n; i++) {
        int breed;
        cin >> breed;
        pre[i] = pre[i - 1];  // 先继承三类已有计数
        pre[i][breed]++;
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << pre[r][1] - pre[l - 1][1] << ' '
             << pre[r][2] - pre[l - 1][2] << ' '
             << pre[r][3] - pre[l - 1][3] << '\n';
    }
}
```

时间 O(N+Q)，空间 O(N)。这里的前缀和保存数量，不是品种编号的和。

### 5. 银组真题：Subsequences Summing to Sevens

**2016 January Silver，Problem 2**  
[官方题面](https://usaco.org/index.php?page=viewproblem2&cpid=595)

**题意概括：** 求最长连续区间，使区间和是 7 的倍数。虽然题名含有 Subsequences，这道题要求的是连续区间。

由区间和公式：

$$
pre[r]-pre[l-1]\equiv0\pmod7
\iff pre[r]\bmod7=pre[l-1]\bmod7
$$

因此，只要找到两个余数相同的前缀。为了让距离最大，记录每种余数最早出现的位置。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> first(7, -1);
    first[0] = 0;  // 空前缀也要记录，才能统计从位置 1 开始的区间

    int remainder = 0, answer = 0;
    for (int i = 1; i <= n; i++) {
        long long x;
        cin >> x;
        remainder = (remainder + x) % 7;

        if (first[remainder] == -1) first[remainder] = i;
        else answer = max(answer, i - first[remainder]);
    }

    cout << answer << '\n';
}
```

时间 O(N)，额外空间 O(7)。本题输入非负；推广到有负数的数组时，余数可以用 `(value % 7 + 7) % 7` 归一化。

## 二、二维前缀和：用容斥求子矩形和

### 1. 定义与构造

`pre[row][col]` 表示从 `(1,1)` 到 `(row,col)` 的所有元素之和，包含边界。
$$
pre[i][j]=pre[i-1][j]+pre[i][j-1]-pre[i-1][j-1]+a[i][j]
$$

上方矩形与左方矩形有重叠，因此要减去左上方被重复计算的部分，再加入当前格子。

```cpp
vector<vector<long long>> pre(n + 1, vector<long long>(m + 1, 0));

for (int row = 1; row <= n; row++) {
    for (int col = 1; col <= m; col++) {
        pre[row][col] = pre[row - 1][col] + pre[row][col - 1]
                      - pre[row - 1][col - 1] + a[row][col];
    }
}
```

### 2. 查询子矩形

查询闭矩形 `[r1,c1] × [r2,c2]`：

$$
sum=pre[r2][c2]-pre[r1-1][c2]-pre[r2][c1-1]+pre[r1-1][c1-1]
$$

```cpp
long long sum = pre[r2][c2]
              - pre[r1 - 1][c2]
              - pre[r2][c1 - 1]
              + pre[r1 - 1][c1 - 1];
```

例如矩阵为：

| 行 / 列 | 1 | 2 | 3 |
|---|---:|---:|---:|
| 1 | 1 | 2 | 3 |
| 2 | 4 | 5 | 6 |
| 3 | 7 | 8 | 9 |

查询第 2～3 行、第 2～3 列：`45 - 6 - 12 + 1 = 28`，即 `5+6+8+9`。

构建 O(NM)，每次查询 O(1)，空间 O(NM)。第 0 行和第 0 列置零，用来统一处理贴边查询。

## 三、坐标离散化与 Rectangular Pasture

### 1. 为什么需要离散化？

坐标值可能达到 10^9，但点的数量远小于坐标范围。如果只关心点之间的相对顺序，就可以把原始坐标改成排序后的排名。

| 原始坐标 | 0 | 500 | 1000000000 |
|---|---:|---:|---:|
| 压缩后的排名 | 1 | 2 | 3 |

**离散化保留顺序，不保留距离和面积。** 如果要计算真实面积，还必须保留原坐标之间的长度，不能把每个压缩格子都视作面积为 1。

### 2. 银组真题：Rectangular Pasture

**2020 December Silver，Problem 2**  
[官方题面](https://usaco.org/index.php?page=viewproblem2&cpid=1063)

**题意概括：** 给定平面上的奶牛，统计能被某个轴对齐矩形恰好圈住的不同奶牛子集，包含空集。题目保证所有横坐标互不相同，所有纵坐标也互不相同。

思路：

1. 将横、纵坐标分别离散化为 `1...N`；在奶牛所在格子标记 1。
2. 构建二维前缀和，用来统计任意矩形内的奶牛数量。
3. 按纵坐标排序，枚举最下方和最上方的两头牛 `bottom、top`。
4. 设它们的横坐标较小值为 `minX`，较大值为 `maxX`。
5. 在该纵向条带内，统计 `x <= minX` 的奶牛数 `leftChoices`，以及 `x >= maxX` 的奶牛数 `rightChoices`。
6. 贡献为 `leftChoices * rightChoices`，全部累加后加 1，计入空集。

为什么相乘？每个非空子集有唯一的最下、最上、最左、最右奶牛。固定上下极值后，左右极值的选择分别来自两侧，且都能圈住固定的两头牛。不同选择得到不同子集；题目统计子集，不是矩形边界放置的方法数。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<int, int>> cows(n);
    for (auto& [x, y] : cows) cin >> x >> y;

    sort(cows.begin(), cows.end());
    for (int i = 0; i < n; i++) cows[i].first = i + 1;

    sort(cows.begin(), cows.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });
    for (int i = 0; i < n; i++) cows[i].second = i + 1;

    // 第一维为 x 排名，第二维为 y 排名。
    vector<vector<int>> pre(n + 1, vector<int>(n + 1, 0));
    for (auto [x, y] : cows) pre[x][y] = 1;

    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= n; y++) {
            pre[x][y] += pre[x - 1][y] + pre[x][y - 1]
                       - pre[x - 1][y - 1];
        }
    }

    auto query = [&](int x1, int y1, int x2, int y2) {
        return pre[x2][y2] - pre[x1 - 1][y2]
             - pre[x2][y1 - 1] + pre[x1 - 1][y1 - 1];
    };

    long long answer = 1;  // 空集
    for (int bottom = 0; bottom < n; bottom++) {
        for (int top = bottom; top < n; top++) {
            int minX = min(cows[bottom].first, cows[top].first);
            int maxX = max(cows[bottom].first, cows[top].first);
            int y1 = bottom + 1, y2 = top + 1;

            int leftChoices = query(1, y1, minX, y2);
            int rightChoices = query(maxX, y1, n, y2);
            answer += 1LL * leftChoices * rightChoices;
        }
    }

    cout << answer << '\n';
}
```

时间 O(N^2+N\log N)，空间 O(N^2)。前缀和只统计牛数，可以用 `int`；答案必须用 `long long`。本题的排名赋值利用了各坐标互异的保证；一般允许重复坐标时，相同坐标必须压缩成相同排名。

## 四、一维差分：把区间修改转成端点修改

### 1. 定义与还原

约定 `a[0] = 0`，定义：

$$
diff[i]=a[i]-a[i-1]
$$

反过来：

$$
a[i]=\sum_{j=1}^{i}diff[j]
$$

差分记录“当前位置比前一个位置改变多少”。对差分求前缀和，就能还原原数组。

### 2. 为什么只改两个端点？

给闭区间 `[l,r]` 全部加 `v`：

```cpp
diff[l] += v;
diff[r + 1] -= v;
```

- 在 `l` 处开始增加 `v`。
- 区间内部，相邻两项同时增加 `v`，差值不变。
- 从 `r+1` 开始取消这份增加。

例如长度为 5、初始全零的数组：

| 步骤 | diff[1] | diff[2] | diff[3] | diff[4] | diff[5] | diff[6] |
|---|---:|---:|---:|---:|---:|---:|
| 初始 | 0 | 0 | 0 | 0 | 0 | 0 |
| `[2,4]` 加 3 | 0 | 3 | 0 | 0 | -3 | 0 |
| 再对 `[1,3]` 加 2 | 2 | 3 | 0 | -2 | -3 | 0 |

累加 `diff[1...5]`，得到 `{2,5,5,3,0}`。

### 3. 完整模板：支持初始数组非零

**示例输入约定：** 先输入 `n、q`，再输入 `n` 个初始值，随后输入 `q` 次 `l、r、v`，最后输出修改后的数组。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<long long> a(n + 1, 0), diff(n + 2, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        diff[i] = a[i] - a[i - 1];
    }

    while (q--) {
        int l, r;
        long long v;
        cin >> l >> r >> v;
        diff[l] += v;
        diff[r + 1] -= v;
    }

    long long current = 0;
    for (int i = 1; i <= n; i++) {
        current += diff[i];
        cout << current << (i == n ? '\n' : ' ');
    }
}
```

构造 O(N)，每次更新 O(1)，最后恢复 O(N)；`Q` 次更新的总复杂度为 O(N+Q)。

**适用范围：** 先处理一批修改，再统一查看结果。普通差分不支持在每次修改之后立即以 O(1) 查询任意区间和。若修改与查询交错，需要考虑其他数据结构。

### 4. 铜组真题：Haybale Stacking

**2012 January Bronze，Problem 2**  
[官方题面](https://usaco.org/index.php?page=viewproblem2&cpid=104)

**题意概括：** 草垛初始高度为 0，每次给一段草垛加 1；全部操作结束后，求所有高度的中位数。题目保证 `N` 为奇数。

做法：差分记录每次区间加 1，最后累加得到高度，排序后取中间元素。

```cpp
// 先读入 n、k，之后读入 k 组 l、r。
vector<int> diff(n + 2, 0);
for (int i = 0; i < k; i++) {
    int l, r;
    cin >> l >> r;
    diff[l]++;
    diff[r + 1]--;
}

vector<int> height(n);
int current = 0;
for (int i = 1; i <= n; i++) {
    current += diff[i];
    height[i - 1] = current;
}

sort(height.begin(), height.end());
cout << height[n / 2] << '\n';
```

总时间 O(N\log N+K)，空间 O(N)。

## 五、差分建模与贪心：Air Cownditioning

**2021 December Bronze，Problem 2**  
[官方题面](https://usaco.org/index.php?page=viewproblem2&cpid=1156) · [官方题解](https://usaco.org/current/data/sol_prob2_bronze_dec21.html)

### 1. 先区分两个数组

目标温度为 `p[i]`，当前温度为 `t[i]`。定义：

$$
need[i]=p[i]-t[i]
$$

`need` 是各位置需要的温度改变量，**还不是差分数组**。它的相邻差 `need[i]-need[i-1]` 才是进一步使用的差分。

一次操作可以给一个连续区间整体加 1 或减 1。等价地，要从全零数组经过这些操作，得到 `need`。

### 2. 在两端补零

令 `need[0] = need[N+1] = 0`，则最少操作数为：

$$
answer=\frac12\sum_{i=1}^{N+1}|need[i]-need[i-1]|
$$

直观理解：一次区间操作在差分中只改变两个端点，各改变 1；因此要形成全部边界变化，至少需要“相邻差绝对值总和的一半”次操作。按同号区间向零调整的贪心可以达到这个下界。

例如 `need = {0,3,1,1,3}`，补零后相邻变化为 `{0,3,-2,0,2,-3}`，绝对值之和为 10，答案为 5。

### 3. 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> p(n + 1), need(n + 2, 0);
    for (int i = 1; i <= n; i++) cin >> p[i];

    for (int i = 1; i <= n; i++) {
        long long temperature;
        cin >> temperature;
        need[i] = p[i] - temperature;
    }

    long long totalChange = 0;
    for (int i = 1; i <= n + 1; i++) {
        totalChange += abs(need[i] - need[i - 1]);
    }

    cout << totalChange / 2 << '\n';
}
```

时间 O(N)，空间 O(N)。这题不是“直接执行已给定的区间更新”，而是借差分分析“最少需要多少次更新”。只记端点修改模板还不足以独立解决。

## 六、二维差分：矩形加法只修改四个角

### 1. 闭矩形模板

若数组从 1 开始，给闭矩形 `[r1,r2] × [c1,c2]` 全部加 `v`：

```cpp
//diff[i][j]=a[i][j]-a[i-1][j]-a[i][j-1]+a[i-1][j-1];
  
diff[r1][c1] += v;
diff[r2 + 1][c1] -= v;
diff[r1][c2 + 1] -= v;
diff[r2 + 1][c2 + 1] += v;
```

为 `+1` 边界留空间，数组至少开成 `(n+2) × (m+2)`。

还原时求二维前缀和：

```cpp
// d 是二维差分数组
// a 是还原后的数组
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
        a[i][j] = d[i][j]
                + a[i-1][j]
                + a[i][j-1]
                - a[i-1][j-1];
    }
}
//第二种写法
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
        d[i][j] += d[i-1][j]
                 + d[i][j-1]
                 - d[i-1][j-1];
    }
}
```

若初始矩阵不全为 0，可以让这里的差分只记录新增量，最后把还原的新增量加到原矩阵上。

`Q` 次矩形更新加一次恢复，总时间 O(Q+NM)，空间 O(NM)。

### 2. 银组真题：Painting the Barn

**2019 February Silver，Problem 2**  
[官方题面](https://usaco.org/index.php?page=viewproblem2&cpid=919)

**题意概括：** 多次给坐标平面上的矩形刷一层油漆，求最终恰好刷了 `K` 层的面积。

这里 `(x1,y1)` 与 `(x2,y2)` 是几何顶点。矩形对应单位格：

$$
[x1,x2)\times[y1,y2)
$$

例如从 `(1,1)` 到 `(3,2)` 的矩形覆盖两个单位格，面积为 2，不是 6。右端点和上端点是“结束边界”，不需要再加 1。

对每个矩形修改：

```cpp
diff[x1][y1]++;
diff[x2][y1]--;
diff[x1][y2]--;
diff[x2][y2]++;
```

```cpp
#include <bits/stdc++.h>
using namespace std;

const int LIMIT = 1000;
int diff[LIMIT + 2][LIMIT + 2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, K;
    cin >> n >> K;

    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        diff[x1][y1]++;
        diff[x2][y1]--;
        diff[x1][y2]--;
        diff[x2][y2]++;
    }

    int answer = 0;
    for (int x = 0; x < LIMIT; x++) {
        for (int y = 0; y < LIMIT; y++) {
            if (x > 0) diff[x][y] += diff[x - 1][y];
            if (y > 0) diff[x][y] += diff[x][y - 1];
            if (x > 0 && y > 0) diff[x][y] -= diff[x - 1][y - 1];

            // (x,y) 表示 [x,x+1) × [y,y+1) 的单位格。
            if (diff[x][y] == K) answer++;
        }
    }

    cout << answer << '\n';
}
```

坐标最大为 1000，单位格左下角的范围是 `0...999`，故只统计这个范围。时间 O(N+1000^2)，空间 O(1000^2)。

## 七、频次与差分结合：Convoluted Intervals

**2021 December Silver，Problem 3**  
[官方题面](https://usaco.org/index.php?page=viewproblem2&cpid=1160) · [官方题解](https://usaco.org/current/data/sol_prob3_silver_dec21.html)

### 1. 每个区间对贡献一个合法范围

区间 `i` 和区间 `j` 使以下每个 `k` 的答案加 1：

$$
a_i+a_j\le k\le b_i+b_j
$$

因此，每对区间可用两次差分修改代替逐个 `k` 更新：

```cpp
diff[a[i] + a[j]]++;
diff[b[i] + b[j] + 1]--;
```

枚举区间对需要 $O(N^2)$；加上恢复为 $O(N^2+M)$，只能获得部分分。

### 2. 从枚举区间变成枚举端点值

因为端点值都在 `0...M`，而 $M\le5000$，远小于最大 $N=2\times10^5$，统计：

```cpp
leftCount[x]   // 左端点为 x 的区间数量
rightCount[x]  // 右端点为 x 的区间数量
```

左端点值为 `x、y` 的有序区间对有 `leftCount[x] * leftCount[y]` 个；这些贡献都从 `x+y` 开始。右端点同理。

左右端点可以分别处理，因为差分增加只依赖左端点和，差分减少只依赖右端点和，最后把所有贡献相加即可。

### 3. 满分代码

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<ll> leftCount(m + 1, 0), rightCount(m + 1, 0);
    vector<ll> diff(2 * m + 2, 0);

    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        leftCount[a]++;
        rightCount[b]++;
    }

    for (int x = 0; x <= m; x++) {
        for (int y = 0; y <= m; y++) {
            diff[x + y] += leftCount[x] * leftCount[y];
            diff[x + y + 1] -= rightCount[x] * rightCount[y];
        }
    }

    ll answer = 0;
    for (int k = 0; k <= 2 * m; k++) {
        answer += diff[k];
        cout << answer << '\n';
    }
}
```

时间 O(N+M^2)，空间 O(M)，无须 FFT。`(i,j)` 是有序对，`(i,i)` 也允许，所以对同一个端点频次为 `c` 的情况要用 `c*c`，不是 `c*(c-1)`。计数最大可达 N^2，必须用 `long long`。

## 八、前缀和与差分怎么选？

| 比较项 | 前缀和 | 普通差分 |
|---|---|---|
| 主要解决的问题 | 静态区间查询 | 批量区间加减 |
| 保存的内容 | 从起点开始的累计值 | 相邻元素的变化量 |
| 一次区间求和 | 预处理后 $O(1)$ | 需还原，再构建前缀和才可 $O(1)$ |
| 一次区间加法 | 一般需更新受影响的前缀值，最坏 $O(N)$ | 记录两个端点，$O(1)$ |
| 是否适合修改与查询频繁交错 | 不能直接高效支持 | 不能直接高效支持 |

### 两种工具可以串起来用

如果题目是“先完成全部区间修改，再回答全部区间查询”：

1. 差分记录修改。
2. 对差分累加，得到最终数组 `a`。
3. 对最终数组再构建一次前缀和 `pre`。
4. 用 `pre[r] - pre[l-1]` 回答查询。

第 2 步的累加得到的是“每个位置的最终值”，并不直接等于第 3 步的“前缀总和”。

## 九、练习顺序与课堂安排

| 顺序 | 真题 | 组别与时间 | 主要训练点 |
|---:|---|---|---|
| 1 | [Daisy Chains](https://usaco.org/index.php?page=viewproblem2&cpid=1060) | 2020 Dec 铜组 | 前缀和辅助区间枚举，整数平均数判断 |
| 2 | [Breed Counting](https://usaco.org/index.php?page=viewproblem2&cpid=572) | 2015 Dec 银组 | 分类前缀计数，多次区间查询 |
| 3 | [Subsequences Summing to Sevens](https://usaco.org/index.php?page=viewproblem2&cpid=595) | 2016 Jan 银组 | 相同余数的两个前缀，空前缀初始化 |
| 4 | [Haybale Stacking](https://usaco.org/index.php?page=viewproblem2&cpid=104) | 2012 Jan 铜组 | 一维差分、恢复、中位数 |
| 5 | [Air Cownditioning](https://usaco.org/index.php?page=viewproblem2&cpid=1156) | 2021 Dec 铜组 | 改变量、相邻差、最少区间操作 |
| 6 | [Painting the Barn](https://usaco.org/index.php?page=viewproblem2&cpid=919) | 2019 Feb 银组 | 二维差分、单位格面积、半开边界 |
| 7 | [Rectangular Pasture](https://usaco.org/index.php?page=viewproblem2&cpid=1063) | 2020 Dec 银组 | 离散化、二维前缀和、去重计数 |
| 8 | [Convoluted Intervals](https://usaco.org/index.php?page=viewproblem2&cpid=1160) | 2021 Dec 银组 | 端点频次、乘法计数、差分 |

***

