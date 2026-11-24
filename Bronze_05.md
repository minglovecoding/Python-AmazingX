## 📚铜组专题：字符串、矩形几何、坐标几何

## 1.字符与字符串

`char` 保存一个字符，`string` 保存一串字符。

```cpp
char c = 'A';
string s = "USACO";
```

| 写法 | 含义 |
|---|---|
| `'A'` | 字符，使用单引号 |
| `"A"` | 字符串，使用双引号 |
| `s.size()` | 字符串长度 |
| `s[i]` | 下标为 `i` 的字符 |
| `s.substr(i, k)` | 从 `i` 开始，截取长度为 `k` 的子串 |
| `s += t` | 将 `t` 拼接到末尾 |
| `s == t` | 内容是否相同 |
| `s < t` | 按字典序比较 |

```cpp
string s = "USACO";
for (int i = 0; i < (int)s.size(); i++) {
    cout << i << ' ' << s[i] << '\n';
}
```

只读取字符，不需要下标时：

```cpp
//增强型for循环
for (char c : s) {
    cout << c << '\n';
}
```

### 输入：`cin` 与 `getline`

```cpp
string word;
cin >> word;       // 读取到空白字符之前

string line;
getline(cin, line); // 读取整行，可以包含空格
```

如果先用 `cin >> n`，再读取下一整行，要处理留下的换行：

```cpp
cin >> n;
cin.ignore();  //丢弃换行符
getline(cin, line);  //也可以用cin >> ws代替cin跳过所有前导空白，但会跳过空格、换行和空行。
```

### 字典序

逐个比较对应字符；第一次不同决定大小。一个字符串是另一个的前缀时，短的更小。

```cpp
// "ABC" < "ABD"
// "ABC" < "ABCD"
```

不要混淆 `"10" < "2"` 与数值 `10 < 2`：前者按字符比较，为真。

### 1.2 字符计数：把字母映射为数组下标

如果题目保证所有字符都是小写英文字母：

```cpp
int cnt[26] = {};
for (char c : s) {
    cnt[c - 'a']++;
}
```

- `'a' - 'a' = 0`。
- `'b' - 'a' = 1`。
- `'z' - 'a' = 25`。

大写字母使用 `c - 'A'`。大小写或其他字符混用时，不能直接套用同一段代码。

**课堂小练习：**`ABACA` 中，A、B、C 各出现几次？

**答案：**3、1、1。时间复杂度为 `O(n)`，计数数组空间为 `O(26)`。

### 1.3 真题 1：Bovine Genomics——按列比较字符集合

