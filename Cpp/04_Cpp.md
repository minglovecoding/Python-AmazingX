## USACO 铜组：C++ 常用函数与语法

### 📌 基础头文件

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <numeric>
#include <functional>
#include <utility>
#include <cstdlib>
using namespace std;
```

标准库算法的范围通常为 **`[begin, end)`**，即包含起点，不包含终点。

| 容器 | 完整范围 |
|---|---|
| 长度为 `n` 的普通数组 `a` | `a, a + n` |
| `vector` 或 `string` | `a.begin(), a.end()` |

### 📌 1. 排序：sort

头文件：`<algorithm>`；降序示例中的 `greater<int>` 需要 `<functional>`。

### 升序排序

```cpp
int a[] = {5, 2, 4, 1, 3};
int n = 5;
sort(a, a + n); // 1 2 3 4 5

vector<int> v = {5, 2, 4, 1, 3};
sort(v.begin(), v.end()); // 1 2 3 4 5
```

### 降序排序

```cpp
sort(v.begin(), v.end(), greater<int>()); // 5 4 3 2 1
```

### 对部分范围排序

```cpp
int a[] = {9, 5, 2, 4, 8};
sort(a + 1, a + 4); // 排序下标 1、2、3：9 2 4 5 8
```

常见用途：按大小处理数据、排序后比较相邻元素。时间复杂度为 `O(n log n)`。

### 📌2. 最大、最小值：max、min

头文件：`<algorithm>`。

```cpp
int x = max(3, 7);       // 7
int y = min(3, 7);       // 3
int z = max({3, 7, 5});  // 7
int w = min({3, 7, 5});  // 3
```

### 更新答案

```cpp
int a[] = {3, 8, 2, 6};
int ans = a[0];
for (int i = 1; i < 4; i++) {
    ans = max(ans, a[i]);
}
cout << ans; // 8
```

### 查找整个范围的最大、最小元素

```cpp
int a[] = {3, 8, 2, 6};
int biggest = *max_element(a, a + 4);  // 8
int smallest = *min_element(a, a + 4); // 2
int index = max_element(a, a + 4) - a; // 最大值下标：1
```

`max_element` 和 `min_element` 返回位置，使用 `*` 取出元素值。若范围为空，返回终点，不能解引用。

注意：`max` 和 `min` 的两个普通参数应具有相同类型，例如 `max(3LL, 7LL)`。

### 📌3. 交换：swap

头文件：`<utility>`。

```cpp
int a = 3, b = 7;
swap(a, b); // a = 7，b = 3
```

交换数组或 vector 中两个位置的元素：

```cpp
vector<int> v = {10, 20, 30};
swap(v[0], v[2]); // 30 20 10
```

常见用途：交换位置、模拟物品移动。

### 📌4. 绝对值：abs

整数版本可引入 `<cstdlib>`。

```cpp
cout << abs(-5); // 5
cout << abs(5);  // 5
```

### 一维距离

```cpp
int x1 = 3, x2 = 10;
int distance = abs(x1 - x2); // 7
```

### 曼哈顿距离

只允许上下左右移动时，两个点之间的距离为：

```cpp
int x1 = 1, y1 = 2;
int x2 = 4, y2 = 6;
int distance = abs(x1 - x2) + abs(y1 - y2); // 7
```

若坐标或差值可能很大，使用 `long long`，并在减法前转换类型：

```cpp
long long distance = abs(1LL * x1 - x2) + abs(1LL * y1 - y2);
```

### 📌5. vector 的基本操作

头文件：`<vector>`。

```cpp
vector<int> v;
v.push_back(10);    // 末尾添加 10
v.push_back(20);    // 当前为 {10, 20}

cout << v.size();   // 元素个数：2
cout << v[0];      // 第一个元素：10
cout << v.back();  // 最后一个元素：20

v.pop_back();      // 删除最后一个元素，剩下 {10}
cout << v.empty(); // 是否为空：false（默认输出 0）

