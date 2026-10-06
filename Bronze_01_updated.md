## USACO 铜组：复杂度、枚举、贪心、递推与递归

## 1. 时间复杂度与空间复杂度

### 1.1 什么是输入规模

n 可以表示数组长度、字符串长度或对象数量。有些问题需要多个参数，例如 K 场比赛、N 头牛，复杂度写作 O(KN²)，不必把所有参数都叫 n。

时间复杂度描述操作次数随规模增长的趋势，不是程序实际运行的秒数。空间分析应说明口径：总空间包括保存输入的数据；辅助空间仅统计算法额外需要的存储。本讲义会明确使用哪一种。

### 1.2 O、Θ、Ω

| 记号 | 含义 |
|---|---|
| O(f(n)) | 渐近上界 |
| Θ(f(n)) | 渐近紧确界 |
| Ω(f(n)) | 渐近下界 |

O 不等于“最坏情况”，Ω 不等于“最好情况”。最坏、平均、最好描述输入情况下的运行成本；O、Θ、Ω 描述成本函数的界。本章通常分析最坏情况下的 O 上界。

### 1.3 常见增长量级

从较低到较高的常见增长量级：

O(1)、O(log n)、O(n)、O(n log n)、O(n²)、O(n³)、O(2ⁿ)、O(n!)。

常数可能影响小数据下的实际快慢。例如一个 O(n²) 程序不一定在所有小规模输入上都比另一个 O(n) 程序慢。

### 1.4 从代码计算工作量

**顺序执行的循环相加：**

```cpp
for (int i = 0; i < n; i++) { /* O(1) 操作 */ }
for (int j = 0; j < n; j++) { /* O(1) 操作 */ }
// n + n = 2n，时间 O(n)，不是 O(n²)
```

**嵌套循环计算总次数：**

```cpp
long long cnt = 0;
for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
        cnt++;
    }
}
// n(n - 1) / 2 次，时间 O(n²)
```

**循环变量倍增或折半：**

```cpp
// 假设 n >= 1，且此处倍增不会溢出
for (long long x = 1; x <= n; x *= 2) {
    // O(1) 操作
}
// O(log n)
```

循环体如果又进行扫描、复制或排序，也要计入成本。不能只数 for 的层数。

### 1.5 数组求和：区分总空间和辅助空间

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    long long sum = 0;
    for (int x : a) sum += x;
    cout << sum << '\n';
    return 0;
}
```

时间 O(n)，保存数组的总空间 O(n)，求和过程的辅助空间 O(1)。若读取一个数就立即累加，无需保存数组，总空间也可以为 O(1)。

### 1.6 二分查找

必须在有序数组上使用以下查找方式。函数放在 main 外：

```cpp
int binarySearch(const vector<int>& a, int target) {
    int l = 0, r = static_cast<int>(a.size()) - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (a[mid] == target) return mid;
        if (a[mid] < target) l = mid + 1;
        else r = mid - 1;
    }
    return -1;
}
```

每次排除约一半候选位置，查找时间 O(log n)，辅助空间 O(1)。如果先排序再查找一次，总时间还需要计入 O(n log n) 的排序成本。

### 1.7 用数据范围筛选算法

下面是假设循环体较轻时的课堂估算，不是通过时限的保证：

| 规模示例 | 运算量 | 判断 |
|---|---|---|
| n = 20，O(n³) | 约 8000 | 通常很小 |
| n = 100，O(n³) | 约 100 万 | 可考虑 |
| n = 5000，O(n²) | 约 2500 万 | 结合时限、常数判断 |
| n = 200000，O(n²) | 约 400 亿 | 通常不可行 |
| 10 个元素的排列 | 10! = 3628800 | 还要计入每个排列的检查成本 |

多组测试要计算总工作量。字符串比较、容器复制等操作不能默认算 O(1)。

### 1.8 递归与空间

递归时间应计算**所有调用的总工作量**。存在分支时，不能只用“最大深度 × 单次调用成本”。递归辅助空间则关注同时存在的调用层数，以及每层的局部存储。

例如阶乘递归有 n + 1 次调用；朴素 Fibonacci 递归会重复展开相同子问题，O(2ⁿ) 是常用上界，深度却只有 O(n)。

归并排序和主定理可留到后续算法课程；本章先掌握循环计数和递归调用树。

## 2. 枚举：确定对象、范围与检查方法

枚举是逐一检查候选方案的策略。设计时回答四个问题：

1. 枚举什么？
2. 范围是什么，能否覆盖全部候选？
3. 如何检查候选是否合法？
4. 如何统计、更新答案，是否会重复？

枚举并不意味着一定超时。小数据允许直接尝试；还可以利用约束减少需要枚举的变量。

### 2.1 原例：百钱买百鸡

公鸡每只 5 元，母鸡每只 3 元，小鸡每 3 只 1 元。用 100 元买 100 只鸡，输出所有方案。

枚举公鸡和母鸡数量，小鸡数量由总数决定，不必再增加第三层循环。

```cpp
#include <iostream>
using namespace std;

