## USACO 铜组补充：数学推理、计数预处理、模拟优化与位掩码

## 一、基础数学与推理

### 1. 整数除法与上下取整

对于 `a >= 0、b > 0`：

```cpp
long long floorValue = a / b;
long long ceilValue = a / b + (a % b != 0);
```

例如 17 件物品，每箱装 5 件，需要 `17/5+1=4` 箱。

- C++ 有符号整数除法向 0 截断，不能把上面的非负数公式直接用于负数。
- `1LL * x * y` 可避免两个 int 相乘时先溢出。

### 2. 奇偶性与取余

反复翻转一个二元状态时，只需记录翻转次数的奇偶性：

```cpp
bool flipped = false;
flipped = !flipped;
```

偶数次翻转恢复原状，奇数次翻转得到相反状态。

循环下标中，正整数 `n` 下可用：

```cpp
int next = (i + 1) % n;
int previous = (i - 1 + n) % n;
```

### 3. 不变量：交换不会改变元素的出现次数

**问题：**允许任意交换数组中的两个元素，判断 A 能否变成 B。

例如：

```
A = {1, 2, 2}
B = {2, 1, 2}  → 可以

A = {1, 2, 2}
B = {1, 1, 3}  → 不可以
```

虽然第二组数组总和相同，但元素出现次数不同。

**不变量：无论交换多少次，每个数的出现次数都不会改变。**

```
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

bool canTransform(vector<int> a, vector<int> b) {
    if (a.size() != b.size()) return false;

    // 排序后比较，相当于检查每个数的出现次数是否相同
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    return a == b;
}

int main() {
    cout << canTransform({1, 2, 2}, {2, 1, 2}) << '\n'; // 1
    cout << canTransform({1, 2, 2}, {1, 1, 3}) << '\n'; // 0
}
```

**正确性：**次数不同，交换无法改变它；次数相同，就能通过交换把各元素放到目标位置。

### 4. 分类讨论与证明：恰好移动 K 步

**问题：\**在数轴上从位置 `a` 出发，每步向左或向右移动 1，判断能否\**恰好走 K 步**到达 `b`。

令：

\[ d=|a-b| \]

分三种情况：

| 情况                      | 能否到达 | 原因                   |
| ------------------------- | -------- | ---------------------- |
| `K < d`                   | 不可以   | 步数不足               |
| `K >= d`，且 `K-d` 为奇数 | 不可以   | 多出的步数无法全部抵消 |
| `K >= d`，且 `K-d` 为偶数 | 可以     | 多出的步数可以组成往返 |

```
#include <cstdlib>
#include <iostream>
using namespace std;

bool canReach(long long a, long long b, long long k) {
    long long distance = abs(a - b);

    if (k < distance) return false;             // 情况一
    if ((k - distance) % 2 == 1) return false;  // 情况二
    return true;                               // 情况三
}

int main() {
    cout << canReach(2, 5, 2) << '\n'; // 0：至少需要 3 步
    cout << canReach(2, 5, 4) << '\n'; // 0：多出 1 步
    cout << canReach(2, 5, 5) << '\n'; // 1：多出 2 步
}
```

**必要性证明：**假设向目标方向走 `p` 步，反方向走 `q` 步，则：
$$
p+q=K,\qquad p-q=d
$$
因此：
$$
K-d=2q
$$
它必须为非负偶数。

**充分性证明：**先走 `d` 步到目标，再做 `(K-d)/2` 次往返，就能恰好用完所有步数。

### 5. 逆向思考与构造：通过前缀翻转得到目标串

**问题：**初始有一个全为 `0` 的字符串。每次可以选择一个前缀，将其中的 `0、1` 全部翻转。构造操作，使字符串变成目标串。

例如：

```
初始：000
目标：101

翻转前 3 个：111
翻转前 2 个：001
翻转前 1 个：101
```

**从右向左确定字符：**处理位置 `i` 时，如果当前值不对，就翻转前 `i+1` 个字符。之后只操作更短的前缀，已经确定的右侧不会再改变。

```
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    string target;
    cin >> target;

    vector<int> operations;
    bool flipped = false; // 尚未处理的位置累计被翻转的奇偶性

    for (int i = (int)target.size() - 1; i >= 0; i--) {
        int current = flipped ? 1 : 0;
        int wanted = target[i] - '0';

        if (current != wanted) {
            operations.push_back(i + 1); // 翻转此前缀
            flipped = !flipped;
        }
    }

    cout << operations.size() << '\n';
    for (int length : operations) {
        cout << length << ' ';
    }
    cout << '\n';
}
```

