## C++ STL：标准库与常用工具

本章知识点：标准库与模板、vector 示例、优先队列、迭代器、数学函数、deque、list、map、bitset、string、utility，以及 lower_bound/upper_bound。

### 1. 标准库与 STL

C++ 标准库提供输入输出、字符串、容器和算法等工具。STL 通常指其中的容器、迭代器、算法、函数对象和适配器等设施，并不等同于整个标准库。

- **容器**：保存数据，例如 vector、deque、list、map。
- **迭代器**：表示位置，用于遍历容器和指定算法范围。
- **算法**：处理数据，例如排序、查找。
- **函数对象**：可以像函数一样调用的对象，例如优先队列的比较器。
- **容器适配器**：在底层容器之上提供特定接口，例如 priority_queue。

### vector 示例

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v;
    for (int i = 0; i < 5; i++) {
        v.push_back(i);
    }

    cout << v.size() << '\n'; // 5
    for (int x : v) {
        cout << x << ' '; // 0 1 2 3 4
    }
    cout << '\n';
    return 0;
}
```

### 2. 标准库头文件

使用某个工具前，包含提供它的头文件，不依赖其他头文件间接包含它。

| 头文件 | 提供的主要工具 |
|---|---|
| `<iostream>` | cin、cout |
| `<fstream>` | 文件输入输出 |
| `<sstream>` | 字符串流 |
| `<array>` | 定长数组容器 |
| `<vector>` | 动态数组 |
| `<deque>` | 双端队列 |
| `<list>`、`<forward_list>` | 双向链表、单向链表 |
| `<stack>` | 栈适配器 |
| `<queue>` | 队列、优先队列适配器 |
| `<set>`、`<map>` | 有序集合、映射 |
| `<unordered_set>`、`<unordered_map>` | 哈希集合、映射 |
| `<bitset>` | 固定长度位集合 |
| `<algorithm>` | 排序、查找等算法 |
| `<iterator>` | advance 等迭代器工具 |
| `<numeric>` | 数值算法 |
| `<complex>`、`<valarray>` | 复数、数值数组 |
| `<cmath>` | 数学函数 |
| `<string>` | 字符串 |
| `<regex>` | 正则表达式 |
| `<utility>` | pair、swap、move、forward |
| `<functional>` | greater 等函数对象 |

该表用于查阅，无需在入门阶段逐项展开。

### bits/stdc++.h

```cpp
#include <bits/stdc++.h>
```

这是 GCC/libstdc++ 环境提供的非标准头文件，会包含大量标准库头文件。在支持它的竞赛环境中可以使用，但并非所有编译环境都支持，且可能增加编译时间。

### 3. 函数模板

模板可以让同一段代码处理满足相应操作要求的多种类型，并非任意类型。

```cpp
#include <iostream>
#include <string>
using namespace std;

template <typename T>
T add(T a, T b) {
    return a + b;
}

int main() {
    cout << add(3, 5) << '\n';       // 8
    cout << add(3.2, 4.8) << '\n';   // 8
    cout << add<string>("Hi, ", "C++") << '\n'; // Hi, C++
    return 0;
}
```

- T 是类型参数，通常由实参推导，也可以显式指定。
- 这里要求 T 支持加法，且结果能作为 T 返回。
- `add(3, 4.5)` 无法直接推导出一致的 T；可写 `add<double>(3, 4.5)`。
- 原例中的 `int add(){}`、`float add(){}`、`double add(){}` 应删除：仅返回类型不同不能构成函数重载。

### 4. priority_queue：优先队列

需要 `<queue>`。默认使用 vector 作为底层容器，是最大堆，每次访问当前最大元素。

### 4.1 最大堆

```cpp
priority_queue<int> pq;
pq.push(4);
pq.push(3);
pq.push(2);
pq.push(1);