int main() {
    for (int rooster = 0; rooster <= 20; rooster++) {
        for (int hen = 0; hen <= 33; hen++) {
            int chick = 100 - rooster - hen;
            if (chick >= 0 && chick % 3 == 0 &&
                5 * rooster + 3 * hen + chick / 3 == 100) {
                cout << rooster << ' ' << hen << ' ' << chick << '\n';
            }
        }
    }
    return 0;
}
```

这里不能写 `1 / 3 * chick`：整数除法 1 / 3 等于 0。先判断小鸡数量为 3 的倍数，再使用 chick / 3。

固定金额下循环次数为常数。若把金额和总数量推广为规模变量，需重新分析范围。

### 2.2 USACO 真题：Cow Gymnastics

**2019 December Bronze，Problem 1**

[官方题目](https://usaco.org/index.php?page=viewproblem2&cpid=963)

**教学概述：**K 场训练，每场给出 N 头牛的排名。统计有多少对牛在所有训练中始终保持同一相对次序。范围 K ≤ 10、N ≤ 20。

**与知识点的对应：**枚举牛对，逐场检查。先存“牛在每场的位置”，就能 O(1) 比较两头牛的排名。

```text
pos[场次][牛编号] = 排名位置
```

代码枚举有方向的牛对 (a, b)，要求 a 每次都领先 b。每个合法无序牛对恰好有一个方向成立，因此不需要除以 2。

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int k, n;
    cin >> k >> n;
    vector<vector<int>> pos(k, vector<int>(n + 1));
    for (int round = 0; round < k; round++) {
        for (int rank = 0; rank < n; rank++) {
            int cow;
            cin >> cow;
            pos[round][cow] = rank;
        }
    }

    int answer = 0;
    for (int a = 1; a <= n; a++) {
        for (int b = 1; b <= n; b++) {
            if (a == b) continue;
            bool ok = true;
            for (int round = 0; round < k; round++) {
                if (pos[round][a] >= pos[round][b]) {
                    ok = false;
                    break;
                }
            }
            if (ok) answer++;
        }
    }
    cout << answer << '\n';
    return 0;
}
```

**官方样例输入：**

```text
3 4
4 1 2 3
4 1 3 2
4 2 1 3
```

**输出：**

```text
4
```

时间 O(KN²)，总空间 O(KN)。

**课堂提问：**如果不存 pos，每次比较都扫描排名寻找两头牛，最坏复杂度会增加到 O(KN³)。这说明检查一个候选方案的成本也很重要。

## 3. 暴力求解：尝试所有候选方案

暴力和枚举经常重叠，不必把它们当作完全独立的算法。暴力强调直接、全面地尝试；枚举说明候选如何被遍历。

### 3.1 原例：两数之和

