## 排序与离散化：从数据顺序到坐标压缩

## 本章学习路线

| 工具 | 作用 | 常见复杂度 |
| --- | --- | --- |
| `sort` | 对一个区间排序 | O(N\log N) 次比较 |
| `unique` | 合并连续重复段，返回新的逻辑终点 | O(N) |
| `vector::erase` | 删除指定位置或区间 | 与移动和销毁的元素数量有关 |
| `lower_bound` | 找第一个不小于目标的位置 | 有序 `vector` 上 O(\log N) |
| `upper_bound` | 找第一个严格大于目标的位置 | 有序 `vector` 上 O(\log N) |
| 坐标离散化 | 把大数值映射为连续排名 | 通常 O(N\log N) |

排序不是解题目标，而是让后续计算更容易进行的一步预处理。

## 排序基础

### 1. 普通数组

```cpp
int a[6] = {5, 2, 8, 2, 1, 9};
sort(a, a + 6); // 1 2 2 5 8 9
```

`sort(first,last)` 处理的是左闭右开区间 `[first,last)`，不包含 last 指向的位置。

若数组从 1 开始使用：

```cpp
sort(a + 1, a + n + 1);
```

不要写成 `sort(a+1,a+n)`，那样最后一个元素不会参与排序。

### 2. 动态数组 vector

```cpp
vector<int> a = {5, 2, 8, 2, 1};
sort(a.begin(), a.end());
cout << a[0]; // 可以像普通数组一样使用下标
```

`vector` 可以排序，也可以用下标访问；下标范围必须在 `[0,size())` 内。

```cpp
vector<int> a;
a.reserve(100); // 只预留容量，size 仍为 0
// a[0] = 7;    // 错误：还没有元素

a.push_back(7); // 现在 a[0] 才存在
```

### 3. 从大到小

```cpp
sort(a.begin(), a.end(), greater<int>());
```

也可以写：

```cpp
sort(a.begin(), a.end(), [](int x, int y) {
    return x > y;
});
```

### 4. pair 的默认顺序

```cpp
vector<pair<int,int>> points = {{2,5}, {1,9}, {2,3}};
sort(points.begin(), points.end());
```

结果：`{1,9}`、`{2,3}`、`{2,5}`。

先比较 `first`，相等时再比较 `second`，都按升序。

`pair` 的默认排序不会理解题意；如果要求第二项降序，就需要自定义规则。

## 三、自定义排序与多关键字

### 1. 比较函数的含义

```cpp
bool cmp(const Student &a, const Student &b)
```

返回 true 表示：**按照你定义的顺序，a 应排在 b 前面。**

例如分数高的在前，分数相同时编号小的在前：

```cpp
if (a.score != b.score) return a.score > b.score;
return a.id < b.id;
```

### 2. 为什么不能写 >=

```cpp
return a.score >= b.score; // 错误的比较规则
```

相同元素之间会出现 `cmp(a,a)==true`，不满足 `sort` 要求的严格弱序。

至少应保证：

1. `cmp(a,a)` 为 false。
2. `cmp(a,b)` 为 true 时，`cmp(b,a)` 为 false。
3. 排序关系具有传递性，不能出现 a 在 b 前、b 在 c 前、c 又在 a 前。
4. “视为相等”的关系也要一致，不能前后矛盾。

初学时最稳妥的写法：按关键字依次比较，最后用 `<` 或 `>`，不使用 `<=` 或 `>=`。

不要直接用 `a.x-b.x` 当布尔返回值；也不要依赖可能溢出的差值来判断大小。

### 3. 完整示例：保留原始顺序信息

输入每位学生的姓名与分数。输出按分数降序排列的名单，分数相同时保持原始输入顺序。

```cpp
#include <bits/stdc++.h>
using namespace std;

struct Student {
    string name;
    int score, id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<Student> students(n);
    for (int i = 0; i < n; i++) {
        cin >> students[i].name >> students[i].score;
        students[i].id = i;
    }
    sort(students.begin(), students.end(), [](const Student &a, const Student &b) {
        if (a.score != b.score) return a.score > b.score;
        return a.id < b.id;
    });
    for (const auto &s : students) cout << s.name << ' ' << s.score << '\n';
}
```

这里 `id` 记录输入编号，排序后不能再用数组当前下标表示原始编号。

### 4. sort 与 stable_sort