输入：

```
101
```

输出：

```
3
3 2 1
```

**正确性：**每次让当前最右侧未确定的字符正确，后续操作不会影响它，最终所有位置都正确。

## 二、计数与前后缀预处理

### 1. 频率与不同值数量

```cpp
vector<int> cnt(n + 1, 0); // 假设 1 <= a[i] <= n
int distinct = 0;
for (int x : a) {
    if (cnt[x] == 0) distinct++;
    cnt[x]++;
}
```

必须区分“出现了多少次”和“有多少种值”。数值范围很大时可改用 map 或离散化。

### 2. 计数对象与去重

**先明确：统计的是下标组合，还是不同的数值组合。**

例如数组：

```
a = {1, 1, 2}
```

选择两个不同下标：

| 下标组合 | 对应数值 |
| -------- | -------- |
| `(0,1)`  | `(1,1)`  |
| `(0,2)`  | `(1,2)`  |
| `(1,2)`  | `(1,2)`  |

因此：

- 不同的**下标组合**有 `3` 个。
- 不同的**无序数值组合**有 `2` 个。

```
#include <algorithm>
#include <iostream>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int main() {
    vector<int> a = {1, 1, 2};

    int indexPairs = 0;
    set<pair<int, int>> valuePairs;

    for (int i = 0; i < (int)a.size(); i++) {
        for (int j = i + 1; j < (int)a.size(); j++) {
            indexPairs++;

            // 统一为“小的在前”，让 (1,2) 和 (2,1) 视为同一组合
            int x = min(a[i], a[j]);
            int y = max(a[i], a[j]);

            valuePairs.insert({x, y});
        }
    }

    cout << indexPairs << '\n';        // 3：下标组合数量
    cout << valuePairs.size() << '\n'; // 2：不同数值组合数量
}
```

这里有两种不同的“去重”：

- `j = i + 1`：避免重复枚举 `(i,j)` 和 `(j,i)`，同时保证不使用同一个位置。
- `set`：合并不同下标产生的相同数值组合。

**注意：**只有题目不区分数值顺序时，才能用 `min/max` 统一顺序。若统计有序数值对，`(1,2)` 与 `(2,1)` 应分别保留。

时间复杂度上界为 \(O(N^2\log N)\)，集合空间上界为 \(O(N^2)\)。

### 3. 前缀不只可以求和

统一约定：`pre[i]` 描述下标 `[0,i)`，即前 i 个元素。

| 维护的信息 | 作用 |
|---|---|
| 前缀和 | 快速求区间和 |
| 前缀频次 | 查询某种值出现多少次 |
| 前缀最大值 | 判断左侧是否存在更大的元素 |
| 前缀不同值数 | 查询前 i 个位置中有多少种值 |
| 前缀缺失数 | 统计一定数值范围中缺了多少种值 |

例如，前缀不同值数：

```cpp
vector<int> pre(n + 1, 0), cnt(n + 1, 0);
for (int i = 0; i < n; i++) {
    pre[i + 1] = pre[i] + (cnt[a[i]] == 0);
    cnt[a[i]]++;
}
```

数组 `2 1 2 3` 对应 `pre = {0,1,2,2,3}`。

**不能把所有前缀统计都相减。**前缀不同值数之差，不等于区间不同值数；例如 `1 2 1` 的区间 `[1,2]` 有两种值，但 `pre[3]-pre[1]=1`。

### 4. 后缀与最近位置

后缀从右向左处理。例如记录每个位置右侧（含自己）最近的字符 c：

```cpp
vector<int> nextPos(n + 1, n); // n 表示不存在
for (int i = n - 1; i >= 0; i--) {
    nextPos[i] = (s[i] == c ? i : nextPos[i + 1]);
}
```

使用 `nextPos[i]` 前判断是否等于 `n`，不能访问 `s[n]`。

### 5. 重新编号

**当题目要求变成指定顺序时，可以按目标位置重新编号，将目标转化为递增序列。**

例如：

```
原序列 A：50 10 30 20
目标序列 B：20 50 10 30
```

按照 B 中的位置建立排名：

| 原数值 | 新编号 |
| ------ | ------ |
| 20     | 1      |
| 50     | 2      |
| 10     | 3      |
| 30     | 4      |

替换后：

```
A → 2 3 4 1
B → 1 2 3 4
```

现在，“把 A 变成 B”就转化为“把新编号序列变成递增序列”。