输入 n、target 和 n 个整数。找到两个不同下标使其和等于 target，输出一组从 0 开始的下标，找不到输出 -1。

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    long long target;
    cin >> n >> target;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (1LL * a[i] + a[j] == target) {
                cout << i << ' ' << j << '\n';
                return 0;
            }
        }
    }
    cout << -1 << '\n';
    return 0;
}
```

时间 O(n²)，保存输入的总空间 O(n)，搜索辅助空间 O(1)。使用 j = i + 1，避免使用同一个元素和重复检查反方向。

### 3.2 USACO 真题：Lifeguards

**2018 January Bronze，Problem 2**

[官方题目](https://usaco.org/index.php?page=viewproblem2&cpid=784)

**教学概述：**N 位救生员各负责一段时间，必须恰好解雇一位，最大化剩余人员覆盖的总时间。N ≤ 100，端点是 0 到 1000 的整数。

**枚举对象：**被解雇的人员。

**检查方法：**重新标记其他人的时间段，再计算覆盖总长度。这里数组下标 t 表示单位区间 [t, t + 1)，不是一个孤立时间点。区间 [4, 7) 长度为 3，循环必须写 t < 7。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> start(n), finish(n);
    for (int i = 0; i < n; i++) cin >> start[i] >> finish[i];

    int answer = 0;
    for (int fired = 0; fired < n; fired++) {
        bool covered[1000] = {};
        for (int i = 0; i < n; i++) {
            if (i == fired) continue;
            for (int t = start[i]; t < finish[i]; t++) {
                covered[t] = true;
            }
        }
        int total = 0;
        for (int t = 0; t < 1000; t++) total += covered[t];
        answer = max(answer, total);
    }
    cout << answer << '\n';
    return 0;
}
```

**官方样例输入：**

```text
3
5 9
1 4
3 7
```

**输出：**

```text
7
```

设时间范围长度为 T，时间 O(N²T)，总空间 O(N + T)。本题 T = 1000，N ≤ 100，这个简单实现适合讲解铜组暴力。

**易错点：**每次枚举解雇对象都要重置标记；重叠部分只统计一次；N = 1 时答案为 0。

### 3.3 原例：P2241 统计方形

[洛谷题目](https://www.luogu.com.cn/problem/P2241)

n × m 个小方格组成棋盘，统计正方形和非正方形长方形，n、m ≤ 5000。

**原有枚举思路：**枚举高度 h、宽度 w；这一尺寸有 (n - h + 1)(m - w + 1) 个位置。h = w 时是正方形。时间 O(nm)，最大约 2500 万个尺寸组合，应结合时限判断。

**减少枚举对象：**全部矩形由两条横向边界和两条纵向边界确定：

全部矩形数 = n(n + 1)m(m + 1) / 4。

只需枚举正方形边长，再用全部矩形数减去正方形数。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    long long n, m;
    cin >> n >> m;
    long long squares = 0;
    for (long long side = 1; side <= min(n, m); side++) {
        squares += (n - side + 1) * (m - side + 1);
    }
    long long all = n * (n + 1) / 2 * (m * (m + 1) / 2);
    cout << squares << ' ' << all - squares << '\n';
    return 0;
}
```

时间 O(min(n, m))，辅助空间 O(1)。n、m 和乘积使用 long long。输入 2 3，输出 8 10。

**课堂提问：**优化来自数学计数和减少枚举维度，不是只把循环语法写得更短。

## 4. 贪心：选择必须有理由

贪心每次作出一个选择，并不回头枚举所有选择组合。只有当能说明这种选择不会破坏全局最优时，才可认为算法正确。“当前看起来最好”不是证明。

讲解顺序：提出策略 → 尝试反例 → 证明不会更差 → 实现。

### 4.1 原例：P3817 小 A 的糖果

[洛谷题目](https://www.luogu.com.cn/problem/P3817)

相邻两盒糖果总数不能超过 x，求最少需要吃掉多少颗。这里的对象是糖果盒，不是苹果或按天输入的数据。

从左到右处理。若前盒已合法，而当前相邻和超过 x，至少需要删掉超出数量。优先从当前盒删：这不会改变已经处理好的左侧关系，还可能帮助下一组相邻盒满足条件。

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    long long x;
    cin >> n >> x;
    vector<long long> a(n);
    for (long long& value : a) cin >> value;

    if (n == 1) { // 没有相邻盒约束
        cout << 0 << '\n';
        return 0;
    }
    long long answer = 0;
    if (a[0] > x) {
        answer += a[0] - x;
        a[0] = x;
    }
    for (int i = 1; i < n; i++) {
        long long excess = a[i - 1] + a[i] - x;
        if (excess > 0) {
            answer += excess;
            a[i] -= excess;
        }
    }
    cout << answer << '\n';
    return 0;
}
```