- `sort` 不保证等价元素保留原相对顺序。
- `stable_sort` 保留比较规则下等价元素的原相对顺序。

例如只比较分数：

```cpp
stable_sort(students.begin(), students.end(), [](const Student &a, const Student &b) {
    return a.score > b.score;
});
```

稳定排序只帮助保留顺序，不会自动实现所有题目需要的第二关键字。

## 二分查找：lower_bound 与 upper_bound

本节统一使用**升序 vector**。

```cpp
vector<int> a = {2, 4, 4, 7, 10};
```

| 表达式 | 含义 | 示例结果：下标 |
| --- | --- | --- |
| `lower_bound(a.begin(),a.end(),4)` | 第一个 >=4 | 1 |
| `upper_bound(a.begin(),a.end(),4)` | 第一个 >4 | 3 |
| `lower_bound(a.begin(),a.end(),6)` | 第一个 >=6 | 3 |
| `upper_bound(a.begin(),a.end(),10)` | 第一个 >10 | 5，即 end |

它们返回**迭代器**，不是元素的值。

```cpp
auto it = lower_bound(a.begin(), a.end(), x);
int index = int(it - a.begin());
```

### 1. 怎么判断 x 是否存在

```cpp
if (it != a.end() && *it == x) {
    // x 存在
}
```

不能只判断 `it != a.end()`，因为找到的值可能大于 x。也不能对 `end()` 解引用。

### 2. 统计区间中的元素数量

```cpp
int count = int(upper_bound(a.begin(), a.end(), r)
              - lower_bound(a.begin(), a.end(), l));
```

统计闭区间 `[l,r]` 中的元素个数，包含重复元素，要求 `l<=r`。

### 3. 二分查找的前提

本课默认升序排序后再使用默认版本。若按降序或其他规则排序，查找规则必须匹配。

`set`、`map` 应优先使用成员函数 `s.lower_bound(x)`、`mp.lower_bound(x)`。对这些容器使用通用 `std::lower_bound`，比较次数虽然是对数级，但迭代器移动可能达到线性级。

## 去重：unique 与 erase

### 1. unique 只处理连续重复

```cpp
vector<int> a = {2, 2, 5, 5, 5, 8};
auto newEnd = unique(a.begin(), a.end());
```

逻辑上的不同元素被放到前面，成为 `{2,5,8}`。

但 `a.size()` 没有变化。`newEnd` 后面的元素仍然占据 vector 的位置，只是不再属于我们要保留的逻辑区间，不应依赖它们的具体数值。

### 2. erase 删除多余部分

```cpp
a.erase(newEnd, a.end());
```

删除 `[newEnd,a.end())`，vector 的大小才真正缩小。

合起来：

```cpp
sort(a.begin(), a.end());
a.erase(unique(a.begin(), a.end()), a.end());
```

### 3. 为什么通常先排序

`{2,5,2}` 中两个 2 不连续，直接 `unique` 不会把它们全部合并。

若要对所有相同值去重，先排序，让相同值相邻。

**去重的是哪些数据，要由题意决定。** 坐标映射表可以去重；多头牛站在相同坐标时，不能因此把它们当作一头牛。

## 离散化是什么

离散化，也叫坐标压缩，英文常用 **Coordinate Compression**。

当原始数值很大，但实际出现的不同数值很少时，把这些值按大小映射成连续整数。

例如：

```text
原数组：1000000000  -5  100  -5  700000000
```

排序去重后：

| 原值 | 压缩后编号，从 1 开始 |
| --- | --- |
| -5 | 1 |
| 100 | 2 |
| 700000000 | 3 |
| 1000000000 | 4 |

原数组变成：

```text
4 1 2 1 3
```

相同值映射为相同编号；不同值保持原来的大小顺序。

### 1. 离散化保留什么

对于被映射的数值 a、b：

$$
a<b\iff rank(a)<rank(b)
$$

$$
a=b\iff rank(a)=rank(b)
$$

因此相对大小、相等关系、已收集点的区间包含关系得以保留。

### 2. 离散化不保留什么

一般不保留：

- 两个数的真实差值。
- 真实长度、面积、斜率。
- 原整数坐标之间有多少个空位置。
- 正方形的宽高相等关系。

例如原坐标 1、100、101，压缩后为 1、2、3：