cout << pq.top(); // 4
pq.pop();
cout << pq.top(); // 3
```

### 4.2 最小堆

引入 `<vector>` 和 `<functional>`：

```cpp
priority_queue<int, vector<int>, greater<int>> pq;
pq.push(4);
pq.push(2);
pq.push(1);
cout << pq.top(); // 1
```

也可以使用原章的函数对象写法：

```cpp
struct Compare {
    bool operator()(int a, int b) const {
        return a > b;
    }
};
```

在 main 中声明：

```cpp
priority_queue<int, vector<int>, Compare> pq;
```

比较器返回 true 表示 a 的优先级低于 b；这里较大的数优先级较低，因此形成最小堆。该例的元素仍是 int，自定义的是比较器，而不是元素类型。

### 4.3 常用接口

| 接口 | 功能 | 复杂度 |
|---|---|---|
| empty、size | 判断为空、获取数量 | O(1) |
| top | 访问堆顶 | O(1) |
| push | 插入元素 | 均摊 O(log n) |
| pop | 删除堆顶 | O(log n) |

默认底层 vector 的单次扩容可能带来 O(n) 开销。`top` 和 `pop` 要求非空，`pop` 不返回被删除的值。

### 5. 迭代器

### 5.1 遍历 vector

```cpp
vector<int> v = {1, 2, 3};
for (auto it = v.begin(); it != v.end(); ++it) {
    cout << *it << ' ';
}
```

- begin 指向首元素；空容器的 begin 等于 end。
- end 是尾后位置，不能解引用。
- `*it` 访问元素，`++it` 移动到下一位置。
- auto 根据初始化表达式推导类型。

只读取每个值时也可用范围 for：

```cpp
for (int x : v) {
    cout << x << ' ';
}
```

### 5.2 不同容器的迭代器能力

vector 的迭代器支持加减和计算距离；list、map 的迭代器不支持 `it + 2` 或迭代器相减。

`advance` 需要 `<iterator>`：

```cpp
list<int> values = {10, 20, 30};
auto it = values.begin();
advance(it, 2);
cout << *it; // 30
```

对 list 逐步移动 k 个位置需要 O(k)，不能认为定位任意位置都为 O(1)。移动时也必须确保范围有效。

### 6. cmath：数学函数

浮点数学函数需要 `<cmath>`；整数 abs 可明确包含 `<cstdlib>`。

| 函数 | 功能 | 示例 |
|---|---|---|
| **abs** | 绝对值，有多种类型重载 | `abs(-5)` → 5 |
| fabs | 浮点绝对值 | `fabs(-5.5)` → 5.5 |
| **sqrt** | 平方根 | `sqrt(16.0)` → 4.0 |
| cbrt | 立方根 | `cbrt(27.0)` → 约 3.0 |
| **ceil** | 向上取整，返回浮点值 | `ceil(2.3)` → 3.0 |
| **floor** | 向下取整，返回浮点值 | `floor(-2.3)` → -3.0 |
| **pow** | 幂运算 | `pow(4.0, 2.0)` → 16.0 |
| fmod | 浮点余数 | `fmod(5.3, 2.0)` → 约 1.3 |
| fmax、fmin | 浮点最大、最小值 | `fmax(3.5, 4.2)` → 4.2 |
| sin、cos、tan | 三角函数，参数为弧度 | `sin(0.0)` → 0.0 |

优先掌握 abs、sqrt、ceil、floor，其他函数按题目需要查阅。浮点计算可能有误差，整数幂不宜依赖 pow 进行精确的大整数计算。

```cpp
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

int main() {
    cout << abs(-5) << '\n';
    cout << sqrt(16.0) << '\n';
    cout << ceil(2.3) << ' ' << floor(2.3) << '\n';
    return 0;
}
```

### 7. deque：双端队列

需要 `<deque>`。支持两端插入、删除和下标访问。

```cpp
deque<int> d;
d.push_back(10);
d.push_back(20);
d.push_front(5); // {5, 10, 20}

