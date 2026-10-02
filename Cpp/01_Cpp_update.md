## C++ 基础：USACO 铜组常用语法

本章使用 C++17，重点学习输入输出、数字类型、函数、数组、字符串、引用和结构体。

## 1. 基本输入输出

### 1.1 程序模板

```cpp
#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b;
    cin >> a >> b;
    cout << a + b << '\n';

    return 0;
}
```

- `cin >>` 读取数据，通常以空格或换行分隔。
- `cout <<` 输出数据。
- `'\n'` 输出换行；`' '` 输出空格。
- `main()` 是程序入口，`return 0;` 表示正常结束。
- 提交时只输出题目要求的内容，不添加“请输入”等提示语。

```cpp
cout << a << ' ' << b << '\n';
```

### 1.2 快速输入输出

```cpp
ios::sync_with_stdio(false);
cin.tie(nullptr);
```

放在 `main()` 的开头、任何输入输出之前：第一行关闭 C++ 流与 C 标准输入输出的同步；第二行解除读取前自动刷新 `cout` 的绑定。使用这套模板时统一使用 `cin/cout`。

`endl` 会换行并刷新输出缓冲区；普通竞赛输出通常使用 `'\n'` 即可。

练习较早的题目时，如果题目要求从指定文件输入、输出，应按题目要求处理。

## 2. 数字类型与运算

### 2.1 常用类型

| 类型 | 用途 | 示例 |
|---|---|---|
| `int` | 一般整数、下标、循环变量 | `int n = 100;` |
| `long long` | 较大的整数、总和、乘积 | `long long ans = 0;` |
| `double` | 平均值等浮点运算 | `double avg = 3.5;` |
| `char` | 单个字符 | `char c = 'A';` |
| `bool` | 是否满足条件 | `bool ok = true;` |

常见竞赛环境中，`int` 是 32 位，最大值约为 `2.1 × 10^9`；`long long` 是 64 位，最大值约为 `9.2 × 10^18`。选择类型前，需要估算计算过程和答案的范围。

### 2.2 整数除法与取模

```cpp
cout << 17 / 5 << '\n'; // 3
cout << 17 % 5 << '\n'; // 2
```

整数除法向 0 截断。对于非负整数，可以理解为舍去小数部分。除数不能为 0。

```cpp
int x = 1234;
bool even = (x % 2 == 0);
int lastDigit = x % 10; // 4，假设 x 非负
x /= 10;               // 123
```

### 2.3 小数除法

```cpp
double a = 7 / 2;   // 3.0：先做整数除法，再转换
double b = 7.0 / 2; // 3.5

int sum = 7, n = 2;
double avg = static_cast<double>(sum) / n; // 3.5
```

### 2.4 防止乘法溢出

```cpp
int a = 100000, b = 100000;
long long product = 1LL * a * b; // 10000000000
```

`1LL` 是 `long long` 类型的 1，使乘法从一开始就按 `long long` 计算。

下面的写法仍可能溢出，因为右边先按 `int` 相乘：

```cpp
long long product = a * b; // 不要这样计算可能超出 int 范围的乘积
```

求和也需要留意范围：

```cpp
long long sum = 0;
for (int i = 0; i < n; i++) {
    sum += a[i]; // 假设已定义数组 a 和长度 n
}
```

### 2.5 常量

```cpp
const int MAX_N = 100005;
const double PI = 3.141592653589793;
```

`const` 表示不能通过这个变量修改其值。数组容量必须满足题目的数据范围；如果采用从 1 开始的下标，应为下标 0 等位置预留空间。

### 2.6 常用数学函数

整数绝对值可引入 `<cstdlib>`；浮点数学函数引入 `<cmath>`。

| 函数 | 功能 | 示例 |
|---|---|---|
| `abs(x)` | 整数绝对值 | `abs(-5)` 得到 5 |
| `sqrt(x)` | 平方根 | `sqrt(9.0)` 得到 3.0 |
| `floor(x)` | 向下取整，返回浮点值 | `floor(-2.3)` 得到 -3.0 |
| `ceil(x)` | 向上取整，返回浮点值 | `ceil(2.3)` 得到 3.0 |

`pow` 属于浮点计算。整数平方通常直接使用 `1LL * x * x`，避免不必要的浮点转换和精度问题。

