## USACO 铜组：结构体、记录排序与模拟

### 一、什么是 `struct`？

`struct`（结构体）是一种**自定义数据类型**，可以把多个相关的数据组合成一个整体。

例如，一个人的姓名、年龄、成绩属于同一个对象：

```cpp
struct Person {
    string name;
    int age = 0;
    double score = 0;
}; // 注意分号
```

它定义的是一种名为 `Person` 的类型，**还没有创建某个具体的人**。

### ✔️ 定义类型与创建变量

```cpp
Person p1;
p1.name = "Alice";
p1.age = 18;
p1.score = 95.5;

cout << p1.name << ' ' << p1.age << ' ' << p1.score << '\n';
```

使用 `.` 访问成员，读作“对象的某个属性”。

| 表达式 | 含义 |
|---|---|
| `Person` | 类型名 |
| `p1` | 该类型的一个变量 |
| `p1.name` | `p1` 的姓名 |
| `p1.age` | `p1` 的年龄 |

### ✔️ 花括号初始化

```cpp
Person p2{"Bob", 20, 88.0};
```

值按照成员的**声明顺序**依次对应：`name`、`age`、`score`。

```cpp
Person p3{};  // name 为空字符串；age、score 使用上面声明的默认值 0
```

### ❗ 局部变量不一定自动为零

如果成员没有默认值：

```cpp
struct Point {
    int x;
    int y;
};

Point a;         // 局部变量：x、y 未初始化，不要直接读取
Point b{};       // x、y 都为 0
Point c{2, 5};   // x 为 2，y 为 5
```

养成初始化习惯，不依赖“这次运行恰好是零”。

### 完整示例

```cpp
// program: person_demo
#include <bits/stdc++.h>
using namespace std;

struct Person {
    string name;
    int age = 0;
    double score = 0;
};

int main() {
    Person p1;
    p1.name = "Alice";
    p1.age = 18;
    p1.score = 95.5;

    Person p2{"Bob", 20, 88.0};

    cout << p1.name << ' ' << p1.age << ' ' << p1.score << '\n';
    cout << p2.name << ' ' << p2.age << ' ' << p2.score << '\n';
    return 0;
}
```

```text
输出：
Alice 18 95.5
Bob 20 88
```

这里 `88.0` 输出为 `88` 是默认浮点格式的表现。若题目要求固定一位小数，可使用 `fixed << setprecision(1)`。

## 二、结构体数组与 `vector`

### ✔️ 固定大小的数组

```cpp
Person people[3] = {
    {"Tom", 17, 89.5},
    {"Jerry", 18, 92.0},
    {"Mike", 19, 85.0}
};

cout << people[1].name << '\n'; // Jerry
```

`people[i]` 是一个完整的 `Person`，`people[i].score` 才是其中的成绩。

### ✔️ 动态数组

```cpp
int n;
cin >> n;
vector<Person> people(n);

for (int i = 0; i < n; i++) {
    cin >> people[i].name >> people[i].age >> people[i].score;
}
```

也可以从空 `vector` 开始逐条添加：

```cpp
vector<Person> people;
people.push_back({"Alice", 18, 95.5});
people.push_back({"Bob", 20, 88.0});
```

这两种方式要分清：

- `vector<Person> people(n)` 已经有 `n` 个元素，可以使用下标 `0 ~ n-1`。
- `vector<Person> people` 初始为空，不能直接写 `people[0]`，应先添加元素或调整大小。

### ✔️ 范围循环：复制与引用

```cpp
for (auto person : people) {
    person.age++; // 修改副本，不会修改 people 中的元素
}

for (auto &person : people) {
    person.age++; // 引用：修改原元素
}

for (const auto &person : people) {
    cout << person.name << '\n'; // 只读，不复制，也不允许修改
}
```

## 三、函数传参：什么时候需要 `&`？

```cpp
void birthday(Person person) {
    person.age++; // 值传递：只修改副本
}

void birthdayInPlace(Person &person) {
    person.age++; // 引用传递：修改调用者的对象
}

void printPerson(const Person &person) {
    cout << person.name << ' ' << person.age << '\n';
}
```