- 比赛：2017 US Open，Bronze，Problem 2。
- [官方题目](https://usaco.org/index.php?page=viewproblem2&cpid=736)

### 题意与知识点

两组各有 `N` 个长度为 `M` 的基因字符串。求有多少个位置，能仅凭该位置的字符区分两组。

### 思路

枚举列 `j`，记录第一组在该列出现的所有字符，再检查第二组是否出现相同字符。

### 参考代码

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<string> spotty(n), plain(n);
    for (string& s : spotty) cin >> s;
    for (string& s : plain) cin >> s;

    int answer = 0;
    for (int col = 0; col < m; col++) {
        bool seen[26] = {}; // 每换一列，必须重新清空
        for (int row = 0; row < n; row++) {
            seen[spotty[row][col] - 'A'] = true;
        }
        bool good = true;
        for (int row = 0; row < n; row++) {
            if (seen[plain[row][col] - 'A']) {
                good = false;
                break;
            }
        }
        if (good) answer++;
    }
    cout << answer << '\n';
}
//时间复杂度O(NM)
```

### 1.4 子串、子序列与连续片段

- **子串(substring)**必须连续。
- **子序列(subsequence)**保持原顺序，可以跳过部分字符。

例如在 `ABCDE` 中，`BCD` 是子串；`ACE` 是子序列，但不是子串。

### 枚举长度为 `k` 的所有子串

```cpp
int n = (int)s.size();
for (int i = 0; i + k <= n; i++) {
    string sub = s.substr(i, k);
}
```

合法起点为 `0` 到 `n-k`，共 `n-k+1` 个。只有在 `1 <= k <= n` 时才使用这个计数。

### 用 `set` 检查重复

```cpp
set<string> seen;
for (int i = 0; i + k <= (int)s.size(); i++) {
    string sub = s.substr(i, k);
    if (seen.count(sub) > 0) {
    // 当前 sub 之前出现过
    }
    seen.insert(sub);
    //也可以用if (!seen.insert(sub).second) .first是指向该元素的迭代器 .second返回是否成功插入
}
```

`insert()` 返回一个 pair：

- `.first`：集合中对应元素的迭代器。
- `.second`：本次是否成功插入；新元素为 `true`，已有元素为 `false`。

### 1.5 真题 2：Where Am I?——枚举长度，检查重复子串

- 比赛：2019 December，Bronze，[Problem 2](https://usaco.org/index.php?page=viewproblem2&cpid=964)。

### 题意

找最小的 `K`，使所有长度为 `K` 的连续子串互不相同。

### 思路与正确性

从 `K=1` 到 `N` 依次检查；若有重复子串，该长度不合法。第一个合法长度就是最小答案， `K=N` 一定合法。

### 参考代码

```cpp
#include <iostream>
#include <set>
#include <string>
using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;
    for (int k = 1; k <= n; k++) {
        set<string> seen;
        bool good = true;
        for (int i = 0; i + k <= n; i++) {
            if (!seen.insert(s.substr(i, k)).second) {
                good = false;
                break;
            }
        }
        if (good) {
            cout << k << '\n';
            return 0;
        }
    }
}
```

时间复杂度分析如下：

1. 外层枚举长度 `k`：最多 \(n\) 次。

2. 内层枚举子串起点：每次最多 \(n\) 次。

3. 每次操作：

   ```
   seen.insert(s.substr(i, k))
   ```

   - `substr(i, k)` 复制 \(k\) 个字符：\(O(k)\)。
   - `set` 插入需要 \(O(log n)\) 次字符串比较，每次比较最坏 \(O(k)\)，因此为 \(O(klog n)\)。

合起来：
$$
O\left(\sum_{k=1}^{n}(n-k+1)\,k\log n\right) =O(n^3\log n)
$$

```c++
//最长重复子串
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;
  
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    //从两个不同位置 i、`j` 出发，最多有多少个连续字符相同。
    int longest = 0;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            if (s[i] == s[j]) {
                dp[i][j] = dp[i + 1][j + 1] + 1;
                longest = max(longest, dp[i][j]);
            }
        }
    }

    cout << longest + 1 << '\n';
    return 0;
}
```

### 1.6 真题 3：Moo Operations——先分析操作，再枚举

- 比赛：2023 January，Bronze，Problem 3。
- [官方题目](https://usaco.org/index.php?page=viewproblem2&cpid=1277)

### 题意

字符串只包含 M、O。每次可以删除首尾字符，或把首尾字符 M、O 互换；求变成 `MOO` 的最少操作数。

### 参考代码

```cpp
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

int main() {
    int q;
    cin >> q;
    while (q--) {
        string s;
        cin >> s;
        int n = (int)s.size();
        int answer = n + 1;
        for (int i = 0; i + 2 < n; i++) {
            if (s[i + 1] != 'O') continue;
            int cost = n - 3;
            cost += (s[i] != 'M');
            cost += (s[i + 2] != 'O');
            answer = min(answer, cost);
        }
        cout << (answer == n + 1 ? -1 : answer) << '\n';
    }
}
//复杂度：每个字符串时间 `O(n)`，除输入外额外空间 `O(1)`。
```

### 1.7 连续段与局部影响

### 将字符串分成连续相同字符段

```cpp
for (int l = 0; l < (int)s.size(); ) {
    int r = l;
    while (r < (int)s.size() && s[r] == s[l]) r++;
    // 当前段为 [l, r)，长度为 r-l
    cout << s[l] << ' ' << r - l << '\n';
    l = r;
}
```

例如 `AAABBCCCC` 被分成 `A×3、B×2、C×4`。

### 提高真题：It's Mooin' Time

- 比赛：2024 December，Bronze，Problem 3。
- [官方题目](https://usaco.org/index.php?page=viewproblem2&cpid=1445)

题目要找可能达到频率门槛的 `abb` 型子串，其中 `a != b`；允许原字符串至多有一个字符错误。

```c++
#include <bits/stdc++.h>
using namespace std;