对于非负整数 `a` 和正整数 `b`，可以直接用整数运算向上取整：

```cpp
long long groups = a / b + (a % b != 0);
```

## 3. 函数

### 3.1 定义与调用

函数将一段操作组织起来，便于重复调用。

```cpp
#include <iostream>
using namespace std;

int add(int a, int b) {
    return a + b;
}

int main() {
    int result = add(3, 5);
    cout << result << '\n'; // 8
    return 0;
}
```

一般形式：

```cpp
返回类型 函数名(参数列表) {
    // 操作
    return 返回值;
}
```

`a`、`b` 是形参；调用时传入的 `3`、`5` 是实参。

### 3.2 没有返回值：void

```cpp
void printAnswer(int answer) {
    cout << answer << '\n';
}
```

该函数执行输出，但不返回可用于计算的值。可以用 `return;` 提前结束 `void` 函数。

### 3.3 条件判断与提前返回

```cpp
bool isEven(int x) {
    return x % 2 == 0;
}

int larger(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}
```

执行 `return` 后，当前函数立即结束。返回非 `void` 的普通函数，应确保每条正常执行路径都能返回相应类型的值。

### 3.4 作用域与函数声明

函数中的局部变量只能在相应作用域内使用，不会自动成为其他函数的变量。

```cpp
int add(int a, int b) {
    int result = a + b;
    return result;
}
// 在这个函数外，不能直接使用它的局部变量 result
```

可以将函数定义放在 `main()` 前。如果定义放在调用之后，需要先声明：

```cpp
int add(int a, int b); // 声明

int main() {
    cout << add(3, 5) << '\n';
    return 0;
}

int add(int a, int b) { // 定义
    return a + b;
}
```

## 4. 数组与 vector

### 4.1 一维数组

```cpp
int a[5] = {1, 2, 3, 4, 5};
cout << a[0]; // 1
cout << a[4]; // 5
```

长度为 `n` 的数组，下标范围是 `0` 到 `n - 1`。

```cpp
int cnt[101] = {}; // 全部初始化为 0
```

函数内的普通数组如果没有初始化，其整数元素不能直接当作 0 使用。

### 4.2 数组遍历

```cpp
for (int i = 0; i < 5; i++) {
    cout << a[i] << ' ';
}
```

### 4.3 vector：长度可变的数组

需要 `<vector>`。

```cpp
vector<int> a(5, 0); // 5 个元素，初始值为 0
a[0] = 10;
a.push_back(20);    // 末尾添加元素，长度变为 6

cout << a.size();   // 6
cout << a.back();   // 20
```

根据输入长度创建：

```cpp
int n;
cin >> n;
vector<int> a(n);
for (int i = 0; i < n; i++) {
    cin >> a[i];
}
```

范围遍历：

```cpp
for (int x : a) {
    cout << x << ' ';
}

for (int& x : a) {
    x *= 2; // 修改原元素
}
```

### 4.4 二维数组

```cpp
int grid[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};

cout << grid[1][2]; // 第 2 行第 3 列：6
```

二维数组写作 `grid[行][列]`，两个下标都从 0 开始。

遍历并输出：

```cpp
for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        cout << grid[i][j] << ' ';
    }
    cout << '\n';
}
```

根据输入创建二维 vector：

```cpp
int n, m;
cin >> n >> m;
vector<vector<int>> grid(n, vector<int>(m, 0));

for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
        cin >> grid[i][j];
    }
}
```

访问上下左右时，先检查边界：

```cpp
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

// 假设 (x, y) 是当前格子的行、列
for (int k = 0; k < 4; k++) {
    int nx = x + dx[k];
    int ny = y + dy[k];
    if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
        // 此处可以访问 grid[nx][ny]
    }
}
```

### 4.5 频率数组

```cpp
int cnt[101] = {};
int n;
cin >> n;

for (int i = 0; i < n; i++) {
    int x;
    cin >> x; // 假设 0 <= x <= 100
    cnt[x]++;
}

cout << cnt[5]; // 5 出现的次数
```

只有当数值能够安全地作为数组下标时，才能直接使用这一写法。

## 5. 字符串 string

需要 `<string>`。

### 5.1 定义、复制、拼接和长度

```cpp
string a = "USACO";
string b = a;
string c = a + " Bronze";

cout << a.size() << '\n'; // 5
cout << c << '\n';        // USACO Bronze
```

