## USACO Bronze 02：二分查找与双指针

## 一、二分查找：每次排除一半候选

### 1. 使用前提

二分查找通常用于有序数组。以升序数组为例，比较中间元素与目标后，可以确定目标不会出现在哪一半。

例如在 `a = {1, 3, 4, 6, 8, 10}` 中查找 `8`：

| 步骤 | 左下标 `l` | 右下标 `r` | 中点 `mid` | `a[mid]` | 下一步 |
|---|---:|---:|---:|---:|---|
| 1 | 0 | 5 | 2 | 4 | 目标更大，令 `l = 3` |
| 2 | 3 | 5 | 4 | 8 | 找到，返回下标 4 |

每次排除约一半候选，查找复杂度为 O(log N)。若输入无序，先排序需要 O(N\log N)，不能把这部分成本忽略。

### 2. 查找某个目标值

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// 要求 a 已升序排序；找到返回下标，否则返回 -1。
int findIndex(const vector<int>& a, int target) {
    int l = 0;
    int r = (int)a.size() - 1;

    while (l <= r) {
        int mid = l + (r - l) / 2;

        if (a[mid] == target) return mid;
        if (a[mid] < target) l = mid + 1;
        else r = mid - 1;
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, target;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    cin >> target;

    sort(a.begin(), a.end());
    cout << findIndex(a, target) << '\n';
}
```

注意：

- 这里维护闭区间 `[l, r]`，因此循环条件是 `l <= r`。
- 中点已被排除时，更新到 `mid + 1` 或 `mid - 1`，避免死循环。
- 有多个相同值时，这个模板返回其中一个位置，不保证是第一次出现的位置。
- 排序后返回的是排序后的下标。如果需要原始编号，应在排序前保存编号。
- `l + (r - l) / 2` 可以避免直接计算 `l + r` 带来的溢出风险。

## 二、查找边界：lower_bound 与 upper_bound

以下用法要求数组已升序排序。

| 函数 | 返回的位置 | 找不到时 |
|---|---|---|
| `lower_bound(begin, end, x)` | 第一个大于等于 `x` 的元素 | 返回 `end` |
| `upper_bound(begin, end, x)` | 第一个严格大于 `x` 的元素 | 返回 `end` |

例如：

```cpp
vector<int> a = {1, 3, 3, 3, 6, 8};

int first = lower_bound(a.begin(), a.end(), 3) - a.begin();
int after = upper_bound(a.begin(), a.end(), 3) - a.begin();

// first = 1，after = 4
// 数值 3 出现了 after - first = 3 次。
```

返回值是迭代器，减去 `a.begin()` 才得到下标。若返回 `a.end()`，换算得到下标 `a.size()`，不能访问 `a[a.size()]`。

### 真题应用：Counting Haybales（银组拓展）

**USACO 2016 December Silver，Problem 1**  
[官方题面](https://usaco.org/index.php?page=viewproblem2&cpid=666)

给定草垛的位置，多次询问闭区间 `[L, R]` 内有多少个草垛。

排序后：

- `lower_bound(L)` 找到第一个不小于 `L` 的位置。
- `upper_bound(R)` 找到第一个大于 `R` 的位置。
- 两个位置之差就是区间内的数量。

核心代码：

```cpp
auto left = lower_bound(a.begin(), a.end(), L);
auto right = upper_bound(a.begin(), a.end(), R);
cout << right - left << '\n';
```

预处理排序 $O(N\log N)$，每次查询 $O(\log N)$。这个边界写法也适用于包含重复元素的有序数组。

## 三、二分答案：先证明条件具有单调性

普通二分查找比较数组值；二分答案判断某个候选答案是否可行。

例如我们要求“最小可行值”，并且判断结果随候选值增大只能从不成立变成成立：

| 候选值 | 1 | 2 | 3 | 4 | 5 | 6 |
|---|---|---|---|---|---|---|
| `check` | false | false | false | true | true | true |

这时可以二分寻找第一个 `true`。

### 1. 最小可行值模板

```cpp
// 前提：答案在闭区间 [L, R] 内，并且 check(R) 为 true。
// check(x) 的结果从 false 单调变为 true。
int l = L, r = R;

while (l < r) {
    int mid = l + (r - l) / 2;

    if (check(mid)) r = mid;  // mid 可行，保留它并尝试更小的值
    else l = mid + 1;        // mid 不可行，排除 mid 及更小的值
}

// l == r，即最小可行值。
cout << l << '\n';
```

这个模板维护的是闭区间 `[l, r]`。使用前要确认至少存在一个可行值；不能在没有可行答案时直接把最终的 `l` 当成答案。

判断是否能二分时，先回答三个问题：

1. `check(x)` 判断的是什么？
2. 为什么 `x` 可行之后，更大的值一定可行？
3. 初始范围为什么包含答案？

若一次判断需要 T 时间，候选值数量为 V，二分部分复杂度为 O(Tlog V)。

### 2. 铜组真题：Where Am I?

**USACO 2019 December Bronze，Problem 2**  
[官方题面](https://usaco.org/index.php?page=viewproblem2&cpid=964)

**题意概括：** 给定一个字符串，求最小的长度 `k`，使所有长度为 `k` 的连续子串互不相同。

例如字符串 `ABCDABC`：长度 3 时，`ABC` 出现两次；长度 4 时，没有重复子串，因此答案为 4。

**为什么可以二分？**

如果长度 `k` 的子串都不相同，那么长度 `k+1` 的子串也不可能相同：否则两个相同长子串的前 `k` 个字符也会相同，与前提矛盾。

因此可行性具有单调性。`k = n` 时只有一个子串，一定可行。

```cpp
#include <iostream>
#include <set>
#include <string>
using namespace std;

bool check(int k, const string& s) {
    set<string> seen;
    int n = (int)s.size();

    for (int i = 0; i + k <= n; i++) {
        string sub = s.substr(i, k);
        if (!seen.insert(sub).second) return false;
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string s;
    cin >> n >> s;

    int l = 1, r = n;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (check(mid, s)) r = mid;
        else l = mid + 1;
    }

    cout << l << '\n';
}
```

`seen.insert(sub).second` 表示是否成功加入一个新字符串；若为 `false`，说明此前已经出现过。

本题 N<=100，从小到大枚举 `k` 也能通过，不必为了使用二分而强行优化。这里用它练习“可行性判断 + 单调性证明”。上述实现包含子串构造和字符串比较，最坏上界可估为 $O(N^2\log^2N)$，不能把一次 `check` 简单看成 $O(N)$。

## 四、双指针：利用不回退的移动减少重复工作

双指针通常用两个整数下标控制扫描位置，不要求使用 C++ 的指针类型。

常见形式：

| 形式 | 指针如何移动 | 适用场景 |
|---|---|---|
| 同向双指针 / 滑动窗口 | 左右端点都向右 | 最长合法区间、区间计数 |
| 相向双指针 | 从两端向中间 | 有序数组中的两数之和 |
| 多序列合并 | 分别扫描两个序列 | 合并有序数组 |

滑动窗口属于同向双指针；不必将它们理解成两种完全独立的算法。

## 五、同向双指针（滑动窗口）：维护合法窗口

### 1. 用例：最大值与最小值之差不超过 K

先将数组升序排序。对于窗口 `[left, right]`：

$$
\max-\min=a[right]-a[left]
$$

当右端点右移导致差值超过 `K` 时，继续右移左端点，直到窗口重新合法。

```cpp
// 前提：a 已升序排序，K >= 0。
int left = 0;
int best = 0;

for (int right = 0; right < n; right++) {
    while (1LL * a[right] - a[left] > K) {
        left++;
    }

    best = max(best, right - left + 1);
}
```

例如 `a = {1, 1, 3, 4, 6}`，`K = 3`：

| `right` | 当前值 | 调整后的 `left` | 合法窗口的值 | 窗口大小 |
|---:|---:|---:|---|---:|
| 0 | 1 | 0 | 1 | 1 |
| 1 | 1 | 0 | 1, 1 | 2 |
| 2 | 3 | 0 | 1, 1, 3 | 3 |
| 3 | 4 | 0 | 1, 1, 3, 4 | 4 |
| 4 | 6 | 2 | 3, 4, 6 | 3 |

最大窗口大小为 4。

### 2. 为什么 for + while 仍是 O(N)？

右指针总共移动 `N` 次。左指针不会回退，总共也最多移动 `N` 次。内层循环的执行次数要在整个算法中累计，不能机械地将两层循环相乘。

因此窗口扫描为 $O(N)$，加上排序后的总复杂度为 $O(N\log N)$。

### 3. 铜组真题：Diamond Collector

**USACO 2016 US Open Bronze，Problem 1**  
[官方题面](https://usaco.org/index.php?page=viewproblem2&cpid=639)

**题意概括：** 从不同大小的钻石中选择尽可能多的钻石，使最大与最小尺寸之差不超过 `K`。

排序后，最佳选择可以表示为一个连续窗口：只要两端的差值合法，中间的钻石也都可以加入。因此直接使用上一节的双指针。

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, K;
    cin >> n >> K;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    sort(a.begin(), a.end());

    int left = 0, answer = 0;
    for (int right = 0; right < n; right++) {
        while (1LL * a[right] - a[left] > K) left++;
        answer = max(answer, right - left + 1);
    }

    cout << answer << '\n';
}
```

本题 $N\le1000$，朴素枚举也可以通过。双指针的价值在于练习窗口维护，并为更大数据规模做准备。

### 4. 固定左端点，推进右端点的等价写法

```cpp
// 前提：a 已升序排序，K >= 0。
int right = 0;
int answer = 0;

for (int left = 0; left < n; left++) {
    while (right < n && 1LL * a[right] - a[left] <= K) {
        right++;
    }

    // right 是第一个不合法的位置，或 n。
    // 当前合法窗口为 [left, right)，长度为 right - left。
    answer = max(answer, right - left);
}
```

这份代码使用左闭右开窗口 `[left, right)`，与上一份闭区间窗口的长度公式不同。关键是始终保持同一套边界约定。

双指针不能直接套在任何问题上。例如用窗口统计“区间和不超过 K”时，若数组中有负数，扩大窗口可能降低总和，常见的单向收缩逻辑就不再保证正确。

- [洛谷P1638 逛画展](https://www.luogu.com.cn/problem/P1638)

## 六、相向双指针：两数之和

这是通用训练例题，不对应某一道特定的 USACO 真题。

在有序数组中，判断是否存在两个不同下标，使两数之和等于 `target`。

```cpp
bool pairSum(const vector<int>& a, long long target) {
    int left = 0;
    int right = (int)a.size() - 1;

    while (left < right) {
        long long sum = 1LL * a[left] + a[right];

        if (sum == target) return true;
        if (sum < target) left++;
        else right--;
    }

    return false;
}
```

使用前必须排序：

```cpp
sort(a.begin(), a.end());
cout << (pairSum(a, target) ? "yes" : "no") << '\n';
```

**为什么可以移动指针？**

- 当前和太小时，`a[left]` 与当前候选范围内任何更小的右端值相加，都不会达到目标，因此可以排除这个左端点。
- 当前和太大时，`a[right]` 与当前候选范围内任何更大的左端值相加，都仍然过大，因此可以排除这个右端点。
- `left < right` 保证使用两个不同的元素。相同数值可以使用，只要它们来自不同下标。

例如 `{1, 3, 4, 6, 8, 10}`，目标为 9：先比较 `1+10=11`，右指针左移；再比较 `1+8=9`，找到答案。

排序后扫描为 $O(N)$，总复杂度为 $O(N\log N)$。如果题目要求输出原始编号，排序时应同时保存原始下标。

## 七、多序列指针：合并两个有序数组

两个数组都按升序排列，每次选两个当前元素中较小的那个。某个数组处理完后，还要加入另一个数组的剩余元素。

```cpp
vector<int> mergeSorted(const vector<int>& A, const vector<int>& B) {
    int i = 0, j = 0;
    int n = (int)A.size(), m = (int)B.size();
    vector<int> result;
    result.reserve(n + m);

    while (i < n && j < m) {
        if (A[i] <= B[j]) result.push_back(A[i++]);
        else result.push_back(B[j++]);
    }

    while (i < n) result.push_back(A[i++]);
    while (j < m) result.push_back(B[j++]);

    return result;
}
```

例如 `A = {1, 4, 7}`、`B = {2, 3, 8}`，合并得到 `{1, 2, 3, 4, 7, 8}`。

复杂度为 $O(n+m)$，结果数组占用 $O(n+m)$ 空间。这里合并会保留重复值，不会自动去重。

## 八、综合拓展：二分答案 + 线性扫描

> 2021 Feb Silver-Problem 3. Just Green Enough

### Angry Cows（银组，可选）

**USACO 2016 January Silver，Problem 1**  
[官方题面](https://usaco.org/index.php?page=viewproblem2&cpid=594)

给定草垛位置和 `K` 头牛，求能覆盖所有草垛的最小整数爆炸半径 `R`。本节讨论银组版本，不是有连锁爆炸规则的同名铜组或金组题。

1. 将草垛位置排序。
2. 判断某个半径 `R`：从最左边尚未覆盖的位置 `x` 开始，一头牛最多覆盖到 `x + 2R`，用下标跳过这段中的所有草垛。
3. 重复覆盖，统计所需奶牛数；不超过 `K` 则可行。
4. 半径越大越容易覆盖，满足单调性，因此二分最小可行半径。

这个例子用来理解“二分减少候选答案，单向扫描减少一次判断的工作量”。铜组学生可先掌握前面的两个铜组例题，再学习本题。

## 九、习题

| 顺序 | 题目 | 练习重点 |
|---:|---|---|
| 1 | [洛谷 P2249：查找](https://www.luogu.com.cn/problem/P2249) | `lower_bound`、首次出现位置、1-based 输出 |
| 2 | [Where Am I?（铜组）](https://usaco.org/index.php?page=viewproblem2&cpid=964) | 写 `check`，证明可行性单调 |
| 3 | [Diamond Collector（铜组）](https://usaco.org/index.php?page=viewproblem2&cpid=639) | 排序、窗口长度、双指针 |
| 4 | [Counting Haybales（银组拓展）](https://usaco.org/index.php?page=viewproblem2&cpid=666) | 使用两次二分统计闭区间 |
| 5 | [Angry Cows（银组拓展）](https://usaco.org/index.php?page=viewproblem2&cpid=594) | 二分答案与线性判断结合 |
