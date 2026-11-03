## USACO 2024–2025 February 

### 金组前置题

| 本场题目 | 核心知识 | 洛谷前置题 | 学习重点 |
| --- | --- | --- | --- |
| Bessie's Function | 函数图；树形 DP；环上 DP | [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)；[P2921 Trick or Treat on the Farm G](https://www.luogu.com.cn/problem/P2921) | 前者练习选或不选的树形 DP；后者认识“每个点出度为 1”的环加树结构 |
| The Best Subsequence | 字典序贪心；异或差分；坐标压缩；快速幂；二分 | [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)；[P2367 语文成绩](https://www.luogu.com.cn/problem/P2367)；[P1226 快速幂](https://www.luogu.com.cn/problem/P1226) | 学会优先删除影响字典序的元素；将普通差分迁移到异或；处理很长的二进制段 |
| Friendship Editing | 补图；图的结构证明；子集划分 DP | [P1433 吃奶酪](https://www.luogu.com.cn/problem/P1433)（基础复习）；[P5911 PRZ](https://www.luogu.com.cn/problem/P5911)（重点） | 从“逐个加入元素”的状压 DP，进阶到“每次划出一个子集”的 DP |

### 银组前置题

| 本场题目 | 核心知识 | 洛谷前置题 | 学习重点 |
| --- | --- | --- | --- |
| The Best Lineup | 字典序贪心；后缀最大值；一次移动的影响范围 | [P1106 删数问题](https://www.luogu.com.cn/problem/P1106) | 理解字典序优先级，以及为什么应该保留或删除某个元素；随后在原题练习后缀最大值 |
| Vocabulary Quiz | 前缀树模型；父指针；叶子删除；均摊分析 | [P2580 于是他错误的点名开始了](https://www.luogu.com.cn/problem/P2580)（用 Trie 实现，概念热身） | 理解共享前缀对应共享祖先；本题已直接给出树，不需要重新建字符 Trie，也不必先学 LCA |
| Transforming Pairs | 逆向思考；唯一前驱；欧几里得式批量运算 | [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)（数论热身） | 复习辗转相除法，理解用除法替代连续减法；原题还需要处理起点边界 |

| 铜组题目 | 核心方法 | 本文实现复杂度 |
| --- | --- | --- |
| Reflection | 四点对称组；局部贡献维护 | 时间 O(N²+U)，空间 O(N²) |
| Making Mexes | 频次；缺失数；操作重合 | 时间 O(N)，空间 O(N) |
| Printing Sequences | 重复结构分类；分段枚举 | 每组时间 O(N²)，空间 O(N) |

***

## Gold 1：Bessie's Function

[题目](https://usaco.org/index.php?page=viewproblem2&cpid=1497) · [官方解析](https://usaco.org/current/data/sol_prob1_gold_feb25.html)

### 题意与数据范围

给定函数 f(i)=a[i]。花费 c[i] 可以把 a[i] 改为任意合法编号。要求最终对所有 i 都满足：

$$
f(f(i))=f(i).
$$

求最小修改代价。N≤2×10^5，c[i]≤10^9，答案使用 long long。

### 从函数条件变成图结构

建立有向边 i→a[i]。每个点恰好有一条出边，这类图叫函数图。每个弱连通分量由一个有向环及若干指向环的树构成；环也可能是自环。

若最终 i 指向 v，则 f(f(i))=f(i) 等价于 f(v)=v。因此，所有被指向的点都必须是固定点，也就是自己指向自己。

关键问题：修改一条出边时，需要尝试指向所有点吗？

不需要。任取一个合法方案，若其中被修改的 i 指向其他固定点 v，可以改为让 i 指向自己，费用不变。这样 i 成为固定点，原来指向 i 的点也仍然合法。逐个调整后，可以得到一种不更贵的方案：每个点只考虑“不修改”或“改成自环”。

因此，针对原图中的每条边 i→a[i]，至少有一个端点必须成为固定点：

$$
selected[i]\lor selected[a[i]]=1.
$$

这就是原图底层边约束上的最小权点覆盖。原本已经满足 a[i]=i 的点免费选中；由于自环约束，它必须处于选中状态。

### 先剥离树，再处理环

维护每个点的入度，将所有入度为 0 的点加入队列。弹出 u 后，去掉 u→a[u]；若父节点入度降为 0，再入队。

这样处理的顺序天然是从树的叶子朝环走。最后剩下的点恰好位于环上，避免了深链递归的栈空间问题。

定义两个状态，暂时只计算已经汇入 u 的树枝：

- dp0[u]：u 不选为固定点的最小代价。
- dp1[u]：u 选为固定点的最小代价。

初值 dp0[u]=0；dp1[u]=c[u]，但已有自环的点取 0。

设 u 的父节点为 v=a[u]，则：

$$
\begin{aligned}
dp0[v]&\mathrel{+}=dp1[u],\\
dp1[v]&\mathrel{+}=\min(dp0[u],dp1[u]).
\end{aligned}
$$

原因：v 不选时，u 必须选；v 选时，u 可选可不选。

### 环上 DP

设环上依次为 v₀,v₁,…,vₘ₋₁，边沿下标方向连接，最后一个点指回第一个。

枚举第一个点不选或选，沿环做两状态 DP。令 cur[0]、cur[1] 表示处理到上一点时，它不选或选的最优代价：

$$
\begin{aligned}
next[0]&=cur[1]+dp0[v],\\
next[1]&=\min(cur[0],cur[1])+dp1[v].
\end{aligned}
$$

结束时还要检查首尾边：第一个点不选，则最后一个点必须选。若环长为 1，直接使用该点的 dp1。

### 手推示例

```text
N = 3
a = [2,3,1]
c = [5,1,4]
```

三个点形成环 1→2→3→1。每条边至少选一个端点，所以至少选两个点。

| 选中的固定点 | 代价 |
| --- | --- |
| 1、2 | 6 |
| 1、3 | 9 |
| 2、3 | 5 |

选择 2、3，将 a[2] 改为 2，a[3] 改为 3。最终函数为 [2,2,3]，答案 5。

### 完整 C++17 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = (1LL << 60);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n), indegree(n, 0);
    vector<ll> cost(n), dp0(n, 0), dp1(n);
    for (int &x : a) { cin >> x; --x; }
    for (ll &x : cost) cin >> x;
    for (int u = 0; u < n; ++u) {
        ++indegree[a[u]];
        dp1[u] = (a[u] == u ? 0 : cost[u]);
    }

    // dp0：不选为固定点；dp1：选为固定点。
    queue<int> q;
    for (int u = 0; u < n; ++u)
        if (indegree[u] == 0) q.push(u);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        int v = a[u];
        dp0[v] += dp1[u];
        dp1[v] += min(dp0[u], dp1[u]);
        if (--indegree[v] == 0) q.push(v);
    }

    ll answer = 0;
    vector<bool> used(n, false);
    for (int start = 0; start < n; ++start) {
        if (indegree[start] == 0 || used[start]) continue;
        vector<int> cycle;
        int u = start;
        do {
            used[u] = true;
            cycle.push_back(u);
            u = a[u];
        } while (u != start);

        if (cycle.size() == 1) {
            // 原本的自环必须保留为固定点，代价为 0。
            answer += dp1[start];
            continue;
        }
        ll best = INF;
        for (int first = 0; first <= 1; ++first) {
            array<ll, 2> cur{INF, INF};
            cur[first] = first ? dp1[start] : dp0[start];
            for (int i = 1; i < (int)cycle.size(); ++i) {
                int v = cycle[i];
                array<ll, 2> next;
                next[0] = cur[1] + dp0[v];
                next[1] = min(cur[0], cur[1]) + dp1[v];
                cur = next;
            }
            // 最后一个点与第一个点也必须至少选一个。
            ll candidate = first ? min(cur[0], cur[1]) : cur[1];
            best = min(best, candidate);
        }
        answer += best;
    }
    cout << answer << '\n';
}
```

---

## 金组第二题：The Best Subsequence

[题目](https://usaco.org/index.php?page=viewproblem2&cpid=1498) · [官方解析](https://usaco.org/current/data/sol_prob2_gold_feb25.html)

### 4.1 题意与数据范围

一个长度 N 的二进制串，初始全为 0。先执行 M 次区间翻转，再回答 Q 个询问：从子串 [l,r] 中选出长度恰好为 k、字典序最大的子序列，输出其二进制数值模 10^9+7。

N≤10^9，M,Q≤2×10^5。所有修改都在所有询问之前完成。子序列可以不连续，字符相对顺序不能改变。

两个难点：如何选出最优子序列，以及如何在无法展开的长串上执行这个选择。

### 4.2 先把字典序贪心想清楚

设区间长度 L=r-l+1，需要删除 d=L-k 个字符。

1. 如果区间中至少有 k 个 1，直接选 k 个 1，答案为 2^k−1。
2. 否则，最终必须保留全部 1，并删除区间中最早出现的 d 个 0。

为什么这样最优？若仍有 0 可以删除，保留 1 通常能把较大的字符放在更前面；若只有尾部的 0，删除它也不劣于删除一个 1。固定保留全部 1 后，优先删除较早的 0，会让后面的 1 尽量前移。可通过逐次交换删除位置，得到上述规范方案。

特别注意：这一性质依赖于字符只有 0 和 1，不能原样推广到任意字母表。

### 4.3 用一个位置描述最终答案

若 d>0，设 p 是 [l,r] 中第 d 个 0 的位置。删除前 d 个 0 后：

- 原区间 [l,p] 中留下的字符全部是 1。
- 后缀 [p+1,r] 原封不动保留。

若 d=0，定义 p=l−1。

令 R=r-p，则最优结果为：

```text
(k-R) 个 1 + 原串 [p+1,r]
```

因此：

$$
answer=(2^{k-R}-1)\cdot2^R+value(p+1,r)
      =2^k-2^R+value(p+1,r).
$$

在“区间中的 1 不够 k 个”的分支中，R≤k，所以前半部分长度非负。

### 4.4 异或差分与坐标压缩

翻转 [l,r]，只需记录两个事件：l 处翻转，r+1 处翻转。同一位置的偶数次事件抵消。

把所有事件排序后，串被分成 O(M) 个连续段，每段全是 0 或全是 1。例如：

```text
原坐标范围       段内字符
[1,4)               0
[4,10)              1
[10,N+1)            0
```

压缩后保存 edge[i] 为段起点、bit[i] 为段内字符，段的真实长度为 edge[i+1]−edge[i]。这里保留的是区间及长度，而不是把坐标简单替换成排名后当作等距字符。

### 4.5 两种前缀信息

在每个段起点处维护：

- zeros[i]：原串 [1,edge[i]) 中 0 的总数。
- value[i]：原串 [1,edge[i]) 对应的二进制数值，已取模。

向前缀追加长度 len、字符为 b 的一整段：

$$
newValue=oldValue\cdot2^{len}+b(2^{len}-1)\pmod{MOD}.
$$

若要计算某个落在段内的位置 x 的前缀值，只需先二分找到所在段，再追加该段到 x 的部分即可。快速幂在 O(log N) 时间计算 2 的幂。

设 P(x) 为前 x 个字符的二进制值，则：

$$
value(p+1,r)=P(r)-P(p)\cdot2^{r-p}\pmod{MOD}.
$$

这个公式与普通区间前缀和类似，但要先把前缀 P(p) 左移相应位数。

### 4.6 如何找到第 d 个零

令 before 为 l 之前的零的个数。我们需要整个串中的第 before+d 个零。

zeros 数组单调不降，对它 lower_bound 找到第一次达到目标计数的边界。目标零一定落在这个边界前面的零段内，再根据偏移计算原坐标 p。

整个询问不需要构造最终子序列，也不需要在 [l,r] 上逐个扫描。

### 4.7 手推示例

```text
子串：10101
k = 4
```

需要删除 1 个字符。保留全部三个 1，删除最早的 0：

```text
1 0 1 0 1  →  1 1 0 1
```

p=2，R=3，原后缀为 101，数值 5。

$$
answer=2^4-2^3+5=13.
$$

若改成 k=3，直接选出 111，答案为 7。

### 4.8 完整 C++17 代码

本实现只压缩翻转事件，不要求事先保存询问端点。任意位置的前缀信息通过“段起点信息 + 段内偏移”计算，不需要模逆元。


```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1000000007;

ll power2(ll exponent) {
    ll result = 1, base = 2;
    while (exponent > 0) {
        if (exponent & 1) result = result * base % MOD;
        base = base * base % MOD;
        exponent >>= 1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n;
    int m, q;
    cin >> n >> m >> q;
    vector<ll> events;
    events.reserve(2 * m + 2);
    for (int i = 0; i < m; ++i) {
        ll l, r; cin >> l >> r;
        events.push_back(l);
        events.push_back(r + 1);
    }
    sort(events.begin(), events.end());

    // edge[i] 是段起点；bit[i] 表示 [edge[i], edge[i+1]) 的值。
    vector<ll> edge{1};
    vector<int> bit{0};
    int current = 0;
    for (int i = 0; i < (int)events.size();) {
        int j = i;
        while (j < (int)events.size() && events[j] == events[i]) ++j;
        ll x = events[i];
        if ((j - i) & 1) {
            current ^= 1;
            if (x == 1) bit[0] = current;
            else if (x <= n) {
                edge.push_back(x);
                bit.push_back(current);
            }
        }
        i = j;
    }
    edge.push_back(n + 1);
    int segments = (int)bit.size();
    vector<ll> zeros(segments + 1, 0), value(segments + 1, 0);
    for (int i = 0; i < segments; ++i) {
        ll length = edge[i + 1] - edge[i];
        ll factor = power2(length);
        zeros[i + 1] = zeros[i] + (bit[i] == 0 ? length : 0);
        value[i + 1] = (value[i] * factor
                       + bit[i] * (factor - 1 + MOD)) % MOD;
    }

    auto segmentOf = [&](ll x) {
        return int(upper_bound(edge.begin(), edge.end(), x)
                   - edge.begin()) - 1;
    };
    auto zeroPrefix = [&](ll x) -> ll {
        if (x == 0) return 0;
        int i = segmentOf(x);
        return zeros[i] + (bit[i] == 0 ? x - edge[i] + 1 : 0);
    };
    auto binaryPrefix = [&](ll x) -> ll {
        if (x == 0) return 0;
        int i = segmentOf(x);
        ll factor = power2(x - edge[i] + 1);
        return (value[i] * factor + bit[i] * (factor - 1 + MOD)) % MOD;
    };

    while (q--) {
        ll l, r, k;
        cin >> l >> r >> k;
        ll before = zeroPrefix(l - 1);
        ll numberZeros = zeroPrefix(r) - before;
        ll length = r - l + 1;
        if (length - numberZeros >= k) {
            cout << (power2(k) - 1 + MOD) % MOD << '\n';
            continue;
        }
        ll erase = length - k;
        ll p = l - 1;
        if (erase > 0) {
            // 找整个串中的第 before+erase 个 0。
            ll target = before + erase;
            int boundary = int(lower_bound(zeros.begin() + 1,
                                           zeros.end(), target) - zeros.begin());
            int i = boundary - 1;
            p = edge[i] + (target - zeros[i]) - 1;
        }
        ll suffixLength = r - p;
        ll factor = power2(suffixLength);
        ll suffixValue = (binaryPrefix(r) - binaryPrefix(p) * factor) % MOD;
        // 保留下来的前半部分全是 1，后半部分是原串 [p+1,r]。
        ll answer = (power2(k) - factor + suffixValue) % MOD;
        if (answer < 0) answer += MOD;
        cout << answer << '\n';
    }
}
```

---

## 5. 金组第三题：Friendship Editing

[题目](https://usaco.org/index.php?page=viewproblem2&cpid=1499) · [官方解析](https://usaco.org/current/data/sol_prob3_gold_feb25.html)

### 5.1 题意与数据范围

给定 N 个点的无向简单图，N≤16。一次操作可以增添或删除一条边。

要求最终满足：如果 a、b 相邻，那么任意其他点 c 至少与 a、b 中的一个相邻。求最少修改次数。

N 很小提示使用状压，但首先必须知道合法图长什么样。

### 5.2 取补图，识别合法结构

假设 a 与 c 不相邻、b 与 c 不相邻。那么 a 与 b 也不能相邻，否则边 a-b 与点 c 就违反要求。

换成补图语言：补图中有 a-c、c-b，就必须有 a-b。沿路径反复应用这个性质，得到补图中每个连通分量都是完全图。

因此：

- 补图：若干互不连接的完全图。
- 原图：若干组，组内没有边，不同组之间全部有边，即完全多部图。

原题等价于：把所有顶点划成若干组，修改成组内无边、组间全连，使总代价最小。

### 5.3 先建立一个统一基准

先把原图补成完全图，需要补的边数为：

$$
baseline=\binom N2-M.
$$

然后决定哪些顶点放在同一组。对于某个组 S，把组内所有边取消。

设原图中 S 内有 E 条边，组内共有 P=|S|(|S|−1)/2 对顶点：

- 原来已有的 E 条边：现在要删除，额外增加 E 次操作。
- 原来没有的 P−E 条边：基准方案补过它们，现在不必补，减少 P−E 次操作。

所以该组相对基准的增量为：

$$
gain[S]=E-(P-E)=2E-P.
$$

gain 可以是负数，它是相对基准的变化量，不是独立修改次数。

### 5.4 子集划分 DP

定义 dp[mask] 为将 mask 中顶点划分成若干组的最小增量，dp[0]=0。

每次取出一个非空子集 group 作为同一组：

$$
dp[mask]=\min_{\varnothing\ne group\subseteq mask}
\{dp[mask\setminus group]+gain[group]\}.
$$

答案为 baseline+dp[(1<<N)−1]。

实现时固定 mask 中编号最小的点，让当前选出的 group 必须包含它。每个划分恰有一组包含该点，这样不会遗漏，而且免去了同一个划分不同选组顺序的重复枚举。

gain 的预处理也可利用最低位：去掉点 u 得到 rest，只需计算 u 与 rest 之间有多少条原边，即可从 gain[rest] 推出 gain[mask]。

### 5.5 手推示例

```text
3 个点，原图只有边 1-2。
```

完全图还缺 1-3、2-3，baseline=2。

取组 {1,2,3}，原边 E=1，点对 P=3，因此 gain=2−3=−1。总代价为 2−1=1，即删掉唯一的边，变为空图。

也可以选择组 {1,3} 和 {2}，只补边 2-3，同样花费 1。两种结果都满足条件。

### 5.6 完整 C++17 代码


```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> adjacency(n, 0);
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v; --u; --v;
        adjacency[u] |= 1 << v;
        adjacency[v] |= 1 << u;
    }
    int total = 1 << n;
    vector<int> gain(total, 0), dp(total, 1000000000);
    for (int mask = 1; mask < total; ++mask) {
        int u = __builtin_ctz((unsigned)mask);
        int rest = mask ^ (1 << u);
        int edges = __builtin_popcount((unsigned)(adjacency[u] & rest));
        gain[mask] = gain[rest] + 2 * edges
                     - __builtin_popcount((unsigned)rest);
    }
    dp[0] = 0;
    for (int mask = 1; mask < total; ++mask) {
        int firstBit = mask & -mask;
        int rest = mask ^ firstBit;
        // 只枚举包含 firstBit 的组，避免同一划分的不同组顺序。
        for (int part = rest;; part = (part - 1) & rest) {
            int group = part | firstBit;
            dp[mask] = min(dp[mask], dp[mask ^ group] + gain[group]);
            if (part == 0) break;
        }
    }
    int baseline = n * (n - 1) / 2 - m;
    cout << baseline + dp[total - 1] << '\n';
}
```

---

## 6. 银组第一题：The Best Lineup

[题目](https://usaco.org/index.php?page=viewproblem2&cpid=1494) · [官方解析](https://usaco.org/current/data/sol_prob1_silver_feb25.html)

### 6.1 题意与数据范围

给定队列 a。可以依次取出队首，选择加入答案队列或丢弃，所以答案是 a 的一个子序列。

在构造答案之前，最多可以把一头牛移到它原位置之前的任意位置。求字典序最大的答案；若一个序列是另一个的前缀，更长的序列更大。

每组 N≤2×10^5，所有测试组的 N 之和≤10^6，标签范围为 [1,N]。

### 6.2 不移动时，哪些元素应该留下

从当前位置向后看，答案的下一项必须选后缀最大值。若最大值出现多次，保留最早一次不会妨碍后面选择，因此相同最大值都可以保留。

等价条件：

$$
a[i]=\max_{j\ge i}a[j].
$$

从右向左维护最大值，取所有不小于当前最大值的元素，再反转。得到的 b 是不增序列。

例如：

```text
a = [4,3,2,1,3]
b = [4,3,3]
```

记录 p[t]：b 的第 t 个元素在 a 中的原位置。后续不仅需要 b 的值，也需要它来自哪里。

### 6.3 一次提前移动有什么用

把某个后缀最大值 b[t] 提前，可以让原来在它前面、被它挡住的一些较小元素出现在它之后，进而进入答案。

自然的移动位置是前一个已选点之后，即 p[t−1]+1。再提前越过一个更大已选值不会更优；相等值之间也不必跨越来扩大候选范围。

移动以后，需要重新检查的局部区域是：

```text
(p[t-1], p[t+1]) 中除去 p[t] 的元素
```

区域右侧的答案已经以 b[t+1] 开头。以 b[t+1] 为初始后缀最大值，从右向左扫描该区域，即可找出新加入的元素。

首尾用哨兵统一处理：p[0]=−1、b[0]=N+1；末尾位置 N、末尾值 −1。

### 6.4 为什么找到第一次有效改进就能停

原来的 b 都能保留，移动的目的只是插入新元素。新插入的元素不小于后面的已选值，否则它不能成为后缀最大值。

应优先改善更靠前的答案位置。依次检查 b[t]，选择第一次能加入新元素的移动，并在该局部取完整的后缀最大值子序列。这也是处理相同标签时应保留等号的原因：新增一个相等元素仍然可能使整个答案更大。

这里只需枚举原本在 b 中的元素。把一个原来不在 b 中的元素提前，不能消除它后方更大的阻挡者，也不会产生更优的后缀最大值序列。

### 6.5 手推示例

```text
a = [4,3,2,1,3]
```

原答案为 [4,3,3]。提前最后一个 3，放在第二个位置的 3 后面：

```text
[4,3,2,1,3] → [4,3,3,2,1]
```

现在 2、1 也都成为后缀最大值，答案为 [4,3,3,2,1]。

再看 [5,1,2,6,3,4]：原答案为 [6,4]。把 6 提到最前面，新增 5，得到 [6,5,4]。

### 6.6 完整 C++17 代码


```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tests; cin >> tests;
    while (tests--) {
        int n; cin >> n;
        vector<int> a(n);
        for (int &x : a) cin >> x;
        vector<int> chosen;
        int maximum = -1;
        for (int i = n - 1; i >= 0; --i) {
            if (a[i] >= maximum) {
                chosen.push_back(i);
                maximum = a[i];
            }
        }
        reverse(chosen.begin(), chosen.end());
        vector<int> pos{-1}, label{n + 1};
        for (int i : chosen) {
            pos.push_back(i);
            label.push_back(a[i]);
        }
        pos.push_back(n);
        label.push_back(-1);

        int insertAfter = -1;
        vector<int> extra;
        int count = (int)chosen.size();
        for (int t = 1; t <= count; ++t) {
            vector<int> candidate;
            int suffixMaximum = label[t + 1];
            // 把 pos[t] 提前到 pos[t-1]+1 后，检查新暴露的后缀最大值。
            for (int j = pos[t + 1] - 1; j > pos[t - 1]; --j) {
                if (j == pos[t]) continue;
                if (a[j] >= suffixMaximum) {
                    candidate.push_back(a[j]);
                    suffixMaximum = a[j];
                }
            }
            if (!candidate.empty()) {
                reverse(candidate.begin(), candidate.end());
                extra = move(candidate);
                insertAfter = t;
                break;
            }
        }
        vector<int> answer;
        for (int t = 1; t <= count; ++t) {
            answer.push_back(label[t]);
            if (t == insertAfter)
                answer.insert(answer.end(), extra.begin(), extra.end());
        }
        for (int i = 0; i < (int)answer.size(); ++i) {
            if (i) cout << ' ';
            cout << answer[i];
        }
        cout << '\n';
    }
}
```

### 6.7 复杂度、部分解与易错点

虽然代码有“枚举 t + 扫描区间”，但每个间隙 (p[t],p[t+1]) 最多被相邻的两个候选检查一次，总扫描量是 O(N)。仅在第一次找到非空新增序列时合并答案，所以不会反复做线性插入。每组总时间 O(N)，空间 O(N)。

小数据可以枚举旧位置和新位置，每次重新求后缀最大值，时间 O(N³)。先写这个暴力非常适合作为全解的对照程序。

易错点：不能直接把 a 排序；重复标签不能随意去重；构造后缀最大值时用 >=；本题答案长度不固定，延长相同前缀也可能变优；最多移动一次，可以完全不移动。

课堂提问：移动一头牛，为什么可能让多头牛同时出现在最终答案里？

---

## 7. 银组第二题：Vocabulary Quiz

[题目](https://usaco.org/index.php?page=viewproblem2&cpid=1495) · [官方解析](https://usaco.org/current/data/sol_prob2_silver_feb25.html)

### 7.1 题意与输入模型

单词 0 是空串。单词 i 由单词 p[i] 追加一个字符得到，且 p[i]<i。所有单词不同。待测单词恰好是那些不是其他单词前缀的单词。

给出待测单词的读取顺序。每读完一个单词，就从词库中删除它。问读取当前单词时，最少读几个字符就能区分它与剩余词库里的其他单词。

N≤10^6。输入不含实际字符，也不额外输入 M；M 是初始叶子数，由 parent 数组计算，随后读入 M 个单词编号。

### 7.2 把单词变成前缀树

p[i]→i 构成一棵以 0 为根的树：

- 节点表示前缀。
- 深度表示单词长度。
- 根到节点的路径表示逐个字符读入。
- 初始叶子表示待测单词。

p[i]<i，因此输入 p[i] 时，depth[p[i]] 已知，可以直接计算 depth[i]，不必 DFS。

由于子节点代表不同的下一字符，读到某个前缀是否足以识别，取决于该前缀下面还剩几条有效分支。

### 7.3 从叶子向上缩短

设当前单词为叶子 x。

如果 x 的父节点只剩这一条有效分支，那么读到父节点的前缀已经足以识别 x，可以令 x=parent[x]，继续尝试缩短。

当发生以下情况之一时停止：

1. x 已经是根 0：只剩一个待测单词，不用读任何字符，答案 0。
2. parent[x] 至少有两条有效分支：不能再省掉 x 这一层，答案为 depth[x]。

读完以后，x 及其下面刚才经过的整条分支都不再有待测单词，可以删除。若 x 不是根，将 parent[x] 的有效孩子数减一。

代码中上移到某个父节点时，把该节点的 children 设为 0，表示这条被识别、即将整体删除的链已经收拢到当前位置。这里维护的是动态有效分支，而不是最初的孩子数量。

### 7.4 为什么总时间是 O(N)

单次上移确实可能走很长一条链，但走过的节点会随当前单词一起被删除，以后不会反复经过。

因此总上移次数最多 N 次，再加每个待测单词一次停止判断，总复杂度为 O(N)。这是均摊分析，不能用“每个单词最长 N”直接得出 O(N²)。

### 7.5 手推示例

```text
N = 4
parent = [0,0,1,1]
读取顺序：4、3、2
```

| 节点 | 父节点 | 深度 | 初始是否为待测单词 |
| --- | --- | --- | --- |
| 1 | 0 | 1 | 否 |
| 2 | 0 | 1 | 是 |
| 3 | 1 | 2 | 是 |
| 4 | 1 | 2 | 是 |

读 4：父节点 1 下面有 3、4 两条分支，需要读 2 个字符。删掉 4 后，节点 1 只剩一条分支。

读 3：可以上移到节点 1；但根下面还有节点 2 的分支，因此答案 1。然后删除节点 1 这一支。

读 2：词库只剩它一个，沿链上移到根，答案 0。

最终输出 2、1、0。

### 7.6 完整 C++17 代码


```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> parent(n + 1, 0), depth(n + 1, 0), children(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> parent[i];
        depth[i] = depth[parent[i]] + 1;
        ++children[parent[i]];
    }
    int words = 0;
    for (int i = 1; i <= n; ++i)
        if (children[i] == 0) ++words;

    for (int i = 0; i < words; ++i) {
        int x; cin >> x;
        // 若父节点只剩这一条有效分支，读到父节点就足以识别。
        while (x != 0 && children[parent[x]] == 1) {
            x = parent[x];
            children[x] = 0;
        }
        cout << depth[x] << '\n';
        // 删除这一整条已经无用的分支。
        if (x != 0) --children[parent[x]];
    }
}
```

### 7.7 复杂度、部分解与易错点

总时间 O(N)，空间 O(N)。只需 parent、depth、children 三个数组，不需要保存完整字符串、邻接表或倍增表。

小数据可显式列出每个单词的祖先路径，与其他未读单词逐对比较最长公共前缀。它有助于理解答案，却可能重复扫描同一条长链。

易错点：最后一个单词的答案是 0；删除单词以后，原来的非叶节点也可能变成需要删除的有效叶子；不能始终使用初始孩子数；本题并不要求计算真正的字符串。

课堂提问：为什么没有输入字符，我们仍能判断两个单词的公共前缀？

---

## 8. 银组第三题：Transforming Pairs

[题目](https://usaco.org/index.php?page=viewproblem2&cpid=1496) · [官方解析](https://usaco.org/current/data/sol_prob3_silver_feb25.html)

### 8.1 题意与数据范围

起点为正整数对 (a,b)，每次可选：

$$
(x,y)\to(x+y,y),\qquad (x,y)\to(x,x+y).
$$

求到目标 (c,d) 的最少操作次数，不可达输出 −1。T≤10^4，各数≤10^18。

### 8.2 从正向搜索转为逆向唯一前驱

正向每步有两个选择，且数值范围过大。反过来看：

- 若 c>d，最后一步只能增加第一项，前驱为 (c−d,d)。
- 若 d>c，最后一步只能增加第二项，前驱为 (c,d−c)。
- 若 c=d，除非已经等于起点，否则没有正整数前驱。

为什么前驱唯一？增加后的那一项等于两个正数之和，必定严格大于没有增加的那一项。

因此不需要 BFS，也不需要比较两条路径。唯一倒推路径能到起点，其操作数就是答案；到不了就无解。

### 8.3 不能逐次减，要批量减

考虑从 (1,10^18) 回到 (1,1)，逐次减 1 需要近 10^18 次。

当 c>d 时，连续多次从第一项减去 d。在不越过起点下界 a 的前提下，最多能减：

$$
batch=\left\lfloor\frac{c-a}{d}\right\rfloor.
$$

更新 c←c−batch×d，并将答案增加 batch。另一方向对称。

如果 c>d 但 batch=0，说明唯一的下一步就会让第一项小于 a，因此无解。

这里不能一律直接 c%=d，因为可能把本应停在 a 的状态跳过去。

### 8.4 某一项到达起点时直接判断

若 c=a，之后不能再减少第一项，只能重复从 d 减去 c。此时要求：

$$
d\ge b,\qquad (d-b)\bmod c=0.
$$

满足时增加 (d−b)/c 次即可。d=b 的情形对称。

最大公约数在正向操作中不变，但“起点和终点 gcd 相同”只是必要条件，不足以判断有序数对可达。不能为方便计算而只交换目标的两项。

### 8.5 手推示例

```text
起点：(5,3)
目标：(8,19)
```

先从目标倒推。19>8，可以一次减去 2×8：

```text
(8,19) → (8,3)，累计 2 次。
```

第二项到达起点的 3，第一项差 8−5=3，恰好再减一次：

```text
(8,3) → (5,3)，累计 3 次。
```

正向检查：(5,3)→(8,3)→(8,11)→(8,19)。

若目标换成 (19,8)，虽然 gcd 仍然相同，但唯一倒推路径无法到达 (5,3)，答案为 −1。

### 8.6 完整 C++17 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll solve(ll a, ll b, ll c, ll d) {
    ll operations = 0;
    while (c >= a && d >= b) {
        if (c == a && d == b) return operations;
        if (c == a) {
            if ((d - b) % c == 0) return operations + (d - b) / c;
            return -1;
        }
        if (d == b) {
            if ((c - a) % d == 0) return operations + (c - a) / d;
            return -1;
        }
        if (c == d) return -1;
        if (c > d) {
            ll batch = (c - a) / d;
            if (batch == 0) return -1;
            c -= batch * d;
            operations += batch;
        } else {
            ll batch = (d - b) / c;
            if (batch == 0) return -1;
            d -= batch * c;
            operations += batch;
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tests; cin >> tests;
    while (tests--) {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
        cout << solve(a, b, c, d) << '\n';
    }
}
```