对至少两盒的情况，任一盒超过 x 的部分都必须删除。处理当前盒前，前一盒已不超过 x，因此删除的 excess 不会超过当前盒数量。

时间 O(n)，此实现总空间 O(n)。

### 4.2 USACO 真题：Sleepy Cow Sorting

**2019 January Bronze，Problem 2**

[官方题目](https://usaco.org/index.php?page=viewproblem2&cpid=892)

**教学概述：**一个由 1 到 N 构成的排列，每次只能把队首元素移到后面的某个位置。求排成升序的最少操作数，N ≤ 100。

**观察：**没有被移动的元素始终保持相对次序。希望保留不动的部分尽可能长，它必须是原排列末尾的一段递增后缀。

例如 1 2 4 3，最长递增后缀只有 3，前面 3 个元素需要移动，因此答案为 3。

**为什么答案等于后缀前的元素数量？**

- 下界：操作只能处理队首，若只移动前 k 个元素，其后的原始后缀保持相对顺序；这个后缀必须已经递增。因此少于最长递增后缀之前的元素数不够。
- 可行性：保留递增后缀，把前面的元素按队首顺序取出，逐个插入当前有序后缀的合适位置，即可完成排序。这里是证明构造，不需要真的模拟所有插入。

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (int& x : p) cin >> x;

    int start = n - 1;
    while (start > 0 && p[start - 1] < p[start]) {
        start--;
    }
    cout << start << '\n';
    return 0;
}
```

**官方样例输入：**

```text
4
1 2 4 3
```

**输出：**

```text
3
```

时间 O(n)，总空间 O(n)，扫描辅助空间 O(1)。本题更适合用“保留最长有序后缀”和上下界证明解释，而不是仅说“贪心地选最小牛”。

### 4.3 原例：P4995 跳跳！

[洛谷题目](https://www.luogu.com.cn/problem/P4995)

原稿把标题写成“排队接水”，应改为“跳跳！”。目标是最大化平方高度差总和，而不是最小化。从高度 0 的地面出发，每块石头恰好访问一次，不能再跳回地面。

常用方案是将石头排序，从最高开始，再取最低、次高、次低，交替访问两端。实现中使用整数乘法，不使用 pow 计算整数平方；每次仅取一块石头，避免指针交错时额外计算一次跳跃。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> h(n);
    for (long long& x : h) cin >> x;
    sort(h.begin(), h.end());

    int l = 0, r = n - 1;
    bool takeHigh = true;
    long long previous = 0, answer = 0;
    while (l <= r) {
        long long current;
        if (takeHigh) current = h[r--];
        else current = h[l++];
        long long diff = current - previous;
        answer += diff * diff;
        previous = current;
        takeHigh = !takeHigh;
    }
    cout << answer << '\n';
    return 0;
}
```

时间 O(n log n)，总空间 O(n)。这道题的最优性论证较基础线性贪心更复杂，适合作为选练；不能把“先跳到最远处”当成通用贪心定理。主课建议先讲上一道有清晰下界与构造的 USACO 真题。