- 原来的间距是 99、1。
- 压缩后的间距都是 1。

**排名相邻，不代表原位置相邻。**

## 标准离散化四步

### 第一步：复制需要压缩的数值

```cpp
vector<long long> values = a;
```

保留 a 的原始顺序，排序副本 values。

### 第二步：排序

```cpp
sort(values.begin(), values.end());
```

### 第三步：去重

```cpp
values.erase(unique(values.begin(), values.end()), values.end());
```

### 第四步：二分查找排名

```cpp
int rank = int(lower_bound(values.begin(), values.end(), x) - values.begin()) + 1;
```

这里 x 已经收集进 values，所以一定存在。加 1 后排名范围是 `[1,M]`，M 为不同数值的数量。

### 完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<ll> a(n);
    for (ll &x : a) cin >> x;
    vector<ll> values = a;
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());
    vector<int> rank(n);
    for (int i = 0; i < n; i++) {
        rank[i] = int(lower_bound(values.begin(), values.end(), a[i]) - values.begin()) + 1;
    }
    for (int i = 0; i < n; i++) {
        cout << rank[i] << (i + 1 == n ? '\n' : ' ');
    }
}
```

时间 $O(N\log N)$，空间 $O(N)$。

### 如何还原原值

本课排名从 1 开始，所以：

```cpp
long long original = values[rank - 1];
```

`rank` 是编号；`values[rank-1]` 才是对应的原始数值。

## 什么时候能直接按排序位置编号

若题目保证所有坐标互不相同，可以排序后直接赋排名：

```cpp
sort(cows.begin(), cows.end(), [](const Cow &a, const Cow &b) {
    return a.x < b.x;
});
for (int i = 0; i < n; i++) cows[i].cx = i + 1;
```

但是原值若重复，就不能给每个元素分配不同排名。

例如 `{10,10,20}` 应压缩成 `{1,1,2}`，不是 `{1,2,3}`。

还有一个区别：直接对 cows 排序会改变元素顺序，若之后需要原始编号，必须把 `id` 一起保留。

## 应用：离散化 + 稀疏点权前缀和

### 1. 练习题设

给 n 个带权点 `(x,weight)`，坐标可能很大，也可能重复。每次询问原坐标区间 `[l,r]` 内的总权值。所有点先给出，之后只有查询，没有动态修改。

例如：

```text
4 3
-5 2
100 3
100 4
1000000000 5
0 100
-10 -6
101 2000000000
```

输出：

```text
7
0
5
```

### 2. 为什么不用开到十亿的数组

只需为实际出现的不同点坐标分配位置。同一坐标的权值累加，然后建立前缀和。

### 3. 查询端点不在映射表里怎么办

不需要强行把每个查询端点加入映射表。

```cpp
beforeL = lower_bound(values.begin(), values.end(), l) - values.begin();
throughR = upper_bound(values.begin(), values.end(), r) - values.begin();
```

- `beforeL` 是原坐标严格小于 l 的不同坐标数。
- `throughR` 是原坐标不超过 r 的不同坐标数。
- 因此前缀和相减：`prefix[throughR]-prefix[beforeL]`。

这里返回的是“前面有多少个位置”的计数，不是一定存在的端点排名，所以不需要再加 1。

### 4. 完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<pair<ll, ll>> points(n);
    vector<ll> values;
    for (auto &[x, weight] : points) {
        cin >> x >> weight;
        values.push_back(x);
    }
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());
    int m = int(values.size());
    vector<ll> prefix(m + 1, 0);
    for (auto [x, weight] : points) {
        int rank = int(lower_bound(values.begin(), values.end(), x) - values.begin()) + 1;
        prefix[rank] += weight; // 同一位置的权值累加
    }
    for (int i = 1; i <= m; i++) prefix[i] += prefix[i - 1];
    while (q--) {
        ll l, r;
        cin >> l >> r; // 本练习保证 l <= r
        int beforeL = int(lower_bound(values.begin(), values.end(), l) - values.begin());
        int throughR = int(upper_bound(values.begin(), values.end(), r) - values.begin());
        cout << prefix[throughR] - prefix[beforeL] << '\n';
    }
}
```

时间 $O((N+Q)\log(N+1))$，空间 $O(N)$。权值和使用 `long long`。

## 二维离散化：x、y 分别处理

一组二维点：

