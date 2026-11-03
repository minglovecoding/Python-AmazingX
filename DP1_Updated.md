## 📚动态规划：背包DP、区间DP

| 模块 | 主讲内容 | USACO 往年真题 |
| --- | --- | --- |
| 背包DP | 0-1、完全、多重、多资源、分组、计数 | [Fruit Feast，2015 December Gold](https://usaco.org/index.php?page=viewproblem2&cpid=574) |
| 区间DP | 最后合并、端点合并、重复结构 | [Modern Art 3，2021 February Gold](https://usaco.org/index.php?page=viewproblem2&cpid=1114)；[Printing Sequences，2025 February Bronze](https://usaco.org/index.php?page=viewproblem2&cpid=1493) |

首先区分恰好和最好，对于物品重量 weight、价值 value：

| 定义 | dp[0] | 其他初值 | 答案 |
| --- | --- | --- | --- |
| 总重量不超过 j 的最大价值 | 0 | 0，允许空集 | dp[W] |
| 总重量恰好 j 的最大价值 | 0 | NEG，表示不可达 | dp[W]；若仍为 NEG 则无解 |
| 总重量恰好 j 的方案数 | 1 | 0 | dp[W] |
| 能否恰好凑出 j | true | false | reachable[W] |

### 0-1 背包：先理解二维，再压缩

每件物品最多用一次。二维定义：f[i][j] 为前 i 件物品、总重量不超过 j 的最大价值。

$$
f[i][j]=\max(f[i-1][j],f[i-1][j-w_i]+v_i).
$$

两项都读取上一层。因此压成一维后，容量从大到小枚举，让 dp[j−w_i] 仍是上一层的值。

**输入约定：**第一行 n,W，接下来 n 行为重量、价值；重量为正整数。


```cpp
//时间复杂度O(nW)，空间复杂度O(W)。
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    int n, capacity; 
    cin >> n >> capacity;
    vector<ll> dp(capacity + 1, 0); // 总重量不超过当前容量。
    for (int i = 0; i < n; ++i) {
        int weight; ll value; 
        cin >> weight >> value;
        for (int j = capacity; j >= weight; --j)
            dp[j] = max(dp[j], dp[j - weight] + value);
    }
    cout << dp[capacity] << '\n';
}
/*
A	1kg	2
B	2kg	4
C	3kg	4
D	4kg	5
  
dp[5]=dp[4]+2=2 dp[4]=dp[3]+2=2 dp[3]=dp[2]+2=2 dp[2]=dp[1]+2=2 dp[1]=2
dp[5]=dp[3]+4=6 ...dp[2]=dp[0]+4=4
dp[5]=...
  
dp[5]...
*/
```

### 完全背包：允许读取当前层

每种物品有无限件，二维转移可写成：

$$
f[i][j]=\max(f[i-1][j],f[i][j-w_i]+v_i).
$$

第二项读取当前层，表示还能继续取第 i 种物品。因此容量从小到大枚举。

输入与前一节相同，时间 O(nW)，空间 O(W)。正重量是必要的模型约定；零重量、正价值、无限件会使最优值无界，不能直接套下面代码。


```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    int n, capacity; cin >> n >> capacity;
    vector<ll> dp(capacity + 1, 0);
    for (int i = 0; i < n; ++i) {
        int weight; 
        ll value; 
        cin >> weight >> value; // weight 必须为正。
        for (int j = weight; j <= capacity; ++j)
            dp[j] = max(dp[j], dp[j - weight] + value);
    }
    cout << dp[capacity] << '\n';
}
```

### 多重背包：二进制拆分用于最优化，不可直接用于计数

每种物品最多 count 件。朴素转移枚举取用数量 q：

$$
f[i][j]=\max_{0\le q\le count_i,\ qw_i\le j}
(f[i-1][j-qw_i]+qv_i).
$$

将数量 13 拆成 1、2、4、6，变成四件“捆绑物品”，每捆只能选一次。0 到 13 的任意数量都能表示，原问题就转成 0-1 背包。

注意同一个数量可能有不同捆绑表示，如 6 与 2+4。因此这份拆分适合求最优值或可达性，不能不加处理地用来统计每种原物品选取数量的方案数。

**输入约定：**n,W，随后每行 weight,value,count。先将 count 截到 W/weight，避免无效大数量。时间 O(WΣlog(count_i+1))，空间 O(W)。


```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    int n, capacity; cin >> n >> capacity;
    vector<ll> dp(capacity + 1, 0);
    for (int i = 0; i < n; ++i) {
        int weight, count; ll value; cin >> weight >> value >> count;
        count = min(count, capacity / weight);
        for (ll block = 1; count > 0; block *= 2) {
            int take = (int)min<ll>(block, count);
            int bundleWeight = weight * take;
            ll bundleValue = value * take;
            for (int j = capacity; j >= bundleWeight; --j)
                dp[j] = max(dp[j], dp[j - bundleWeight] + bundleValue);
            count -= take;
        }
    }
    cout << dp[capacity] << '\n';
}
```

### 多资源 0-1 背包

每个物品同时消耗重量与时间。定义 dp[w][t] 为总重量不超过 w、总时间不超过 t 的最大价值。

转移仍然是选或不选，只是两个资源都要检查。下面两个维度都倒序，直接保证每件物品只使用一次。

**输入约定：**n,W,T，随后 n 行 weight,time,value；资源消耗为正整数。时间 O(nWT)，空间 O(WT)。


```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    int n, W, T; cin >> n >> W >> T;
    vector<vector<ll>> dp(W + 1, vector<ll>(T + 1, 0));
    for (int i = 0; i < n; ++i) {
        int weight, time; ll value; cin >> weight >> time >> value;
        for (int w = W; w >= weight; --w)
            for (int t = T; t >= time; --t)
                dp[w][t] = max(dp[w][t], dp[w - weight][t - time] + value);
    }
    cout << dp[W][T] << '\n';
}
```

### 分组背包：每个已知物品组至多选一件

分组背包不是把序列切成连续段。每组里已有多个互斥候选，最多选一件，也可以不选。

使用 next=dp 表示“不选本组”；枚举该组某一件时，所有前驱都读取旧 dp。因为没有在原数组上覆盖，同一组内不会连续取两件，容量循环可以从小到大。

**输入约定：**第一行 groups,W；每组先输入物品数，再输入各物品的 weight,value。时间 O(W×物品总数)，空间 O(W+单组物品数)。


```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    int groups, capacity; cin >> groups >> capacity;
    vector<ll> dp(capacity + 1, 0);
    for (int g = 0; g < groups; ++g) {
        int count; cin >> count;
        vector<pair<int,ll>> items(count);
        for (auto &[weight, value] : items) cin >> weight >> value;
        vector<ll> next = dp; // 允许本组不选；所有转移读取旧层。
        for (int j = 0; j <= capacity; ++j)
            for (auto [weight, value] : items)
                if (weight <= j) next[j] = max(next[j], dp[j - weight] + value);
        dp.swap(next);
    }
    cout << dp[capacity] << '\n';
}
```

如果要求每组恰好选一件，不能简单令 next=dp；需要把 next 设为不可达，仅从旧层通过选一件产生新层。

### 组合数与排列数：循环顺序改变了计数对象

面额为 1、2，目标为 3：

- 不区分取用顺序：1+1+1、1+2，共 2 种。
- 区分取用顺序：1+1+1、1+2、2+1，共 3 种。

前者按面额逐种处理；后者按当前总和，枚举最后一次取哪种面额。两者都让 dp[0]=1，但状态分类方式不同。

输入 n,target 与 n 个互不相同的正面额。以下程序先输出组合数，再输出有序序列数，两者均模 10^9+7。时间 O(n×target)，空间 O(target)。


```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1000000007;
int main() {
    int n, target; cin >> n >> target;
    vector<int> coins(n);
    for (int &x : coins) cin >> x; // 输入正整数面额，假设互不相同。
    vector<ll> combinations(target + 1, 0), sequences(target + 1, 0);
    combinations[0] = sequences[0] = 1;
    for (int coin : coins)
        for (int sum = coin; sum <= target; ++sum)
            combinations[sum] = (combinations[sum] + combinations[sum - coin]) % MOD;
    for (int sum = 1; sum <= target; ++sum)
        for (int coin : coins)
            if (coin <= sum) sequences[sum] = (sequences[sum] + sequences[sum - coin]) % MOD;
    cout << combinations[target] << '\n' << sequences[target] << '\n';
}
```

### USACO 主讲：Printing Sequences

**2025 February Bronze** · [官方题目](https://usaco.org/index.php?page=viewproblem2&cpid=1493)

程序包含 PRINT 与可嵌套的 REP，问能否只用 K≤3 条源代码中的 PRINT 输出目标序列。循环执行次数不计入 PRINT 语句数量。

可用区间 DP：dp[l][r] 表示输出这一段所需的最少 PRINT 语句数。

1. **拼接两段程序**：枚举 cut，尝试 dp[l][cut]+dp[cut+1][r]。
2. **重复一段程序**：若 [l,r] 是其长度 p 的前缀重复若干次，且 p 整除长度，则尝试 dp[l][l+p−1]，外围 REP 不增加 PRINT 数。

单个元素初值为 1。任何程序不是顶层拼接，就是一条 REP 包住更短输出，因此这两类转移可以覆盖合法程序结构。

预处理 lcp[i][j]，表示从 i、j 开始的最长相同前缀。长度 len、周期 p 的重复条件为：

$$
len\bmod p=0,\qquad lcp[l][l+p]\ge len-p.
$$

这使每个候选周期的检查降为 O(1)，总体时间 O(N³)，空间 O(N²)，适用于 N≤100。

例 [1,2,2,1,2,2]：对 [1,2,2] 写一段两条 PRINT 的程序，外围重复两次即可；同样的输出并不要求六条 PRINT。

```c++
#include <bits/stdc++.h>
using namespace std;
int main() {
    int tests; cin >> tests;
    while (tests--) {
        int n, k; cin >> n >> k;
        vector<int> a(n);
        for (int &x : a) cin >> x;
        vector<vector<int>> lcp(n + 1, vector<int>(n + 1, 0));
        for (int i = n - 1; i >= 0; --i)
            for (int j = n - 1; j >= 0; --j)
                if (a[i] == a[j]) lcp[i][j] = 1 + lcp[i + 1][j + 1];
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int length = 1; length <= n; ++length) {
            for (int l = 0; l + length <= n; ++l) {
                int r = l + length - 1;
                dp[l][r] = length;
                for (int cut = l; cut < r; ++cut)
                    dp[l][r] = min(dp[l][r], dp[l][cut] + dp[cut + 1][r]);
                for (int period = 1; period < length; ++period) {
                    if (length % period == 0 && lcp[l][l + period] >= length - period)
                        dp[l][r] = min(dp[l][r], dp[l][l + period - 1]);
                }
            }
        }
        cout << (dp[0][n - 1] <= k ? "YES" : "NO") << '\n';
    }
}
```

### USACO 主讲：Fruit Feast

**2015 December Gold** · [P4817](https://www.luogu.com.cn/problem/P4817) · [官方题目](https://usaco.org/index.php?page=viewproblem2&cpid=574)

饱腹度不能超过 T，可以无限吃两种增加值为 A、B 的水果，最多喝一次水让当前饱腹度向下取整减半。求最大饱腹度。

单一 reachable[x] 不够：同样饱腹度下，“还能不能喝水”影响未来。需要记录喝水前和喝水后两个阶段。

1. 用 before[x] 计算不喝水能到达的饱腹度；吃水果只会增加，所以 x 递增。
2. 对所有 before[x]，令 after[x/2]=true，表示在这个时刻喝水。
3. 从 after 的所有种子再递增扩展吃水果，最后从大到小找可达值。

不能把“喝水”和“吃水果”放在一个只按 x 递增的一维循环中，因为喝水会倒退到较小的 x。先分阶段，状态依赖就清楚了。

T=8、A=5、B=6：先吃 6，喝水变 3，再吃 5，达到 8。

T≤5×10^6，时间 O(T)，空间 O(T)。用字节数组保存布尔可达性，无需两个 long long 大数组。


```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int T, A, B; cin >> T >> A >> B;
    vector<unsigned char> before(T + 1, 0), after(T + 1, 0);
    before[0] = 1;
    for (int x = 0; x <= T; ++x) {
        if (!before[x]) continue;
        if (x + A <= T) before[x + A] = 1;
        if (x + B <= T) before[x + B] = 1;
    }
    for (int x = 0; x <= T; ++x)
        if (before[x]) after[x / 2] = 1;
    for (int x = 0; x <= T; ++x) {
        if (!after[x]) continue;
        if (x + A <= T) after[x + A] = 1;
        if (x + B <= T) after[x + B] = 1;
    }
    for (int x = T; x >= 0; --x) {
        if (before[x] || after[x]) { cout << x << '\n'; break; }
    }
}
```

## 区间 DP

### 按最后操作拆分一个区间

定义 dp[l][r] 为处理完整区间 [l,r] 的结果。其前驱通常是更短的区间，故按长度从小到大计算。

区间 DP 不只一种转移：有的枚举最后分割点，有的比较端点，有的检查整段重复。不能见到 dp[l][r] 就默认加区间和。

### 石子合并：链与环的区别

线性石子合并，最后一次把 [l,cut] 与 [cut+1,r] 合并，费用为整段石子数：

$$
dp[l][r]=\min_{l\le cut<r}
\{dp[l][cut]+dp[cut+1][r]+pre[r]-pre[l-1]\}.
$$

单堆 dp[i][i]=0。求最大费用时，左右两边也必须读取最大费用 DP，不能复用最小费用的 cost。

**环形处理：**将 a 复制成长度 2N，计算长度不超过 N 的区间，最后枚举 N 个起点，取 [l,l+N−1] 的答案。数组需要按 2N 分配。

[P1880 石子合并](https://www.luogu.com.cn/problem/P1880) 的输入是环；下面程序输出最小费用、最大费用，各一行。时间 O(N³)，空间 O(N²)。

自拟小例 [1,2,3]：最小 9，最大 11。单堆时两者均为 0。


```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = (1LL << 60);
int main() {
    int n; cin >> n;
    vector<ll> a(2 * n + 1), pre(2 * n + 1, 0);
    for (int i = 1; i <= n; ++i) { cin >> a[i]; a[i + n] = a[i]; }
    for (int i = 1; i <= 2 * n; ++i) pre[i] = pre[i - 1] + a[i];
    vector<vector<ll>> small(2 * n + 1, vector<ll>(2 * n + 1, 0));
    vector<vector<ll>> large = small;
    for (int length = 2; length <= n; ++length) {
        for (int l = 1; l + length - 1 <= 2 * n; ++l) {
            int r = l + length - 1;
            small[l][r] = INF;
            large[l][r] = -INF;
            ll sum = pre[r] - pre[l - 1];
            for (int cut = l; cut < r; ++cut) {
                small[l][r] = min(small[l][r], small[l][cut] + small[cut + 1][r] + sum);
                large[l][r] = max(large[l][r], large[l][cut] + large[cut + 1][r] + sum);
            }
        }
    }
    ll answerMin = INF, answerMax = -INF;
    for (int l = 1; l <= n; ++l) {
        answerMin = min(answerMin, small[l][l + n - 1]);
        answerMax = max(answerMax, large[l][l + n - 1]);
    }
    cout << answerMin << '\n' << answerMax << '\n';
}
```

### USACO 主讲：Modern Art 3

**2021 February Gold** · [P7414](https://www.luogu.com.cn/problem/P7414) · [官方题目](https://usaco.org/index.php?page=viewproblem2&cpid=1114)

每次可以把一个区间涂成同一种颜色，允许覆盖，求完成目标序列的最少笔数。

相邻相同颜色可压缩为一个，因为它们不需要在最终图案中分开处理。定义 dp[l][r] 为涂出压缩区间的最少笔数，dp[i][i]=1。

先单独处理左端：

$$
dp[l][r]=1+dp[l+1][r].
$$

若存在 k>l 且 a[k]=a[l]，可以把处理 a[k] 的某一笔向左延伸来同时覆盖 l，再修复中间区域：

$$
dp[l][r]=\min(dp[l][r],dp[l+1][k-1]+dp[k][r]).
$$

k=l+1 时中间为空，贡献 0。必须枚举所有同色 k，不能只取最右侧同色位置。

例 [1,2,1]：先把整段涂成 1，再把中间涂成 2，共 2 笔。例 [1,2,3,1]：一笔底色 1，再补 2、3，共 3 笔。

N≤300，时间 O(N³)，空间 O(N²)。相邻压缩只会降低实际规模。


```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; cin >> n;
    vector<int> a;
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        if (a.empty() || a.back() != x) a.push_back(x);
    }
    n = (int)a.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) dp[i][i] = 1;
    for (int length = 2; length <= n; ++length) {
        for (int l = 0; l + length <= n; ++l) {
            int r = l + length - 1;
            dp[l][r] = 1 + dp[l + 1][r];
            for (int k = l + 1; k <= r; ++k) {
                if (a[l] != a[k]) continue;
                int middle = (k == l + 1 ? 0 : dp[l + 1][k - 1]);
                dp[l][r] = min(dp[l][r], middle + dp[k][r]);
            }
        }
    }
    cout << dp[0][n - 1] << '\n';
}
```