v.clear();         // 清空
```

### 创建指定大小的 vector

```cpp
vector<int> a(100);     // 100 个元素，初始值为 0
vector<int> b(100, -1); // 100 个元素，初始值为 -1
```

### 遍历

```cpp
vector<int> v = {1, 2, 3};
for (int i = 0; i < (int)v.size(); i++) {
    cout << v[i] << ' ';
}

for (int x : v) {
    cout << x << ' ';
}
```

注意：下标从 `0` 开始；不能越界访问；空 vector 不能调用 `back()` 或 `pop_back()`。

### 📌6. 字符串操作

头文件：`<string>`；输入输出需要 `<iostream>`。

### 长度、下标和拼接

```cpp
string s = "USACO";
cout << s.size(); // 5
cout << s[0];     // U
s += " Bronze";  // USACO Bronze
```

### 截取子串：substr

语法：`s.substr(起始下标, 字符数量)`。

```cpp
string s = "abcdef";
cout << s.substr(2, 3); // cde
cout << s.substr(2);    // cdef：省略数量时取到结尾
```

第二个参数是**字符数量**，不是结束下标。数量超过剩余长度时取到结尾；起始下标大于字符串长度时会抛出异常。

### 查找子串：find

```cpp
string s = "abcdef";
size_t pos = s.find("cd");
if (pos != string::npos) {
    cout << pos; // 2
} else {
    cout << "Not found";
}
```

找到时返回第一次出现的位置，找不到时返回 `string::npos`。

### 读取一整行：getline

```cpp
string line;
getline(cin, line); // 可以读取含空格的一整行
```

前面刚使用过 `cin >> n` 时，可跳过残留换行及前导空白：

```cpp
int n;
cin >> n;
string line;
getline(cin >> ws, line);
```

注意：`ws` 也会跳过空行和行首空格；需要保留这些内容时，应先妥善处理上一行的换行符，再使用普通 `getline`。

### 📌7. 反转：reverse

头文件：`<algorithm>`。

```cpp
string s = "abc";
reverse(s.begin(), s.end()); // cba

vector<int> v = {1, 2, 3};
reverse(v.begin(), v.end()); // 3 2 1

int a[] = {1, 2, 3, 4};
reverse(a, a + 4); // 4 3 2 1
```

`reverse` 直接修改原内容，不需要接收返回值。时间复杂度为 `O(n)`。

### 📌8. 填充：fill

头文件：`<algorithm>`。

语法：`fill(起点, 终点, 填充值)`。

```cpp
int a[100];
fill(a, a + 100, -1); // 所有元素设为 -1

vector<int> v(100);
fill(v.begin(), v.end(), 5); // 所有元素设为 5
```

也可以填充部分范围：

```cpp
int a[] = {1, 2, 3, 4, 5};
fill(a + 1, a + 4, 0); // 1 0 0 0 5
```

常见用途：初始化数组、每次模拟前重置数据。时间复杂度为 `O(n)`。

### 📌9. 求和、计数：accumulate、count

### 求和：accumulate

头文件：`<numeric>`。

语法：`accumulate(起点, 终点, 初始值)`。

```cpp
int a[] = {1, 2, 3, 4};
long long sum = accumulate(a, a + 4, 0LL); // 10

vector<int> v = {10, 20, 30};
long long total = accumulate(v.begin(), v.end(), 0LL); // 60
```

初始值也参与求和，并决定累加器的类型：

```cpp
int sum = accumulate(a, a + 4, 100); // 100 + 1 + 2 + 3 + 4 = 110
```

**总和可能较大时，使用 `0LL`。** 只把接收变量写成 `long long`，无法避免内部以 `int` 累加时的溢出。

### 计数：count

头文件：`<algorithm>`。

```cpp
int a[] = {1, 2, 2, 3, 2};
int cnt = count(a, a + 5, 2); // 3