```text
(100,20), (500,10), (300,80)
```

- x 排序：100、300、500，对应 1、2、3。
- y 排序：10、20、80，对应 1、2、3。

压缩后：

```text
(1,2), (3,1), (2,3)
```

注意同一个点的两个坐标仍必须配对，不能把排序后的 x、y 任意重新组合。

```cpp
cow.cx = lower_bound(xs.begin(), xs.end(), cow.x) - xs.begin() + 1;
cow.cy = lower_bound(ys.begin(), ys.end(), cow.y) - ys.begin() + 1;
```

分别压缩 x、y 后，轴对齐矩形中包含哪些已知点不会改变。但矩形的实际宽高、面积、是否为正方形，一般会改变。

## 真题一：Diamond Collector，铜组

[USACO 2016 US Open Bronze — Diamond Collector](https://usaco.org/index.php?page=viewproblem2&cpid=639)

### 1. 为什么先排序

选出尽量多的钻石，使最大尺寸与最小尺寸之差不超过 K。

排序后，如果区间两端满足 `a[r]-a[l]<=K`，中间的钻石也都能选，没有理由跳过。

因此只需要找一个尽可能长的连续区间。

### 2. 基础做法

枚举左端 l，向右找到第一个不满足条件的位置 r，合法数量为 `r-l`。

排序 $O(N\log N)$，扫描最坏 $O(N^2)$，能满足本题 $N\le1000$。

### 3. 完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int &x : a) cin >> x;
    sort(a.begin(), a.end());
    int answer = 0;
    for (int l = 0; l < n; l++) {
        int r = l;
        while (r < n && a[r] - a[l] <= k) r++;
        answer = max(answer, r - l); // 合法区间是 [l,r)
    }
    cout << answer << '\n';
}
```

### 4. 双指针优化

```cpp
int r = 0;
for (int l = 0; l < n; l++) {
    while (r < n && a[r] - a[l] <= k) r++;
    answer = max(answer, r - l);
}
```

当 l 增加时，合法 r 不会向左退，因此 r 可以保留上次的位置。排序后扫描变为 $O(N)$。

本题要求真实尺寸之差，不能把尺寸压缩为排名后再计算差值。

## 真题二：Sleepy Cow Sorting，铜组

[USACO 2019 January Bronze — Sleepy Cow Sorting](https://usaco.org/index.php?page=viewproblem2&cpid=892)

### 1. 排序题不代表直接调用 sort

只允许把队首奶牛取出，插入队伍后方某个位置，求最少操作次数。

直接 `sort` 会得到目标排列，却不会告诉你在指定操作下最少需要几步。

### 2. 观察不必移动的部分

从后往前找到最长严格递增后缀。这个后缀本来已经有序，可以保持它的相对顺序。

它前面的每头牛都必须至少移走一次；依次把这些队首牛插入已排序部分的合适位置，可以让每头恰好移动一次。

因此答案就是递增后缀之前的牛数。

更严格地说，任何没有被操作过的奶牛都必须形成原排列的一个后缀，且最终相对顺序不变，所以该后缀必须递增。

### 3. 样例

`1 2 4 3` 的最长递增后缀只有 `{3}`，前面有 3 头牛，因此答案是 3。不是只看“有几头牛位置不对”。

### 4. 完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> p(n);
    for (int &x : p) cin >> x;
    int start = n - 1;
    while (start > 0 && p[start - 1] < p[start]) start--;
    cout << start << '\n'; // 最长递增后缀之前有多少头牛
}
```

时间 $O(N)$，空间 $O(N)$。

## 真题三：Mountain View，银组