cout << d.front(); // 5
cout << d.back();  // 20
cout << d[1];     // 10

d.front() = 15;
d.back() = 25;    // {15, 10, 25}
d.pop_front();
d.pop_back();    // {10}
```

两端插入、删除与下标访问为 O(1)；中间插入、删除为 O(n) 上界。访问或删除端点要求非空。

```cpp
for (int x : d) {
    cout << x << ' ';
}
```

### 8. list：双向链表

需要 `<list>`。了解与 vector 的区别即可，铜组阶段不必花大量时间练习所有接口。

### 8.1 初始化与两端操作

```cpp
list<int> a;
list<int> b(5);     // 5 个 0
list<int> c(5, 10); // 5 个 10
list<int> values = {10, 20, 30};

values.push_front(5);
values.push_back(40);
values.pop_front();
values.pop_back(); // 恢复为 {10, 20, 30}

cout << values.front(); // 10
cout << values.back();  // 30
```

### 8.2 指定位置插入和删除

```cpp
list<int> values = {1, 2, 3, 4, 5};
auto it = values.begin();
advance(it, 2);         // 指向原来的 3，需要 <iterator>
values.insert(it, 10); // {1, 2, 10, 3, 4, 5}，it 仍指向 3
it = values.erase(it); // {1, 2, 10, 4, 5}，it 指向 4
```

原注释“删除第三个元素”不准确：插入后第三个元素是 10，旧 it 指向的 3 已变成第四个元素。

已知有效迭代器时，单元素插入、删除为 O(1)；查找或定位该位置可能需要 O(n)。被删除元素的迭代器失效。

### 8.3 排序、去重、合并、反转

```cpp
list<int> values = {1, 2, 3, 5, 4, 4};
values.sort();   // {1, 2, 3, 4, 4, 5}
values.unique(); // {1, 2, 3, 4, 5}
```

list 的 unique 直接删除连续重复元素。想去除所有重复值，可先排序；排序会改变原顺序。

```cpp
list<int> a = {1, 3, 5};
list<int> b = {2, 4, 6};
a.merge(b); // a = {1, 2, 3, 4, 5, 6}，b 为空
a.reverse(); // {6, 5, 4, 3, 2, 1}
```

merge 要求两个链表已按相同规则排序。list 使用成员 sort，不能使用要求随机访问迭代器的通用 sort。

| 接口 | 功能 |
|---|---|
| push_front、push_back | 两端插入 |
| pop_front、pop_back | 两端删除，要求非空 |
| insert、erase | 在迭代器位置插入、删除 |
| remove(x) | 删除全部等于 x 的元素 |
| clear、size、empty | 清空、数量、判空 |
| front、back | 访问端点，要求非空 |
| sort、unique、merge、reverse | 排序、连续去重、合并、反转 |
| begin、end | 获取首位置、尾后位置 |

### 容器对比

| 特性 | vector | deque | list |
|---|---|---|---|
| 存储 | 连续 | 通常分段存储，不保证整体连续 | 链表节点 |
| 下标访问 | O(1) | O(1) | 不支持 |
| 两端操作 | 末尾高效，头部需移动元素 | 两端高效 | 两端高效 |
| 中间插入、删除 | 通常 O(n) | O(n) 上界 | 已有位置时单元素操作 O(1)，定位另算 |
| 迭代器 | 扩容时全部失效 | 失效规则依操作而定 | 插入不影响现有迭代器，删除仅使被删元素迭代器失效 |

### 9. map：有序键值对

需要 `<map>`；字符串键需要 `<string>`。默认按键的升序遍历，通常由平衡搜索树实现，无需先学习其底层结构。

### 9.1 插入、更新与计数

```cpp
map<string, int> scores;
scores["Alice"] = 90;
scores["Bob"] = 85;
scores.insert({"Charlie", 92});
```

`insert` 不会覆盖已存在的键；`scores[key] = value` 可以更新。

```cpp
map<string, int> cnt;
cnt["Bessie"]++;
cnt["Bessie"]++;
cout << cnt["Bessie"]; // 2
```

下标操作在键不存在时插入新键，这里的 int 值初始化为 0。

### 9.2 遍历、查找、删除

```cpp
for (const auto& p : scores) {
    cout << p.first << ' ' << p.second << '\n';
}