string s = "banana";
int num = count(s.begin(), s.end(), 'a'); // 3
```

`count` 统计等于目标值的元素个数，不要求数据有序。两者的时间复杂度均为 `O(n)`。

### 📌10. 枚举排列：next_permutation

头文件：`<algorithm>`。

`next_permutation` 把当前序列修改为按字典序排列的下一个排列。有下一个排列时返回 `true`；当前已是最后一个排列时，将序列重置为最小排列并返回 `false`。

### 枚举全部排列

```cpp
vector<int> v = {1, 2, 3};
sort(v.begin(), v.end());

do {
    for (int x : v) {
        cout << x << ' ';
    }
    cout << '\n';
} while (next_permutation(v.begin(), v.end()));
```

输出：

```text
1 2 3
1 3 2
2 1 3
2 3 1
3 1 2
3 2 1
```

- 先升序排序，才能从最小排列开始枚举全部排列。
- 使用 `do ... while`，确保初始排列也被处理。
- 有重复元素时，从升序排列出发会枚举不同的值序列，不会重复输出相同排列。
- `n` 个互不相同的元素有 `n!` 种排列，需要根据数据规模判断是否可行。

## 速查表

| 项目 | 常用写法 | 功能 |
|---|---|---|
| 排序 | `sort(a, a + n)` | 升序排序 |
| 最大、最小值 | `max(x, y)` / `min(x, y)` | 比较两个值 |
| 交换 | `swap(a, b)` | 交换内容 |
| 绝对值 | `abs(x)` | 取绝对值 |
| vector | `v.push_back(x)` / `v.size()` | 添加元素、查询长度 |
| 字符串 | `s.substr(pos, len)` / `s.find(t)` | 截取、查找子串 |
| 反转 | `reverse(v.begin(), v.end())` | 反转顺序 |
| 填充 | `fill(a, a + n, x)` | 设置范围内的元素 |
| 求和、计数 | `accumulate(a, a + n, 0LL)` / `count(a, a + n, x)` | 求总和、统计出现次数 |
| 枚举排列 | `next_permutation(v.begin(), v.end())` | 生成下一个排列 |

***

另外整理 12 项常用语法和代码模板，重点包括枚举、模拟、频率统计和自定义排序。

### 📌1. long long：防止整数溢出

两个 `int` 相乘时，即使结果存入 `long long`，也可能在乘法时已经溢出。

```cpp
int a = 100000, b = 100000;
long long ans = 1LL * a * b; // 10000000000
```

`1LL` 是 `long long` 类型的整数 1，使后面的乘法使用 `long long` 计算。

求和也经常需要使用 `long long`：

```cpp
vector<int> nums = {1000000000, 1000000000, 1000000000};
long long sum = 0;
for (int x : nums) {
    sum += x;
}
```

### 📌2. 范围遍历：for (类型 变量 : 容器)

### 读取每个元素

```cpp
vector<int> a = {1, 2, 3};
for (int x : a) {
    cout << x << ' ';
}
```

这里的 `x` 是元素的副本，修改 `x` 不会修改原元素。

### 修改原来的元素

```cpp
for (int& x : a) {
    x *= 2;
}
// a 变为 {2, 4, 6}
```

`&` 表示引用，使 `x` 对应原来的元素。

### 遍历字符串

```cpp
string s = "USACO";
for (char c : s) {
    cout << c << '\n';
}
```

需要使用下标或访问相邻元素时，普通的下标循环通常更方便。

### 📌3. 频率数组：统计出现次数

当数值范围较小时，可以把数值直接作为下标。

```cpp
int cnt[101] = {}; // 全部初始化为 0

int n;
cin >> n;
for (int i = 0; i < n; i++) {
    int x;
    cin >> x; // 假设 0 <= x <= 100
    cnt[x]++;
}

cout << cnt[5]; // 数字 5 出现的次数
```

### 统计小写字母

```cpp
int cnt[26] = {};
string s;
cin >> s;

for (char c : s) {
    cnt[c - 'a']++;
}
```

`'a' - 'a' = 0`，`'b' - 'a' = 1`，依次对应数组下标。该模板假设字符串只包含小写英文字母。

### 📌4. 二维数组：存储网格

```cpp
int grid[100][100] = {};