int main() {

    int N, F;
    cin >> N >> F;
    string S;
    cin >> S;

    set<string> moos;  // save different moos

    auto find_moos = [&](const string &s) {
        unordered_map<string, int> cnt; //hash map
        for (int i = 0; i + 2 < N; ++i) {
            if (s[i] != s[i + 1] && s[i + 1] == s[i + 2]) {
                string t = s.substr(i, 3); //substr
                if (++cnt[t] >= F) moos.insert(t);
            }
        }
    };

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < 26; ++j) {
            string T = S;
            T[i] = char('a' + j);
            find_moos(T);
        }
    }

    cout << moos.size() << '\n';
    for (const auto &moo : moos) cout << moo << '\n';
    return 0;
}
//lambda函数
//哈希表unordered_map<string,int>
//set容器
//string的substr用法
```

**常见的数据转换方法**：

| 转换场景              | 常用写法                         | 注意事项                              |
| --------------------- | -------------------------------- | ------------------------------------- |
| 数字字符 → 整数       | `c - '0'`                        | `c` 必须是 `'0'`～`'9'`               |
| 整数 → 数字字符       | `char(x + '0')`                  | `x` 必须在 0～9                       |
| 字母 → 数组下标       | `c - 'a'`                        | 小写字母映射为 0～25                  |
| 字符串 → 数字         | `stoi(s)`、`stoll(s)`、`stod(s)` | 分别得到 `int`、`long long`、`double` |
| 数字 → 字符串         | `to_string(x)`                   | 如 `123` 变成 `"123"`                 |
| 整数 → 浮点数         | `double(a) / b`                  | 避免整数除法                          |
| 浮点数 → 整数         | `int(x)`                         | 向零截断，不是四舍五入                |
| 整数 → 更大的整数类型 | `1LL * a * b`                    | 在乘法发生前提升类型，避免 `int` 溢出 |
| 容器长度 → `int`      | `int(v.size())`                  | 确认长度在 `int` 范围内               |

***

## 2：矩形几何

### 2.1 用坐标描述矩形

设左下角 `(x1,y1)`，右上角 `(x2,y2)`，且 `x1<x2、y1<y2`：

$$
width=x_2-x_1,\quad height=y_2-y_1
$$

$$
area=width\times height
$$

```cpp
struct Rect {
    long long x1, y1, x2, y2;
};
long long area(const Rect& r) {
    return (r.x2 - r.x1) * (r.y2 - r.y1);
}
```

如果输入是任意两个对角顶点，应先用 `min/max` 规范化；如果题目已经保证左下、右上顺序，不需要额外交换。

### 点是否在矩形内

```cpp
// 内部或边界
bool inside = r.x1 <= x && x <= r.x2 &&
              r.y1 <= y && y <= r.y2;