### 5.2 字符与下标

```cpp
string s = "cow";
cout << s[0]; // c
s[0] = 'C';  // s 变为 Cow

for (char c : s) {
    cout << c << '\n';
}
```

`'C'` 是单个字符，`"C"` 是字符串字面量。字符串元素的有效下标为 `0` 到 `s.size() - 1`。

### 5.3 输入单词与整行

```cpp
string word;
cin >> word; // 遇到空白时停止
```

```cpp
string line;
getline(cin, line); // 读取一整行，可包含空格
```

前面使用过 `cin >>` 时，若允许跳过空行和行首空格，可以写：

```cpp
getline(cin >> ws, line);
```

### 5.4 比较字符串

```cpp
string a = "cow", b = "cow";
if (a == b) {
    cout << "相同";
}
```

`string` 支持按字典序比较：例如 `"abc" < "abd"`，以及 `"ab" < "abc"`。

### 5.5 截取与查找

```cpp
string s = "abcdef";
cout << s.substr(2, 3); // cde：从下标 2 开始取 3 个字符
cout << s.substr(2);    // cdef：取到结尾

size_t pos = s.find("cd");
if (pos != string::npos) {
    cout << pos; // 2
}
```

`substr` 的第二个参数是字符数量。起点大于字符串长度时会抛出异常。`find` 找不到时返回 `string::npos`。

### 5.6 字母统计

```cpp
string s = "banana";
int cnt[26] = {};
for (char c : s) {
    cnt[c - 'a']++;
}
cout << cnt['a' - 'a']; // 3
```

该模板假设输入只包含小写英文字母。

## 6. 引用与函数参数

### 6.1 引用是别名

```cpp
int a = 10;
int& ref = a;
ref = 20;
cout << a; // 20
```

`ref` 与 `a` 对应同一个对象。普通局部引用定义时需要初始化，之后不能重新绑定到另一个对象。

### 6.2 值传递

```cpp
void change(int x) {
    x = 100;
}
```

```cpp
int a = 10;
change(a);
cout << a; // 10：修改的是参数副本
```

### 6.3 引用传递

```cpp
void change(int& x) {
    x = 100;
}
```

```cpp
int a = 10;
change(a);
cout << a; // 100
```

### 6.4 vector 参数

| 参数写法 | 调用时是否复制传入的 vector | 能否通过参数修改原元素 |
|---|---|---|
| `vector<int> a` | 是 | 否，修改的是副本 |
| `vector<int>& a` | 否 | 能 |
| `const vector<int>& a` | 否 | 不能 |

只读取时，常用 `const` 引用避免复制：

```cpp
long long getSum(const vector<int>& a) {
    long long sum = 0;
    for (int x : a) {
        sum += x;
    }
    return sum;
}
```

需要修改时，使用普通引用：

```cpp
void doubleValues(vector<int>& a) {
    for (int& x : a) {
        x *= 2; // 假设结果不会超出 int 范围
    }
}
```

### 6.5 普通数组传给函数

```cpp
long long getSum(const int a[], int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum;
}
```

```cpp
int a[] = {1, 2, 3};
cout << getSum(a, 3); // 6
```

这种数组形参实际按指针处理，长度需单独传入。`int a[10]` 作为函数形参时，也不会强制要求实参长度为 10。省略 `const` 后，通过形参修改元素会影响原数组。

### 6.6 返回 vector

```cpp
vector<int> createArray(int n) {
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = i + 1;
    }
    return a;
}
```

```cpp
vector<int> a = createArray(5); // {1, 2, 3, 4, 5}
```

返回 vector 的值是安全的；不要返回普通局部数组的地址或普通局部变量的引用，它们会在函数结束后失效。

## 7. 结构体与排序

### 7.1 将相关数据组合起来

结构体定义通常放在 `main()` 前。

```cpp
struct Cow {
    int id;
    int score;
};
```

创建对象并访问成员：

```cpp
Cow cow = {1, 90};
cout << cow.id << ' ' << cow.score << '\n';
```

使用 `.` 访问对象的成员。

### 7.2 结构体数组和 vector

```cpp
Cow cows[3] = {{1, 80}, {2, 90}, {3, 90}};
cout << cows[0].score; // 80
```

```cpp
vector<Cow> cows = {{1, 80}, {2, 90}, {3, 90}};
cows.push_back({4, 85});
```