| 参数形式 | 是否复制 | 是否能通过参数修改原对象 |
|---|---|---|
| `Person person` | 是 | 否 |
| `Person &person` | 否 | 是 |
| `const Person &person` | 否 | 否 |

**需要更新物体状态时用引用；只读取记录时通常用 `const` 引用。**

注意：这里的 `&` 是声明引用，不是要求在调用时写 `&p1`。

```cpp
birthdayInPlace(p1); // 正确
```

## 四、结构体排序：必须说清楚谁排在前面

### 为什么不能只排序其中一个属性？

假设学生记录为：

| 学号 | 姓名 | 成绩 |
|---|---|---|
| 1 | Alice | 80 |
| 2 | Bob | 95 |

如果只把成绩数组排成 `95、80`，而姓名数组不变，就会错误地认为 Alice 得了 `95`。

结构体排序会把**整条记录一起移动**，避免姓名、成绩错配。

### ✔️ 单关键字排序

```cpp
bool compareByScore(const Person &a, const Person &b) {
    return a.score > b.score; // 分数高的排前面
}

sort(people.begin(), people.end(), compareByScore);
```

比较函数返回 `true`，表示 **`a` 应当排在 `b` 前面**，不是“是否要交换”。

### ✔️ 多关键字排序

例如“分数从高到低；同分时学号从小到大”：

```cpp
struct Student {
    int id;
    string name;
    int score;
};

bool compareStudent(const Student &a, const Student &b) {
    if (a.score != b.score) return a.score > b.score;
    return a.id < b.id;
}
```

`if` 的先后顺序，就是关键字的优先级。注意两条记录完全相同时，应返回 `false`。

### ✔️ Lambda 写法

```cpp
sort(students.begin(), students.end(),
     [](const Student &a, const Student &b) {
         if (a.score != b.score) return a.score > b.score;
         return a.id < b.id;
     });
```

两种写法含义相同，初学时先掌握独立比较函数即可。

### ❗ 不能使用 `>=` 或 `<=`

```cpp
return a.score >= b.score; // 错误：分数相等时，双向比较都为 true
```

排序规则必须保持一致，`compare(a, a)` 应为 `false`，否则不满足 `sort` 的要求，可能出现错误甚至异常。

另外，`sort` 不保证等价记录维持输入顺序。若题目要求同分按原顺序，最直观的方式是记录原编号并用它作第二关键字，也可以使用 `stable_sort`。

### 完整练习：学生成绩排名

输入 `n`，接着每行输入姓名和成绩。学号按输入顺序从 `1` 开始。按成绩降序、学号升序输出学号、姓名、成绩。

```cpp
// program: student_ranking
#include <bits/stdc++.h>
using namespace std;
struct Student {
    int id;
    string name;
    int score;
};
bool compareStudent(const Student &a, const Student &b) {
    if (a.score != b.score) return a.score > b.score;
    return a.id < b.id;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Student> students(n);

    for (int i = 0; i < n; i++) {
        students[i].id = i + 1;
        cin >> students[i].name >> students[i].score;
    }

    sort(students.begin(), students.end(), compareStudent);

    for (const auto &student : students) {
        cout << student.id << ' ' << student.name << ' '
             << student.score << '\n';
    }
    return 0;
}
```

```text
输入：
4
Alice 80
Bob 95
Carol 95
David 70

输出：
2 Bob 95
3 Carol 95
1 Alice 80
4 David 70
```

时间 `O(n log n)`，记录数组空间 `O(n)`。

## 五、模拟：把题目规则变成状态更新

**模拟（Simulation）就是按照题目的规则，按正确顺序执行操作，维护状态，得到结果。**

| 题目 | 状态 | 初始状态 | 单次操作 | 统计时机 |
|---|---|---|---|---|
| Mixing Milk | 三个桶的当前奶量 | 输入给出 | 从一个桶尽量倒入另一个桶 | 100 次操作后输出 |
| Milk Measurement | 三头牛的奶量、展示名单 | 奶量全为 7，三头都展示 | 某头牛奶量增加或减少 | 更新后比较展示名单 |
| Shell Game | 石子位置、猜中次数 | 枚举 1、2、3 | 交换两个位置，再猜测 | 每次交换后计分 |