```

若严格要求内部，改为严格不等号。

### 2.2 真题 4：Square Pasture——最小外接正方形

- 比赛：2016 December，Bronze，Problem 1。
- [官方题目](https://usaco.org/index.php?page=viewproblem2&cpid=663)

### 题意

用一个边平行坐标轴的正方形盖住两个矩形，求最小面积。

### 推导

先求所有区域的边界：

$$
L=\min(a_{x1},b_{x1}),\quad R=\max(a_{x2},b_{x2})
$$

$$
B=\min(a_{y1},b_{y1}),\quad T=\max(a_{y2},b_{y2})
$$

正方形必须同时容纳宽 `R-L` 和高 `T-B`：

$$
side=\max(R-L,T-B),\quad answer=side^2
$$
**正确性：**更小的边长至少有一个方向放不下；取上述边长，在外接矩形基础上向较短方向扩展即可覆盖。

### 参考代码

```cpp
#include <algorithm>
#include <iostream>
using namespace std;

int main() {
    int ax1, ay1, ax2, ay2;
    int bx1, by1, bx2, by2;
    freopen("square.in","r",stdin);
    freopen("square.out","w",stdout);
    cin >> ax1 >> ay1 >> ax2 >> ay2;
    cin >> bx1 >> by1 >> bx2 >> by2;
    int width = max(ax2, bx2) - min(ax1, bx1);
    int height = max(ay2, by2) - min(ay1, by1);
    int side = max(width, height);
    cout << side * side << '\n';
    return 0;
}
//时间复杂度、额外空间均为 O(1)。
```

### 2.3 矩形的交集

先把二维问题拆成横向与纵向的区间相交。

横向重叠区间左端取较大值，右端取较小值：

$$
L=\max(a_{x1},b_{x1}),\quad R=\min(a_{x2},b_{x2})
$$

$$
B=\max(a_{y1},b_{y1}),\quad T=\min(a_{y2},b_{y2})
$$

$$
w=\max(0,R-L),\quad h=\max(0,T-B),\quad S=w h
$$

```cpp
long long overlap(const Rect& a, const Rect& b) {
    long long w = max(0LL, min(a.x2, b.x2) - max(a.x1, b.x1));
    long long h = max(0LL, min(a.y2, b.y2) - max(a.y1, b.y1));
    return w * h;
}
```

### 2.4 真题 5：Blocked Billboard——可见面积

- 比赛：2017 December，Bronze，Problem 1。
- [官方题目](https://usaco.org/index.php?page=viewproblem2&cpid=759)

### 题意与模型

两个广告牌被一个矩形卡车遮挡，求总可见面积。题目保证两个广告牌本身没有正面积的重叠。

分别计算两个牌子的剩余面积：

$$
answer=S_A+S_B-S_{A\cap C}-S_{B\cap C}
$$
### 参考代码

```cpp
#include <algorithm>
#include <iostream>
using namespace std;

struct Rect {
    long long x1, y1, x2, y2;
};
long long area(const Rect& r) {
    return (r.x2 - r.x1) * (r.y2 - r.y1);
}
long long overlap(const Rect& a, const Rect& b) {
    long long w = max(0LL, min(a.x2, b.x2) - max(a.x1, b.x1));
    long long h = max(0LL, min(a.y2, b.y2) - max(a.y1, b.y1));
    return w * h;
}
int main() {
    Rect a, b, truck;
    cin >> a.x1 >> a.y1 >> a.x2 >> a.y2;
    cin >> b.x1 >> b.y1 >> b.x2 >> b.y2;
    cin >> truck.x1 >> truck.y1 >> truck.x2 >> truck.y2;
    cout << area(a) + area(b)
            - overlap(a, truck) - overlap(b, truck) << '\n';
}
```

时间、额外空间均为 `O(1)`。

### 2.5 真题 6：Blocked Billboard II——可见面积不等于所需遮盖面积

- 比赛：2018 January，Bronze，Problem 1。
- [官方题目](https://usaco.org/index.php?page=viewproblem2&cpid=783)

### 题意

A 被 B 挡住一部分，要再用一块轴对齐的矩形布盖住 A 的全部剩余部分，求布的最小面积。要考虑一块矩形布要同时盖住所有剩余部分，因此不能直接输出 `area(A)-overlap(A,B)`。

### 分类

1. B 完全盖住 A：答案 0。
2. B 贯穿 A 的整个高度，并盖住左边或右边：可缩短布的宽度。
3. B 贯穿 A 的整个宽度，并盖住下边或上边：可缩短布的高度。
4. 其他情况：仍需要 A 的完整外接范围。

### 参考代码

```cpp
#include <algorithm>
#include <iostream>
using namespace std;