```
#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main() {
    vector<int> a = {50, 10, 30, 20};
    vector<int> b = {20, 50, 10, 30};

    map<int, int> rank;

    // 目标序列中的位置，就是新编号
    for (int i = 0; i < (int)b.size(); i++) {
        rank[b[i]] = i + 1;
    }

    vector<int> transformed;
    for (int x : a) {
        transformed.push_back(rank.at(x));
    }

    for (int x : transformed) {
        cout << x << ' ';
    }
    cout << '\n'; // 2 3 4 1
}
```

**为什么可行？**这里只改变元素的名字，元素在数组中的位置没有改变。交换、移动和相对顺序等关系都得到了保留。

使用 `map` 的时间复杂度为 \(O(N\log N)\)，空间为 \(O(N)\)。

## 三、模拟优化与贡献分析

### 1. 按事件处理，不逐单位时间处理

若时间跨度为 `10^14`，事件只有 `10^5` 个，就应考虑在事件之间一次性更新。

库存为 `stock`，相隔 `gap` 天，每天最多消耗 1 件：

```cpp
long long used = min(stock, gap);
stock -= used;
answer += used;
```

**重点：**明确一段时间包含哪些天，以及事件发生在当天消耗之前还是之后。

### 2. 只更新改变的部分

如果：

$$
answer=\sum contribution_i
$$
一次操作只影响少量项，就使用：

$$
新答案=旧答案-旧贡献+新贡献
$$

| 修改 | 可能受影响的项 |
|---|---|
| 改一个字符 | 包含它的固定长度子串 |
| 改一个格子 | 所属行、列或特定对称组 |
| 交换两个数 | 与这两个位置相关的匹配关系 |

原先每次重算 `O(n)`，若实际只改变常数项，就可能降为每次 `O(1)`。

### 3. 枚举时复用上一个候选的信息

枚举区间 `[l,r]` 后扩大成 `[l,r+1]`，优先考虑新增元素带来的变化，而不是重新扫描整个区间。

**判断依据是影响范围，不是代码里出现了几个 for。**

## 四、基础位运算与位掩码

### 1. 用二进制表示选择

第 i 位为 1 表示选择第 i 个对象，为 0 表示不选。位编号从 0 开始。

| 操作 | 写法 |
|---|---|
| 读取第 i 位 | `(mask >> i) & 1` |
| 设置第 i 位为 1 | `mask | (1 << i)` |
| 清除第 i 位 | `mask & ~(1 << i)` |
| 翻转第 i 位 | `mask ^ (1 << i)` |

这里按 `n <= 20` 的非负 int 掩码使用。更大位数要选择合适的无符号类型，并检查移位范围；不能认为换成 `1LL` 就可以无限移位。

### 2. 枚举所有子集

```cpp
for (int mask = 0; mask < (1 << n); mask++) {
    for (int i = 0; i < n; i++) {
        if ((mask >> i) & 1) {
            // 第 i 个对象被选择
        }
    }
}
```

共 `2^n` 个状态，逐状态检查 n 位需要 `O(n2^n)`。

**位掩码只是状态表示，不等于状压 DP。**本章只要求掌握二元选择和子集枚举。

### 3. 重复信息先合并

如果相同约束出现多次，先统计次数，检查某状态时一次性加上频率。这样可以把“按输入长度检查”转为“按不同类型检查”。

## 第二部分：真题应用

## 真题 1：Palindrome Game——个位规律与证明