int n, m;
cin >> n >> m; // 假设 1 <= n, m <= 100
for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
        cin >> grid[i][j];
    }
}
```

可以理解为：`grid[行][列]`。

### 检查上下左右四个位置

```cpp
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

// 假设 (x, y) 是网格中的一个位置
for (int k = 0; k < 4; k++) {
    int nx = x + dx[k];
    int ny = y + dy[k];

    if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
        // 可以访问 grid[nx][ny]
    }
}
```

**先检查边界，再访问数组。**

### 📌5. 枚举两个或三个不同元素

### 枚举两个不同元素，不重复统计

```cpp
for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
        // 处理 a[i] 和 a[j]
    }
}
```

这里始终有 `i < j`。例如下标 0 和 1 只统计一次，不会再次统计 1 和 0。

### 枚举三个不同元素

```cpp
for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
        for (int k = j + 1; k < n; k++) {
            // 处理 a[i]、a[j]、a[k]
        }
    }
}
```

这里始终有 `i < j < k`。

两种写法分别为 `O(n²)` 和 `O(n³)`，使用前需要结合数据规模判断运算量。如果元素的先后顺序会影响结果，这些模板可能需要调整。

### 📌6. 布尔标记：bool

记录某个位置是否出现过，或某个条件是否成立。

```cpp
bool used[101] = {}; // 初始值全部为 false
used[5] = true;

if (used[5]) {
    cout << "出现过";
}
```

### 判断是否所有元素都满足条件

```cpp
vector<int> nums = {1, 2, -3, 4};
bool ok = true;

for (int x : nums) {
    if (x < 0) {
        ok = false;
        break;
    }
}
```

循环结束后，`ok` 表示是否所有元素都非负。`break` 用于发现不满足条件的元素后立即结束循环。

### 📌7. pair：把两个值放在一起

头文件：`<utility>`。

```cpp
pair<int, int> p = {3, 5};
cout << p.first;  // 3
cout << p.second; // 5
```

### 保存并排序坐标

```cpp
vector<pair<int, int>> points;
points.push_back({2, 3});
points.push_back({1, 5});
points.push_back({2, 1});

sort(points.begin(), points.end());
// 顺序：(1, 5)、(2, 1)、(2, 3)
```

默认排序规则：**先比较 first，相同时再比较 second，均为升序。**

### 📌8. struct 和自定义排序

一个对象有多个属性时，可以使用结构体。下面的结构体和比较函数应定义在 `main()` 外。

```cpp
struct Cow {
    int id;
    int score;
};

bool cmp(const Cow& a, const Cow& b) {
    if (a.score != b.score) {
        return a.score > b.score;
    }
    return a.id < b.id;
}
```

比较规则：按分数降序，分数相同时按编号升序。

### 在 main 中使用

```cpp
vector<Cow> cows = {
    {1, 80},
    {2, 90},
    {3, 90}
};

sort(cows.begin(), cows.end(), cmp);
// 顺序：编号 2、3、1
```

`cmp(a, b)` 返回 `true`，表示 **a 应排在 b 前面**。

注意：比较规则必须满足严格弱序，特别是 `cmp(a, a)` 必须为 `false`。不要直接用 `<=` 或 `>=` 作为排序比较规则。

### 📌9. set：自动去重

头文件：`<set>`。

```cpp
set<int> s;
s.insert(3);
s.insert(1);
s.insert(3);

cout << s.size();   // 2
cout << s.count(3); // 1：存在
cout << s.count(5); // 0：不存在
```

### 遍历

```cpp
for (int x : s) {
    cout << x << ' '; // 1 3
}
```

默认按升序遍历。普通 `set` 中同一个值最多保存一次，因此 `count` 的结果只能为 0 或 1。

### 删除元素

```cpp
s.erase(3); // 删除值为 3 的元素
```

常见用途：统计不同数字的数量、判断一个值是否出现过。插入、查找和按键删除通常为 `O(log n)`。

### 📌10. map：按名字或数值统计

头文件：`<map>`。

数值范围很大，或者需要使用字符串作为键时，可以使用 `map`。

```cpp
map<string, int> cnt;
cnt["Bessie"]++;
cnt["Elsie"]++;
cnt["Bessie"]++;