struct Rect {
    long long x1, y1, x2, y2;
};
int main() {
    Rect a, b;
    cin >> a.x1 >> a.y1 >> a.x2 >> a.y2;
    cin >> b.x1 >> b.y1 >> b.x2 >> b.y2;
    long long left = a.x1, right = a.x2;
    long long bottom = a.y1, top = a.y2;

    if (b.x1 <= a.x1 && b.x2 >= a.x2 &&
        b.y1 <= a.y1 && b.y2 >= a.y2) {
        cout << 0 << '\n';
        return 0;
    }
    // B 贯穿 A 的整个高度，检查能否去掉左侧或右侧。
    if (b.y1 <= a.y1 && b.y2 >= a.y2) {
        if (b.x1 <= a.x1 && b.x2 > a.x1) left = min(a.x2, b.x2);
        if (b.x2 >= a.x2 && b.x1 < a.x2) right = max(a.x1, b.x1);
    }
    // B 贯穿 A 的整个宽度，检查能否去掉下侧或上侧。
    if (b.x1 <= a.x1 && b.x2 >= a.x2) {
        if (b.y1 <= a.y1 && b.y2 > a.y1) bottom = min(a.y2, b.y2);
        if (b.y2 >= a.y2 && b.y1 < a.y2) top = max(a.y1, b.y1);
    }
    cout << max(0LL, right - left) * max(0LL, top - bottom) << '\n';
}
//时间、额外空间均为 O(1)。
```

### 2.6 小坐标范围：用网格验证几何关系

把数组 `covered[x][y]` 解释为单位小格 `[x,x+1) × [y,y+1)` 是否覆盖，而不是坐标点是否覆盖。

```cpp
for (int x = x1; x < x2; x++) {
    for (int y = y1; y < y2; y++) {
        covered[x][y] = true;
    }
}
```

- 使用 `< x2` 与 `< y2`，不多标记边界外的小格。
- 若坐标可能为负，可统一加偏移量，但数组大小也要覆盖平移后的所有下标。
- 坐标范围巨大时，不能直接开数组模拟全部格子。
- 二维数组只是存储方式，不代表一定要用二维前缀和或 BFS。

### 2.7  坐标几何

### 2025 Feb Bronze-Reflection

![](../Python-AmazingX/images/11.png)

```c++
//1.将所有奶牛按照 (x+y) 从大到小排序。
//2.第一头奶牛不可能被其他奶牛阻挡，因此答案一定为 Infinity。
//3.依次遍历后面的奶牛，只需要与前面已经确定最终状态的奶牛比较。
//4.判断轨迹是否相交，以及前面的奶牛是否能够吃到交点。
//5.取所有有效阻挡点中的最小距离；不存在有效阻挡点则为 Infinity。
//6.按照原始输入顺序输出答案。
#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9 + 1;
struct Cow {
    char dir;
    int x, y, id;
};
int main() {
    int n;
    cin >> n;
    vector<Cow> cow(n);
    vector<int> ans(n, INF);
    for (int i = 0; i < n; i++) {
        cin >> cow[i].dir >> cow[i].x >> cow[i].y;
        cow[i].id = i;
    }

    // 按照 x + y 降序排序
    sort(cow.begin(), cow.end(), [](Cow a, Cow b) {
        return a.x + a.y > b.x + b.y;
    });

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (cow[i].dir == cow[j].dir) continue;
            int ti, tj;
            if (cow[i].dir == 'E') {
                ti = cow[j].x - cow[i].x;
                tj = cow[i].y - cow[j].y;
            } else {
                ti = cow[j].y - cow[i].y;
                tj = cow[i].x - cow[j].x;
            }
            // 判断轨迹是否相交及阻挡关系
            if (ti < 0 || tj < 0 || ti <= tj) continue;
            // 判断奶牛 j 是否吃到了交点
            if (ans[cow[j].id] > tj) {
                ans[cow[i].id] = min(ans[cow[i].id], ti);
            }
        }
    }
    for (int x : ans) {
        if (x == INF) cout << "Infinity\n";
        else cout << x << '\n';
    }
    return 0;
}
```

## 3 真题训练

1.**字符串**相关真题：主要结合枚举、计数、连续段、贪心和构造

| 比赛          | 题目                                                         | 主要考点                       |
| ------------- | ------------------------------------------------------------ | ------------------------------ |
| 2021 December | [Lonely Photo](https://usaco.org/index.php?page=viewproblem2&cpid=1155) | 二元字符串、子串计数           |
| 2022 January  | [Herdle](https://usaco.org/index.php?page=viewproblem2&cpid=1179) | 字符比较、频次数组             |
| 2022 February | [Blocks](https://usaco.org/index.php?page=viewproblem2&cpid=1205) | 字符查找、排列枚举、回溯       |
| 2022 US Open  | [Photoshoot](https://usaco.org/index.php?page=viewproblem2&cpid=1227) | 二元字符串、前缀翻转、贪心     |
| 2022 December | [Feeding the Cows](https://usaco.org/index.php?page=viewproblem2&cpid=1252) | 字符串扫描、覆盖贪心、构造     |
| 2023 January  | [Moo Operations](https://usaco.org/index.php?page=viewproblem2&cpid=1277) | 子串枚举、字符修改             |
| 2023 US Open  | [FEB](https://usaco.org/index.php?page=viewproblem2&cpid=1323) | 连续段、相邻字符、奇偶性       |
| 2023 US Open  | [Moo Language](https://usaco.org/index.php?page=viewproblem2&cpid=1324) | 单词分类、枚举、输出构造       |
| 2023 December | [Cowntact Tracing 2](https://usaco.org/index.php?page=viewproblem2&cpid=1348) | 01 字符串、连续段、逆向推理    |
| 2024 US Open  | [Logical Moos](https://usaco.org/index.php?page=viewproblem2&cpid=1419) | 关键词序列、逻辑表达式、预处理 |
| 2024 December | [It’s Mooin’ Time](https://usaco.org/index.php?page=viewproblem2&cpid=1445) | 短子串计数、枚举修改、局部更新 |
| 2025 US Open  | [It’s Mooin’ Time III](https://usaco.org/index.php?page=viewproblem2&cpid=1517) | 字符位置索引、区间查询、二分   |
| 2026 第 1 场  | [COW Splits](https://usaco.org/index.php?page=viewproblem2&cpid=1540) | 循环移位、子序列、构造         |
| 2026 第 2 场  | [It’s Mooin’ Time IV](https://usaco.org/index.php?page=viewproblem2&cpid=1563) | 字符翻转、逆向推理、构造       |

2.**矩形几何**相关真题：

| 比赛          | 题目                                                         | 准确分类             |
| ------------- | ------------------------------------------------------------ | -------------------- |
| 2026 第 1 场  | [Photoshoot](https://usaco.org/index.php?page=viewproblem2&cpid=1541) | 正方形区域统计       |
| 2023 February | [Stamp Grid](https://usaco.org/index.php?page=viewproblem2&cpid=1300) | 网格几何：旋转与覆盖 |
| 2024 US Open  | [Walking Along a Fence](https://usaco.org/index.php?page=viewproblem2&cpid=1420) | 坐标几何：正交多边形 |
| 2025 January  | [Astral Superposition](https://usaco.org/index.php?page=viewproblem2&cpid=1467) | 网格几何：平移与叠加 |
| 2025 February | [Reflection](https://usaco.org/index.php?page=viewproblem2&cpid=1491) | 网格几何：轴对称     |