### 7.3 自定义排序

需要 `<algorithm>`。完整示例：

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Cow {
    int id;
    int score;
};

bool cmp(const Cow& a, const Cow& b) {
    if (a.score != b.score) {
        return a.score > b.score; // 分数降序
    }
    return a.id < b.id; // 同分时编号升序
}

int main() {
    vector<Cow> cows = {{1, 80}, {2, 90}, {3, 90}};
    sort(cows.begin(), cows.end(), cmp);

    for (const Cow& cow : cows) {
        cout << cow.id << ' ' << cow.score << '\n';
    }
    return 0;
}
```

输出：

```text
2 90
3 90
1 80
```

`cmp(a, b)` 为 `true` 表示 a 应排在 b 前。比较规则必须满足严格弱序；相同对象与自身比较应返回 `false`，不能直接用 `<=` 或 `>=` 作为排序规则。

## 8. Lambda 表达式

Lambda 适合临时定义一小段函数。先掌握普通函数，再学习这一写法。

### 8.1 基本写法

```cpp
auto add = [](int a, int b) {
    return a + b;
};

cout << add(3, 5); // 8
```

`[]` 表示不捕获外层局部变量，不影响定义参数或函数体内的局部变量。

### 8.2 用于排序

下面代码可替换上一节中的比较函数调用：

```cpp
sort(cows.begin(), cows.end(), [](const Cow& a, const Cow& b) {
    if (a.score != b.score) {
        return a.score > b.score;
    }
    return a.id < b.id;
});
```

### 8.3 简单捕获

```cpp
int limit = 10;
auto largerThanLimit = [limit](int x) {
    return x > limit;
};
cout << largerThanLimit(12); // 1
```

`[limit]` 捕获 limit 的副本；`[&limit]` 捕获其引用。引用捕获要求被引用对象在使用 Lambda 时仍然有效。复杂捕获组合可以在后续需要时学习。

## 9. 理解基础指针与算法范围

### 9.1 地址与解引用

```cpp
int x = 10;
int* p = &x;

cout << *p; // 10
*p = 20;
cout << x;  // 20
```

- `&x` 取得对象 x 的地址。
- `p` 保存地址。
- `*p` 访问指针指向的对象。
- 声明 `int& ref = x` 中的 `&` 表示引用，与表达式 `&x` 的取地址作用不同。

空指针使用 `nullptr`：

```cpp
int* p = nullptr;
```

不能解引用空指针、未初始化指针或已经失效的指针。

### 9.2 为什么 sort 使用 a + n

```cpp
int a[] = {3, 1, 2};
sort(a, a + 3);
```

在这里，`a` 转换为指向首元素的指针；`a + 3` 指向最后一个元素之后的位置。标准算法通常使用左闭右开范围 `[begin, end)`，尾后位置可以作为范围边界，但不能解引用。

vector 对应的写法是：

```cpp
sort(v.begin(), v.end());
```

铜组基础阶段掌握这些概念即可；多级指针、指针数组和手动动态内存管理可以后移。

## 10. 课堂练习

1. 输入两个 int 范围内的非负整数，使用函数返回它们的 long long 乘积。
2. 输入 n 个整数，用 `const vector<int>&` 参数计算总和。
3. 输入只含小写字母的字符串，统计每个字母出现的次数。
4. 输入 n 行 m 列的网格，输出每行的元素总和。
5. 输入若干头牛的编号和分数，按分数降序、编号升序输出。
6. 编写函数接收 `vector<int>&`，将所有元素增加 1，并验证调用后原 vector 改变。

## 本章速查

| 内容 | 关键写法 |
|---|---|
| 快速输入输出 | `ios::sync_with_stdio(false); cin.tie(nullptr);` |
| 大整数乘法 | `1LL * a * b` |
| 小数除法 | `static_cast<double>(sum) / n` |
| 数组初始化 | `int a[100] = {};` |
| 二维网格 | `grid[row][col]` |
| 字符串长度 | `s.size()` |
| 截取子串 | `s.substr(pos, len)` |
| 引用参数 | `void change(int& x)` |
| 只读 vector 参数 | `const vector<int>& a` |
| 返回一组数据 | `vector<int> createArray(int n)` |
| 自定义排序 | `sort(v.begin(), v.end(), cmp)` |