### 8.7 复杂度、部分解与易错点

批量过程与欧几里得算法相近，每经过常数次非终止批量操作，较大值会显著缩小。每组时间 O(log V)，空间 O(1)。

小范围可以从 (a,b) BFS，超过目标任一坐标就不再扩展；进一步可以逆向逐次减法；最后用除法合并连续减法。

易错点：必须先检查越过起点的情况；不能把正整数减到 0 后继续；相等但不是起点时应判无解；操作数和数值都用 long long。本实现的 batch×较小项不超过被减项与起点之差，避免了大数相加的溢出问题。

课堂提问：为什么本题虽要求“最少次数”，却不需要最短路算法？

---

## 9. 铜组第一题：Reflection

[题目](https://usaco.org/index.php?page=viewproblem2&cpid=1491) · [官方解析](https://usaco.org/current/data/sol_prob1_bronze_feb25.html)

### 9.1 题意与数据范围

给定 N×N 画布，N 为偶数且 N≤2000。要求画布关于横向和纵向中线都对称。一次可修改一个格子的颜色。

随后 U≤10^5 次操作，每次翻转一个格子。输出最初以及每次更新后，使画布满足对称条件的最少修改次数。

### 9.2 将四个对称位置分成一组

使用从 0 开始的坐标，(r,c) 的四个对称位置是：

$$
(r,c),\quad(r,N-1-c),\quad(N-1-r,c),\quad(N-1-r,N-1-c).
$$

最终这四格必须相同。N 是偶数，因此它们是四个不同格子。不同对称组互不影响。

将任意格子映射到左上角代表：

$$
x=\min(r,N-1-r),\qquad y=\min(c,N-1-c).
$$

题目从右上象限生成图案，但选择左上作为分组代表也完全等价。

### 9.3 每组的最优贡献

设这一组有 count 个 '#':

- 全改成 '.'，需要 count 次。
- 全改成 '#'，需要 4−count 次。

所以贡献为 min(count,4−count)。总答案就是所有组的贡献和。

| '#' 的个数 | 0 | 1 | 2 | 3 | 4 |
| --- | --- | --- | --- | --- | --- |
| 最少修改次数 | 0 | 1 | 2 | 1 | 0 |

### 9.4 单点修改只更新一个组

翻转格子前，先从总答案减掉所属组的旧贡献；更新颜色与 count；再加回新贡献。

不需要重新遍历整个画布。更不能真的把画布修复成某个对称状态：题目只询问修复代价，后续更新仍然作用于原画布被逐次翻转后的状态。

### 9.5 手推示例

某组四格为 ['#','#','#','.']，贡献 1。

如果把唯一的 '.' 翻成 '#'，count 从 3 变成 4，贡献从 1 变成 0，总答案减一。若再把一个 '#' 翻成 '.'，贡献又回到 1。

### 9.6 完整 C++17 代码


```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, updates;
    cin >> n >> updates;
    vector<string> grid(n);
    for (string &row : grid) cin >> row;
    int half = n / 2;
    vector<vector<int>> painted(half, vector<int>(half, 0));
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            int x = min(r, n - 1 - r), y = min(c, n - 1 - c);
            painted[x][y] += grid[r][c] == '#';
        }
    }
    auto contribution = [](int count) { return min(count, 4 - count); };
    int answer = 0;
    for (int r = 0; r < half; ++r)
        for (int c = 0; c < half; ++c)
            answer += contribution(painted[r][c]);
    cout << answer << '\n';
    while (updates--) {
        int r, c; cin >> r >> c; --r; --c;
        int x = min(r, n - 1 - r), y = min(c, n - 1 - c);
        answer -= contribution(painted[x][y]);
        if (grid[r][c] == '#') {
            grid[r][c] = '.';
            --painted[x][y];
        } else {
            grid[r][c] = '#';
            ++painted[x][y];
        }
        answer += contribution(painted[x][y]);
        cout << answer << '\n';
    }
}
```

### 9.7 复杂度、部分解与易错点

初始化时间 O(N²)，每次更新 O(1)，总时间 O(N²+U)，空间 O(N²)。

U 很小时可以每次重新计算所有组，时间 O((U+1)N²)。全解是在这一暴力基础上，只重算受影响的贡献。

易错点：使用 0-based 时镜像是 N−1−r；每组只计一次；最初也要输出答案，总共 U+1 行；同一个位置可以连续翻转多次；两种颜色各两格时贡献为 2。

课堂提问：如果一次更新影响的不是一格而是两个格子，最多需要重算几个对称组？

---

## 10. 铜组第二题：Making Mexes

[题目](https://usaco.org/index.php?page=viewproblem2&cpid=1492) · [官方解析](https://usaco.org/current/data/sol_prob2_bronze_feb25.html)

### 10.1 题意与 mex 的定义

给定 N 个整数，0≤a[i]≤N，N≤2×10^5。一次可以将任意一个元素改成任意非负整数。

mex 是数组中没有出现的最小非负整数。例如 [0,0,2] 的 mex 为 1，[1,2] 的 mex 为 0。

对每个目标值 i=0,1,…,N，分别求让 mex 等于 i 的最少修改次数。各个目标独立考虑，不是累计修改数组。

### 10.2 写出两个必要条件

mex=i，当且仅当：

1. 0 到 i−1 每个数都至少出现一次。
2. i 一次都不能出现。

令 frequency[i] 为 i 的出现次数，missing 为 [0,i) 中没出现的数的个数。

至少要改掉 frequency[i] 个元素；也至少要修改 missing 次，才能补齐缺失数。

关键：两种任务可以在同一次操作中完成。把一个 i 改成某个缺失数，就同时减少一个需要删除的 i 和一个缺失数。

所以答案不是二者之和，而是：

$$
answer[i]=\max(frequency[i],missing).
$$

### 10.3 为什么总能达到这个下界

优先把现有 i 改成缺失的小数，尽可能同时满足两个任务。

若 i 还有剩余，全部改成大于 i 的数。若缺失数还有剩余，就用“大于 i 的元素”或“小于 i 但重复出现的多余副本”来补，保留每个已出现小数的一份即可。

这样的可用元素一定足够：目标 i≤N，而最终只需为 0 到 i−1 各保留一个位置。

### 10.4 从小到大维护缺失数

枚举目标 i 时，missing 只统计严格小于 i 的数。因此应先输出答案，再判断 frequency[i] 是否为 0，并决定是否将 missing 加一。

### 10.5 手推示例

```text
a = [2,2,2,0]
```

| 目标 mex | 需要补的小数 | missing | 目标值出现次数 | 最少操作 |
| --- | --- | --- | --- | --- |
| 0 | 无 | 0 | 1 | 1 |
| 1 | 无 | 0 | 0 | 0 |
| 2 | 1 | 1 | 3 | 3 |
| 3 | 1 | 1 | 0 | 1 |
| 4 | 1、3 | 2 | 0 | 2 |

目标 2 时，三个 2 都必须改掉，其中一个可以改成 1。补缺失值不需要再额外加一次。

### 10.6 完整 C++17 代码


```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> frequency(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        ++frequency[x];
    }
    int missing = 0; // [0, target) 中未出现的数的个数。
    for (int target = 0; target <= n; ++target) {
        cout << max(frequency[target], missing) << '\n';
        if (frequency[target] == 0) ++missing;
    }
}
```

### 10.7 复杂度、部分解与易错点

时间 O(N)，空间 O(N)。N≤1000 时，每个目标重新检查一遍小数是否出现也能得到 O(N²) 的部分解；全解把缺失数累计起来。

易错点：输出范围包含 N，因此有 N+1 行；frequency[i] 统计出现次数，missing 统计缺失数值的种类数；不能修改频次数组后继续计算下一个目标；missing 的更新顺序不能提前。

课堂提问：什么时候“完成任务 A 的操作数”和“完成任务 B 的操作数”应该取最大值，什么时候必须相加？这里为什么能够重合？

---

## 11. 铜组第三题：Printing Sequences

[题目](https://usaco.org/index.php?page=viewproblem2&cpid=1493) · [官方解析](https://usaco.org/current/data/sol_prob3_bronze_feb25.html)

### 11.1 题意与最容易误读的地方

程序可以使用 PRINT c 输出一个数，使用 REP o ... END 把里面的程序重复 o 次。可以嵌套循环。

给定长度 N≤100 的序列，判断能否用不超过 K≤3 条 PRINT 语句写出输出该序列的程序。测试组数≤100，序列元素属于 [1,K]。

限制的是源代码里的 PRINT 语句数，不是程序执行时输出的数的个数。REP 的数量没有限制。例如：

```text
REP 100
    PRINT 1
END
```

使用一条 PRINT 语句，却输出 100 个 1。

### 11.2 一条 PRINT 可以表示什么

只能输出一段相同数字，比如 [2,2,2,2]。不论嵌套多少层循环，只有一条 PRINT 就只能输出同一个数。

定义 onePrint(l,r)：区间内全部相同。代码使用左闭右开 [l,r)，并允许空区间消耗零条 PRINT。

### 11.3 两条 PRINT 的结构

至多两条 PRINT 的程序可以规范成：

```text
REP outer
    REP countX
        PRINT x
    END
    REP countY
        PRINT y
    END
END
```

如果全部相同，一条就够。否则先把相邻同值元素压成“数值、长度”的块：

```text
[1,1,2,2,2,1,1,2,2,2]
→ [(1,2),(2,3),(1,2),(2,3)]
```

需要满足：块数为偶数，而且第 i 块与第 i+2 块的数值和长度完全一致。块数不超过 2 的情形也自然可行。

注意不能只比较压缩后的数值；连续长度不同，两个重复单元也不同。

### 11.4 三条 PRINT：外层重复与内部拼接

把包住整个程序的共同外层 REP 提出来，剩余程序若不是单条 PRINT，就能在两条顶层语句之间分开。

总共至多三条 PRINT，左右两部分的 PRINT 数量必然可以分成：

- 至多 1 条 + 至多 2 条。
- 至多 2 条 + 至多 1 条。

因此枚举一个重复单元长度 period，要求 period 整除 N，且整个序列由这个前缀重复构成。再枚举重复单元内部的切分点 cut，检查两边是否符合上面的结构。

period=N 也必须枚举，表示整个程序没有共同外层重复。允许 cut=0 或 cut=period，则一条或两条 PRINT 就能完成的情况也被包含。

### 11.5 手推示例

```text
序列：[3,3,1,2,2,1,2,2]
K = 3
```

直接取 period=N，切分为：

```text
[3,3] + [1,2,2,1,2,2]
```

左边一条 PRINT 就够，右边由 [1,2,2] 重复两次，需要两条 PRINT：

```text
REP 2
    PRINT 3
END
REP 2
    PRINT 1
    REP 2
        PRINT 2
    END
END
```

一共三条 PRINT，答案 YES。

再看 [1,1,2,1]、K=2：压缩后是 [(1,2),(2,1),(1,1)]，有三个不同相邻块，不能由两个块的完整重复形成，答案 NO。

### 11.6 完整 C++17 代码


```cpp
#include <bits/stdc++.h>
using namespace std;

// 区间采用左闭右开 [l,r)，允许空区间。
bool onePrint(const vector<int> &a, int l, int r) {
    for (int i = l + 1; i < r; ++i)
        if (a[i] != a[l]) return false;
    return true;
}

bool twoPrints(const vector<int> &a, int l, int r) {
    vector<pair<int, int>> blocks; // (数值，连续长度)
    for (int i = l; i < r; ++i) {
        if (!blocks.empty() && blocks.back().first == a[i])
            ++blocks.back().second;
        else blocks.push_back({a[i], 1});
    }
    if (blocks.size() <= 2) return true;
    if (blocks.size() % 2 == 1) return false;
    for (int i = 2; i < (int)blocks.size(); ++i)
        if (blocks[i] != blocks[i - 2]) return false;
    return true;
}

bool possible(const vector<int> &a, int k) {
    int n = (int)a.size();
    if (k == 1) return onePrint(a, 0, n);
    if (k == 2) return twoPrints(a, 0, n);
    for (int period = 1; period <= n; ++period) {
        if (n % period != 0) continue;
        bool repeats = true;
        for (int i = period; i < n; ++i) {
            if (a[i] != a[i % period]) { repeats = false; break; }
        }
        if (!repeats) continue;
        for (int cut = 0; cut <= period; ++cut) {
            if (onePrint(a, 0, cut) && twoPrints(a, cut, period)) return true;
            if (twoPrints(a, 0, cut) && onePrint(a, cut, period)) return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tests; cin >> tests;
    while (tests--) {
        int n, k; cin >> n >> k;
        vector<int> a(n);
        for (int &x : a) cin >> x;
        cout << (possible(a, k) ? "YES" : "NO") << '\n';
    }
}
```

### 11.7 复杂度与另一种思路：区间 DP

对某个候选 period=p，检查所有切分点需要 O(p²)。只枚举 N 的因数，因此：

$$
\sum_{p\mid N}p^2
=N^2\sum_{d\mid N}\frac1{d^2}
\le N^2\sum_{d=1}^{\infty}\frac1{d^2}
=O(N^2).
$$

检查周期的总开销也不超过 O(N²)。因此本实现每组时间 O(N²)，辅助空间 O(N)；K=1 或 2 时只需 O(N)。

本题也可以用区间 DP，定义 dp[l][r] 为输出区间所需的最少 PRINT 数：

1. 拼接：枚举分割点 k，转移 dp[l][k]+dp[k+1][r]。
2. 重复：若 [l,r] 是其长度 p 的前缀重复若干次，可以使用 dp[l][l+p−1]。

单个元素初值为 1，按长度从短到长计算。预处理相同位置起始的最长公共前缀后，能在 O(1) 判断一个候选周期，总体可写成 O(N³) 时间、O(N²) 空间的区间 DP。

这与涂色区间 DP 不完全相同：这里重复的是一段程序的完整输出，不能仅凭两个端点相等就合并。

---