[USACO 2019 January Silver — Mountain View](https://usaco.org/index.php?page=viewproblem2&cpid=896)

### 1. 几何转区间

山峰坐标为 `(x,y)`，两侧斜率为 ±1，则山在 x 轴上的投影为：

$$
[L,R]=[x-y,x+y]
$$

一座山峰被另一座山遮挡，当且仅当其投影区间被另一座的投影区间包含。

### 2. 排序规则

- L 从小到大。
- L 相等时，R 从大到小。

例如 `[1,10]` 与 `[1,6]`，必须先处理 `[1,10]`，才能正确判断后者被遮挡。

### 3. 扫描规则

维护已处理区间中的最大右端 `maxRight`：

- `R<=maxRight`：当前区间被某个之前的区间包含。
- `R>maxRight`：可见，答案加 1，并更新 maxRight。

左端条件由排序保证，右端条件由最大值维护完成。山峰在另一座山的边界上也算被挡，所以等号不能漏。

### 4. 完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
struct Mountain { ll left, right; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<Mountain> mountains(n);
    for (auto &mountain : mountains) {
        ll x, y;
        cin >> x >> y;
        mountain = {x - y, x + y};
    }
    sort(mountains.begin(), mountains.end(), [](const Mountain &a, const Mountain &b) {
        if (a.left != b.left) return a.left < b.left;
        return a.right > b.right; // 左端相同，大区间先处理
    });
    ll maxRight = LLONG_MIN;
    int answer = 0;
    for (auto mountain : mountains) {
        if (mountain.right > maxRight) {
            answer++;
            maxRight = mountain.right;
        }
    }
    cout << answer << '\n';
}
```

时间 $O(N\log N)$，空间 $O(N)$。题目保证没有完全相同的山峰，因此不会出现两个完全相同的投影区间。

## 真题四：Convention II，银组

[USACO 2018 December Silver — Convention II](https://usaco.org/index.php?page=viewproblem2&cpid=859)

### 1. 两种顺序要分开

- 奶牛按到达时间进入等待集合。
- 等待中的牛按资历决定谁先吃草。

最先到达的不一定在所有等待者中最先服务；这不是简单的“全体按到达时间排序后依次处理”。

### 2. 数据记录

```cpp
struct Cow {
    long long arrival, duration;
    int id;
};
```

原始输入编号 id 越小，资历越高。排序后必须保留 id。

### 3. 解题步骤

1. 按到达时间排序，记录下一头尚未到达的牛。
2. 当前无人等待时，把时间跳到下一次到达事件。
3. 将所有 `arrival<=now` 的牛加入按 id 排序的小根堆。
4. 取资历最高者，记录等待时间，再增加吃草时长。
5. 重复直到全部处理完。

恰好在上一头牛结束时到达，也要参与这一轮资历比较，所以是 `<=now`。

### 4. 完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
struct Cow { ll arrival, duration; int id; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<Cow> cows(n);
    for (int i = 0; i < n; i++) {
        cin >> cows[i].arrival >> cows[i].duration;
        cows[i].id = i; // 原始编号越小，资历越高
    }
    sort(cows.begin(), cows.end(), [](const Cow &a, const Cow &b) {
        if (a.arrival != b.arrival) return a.arrival < b.arrival;
        return a.id < b.id;
    });
    // {原始编号，排序后的数组下标}，按原始编号最小者优先。
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> waiting;
    ll now = 0, answer = 0;
    int nextCow = 0;
    while (nextCow < n || !waiting.empty()) {
        if (waiting.empty() && nextCow < n) now = max(now, cows[nextCow].arrival);
        while (nextCow < n && cows[nextCow].arrival <= now) {
            waiting.push({cows[nextCow].id, nextCow});
            nextCow++;
        }
        int index = waiting.top().second;
        waiting.pop();
        answer = max(answer, now - cows[index].arrival);
        now += cows[index].duration;
    }
    cout << answer << '\n';
}
```

时间 $O(N\log N)$，空间 $O(N)$。当前时间和等待时间使用 `long long`。

## 真题五：Rectangular Pasture，银组

[USACO 2020 December Silver — Rectangular Pasture](https://usaco.org/index.php?page=viewproblem2&cpid=1063)

### 1. 离散化为什么适用

坐标可到 $10^9$，但牛最多 2500 头，且所有 x 互异、所有 y 互异。

题目统计能够由轴对齐矩形圈出的不同牛群子集，只关心左右上下的相对位置，不关心真实面积。

因此分别将 x、y 压缩为 1 到 N。

### 2. 不枚举四条边

每个非空牛群有唯一的最下方牛、最上方牛。先固定它们，设 y 排名分别为 bottom、top。

这两头牛的 x 排名为 $x_b,x_t$，记：

$$
x_{\min}=\min(x_b,x_t),\qquad x_{\max}=\max(x_b,x_t)
$$

再考虑矩形内最左方牛与最右方牛的选择。

### 3. 两侧候选数量

在 y 区间 `[bottom,top]` 内：

- 左边界对应的最左牛必须满足 `x<=xMin`，数量为 L。
- 右边界对应的最右牛必须满足 `x>=xMax`，数量为 R。

本组上下边界贡献：

$$
L\times R
$$

可选的是**极值牛**，不是无穷多个几何边界坐标。不同左、右极值牛给出不同牛群；每个牛群又有唯一上下极值牛，因此不会重复计算。

上下牛相同时，y 带中只有这一头牛，贡献为 1。

### 4. 用二维前缀和查数量

`prefix[x][y]` 表示压缩网格中 `[1,x]×[1,y]` 内的牛数。

对闭矩形 `[x1,x2]×[y1,y2]`：

$$
count=prefix[x_2][y_2]-prefix[x_1-1][y_2]
-prefix[x_2][y_1-1]+prefix[x_1-1][y_1-1]
$$

所以：

```cpp
L = count(1, bottom, xMin, top);
R = count(xMax, bottom, n, top);
```

枚举全部上下牛对，累加 `L*R`，最后包括空集。

### 5. 完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
struct Cow { ll x, y; int cx, cy; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<Cow> cows(n);
    vector<ll> xs, ys;
    for (auto &cow : cows) {
        cin >> cow.x >> cow.y;
        xs.push_back(cow.x);
        ys.push_back(cow.y);
    }
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    vector<vector<int>> prefix(n + 1, vector<int>(n + 1, 0));
    vector<int> xAtY(n + 1);
    for (auto &cow : cows) {
        cow.cx = int(lower_bound(xs.begin(), xs.end(), cow.x) - xs.begin()) + 1;
        cow.cy = int(lower_bound(ys.begin(), ys.end(), cow.y) - ys.begin()) + 1;
        prefix[cow.cx][cow.cy]++;
        xAtY[cow.cy] = cow.cx; // 本题保证所有 y 不同
    }
    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= n; y++) {
            prefix[x][y] += prefix[x - 1][y] + prefix[x][y - 1] - prefix[x - 1][y - 1];
        }
    }
    auto count = [&](int x1, int y1, int x2, int y2) {
        return prefix[x2][y2] - prefix[x1 - 1][y2]
             - prefix[x2][y1 - 1] + prefix[x1 - 1][y1 - 1];
    };
    ll answer = 1; // 空集
    for (int bottom = 1; bottom <= n; bottom++) {
        for (int top = bottom; top <= n; top++) {
            int leftLimit = min(xAtY[bottom], xAtY[top]);
            int rightLimit = max(xAtY[bottom], xAtY[top]);
            int leftChoices = count(1, bottom, leftLimit, top);
            int rightChoices = count(rightLimit, bottom, n, top);
            answer += 1LL * leftChoices * rightChoices;
        }
    }
    cout << answer << '\n';
}
```

时间 $O(N^2+N\log N)$，空间 $O(N^2)$。

N=2500 时，前缀和约 625 万个 int，主体数据约 25 MB。前缀和只统计牛数，可以用 int；最终答案使用 `long long`，乘法用 `1LL*L*R`。

### 6. 为什么 Square Pasture 不能直接照搬

正方形要求真实宽度等于真实高度。独立压缩 x、y 会改变长度比例，所以不能用排名差代替边长。

可以排序、用排名辅助枚举，但边长与距离判断仍需保留原坐标。

## 金组拓展：Balanced Photo

[USACO 2017 January Gold — Balanced Photo](https://usaco.org/index.php?page=viewproblem2&cpid=693)

> 本节需要树状数组基础。第一次学习离散化时，可以先理解状态定义，代码作为后续拓展。

### 1. 原顺序必须保留

对每头牛，计算原队列中左边、右边比它高的牛数 L、R。若：

$$
\max(L,R)>2\min(L,R)
$$

则这头牛不平衡。

不能直接把原队列按身高排序后，把排序下标当成左右位置。

### 2. 离散化身高

复制身高数组，排序去重，用排名替代身高。身高排名保留“谁比谁高”，足以用于计数。

树状数组按身高排名维护已经扫描过的牛数：

- `add(rank)`：某个身高出现次数加 1。
- `sum(rank)`：已扫描部分中，身高不超过当前身高的牛数。

### 3. 左右分别扫描

从左到右，当前位置 i 从 0 开始，左侧已扫描 i 头：

$$
L_i=i-\operatorname{sum}(rank_i)
$$

从右到左，右侧已扫描 $N-1-i$ 头：

$$
R_i=(N-1-i)-\operatorname{sum}(rank_i)
$$

都是先查询、再加入当前牛，避免把自己算进去。

### 4. 完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<int> tree;
    explicit Fenwick(int n) : n(n), tree(n + 1, 0) {}
    void add(int x) {
        for (; x <= n; x += x & -x) tree[x]++;
    }
    int sum(int x) const {
        int result = 0;
        for (; x > 0; x -= x & -x) result += tree[x];
        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> height(n);
    for (int &x : height) cin >> x;
    vector<int> values = height;
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());
    int m = int(values.size());
    vector<int> rank(n), left(n), right(n);
    for (int i = 0; i < n; i++) {
        rank[i] = int(lower_bound(values.begin(), values.end(), height[i]) - values.begin()) + 1;
    }
    Fenwick leftTree(m);
    for (int i = 0; i < n; i++) {
        left[i] = i - leftTree.sum(rank[i]);
        leftTree.add(rank[i]);
    }
    Fenwick rightTree(m);
    for (int i = n - 1; i >= 0; i--) {
        right[i] = (n - 1 - i) - rightTree.sum(rank[i]);
        rightTree.add(rank[i]);
    }
    int answer = 0;
    for (int i = 0; i < n; i++) {
        if (max(left[i], right[i]) > 2LL * min(left[i], right[i])) answer++;
    }
    cout << answer << '\n';
}
```