cout << cnt["Bessie"]; // 2
```

### 遍历所有键及其次数

以下结构化绑定写法需要 C++17：

```cpp
for (const auto& [name, times] : cnt) {
    cout << name << ' ' << times << '\n';
}
```

默认按键的升序遍历。字符串键按字典序排列。

注意：`cnt[key]` 在键不存在时会创建该键，并将这里的 `int` 值初始化为 0。

只判断键是否存在、无需创建键时，可以写：

```cpp
if (cnt.find("Bessie") != cnt.end()) {
    cout << "存在";
}
```

常见的按键插入、查找操作为 `O(log n)`。

### 📌11. 整数除法和取模：/、%

```cpp
cout << 17 / 5; // 3
cout << 17 % 5; // 2
```

两个整数相除时，结果向 0 截断。对于非负整数，可以理解为去掉小数部分。

### 判断偶数、获取个位和去掉个位

```cpp
int x = 1234;
bool even = (x % 2 == 0); // 判断偶数
int lastDigit = x % 10;   // 非负整数的个位：4
x /= 10;                 // 去掉非负整数的个位：123
```

### 循环移动

```cpp
pos = (pos + 1) % n; // n > 0，假设 0 <= pos < n
```

到最后一个位置后，下一个位置回到 0。

### 向上取整

对于非负整数 `a` 和正整数 `b`：

```cpp
long long a = 17, b = 5;
long long groups = a / b + (a % b != 0); // 4
```

例如 17 个物品，每组最多 5 个，需要 4 组。布尔表达式在这里参与加法时，`true` 对应 1，`false` 对应 0。

### 📌12. 简单前缀和：快速计算区间总和

### 构建前缀和

```cpp
vector<int> a = {2, 4, 1, 5};
int n = (int)a.size();
vector<long long> prefix(n + 1, 0);

for (int i = 0; i < n; i++) {
    prefix[i + 1] = prefix[i] + a[i];
}
```

`prefix[i]` 表示**前 i 个元素之和**。

| i    | prefix[i] | 含义            |
| ---- | --------- | --------------- |
| 0    | 0         | 前 0 个元素之和 |
| 1    | 2         | 2               |
| 2    | 6         | 2 + 4           |
| 3    | 7         | 2 + 4 + 1       |
| 4    | 12        | 2 + 4 + 1 + 5   |

### 查询区间总和

计算下标区间 `[l, r]` 的总和，其中 `0 <= l <= r < n`：

```cpp
int l = 1, r = 3;
long long sum = prefix[r + 1] - prefix[l]; // 4 + 1 + 5 = 10
```

公式：

```text
区间 [l, r] 的总和 = prefix[r + 1] - prefix[l]
```

构建前缀和需要 `O(n)`，之后每次查询只需要 `O(1)`。

### 速查表

| 内容          | 典型写法                        | 用途                   |
| ------------- | ------------------------------- | ---------------------- |
| long long     | `1LL * a * b`                   | 避免 int 乘法溢出      |
| 范围遍历      | `for (int x : a)`               | 读取元素               |
| 引用遍历      | `for (int& x : a)`              | 修改原元素             |
| 频率数组      | `cnt[x]++`                      | 统计出现次数           |
| 二维数组      | `grid[i][j]`                    | 存储网格               |
| 枚举组合      | `j = i + 1`                     | 枚举不同元素，避免重复 |
| bool          | `used[x] = true`                | 标记状态               |
| pair          | `p.first`、`p.second`           | 保存两个相关值         |
| struct 与排序 | `sort(v.begin(), v.end(), cmp)` | 按多个属性排序         |
| set           | `s.insert(x)`                   | 去重、判断存在         |
| map           | `cnt[key]++`                    | 按键统计               |
| 除法与取模    | `x / 10`、`x % 10`              | 拆分数字、周期计算     |
| 前缀和        | `prefix[r + 1] - prefix[l]`     | 快速查询区间总和       |