## 六、真题：Mixing Milk——结构体保存桶的状态

📌 **USACO 2018 December，Bronze，Problem 1。**

- [洛谷 P5116](https://www.luogu.com.cn/problem/P5116)
- [官方题面](https://usaco.org/index.php?page=viewproblem2&cpid=855)
- 教学重点：**相关属性打包、引用修改、循环模拟**。

### 问题概括

三个桶各有容量和当前奶量。按 `1 → 2 → 3 → 1` 的顺序倒奶，共进行 `100` 次；每次一直倒到源桶空或目标桶满，输出最终奶量。

### 结构体设计

```cpp
struct Bucket {
    long long capacity;
    long long milk;
};
```

一次最多倒出的奶量：

```cpp
min(source.milk, destination.capacity - destination.milk)
```

### 思路

1. 保存三个桶的状态。
2. 用 `step % 3` 确定源桶，用 `(step + 1) % 3` 确定目标桶。
3. 按上面的公式求出实际倒奶量。
4. 源桶减少、目标桶增加，容量不变。

### 参考代码

```cpp
// program: mixing_milk_bronze
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Bucket {
    ll capacity;
    ll milk;
};

void pour(Bucket &source, Bucket &destination) {
    ll amount = min(source.milk, destination.capacity - destination.milk);
    source.milk -= amount;
    destination.milk += amount;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Bucket buckets[3];
    for (auto &bucket : buckets) cin >> bucket.capacity >> bucket.milk;

    for (int step = 0; step < 100; step++) {
        int from = step % 3;
        int to = (step + 1) % 3;
        pour(buckets[from], buckets[to]);
    }

    for (const auto &bucket : buckets) cout << bucket.milk << '\n';
    return 0;
}
```

```text
输入：
10 3
11 4
12 5

输出：
0
10
2
```

**复杂度：**固定 `100` 次操作，可视为常数时间；空间 `O(1)`。

### 手推前两次

| 步骤 | 桶 1 | 桶 2 | 桶 3 |
|---|---|---|---|
| 初始 | 3 | 4 | 5 |
| 1 → 2 | 0 | 7 | 5 |
| 2 → 3 | 0 | 0 | 12 |

## 七、排序入门真题：Training Mixing Milk——按价格采购

📌 **USACO Training Section 1.3。它是训练题，不是上面的 2018 铜组倒奶题。**

[洛谷 P1208：混合牛奶](https://www.luogu.com.cn/problem/P1208)

### 问题概括

需要采购一定量的牛奶，每个奶农有单价和最多供应量。可以只买一部分，求最小总费用。

### 结构体设计

```cpp
struct Farmer {
    int price;
    int amount;
};
```

### 思路

1. 按单价从低到高排序整个奶农记录。
2. 优先从便宜奶农处购买，买到需求满足就停止。
3. 每次购买 `min(剩余需求, 当前供应量)`。

**为什么便宜的优先？** 如果还可以买到便宜牛奶，却使用了一单位更贵的牛奶，将它替换后费用不会增加。因此存在最优方案按价格从低到高采购。

### 参考代码

```cpp
// program: mixing_milk_training
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Farmer {
    int price;
    int amount;
};

bool cheaper(const Farmer &a, const Farmer &b) {
    return a.price < b.price;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int need, m;
    cin >> need >> m;
    vector<Farmer> farmers(m);
    for (auto &farmer : farmers) cin >> farmer.price >> farmer.amount;

    sort(farmers.begin(), farmers.end(), cheaper);

    ll answer = 0;
    for (const auto &farmer : farmers) {
        int buy = min(need, farmer.amount);
        answer += 1LL * buy * farmer.price;
        need -= buy;
        if (need == 0) break;
    }

    cout << answer << '\n';
    return 0;
}
```

```text
自测输入：
7 3
5 4
2 3
3 5

输出：
18
```

先买单价 `2` 的 `3` 单位，再买单价 `3` 的 `4` 单位，费用为 `3×2 + 4×3 = 18`。

**复杂度：**时间 `O(m log m)`，记录数组空间 `O(m)`。

### ❗ 排序不等于贪心一定正确

这道题允许拆开购买、每单位成本固定，所以价格排序成立。如果商品不可拆分，或存在满减、组合条件，不能直接套这个结论。

## 八、真题：Milk Measurement——事件排序与展示名单

📌 **USACO 2017 December，Bronze，Problem 3。**

[官方题面](https://usaco.org/index.php?page=viewproblem2&cpid=761)

> 注意这里是只有 Bessie、Elsie、Mildred 三头牛的铜组版本。洛谷 P4087 标为 Silver，数据和要求不同，不能用下面的三头牛代码提交。

### 问题概括

三头牛最初的产奶量都为 `7`。给出若干条乱序日志，每条包含日期、牛名、产奶量变化。每天最多一条日志。展示所有产奶量并列最高的牛，求展示名单改变了多少次。

### 为什么使用结构体？

日期、牛名、变化量属于**同一个事件**，按日期排序时必须一起移动。

```cpp
struct Record {
    int day;
    string name;
    int change;
};
```

### 思路

1. 按 `day` 升序排列日志。
2. 保存三头牛的当前奶量，初始均为 `7`。
3. 用长度为 `3` 的布尔数组记录展示名单，每个位置表示该牛是否并列最高。
4. 执行一条日志后重新计算名单，与之前比较；不同则答案加一。

**不能只比较最高产奶量数值。** 某头牛从 `9` 增加到 `10`，如果始终是同一头牛独占第一，名单并没有改变。相反，第一名数量相同但身份变了，仍然需要更换照片。

### 参考代码

```cpp
// program: milk_measurement_bronze
#include <bits/stdc++.h>
using namespace std;

struct Record {
    int day;
    string name;
    int change;
};

int cowId(const string &name) {
    if (name == "Bessie") return 0;
    if (name == "Elsie") return 1;
    return 2; // Mildred
}

array<bool, 3> display(const array<int, 3> &milk) {
    int highest = *max_element(milk.begin(), milk.end());
    return {milk[0] == highest, milk[1] == highest, milk[2] == highest};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Record> records(n);
    for (auto &record : records) {
        cin >> record.day >> record.name >> record.change;
    }

    sort(records.begin(), records.end(),
         [](const Record &a, const Record &b) {
             return a.day < b.day;
         });

    array<int, 3> milk{7, 7, 7};
    auto previous = display(milk);
    int answer = 0;

    for (const auto &record : records) {
        milk[cowId(record.name)] += record.change;
        auto current = display(milk);

        if (current != previous) answer++;
        previous = current;
    }

    cout << answer << '\n';
    return 0;
}
```

`array<bool, 3>` 是固定长度为 `3` 的数组容器，可直接比较内容是否相同；若学生尚未学过，可以换成三个布尔变量分别比较。

输入 `+3`、`-1` 时，可以直接用 `cin >> int变量` 读取，不必手动拆分符号。

```text
输入：
4
7 Mildred +3
4 Elsie -1
9 Mildred -1
1 Bessie +2

输出：
3
```

### 手推名单变化

| 日期 | Bessie | Elsie | Mildred | 展示名单 | 是否更换 |
|---|---|---|---|---|---|
| 初始 | 7 | 7 | 7 | 三头牛 | — |
| 1 | 9 | 7 | 7 | Bessie | 是 |
| 4 | 9 | 6 | 7 | Bessie | 否 |
| 7 | 9 | 6 | 10 | Mildred | 是 |
| 9 | 9 | 6 | 9 | Bessie、Mildred | 是 |

**复杂度：**排序 `O(n log n)`，模拟 `O(n)`，记录数组空间 `O(n)`。

## 九、模拟真题：Shell Game——枚举初始状态再模拟

📌 **USACO 2019 January，Bronze，Problem 1。**

[官方题面](https://usaco.org/index.php?page=viewproblem2&cpid=891)

### 问题概括

三个杯子中的某一个下面有石子，但初始位置未知。每次先交换两个杯子，再猜石子在哪个位置。给出所有交换与猜测，求可能猜中的最大次数。

### 状态与记录

```cpp
struct Operation {
    int a;
    int b;
    int guess;
};
```

- `operations`：保存所有操作，需要为三个初始位置重复使用。
- `position`：石子当前所在的位置。
- `score`：当前假设下猜中的次数。
- `answer`：三个假设中的最高分。

### 思路

1. 枚举初始位置 `start = 1, 2, 3`。
2. 每次重新设置 `position = start`、`score = 0`。
3. 按输入顺序执行每条操作：先更新石子位置，再判断是否猜中。
4. 用这一轮的 `score` 更新答案。

这里只需要跟踪石子位置，不必同时维护三个杯子的所有信息。**状态够用即可，不必把题面中所有对象都存下来。**

### 参考代码

```cpp
// program: shell_game
#include <bits/stdc++.h>
using namespace std;

struct Operation {
    int a;
    int b;
    int guess;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Operation> operations(n);
    for (auto &op : operations) cin >> op.a >> op.b >> op.guess;

    int answer = 0;
    for (int start = 1; start <= 3; start++) {
        int position = start;
        int score = 0;

        for (const auto &op : operations) {
            if (position == op.a) {
                position = op.b;
            } else if (position == op.b) {
                position = op.a;
            }

            // 题目规定先交换，再猜测
            if (position == op.guess) score++;
        }

        answer = max(answer, score);
    }

    cout << answer << '\n';
    return 0;
}
```

```text
输入：
3
1 2 1
3 2 1
1 3 1

输出：
2
```

### 手推：假设初始位置为 2

| 操作 | 交换后石子位置 | 猜测位置 | 累计得分 |
|---|---|---|---|
| 交换 1、2 | 1 | 1 | 1 |
| 交换 3、2 | 1 | 1 | 2 |
| 交换 1、3 | 3 | 1 | 2 |

初始在位置 `1、2、3` 时，得分分别为 `1、2、0`，因此答案是 `2`。

**复杂度：**枚举 3 个起点，每次模拟 `N` 条操作，时间为 `O(3N) = O(N)`；保存操作的空间为 `O(N)`。

## 十、真题：Lifeguards——结构体保存区间

📌 **USACO 2018 January，Bronze，Problem 2。**

- [洛谷 P1697](https://www.luogu.com.cn/problem/P1697)
- [官方题面](https://usaco.org/index.php?page=viewproblem2&cpid=784)
- 教学重点：**区间记录、单位时间覆盖、枚举删除对象**。

### 问题概括

每位救生员负责一个时间区间。必须恰好解雇一人，求剩余救生员能覆盖的最长总时间。人数不超过 `100`，时间在 `0 ~ 1000`。

### 用结构体表示区间

```cpp
struct Shift {
    int start;
    int finish;
};
```

### 先理解半开区间

班次从 `4` 到 `7`，覆盖的是三个单位时间段：

| 下标 `t` | 代表的时间段 |
|---|---|
| 4 | `[4, 5)` |
| 5 | `[5, 6)` |
| 6 | `[6, 7)` |

所以循环为 `t < finish`，不是 `t <= finish`。区间长度是 `finish - start`，不能额外加一。

### 思路

1. 用 `coverage[t]` 统计每个单位时间段有几位救生员值班。
2. 统计所有人的总覆盖时间 `total`。
3. 枚举解雇哪一位；只有该人值班且 `coverage[t] == 1` 的时间会丢失。
4. 计算 `total - lost`，取最大值。

不需要真的删除再恢复所有区间；只统计被解雇者独自覆盖的部分即可。本题也不需要排序。

### 参考代码

```cpp
// program: lifeguards_bronze
#include <bits/stdc++.h>
using namespace std;

struct Shift {
    int start;
    int finish;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Shift> shifts(n);
    vector<int> coverage(1000, 0);

    for (auto &shift : shifts) {
        cin >> shift.start >> shift.finish;
        for (int t = shift.start; t < shift.finish; t++) {
            coverage[t]++;
        }
    }

    int total = 0;
    for (int t = 0; t < 1000; t++) {
        if (coverage[t] > 0) total++;
    }

    int answer = 0;
    for (const auto &shift : shifts) {
        int lost = 0;
        for (int t = shift.start; t < shift.finish; t++) {
            if (coverage[t] == 1) lost++;
        }
        answer = max(answer, total - lost);
    }

    cout << answer << '\n';
    return 0;
}
```

```text
输入：
3
5 9
1 4
3 7

输出：
7
```

总覆盖为 `[1, 9)`，长度 `8`。解雇 `[3, 7)` 的救生员，只会失去 `[4, 5)`，剩余覆盖为 `7`。

**复杂度：**设时间范围为 `T = 1000`，时间 `O(nT)`，记录与覆盖数组空间 `O(n + T)`。如果坐标扩展到 `10^9`，不能再逐格枚举时间，需要其他处理方式。

## 十一、Air Cownditioning II

📌 **USACO 2023 January，Bronze，Problem 2。**

- [洛谷 P9011](https://www.luogu.com.cn/problem/P9011)
- [官方题面](https://usaco.org/index.php?page=viewproblem2&cpid=1276)
- 前置：已学习 DFS 的选 / 不选枚举。

每台空调同时有“左端点、右端点、降温量、费用”四个属性，适合打包成：

```cpp
struct Conditioner {
    int left;
    int right;
    int power;
    int price;
};

vector<Conditioner> conditioners;
```

### 思路衔接

1. 保存每头牛占据的区间及降温需求。
2. 保存每台空调的四个属性。
3. 最多 `10` 台空调，每台选择开启或关闭，DFS 枚举 `2^M` 个子集。
4. 检查降温需求，更新最小费用；回溯时撤销选中空调的降温效果。

## 十二、拓展：结构体嵌套与 `pair`

### ✔️ 结构体可以嵌套

```cpp
struct StudentInfo {
    string name;
    int age;

    struct Score {
        int math;
        int english;
    } score;
};

StudentInfo student{"Tom", 17, {90, 85}};
cout << student.score.math << '\n'; // 90
```

含义：学生拥有一个成绩对象，这个成绩对象又有数学、英语两个成员。当前阶段会读懂即可，不必为了使用 `struct` 而增加嵌套层级。

### ✔️ `struct` 与 `pair` 怎么选？

| 场景 | 建议 |
|---|---|
| 两个简单坐标，含义明确 | `pair<int, int>` 简洁 |
| 属性较多，或两个属性含义容易混淆 | 用 `struct` 命名成员 |
| 按多个条件排序的记录 | 用 `struct` + 比较函数 |

```cpp
pair<int, int> point{2, 5};
cout << point.first << ' ' << point.second;

struct Point {
    int x;
    int y;
};
Point p{2, 5};
cout << p.x << ' ' << p.y;
```

`pair` 默认先比较 `first`，相同再比较 `second`。自定义结构体不会自动按照声明顺序排序，C++17 下通常要提供比较函数或自己定义 `<`。

## 十三、练习题单

| 顺序 | 题目 | 来源 | 结构体设计 | 主要算法 |
|---|---|---|---|---|
| 1 | [P5116 Mixing Milk B](https://www.luogu.com.cn/problem/P5116) | 2018 December Bronze | `Bucket{capacity, milk}` | 固定次数模拟 |
| 2 | [Shell Game](https://usaco.org/index.php?page=viewproblem2&cpid=891) | 2019 January Bronze | `Operation{a, b, guess}` | 枚举初始位置 + 模拟 |
| 3 | [P1208 Mixing Milk](https://www.luogu.com.cn/problem/P1208) | Training 1.3，不标作月赛铜组 | `Farmer{price, amount}` | 排序 + 贪心 |
| 4 | [Milk Measurement](https://usaco.org/index.php?page=viewproblem2&cpid=761) | 2017 December Bronze | `Record{day, name, change}` | 事件排序 + 模拟 |
| 5 | [P1697 Lifeguards B](https://www.luogu.com.cn/problem/P1697) | 2018 January Bronze | `Shift{start, finish}` | 枚举 + 覆盖统计 |
| 6 | [P9011 Air Cownditioning II B](https://www.luogu.com.cn/problem/P9011) | 2023 January Bronze | `Conditioner{left, right, power, price}` | DFS 子集枚举；学搜索后再做 |