auto it = scores.find("Bob");
if (it != scores.end()) {
    cout << it->second; // 85
}
scores.erase("Alice");
cout << scores.size(); // 2
```

first 是键，second 是值。find 找不到返回 end；只判断是否存在时，使用 find 可以避免下标操作新增键。常用按键插入、查找、删除为 O(log n)。

### 10. bitset：固定长度位集合

需要 `<bitset>`，长度为编译期常量。最右边对应下标 0。

```cpp
bitset<8> a;               // 00000000
bitset<8> b(42);           // 00101010
bitset<8> c("10101010");   // 10101010

bitset<8> bits("00001111");
bits[0] = 1;   // 00001111
bits.set(4);   // 00011111
bits.reset(1); // 00011101
bits.flip();   // 11100010
```

| 接口 | 功能 |
|---|---|
| count | 1 的数量 |
| size | 位数 |
| test(pos) | 某位是否为 1 |
| all、any、none | 是否全为 1、存在 1、全为 0 |
| set、reset、flip | 设为 1、设为 0、翻转；可操作指定位置或全部位 |
| to_ulong、to_ullong | 转为对应无符号整数，装不下会抛出异常 |
| to_string | 转为由 0 和 1 组成的字符串 |

### 位运算

```cpp
bitset<8> a("10101010"), b("11110000");
cout << (a & b); // 10100000：与
cout << (a | b); // 11111010：或
cout << (a ^ b); // 01011010：异或
cout << (~a);    // 01010101：取反
```

位下标必须有效。按下标从 0 到 size - 1 遍历，是从低位到高位，与直接输出 bitset 的显示顺序相反。

```cpp
for (size_t i = 0; i < a.size(); i++) {
    cout << a[i]; // 01010101
}
```

### 11. string：常用成员函数

需要 `<string>`。对竞赛中的 ASCII 输入，size 可以理解为字符数；UTF-8 中文字符串的 size 统计 char 单元数，不是中文字符个数。

### 11.1 长度、判空、访问与拼接

```cpp
string s = "Hello";
cout << s.size();   // 5，length 同义
cout << s.empty();  // 0
cout << s[0];      // H
cout << s.at(1);   // e，越界时抛出异常
s += " World";
s.append("!");    // Hello World!
```

访问实际字符时，下标应小于 size。使用 `==`、`<` 等运算符可进行内容比较，关系比较按字典序。

### 11.2 substr、find 与 rfind

```cpp
string s = "abcabc";
cout << s.substr(1, 3); // bca，从下标 1 取 3 个字符
cout << s.find("bc");  // 1
cout << s.rfind("bc"); // 4，最后一次出现
```

find 系列找不到时返回 `string::npos`：

```cpp
size_t pos = s.find("xyz");
if (pos != string::npos) {
    cout << pos;
}
```

substr 的起点大于 size 时抛出异常，数量超过剩余字符数时取到结尾。

### 11.3 insert、erase、replace、clear

```cpp
string s = "abcdef";
s.insert(2, "XY");  // abXYcdef
s.erase(2, 2);       // abcdef
s.replace(2, 3, "Q"); // abQf
s.clear();          // 空字符串
```

erase 和 replace 的第二个参数是处理的字符数量，不是结束下标。操作后后续下标可能变化；反复中间插入、删除可能带来较高的总开销。

### 11.4 按字符集合查找（查阅）

```cpp
string s = "Hello";
cout << s.find_first_of("aeiou");     // 1
cout << s.find_last_of("aeiou");      // 4
cout << s.find_first_not_of("aeiou"); // 0
cout << s.find_last_not_of("aeiou");  // 3
```

of 表示匹配集合中的任意字符，不是匹配整个子串；not_of 表示找不属于集合的字符。找不到时同样返回 npos。

### 11.5 compare、c_str、data（选学）

```cpp
string s = "abc";
int result = s.compare("abd"); // 小于 0，不保证恰好是 -1
const char* p = s.c_str();
const char* q = s.data();
```

compare 返回负数、0、正数分别表示小于、相等、大于。c_str 提供以空字符结尾的字符数组视图；C++17 的 data 也提供字符数据访问，非 const string 的 data 可返回 char*。字符串修改后，先前取得的指针可能失效。

铜组基础阶段优先掌握前 3 小节，其余接口按需查阅。

### 12. utility：pair、swap 与 move

### 12.1 pair 与 make_pair

```cpp
pair<int, string> p = {1, "hello"};
cout << p.first << ' ' << p.second;
//vector<pair<int,int>>cows;
//cow.push_back({x,y});
//tuple<int,int,int>Three_D;
//Three_D.push_back({x,y,z});
auto q = make_pair(1, string("hello")); // pair<int, string>
```

`make_pair(1, "hello")` 的类型是 `pair<int, const char*>`。如果希望保存和比较字符串内容，明确使用 string。

### 12.2 swap

```cpp
int a = 5, b = 10;
swap(a, b); // a = 10，b = 5
```

### 12.3 move（选学）

```cpp
vector<int> v1 = {1, 2, 3};
vector<int> v2 = std::move(v1);
cout << v2.size(); // 3
```

move 本身不搬运数据，而是将表达式转换为可供移动操作使用的形式。这里用于调用 vector 的移动构造函数。

不要把“移动后源对象一定为空”当作一般规则。移动后的对象通常仍有效，但状态未指定；若还需原来的内容，应正常复制。forward 用于完美转发，铜组阶段知道名称即可。

### 13. lower_bound 与 upper_bound

需要 `<algorithm>`。函数名为 **lower_bound**，不是 low_bound。以下默认比较方式的示例要求范围已按升序排列。

| 函数 | 找到的位置 |
|---|---|
| lower_bound(begin, end, x) | 第一个大于等于 x 的元素 |
| upper_bound(begin, end, x) | 第一个大于 x 的元素 |

范围是 `[begin, end)`，包含起点，不包含终点。找不到符合条件的元素时返回 end。

### 13.1 普通数组

```cpp
int a[6] = {1, 2, 2, 2, 4, 6};
int n = 6;
int l = lower_bound(a, a + n, 2) - a; // 1
int r = upper_bound(a, a + n, 2) - a; // 4
cout << r - l; // 2 出现 3 次
```

返回的是指针或迭代器，减去起点得到下标。

### 13.2 vector

```cpp
vector<int> a = {1, 2, 2, 2, 4, 6};
auto it = lower_bound(a.begin(), a.end(), 2);
if (it != a.end()) {
    cout << *it; // 2
}
```

目标不存在时，lower_bound 仍可能找到更大的值：

```cpp
auto it = lower_bound(a.begin(), a.end(), 3);
// 指向 4，不表示找到了 3
```

判断目标是否存在，需要同时检查相等：

```cpp
int x = 3;
auto it = lower_bound(a.begin(), a.end(), x);
bool exists = (it != a.end() && *it == x);
```

### 13.3 找不到符合条件的元素

```cpp
auto it = lower_bound(a.begin(), a.end(), 10);
int index = it - a.begin(); // 等于 a.size()
```

此时不能读取 `*it` 或 `a[index]`。普通数组和 vector 上，这两个查找的时间复杂度均为 O(log n)。

记忆：lower 找 >=，upper 找 >。