| 专题           | 推荐顺序                                                     |
| -------------- | ------------------------------------------------------------ |
| 基础枚举与暴力 | [Triangles](https://usaco.org/index.php?page=viewproblem2&cpid=1011) → [Daisy Chains](https://usaco.org/index.php?page=viewproblem2&cpid=1060) → [Blocks](https://usaco.org/index.php?page=viewproblem2&cpid=1205) → [Non-Transitive Dice](https://usaco.org/index.php?page=viewproblem2&cpid=1180) → [Air Cownditioning II](https://usaco.org/index.php?page=viewproblem2&cpid=1276) |
| 基础贪心       | [Mad Scientist](https://usaco.org/index.php?page=viewproblem2&cpid=1012) → [Uddered but not Herd](https://usaco.org/index.php?page=viewproblem2&cpid=1083) → [Watching Mooloo](https://usaco.org/index.php?page=viewproblem2&cpid=1301) → [Feeding the Cows](https://usaco.org/index.php?page=viewproblem2&cpid=1252) → [Air Cownditioning](https://usaco.org/index.php?page=viewproblem2&cpid=1156) |

***

## 5. 递推：由已知状态计算下一状态

递推先明确状态含义，再给出初值和计算顺序。递推不等于“所有带循环的代码”；递推式也不自动等于一个完整的动态规划算法。

### 5.1 原例：一次走 1 或 2 级台阶

定义 f[i] 为到达第 i 级的走法数。

- f[0] = 1：空走法计为一种。
- f[1] = 1。
- f[i] = f[i - 1] + f[i - 2]：最后一步来自前一级或前两级，这两类不重叠。

只需要前两个值，不必存整个数组：

```cpp
#include <iostream>
using namespace std;

long long ways(int n) {
    if (n <= 1) return 1;
    long long previous2 = 1, previous1 = 1;
    for (int i = 2; i <= n; i++) {
        long long current = previous2 + previous1;
        previous2 = previous1;
        previous1 = current;
    }
    return previous1;
}

int main() {
    int n;
    cin >> n; // 本例限定 0 <= n <= 91
    cout << ways(n) << '\n';
    return 0;
}
```

时间 O(n)，辅助空间 O(1)。f[91] 能放入常见的有符号 64 位 long long，f[92] 已超出范围。

### 5.2 P1255 数楼梯：为什么原代码需要高精度

[洛谷题目](https://www.luogu.com.cn/problem/P1255)

原题 N 可达 5000，不能直接提交上一段 long long 程序。

原稿的 `int f[5003][5003]` 约占 100 MB（按每个 int 4 字节估算），还存下了所有台阶的大整数。转移只用前两个状态，可以只保留三个十进制字符串。

**选学：用字符串表示非负大整数，按位相加。**

```cpp
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string addDecimal(const string& a, const string& b) {
    int i = static_cast<int>(a.size()) - 1;
    int j = static_cast<int>(b.size()) - 1;
    int carry = 0;
    string result;
    while (i >= 0 || j >= 0 || carry != 0) {
        int sum = carry;
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';
        result.push_back(static_cast<char>('0' + sum % 10));
        carry = sum / 10;
    }
    reverse(result.begin(), result.end());
    return result;
}

int main() {
    int n;
    cin >> n;
    string previous2 = "1", previous1 = "1";
    for (int i = 2; i <= n; i++) {
        string current = addDecimal(previous2, previous1);
        previous2 = previous1;
        previous1 = current;
    }
    cout << previous1 << '\n';
    return 0;
}
```

这里 N 至少为 1。设最大答案位数为 L，总时间 O(NL)，存储为 O(L)。高精度加法是原稿已有的扩展内容，可在学生理解递推后选讲，不宜作为本章入门重点。

## 6. 递归：明确终止条件和状态变化

递归是函数调用自身的实现方式，可以处理线性计算，也可以组织分支枚举。递归不一定慢，也不一定比循环更快。

写递归时先检查：

1. 终止条件是什么？
2. 下一次调用如何更接近终止条件？
3. 每一层有哪些选择？
4. 不同分支是否共享可变状态，是否需要恢复？

### 6.1 原例：阶乘

```cpp
#include <iostream>
using namespace std;

long long factorial(int n) {
    if (n == 0) return 1;
    return n * factorial(n - 1);
}

int main() {
    int n;
    cin >> n; // 本例限定 0 <= n <= 20
    cout << factorial(n) << '\n';
    return 0;
}
```

factorial(3) = 3 × factorial(2) = 3 × 2 × factorial(1) = 6。

时间 O(n)，调用栈辅助空间 O(n)。20! 能放入常见的有符号 64 位整数，21! 已超出范围。负数不满足这个终止设计。

### 6.2 USACO 真题：Back and Forth

**2018 December Bronze，Problem 3**

[官方题目](https://usaco.org/index.php?page=viewproblem2&cpid=857)

**教学概述：**两间牛棚初始各有 1000 单位牛奶和 10 个桶。四天按 A → B、B → A、A → B、B → A 的方向搬运，每次选当地一个桶，牛奶和桶一起转移。统计最终 A 棚牛奶量有多少种。

**为什么适合递归枚举？**只有 4 次选择，各次可选桶数为 10、11、10、11，最多 12100 条选择路径。复杂度分析要计算所有分支，不是“深度 4，所以 O(4)”。

**状态：**已经搬运的次数、A 棚牛奶量、两边当前的桶。

本教学实现按值传递两边的 vector。各分支复制后修改自己的状态，避免初学者遗漏撤销操作；代价是每层多一些复制开销。

```cpp
#include <iostream>
#include <vector>
using namespace std;

bool seen[2001] = {}; // 两棚合计 2000 单位牛奶

void search(int day, int milkA, vector<int> a, vector<int> b) {
    if (day == 4) {
        seen[milkA] = true;
        return;
    }

    if (day % 2 == 0) { // A -> B
        for (int i = 0; i < static_cast<int>(a.size()); i++) {
            int capacity = a[i];
            vector<int> nextA = a, nextB = b;
            nextA.erase(nextA.begin() + i);
            nextB.push_back(capacity);
            search(day + 1, milkA - capacity, nextA, nextB);
        }
    } else { // B -> A
        for (int i = 0; i < static_cast<int>(b.size()); i++) {
            int capacity = b[i];
            vector<int> nextA = a, nextB = b;
            nextB.erase(nextB.begin() + i);
            nextA.push_back(capacity);
            search(day + 1, milkA + capacity, nextA, nextB);
        }
    }
}

int main() {
    vector<int> a(10), b(10);
    for (int& x : a) cin >> x;
    for (int& x : b) cin >> x;
    search(0, 1000, a, b);

    int answer = 0;
    for (bool reached : seen) answer += reached;
    cout << answer << '\n';
    return 0;
}
```

**官方样例输入：**

```text
1 1 1 1 1 1 1 1 1 2
5 5 5 5 5 5 5 5 5 5
```

**输出：**

```text
5
```

**易错点：**桶也要移动；相同容量的不同桶可以产生重复路径，但最终按牛奶量去重；统计的是不同终态数量，不是搬运方案数量。

设每边初始桶数为 B，搬运次数固定为 4。本复制实现的枚举与复制成本上界为 O(B⁵)，递归路径上的桶数组占用 O(B)，另有用于标记最终奶量的数组。实际 B = 10，状态很小；不必为减少常数而牺牲讲解清晰度。若改为引用传参并原地修改，必须在每次递归返回后恢复桶的位置。

## 7. 真题使用

### 7.1 老题文件输入输出

本讲义的真题代码统一使用 cin/cout，方便课堂粘贴样例测试。但这四道官方老题指定了文件输入输出。直接在相应官方题目提交时，按题面要求在读取前加入文件重定向，并包含 `<cstdio>`：

```cpp
freopen("gymnastics.in", "r", stdin);
freopen("gymnastics.out", "w", stdout);
```