**2024 February Bronze，Problem 1**  
[官方题目](https://usaco.org/index.php?page=viewproblem2&cpid=1395) · [官方题解](https://usaco.org/current/data/sol_prob1_bronze_feb24.html)

**题意：**两人轮流取走正回文数颗石子，不能行动者输，判断先手是否必胜。石子数可能非常大。

**对应知识：**取余、分类、规律证明。

- 正回文数的末位不为 0，因此不是 10 的倍数。
- 非 10 的倍数，可取走末位对应的 1 至 9 颗，变成 10 的倍数。
- 从 10 的倍数出发，每次都会变成非 10 的倍数。
- 以 0 为必败起点，可归纳出：10 的倍数必败，其他必胜。

只看最后一位，不需要把整个数转成整数。

```cpp
#include <iostream>
#include <string>
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

复杂度：每个数读取 `O(L)`，读取后判断 `O(1)`。L 为位数。

## 真题 2：It's Mooin' Time IV——逆向构造与翻转奇偶性

**2026 Second Contest Bronze，Problem 1**  
[官方题目](https://usaco.org/index.php?page=viewproblem2&cpid=1563) · [官方题解](https://usaco.org/current/data/sol_prob1_bronze_season26contest2.html)

**题意：**键盘有 M、O。按 O 时，先翻转已输入的全部字符，再追加 O。判断能否打出目标串；`k=1` 时输出按键方案。

**对应知识：**逆向、奇偶、构造。

从右向左，维护右边已确定的按键会翻转当前字符多少次的奇偶性。

1. 奇数次时，当前按键应与目标字符相反。
2. 偶数次时，当前按键应与目标字符相同。
3. 当前按键为 O，会额外翻转所有左侧字符。

每一位都有唯一选择，因此总能构造。

```cpp
#include <iostream>
#include <string>
using namespace std;
int main() {
    int t, k;
    cin >> t >> k;
    while (t--) {
        int n;
        string s;
        cin >> n >> s;
        cout << "YES\n";
        if (k == 0) continue;
        string answer(n, 'M');
        bool flipped = false;
        for (int i = n - 1; i >= 0; i--) {
            char key = s[i];
            if (flipped) key = (key == 'M' ? 'O' : 'M');
            answer[i] = key;
            if (key == 'O') flipped = !flipped;
        }
        cout << answer << '\n';
    }
}
```

复杂度：每组 `O(N)` 时间、`O(N)` 空间。

## 真题 3：Photoshoot 2——重新编号与前缀最大值

**2022 February Bronze，Problem 2**  
[官方题目](https://usaco.org/index.php?page=viewproblem2&cpid=1204) · [官方题解](https://usaco.org/current/data/sol_prob2_bronze_feb22.html)

**题意：**每次把一头牛向左移动任意距离，求把排列 A 变成指定排列 B 的最少次数。

**对应知识：**目标排名、前缀最值、贪心。

按 B 的位置重新编号。若一个数左侧有更大的数，它必须被向左移动至少一次，否则这对数的相对顺序无法纠正。

从左向右扫描，遇到 `x < maxSeen` 就计一次；将 x 移到已处理前缀中的正确位置，一次即可。其他位置不必移动。

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<int> a(n), rank(n + 1);
    for (int& x : a) cin >> x;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        rank[x] = i;
    }
    int maxSeen = 0, answer = 0;
    for (int x : a) {
        int r = rank[x];
        if (r < maxSeen) answer++;
        maxSeen = max(maxSeen, r);
    }
    cout << answer << '\n';
}
```

复杂度：`O(N)` 时间、`O(N)` 空间。注意统计的是需要移动的元素数量，不是逆序对数量。

## 真题 4：It's Mooin' Time II——前缀不同值数与去重

**2025 January Bronze，Problem 2**  
[官方题目](https://usaco.org/index.php?page=viewproblem2&cpid=1468) · [官方题解](https://usaco.org/current/data/sol_prob2_bronze_jan25.html)

**题意：**统计不同的 `[x,y,y]` 子序列，其中 `x != y`。允许不连续，按数值组合去重。

**对应知识：**前缀不同值数、反向频次、固定一种值避免重复。

对每个 y，只使用它最右边的两次出现，记较左的位置为 i。这样 i 左边可供 x 选择的范围最大。

贡献为 `pre[i]`，但若 y 自己也在 i 左边出现，要减 1。

```cpp
#include <iostream>
#include <vector>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<int> a(n), pre(n + 1), cnt(n + 1), first(n + 1, n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        int x = a[i];
        pre[i + 1] = pre[i] + (cnt[x] == 0);
        if (cnt[x] == 0) first[x] = i;
        cnt[x]++;
    }
    vector<int> rightCount(n + 1, 0);
    long long answer = 0;
    for (int i = n - 1; i >= 0; i--) {
        int y = a[i];
        if (++rightCount[y] == 2) {
            answer += pre[i] - (first[y] < i);
        }
    }
    cout << answer << '\n';
}
```

复杂度：`O(N)` 时间、`O(N)` 空间。每种 y 只贡献一次，同一种 x 由前缀去重统计，避免按下标重复计数。

## 真题 5：Hungry Cow——按事件跳跃

**2023 February Bronze，Problem 1**  
[官方题目](https://usaco.org/index.php?page=viewproblem2&cpid=1299) · [官方题解](https://usaco.org/current/data/sol_prob1_bronze_feb23.html)

**题意：**每天晚上有草就吃一捆，若干天早晨送草，求前 T 天吃掉多少。T 可达 `10^14`，送货日期递增且不超过 T。

**对应知识：**事件模拟、区间端点。

维护 `stock` 和上一个事件日 `last`。处理新送货日 d 时，先一次性结算 `[last,d)` 的消耗，再加入当天早晨的草。最后结算到 T，当天晚餐也应计入。

```cpp
#include <algorithm>
#include <iostream>
using namespace std;
int main() {
    int n;
    long long t;
    cin >> n >> t;
    long long stock = 0, last = 1, answer = 0;
    for (int i = 0; i < n; i++) {
        long long d, b;
        cin >> d >> b;
        long long used = min(stock, d - last);
        answer += used;
        stock = stock - used + b;
        last = d;
    }
    answer += min(stock, t - last + 1);
    cout << answer << '\n';
}
```

复杂度：`O(N)` 时间、`O(1)` 额外空间。最容易错的是最后一段漏加 1。

## 真题 6：Reflection——局部贡献更新

**2025 February Bronze，Problem 1**  
[官方题目](https://usaco.org/index.php?page=viewproblem2&cpid=1491) · [官方题解](https://usaco.org/current/data/sol_prob1_bronze_feb25.html)

**题意：**偶数边长的网格应满足水平、竖直对称。初始及每次翻转一个格子后，求恢复对称的最少修改数。

**对应知识：**对称分组、独立贡献、局部更新。

每个格子属于一个四格对称组。若其中有 c 个 `#`，统一成 `.` 需 c 次，统一成 `#` 需 `4-c` 次，所以贡献为 `min(c,4-c)`。

不同组互不影响。一格变化时，只重算所属组。

```cpp
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    int n, q;
    cin >> n >> q;
    vector<string> g(n);
    for (string& row : g) cin >> row;
    auto cost = [&](int r, int c) {
        r = min(r, n - 1 - r);
        c = min(c, n - 1 - c);
        int count = (g[r][c] == '#')
                  + (g[r][n - 1 - c] == '#')
                  + (g[n - 1 - r][c] == '#')
                  + (g[n - 1 - r][n - 1 - c] == '#');
        return min(count, 4 - count);
    };
    int answer = 0;
    for (int r = 0; r < n / 2; r++) {
        for (int c = 0; c < n / 2; c++) answer += cost(r, c);
    }
    cout << answer << '\n';
    while (q--) {
        int r, c;
        cin >> r >> c;
        --r; --c;
        answer -= cost(r, c);
        g[r][c] = (g[r][c] == '#' ? '.' : '#');
        answer += cost(r, c);
        cout << answer << '\n';
    }
}
```

复杂度：总时间 `O(N²+Q)`，空间 `O(N²)`。必须先输出初始答案，共输出 `Q+1` 行。

## 真题 7：Moo Hunt——位掩码枚举与重复约束压缩（提高）

**2026 Second Contest Bronze，Problem 2**  
[官方题目](https://usaco.org/index.php?page=viewproblem2&cpid=1564) · [官方题解](https://usaco.org/current/data/sol_prob2_bronze_season26contest2.html)

**题意：**N 个位置各填 M 或 O。每条操作给定不同位置 x、y、z，恰好对应 MOO 时得 1 分。求最高分及达到最高分的棋盘数量。

**对应知识：**二元状态枚举、频率合并。N 不超过 20，但 K 可达 200000。

- 枚举 `2^N` 个棋盘，逐个检查 K 条操作，通常太慢。
- y、z 都要求 O，可以交换，统一为 `y<z` 并计数。
- 每个棋盘只遍历 M 位置 x 和 O 位置对 y、z，累加频次。
- 保留最高分及其方案数。不同 mask 就是不同棋盘。

```cpp
#include <algorithm>
#include <iostream>
using namespace std;
int freq[20][20][20];
int main() {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < k; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        --x; --y; --z;
        if (y > z) swap(y, z);
        freq[x][y][z]++;
    }
    int best = -1, ways = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        int mPos[20], oPos[20], mc = 0, oc = 0;
        for (int i = 0; i < n; i++) {
            if ((mask >> i) & 1) mPos[mc++] = i;
            else oPos[oc++] = i;
        }
        int score = 0;
        for (int i = 0; i < mc; i++) {
            for (int j = 0; j < oc; j++) {
                for (int h = j + 1; h < oc; h++) {
                    score += freq[mPos[i]][oPos[j]][oPos[h]];
                }
            }
        }
        if (score > best) {
            best = score;
            ways = 1;
        } else if (score == best) {
            ways++;
        }
    }
    cout << best << ' ' << ways << '\n';
}
```

时间上界 `O(K+N³2^N)`，空间 `O(N³)`（代码按 N 的上限固定分配）。这个枚举仍是指数级，只因 N 小、检查范围已压缩，才适用；实际运行也要关注常数。