时间 $O(N\log N)$，空间 $O(N)$。

另一种做法是按身高降序处理，把原位置加入树状数组，此时已加入的都是更高的牛。两种做法都必须区分“身高顺序”和“原位置顺序”。

## 真题拓展

以下只列与本章工具直接有关的题。它们还需要贪心或其他数据结构，不是仅调用 sort 就能解决。

| 年份与组别 | 真题 | 排序/离散化的作用 | 额外知识 |
| --- | --- | --- | --- |
| 2023 December Silver | [Bovine Acrobatics](https://usaco.org/index.php?page=viewproblem2&cpid=1350) | 按重量排序，按批次考虑可衔接的牛群 | 贪心、队列或双指针、数量批量转移 |
| 2024 December Silver | [Deforestation](https://usaco.org/index.php?page=viewproblem2&cpid=1447) | 树的位置排序，把原坐标区间转换为树的下标区间 | 区间贪心与高效维护 |
| 2018 January Gold | [MooTube](https://usaco.org/index.php?page=viewproblem2&cpid=789) | 边与查询按阈值降序，改成只加边的处理过程 | 离线算法、并查集 |

| 阶段 | 真题/练习 | 主要训练点 |
| --- | --- | --- |
| 基础 | 本课学生排序练习 | 多关键字、原始编号 |
| 基础 | 本课离散化与稀疏区间和 | sort + unique + lower_bound + 前缀和 |
| 铜组 | [Diamond Collector](https://usaco.org/index.php?page=viewproblem2&cpid=639) | 排序后区间枚举，再优化双指针 |
| 铜组 | [Sleepy Cow Sorting](https://usaco.org/index.php?page=viewproblem2&cpid=892) | 操作受限的排序，观察递增后缀 |
| 银组 | [Mountain View](https://usaco.org/index.php?page=viewproblem2&cpid=896) | 几何转区间、多关键字、扫描 |
| 银组 | [Convention II](https://usaco.org/index.php?page=viewproblem2&cpid=859) | 到达顺序与服务顺序分离 |
| 银组 | [Rectangular Pasture](https://usaco.org/index.php?page=viewproblem2&cpid=1063) | 二维离散化、前缀和、唯一计数 |
| 近年银组拓展 | [Bovine Acrobatics](https://usaco.org/index.php?page=viewproblem2&cpid=1350) | 排序、贪心、批量处理 |
| 近年银组拓展 | [Deforestation](https://usaco.org/index.php?page=viewproblem2&cpid=1447) | 位置排序、原坐标区间转下标区间 |
| 金组 | [Balanced Photo](https://usaco.org/index.php?page=viewproblem2&cpid=693) | 离散化、树状数组、左右计数 |
| 金组 | [MooTube](https://usaco.org/index.php?page=viewproblem2&cpid=789) | 离线排序、恢复查询顺序 |

