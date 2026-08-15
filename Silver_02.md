## 📚 USACO常见的map、unordered_map

### 📌1、**map 和 unordered_map 的对比**

| 特性               | `map`（有序）      | `unordered_map（无序）` |
| ------------------ | ------------------ | ----------------------- |
| 底层逻辑           | 红黑树             | 哈希表                  |
| 时间复杂度         | 查找/插入 O(log n) | 查找/插入平均 O(1)      |
| key 是否自动排序？ | ✔ 有序（升序）     | ✘ 无序                  |
| 空间               | 较少               | 较多                    |

### 什么时候用 `map`？

- **需要 key 排序的题**
- 需要 lower_bound/upper_bound（比如区间查找）
- 数据量很大但不要求极限速度
- 想要结果有序（输出顺序）

```c++
map<int, int> mp;  // 自动按 key 排序
```

### 什么时候用 `unordered_map`？

- 只需要查找是否存在
- 频率统计（freq counter）
- key 是字符串、大整数、pair 等
- 希望最快的平均性能

```c++
unordered_map<string, int> freq;
```

### ✅ 1. 频率统计（frequency counting）

```c++
unordered_map<int, int> cnt;
for (int x : arr) {
    cnt[x]++;
}
```

统计字符串也一样：

```c++
#include<bits/stdc++.h>
using namespace std;
int main(){
    vector<string>arr={"apple","orange","apple","banana"};
    unordered_map<string, int> cnt; //哈希表存储的是一对一的映射关系
    for (string s : arr) cnt[s]++;
    for (auto &pair : cnt) {
        cout << pair.first << ": " << pair.second << endl;
    }
}
//1 2 3 1 2 3 4 5 3
//1:2 2:2 3:3
//输出编号出现两次以上的映射
```

### ✅ **2. 判断某元素是否出现**

```c++
if (cnt.count(x)) {
    // 存在 x
}
```

### ✅ **3. 遍历所有 key-value**

```c++
for (auto &p : cnt) {
    int key = p.first;
    int value = p.second;
}
```

### ✅ **4. map + 排序（对 key 排序）**

```c++
map<int, int> mp; // 有序
for (auto &p : mp) {
    // 自动按 key 从小到大
}
```

### ✅ **5. 多重映射（key → vector）**

适用于“分组统计”类题。

```c++
unordered_map<int, vector<int>> g;
g[key].push_back(val);
```

### ✅ **6. 字符串映射（非常常见）**

```c++
unordered_map<string, int> id;
id["cow"] = 5;
```

### ✅ **7. pair 映射（二维 key）**

```c++
unordered_map<long long, int> mp;
long long key = 1LL * x * 1e9 + y; // 手动哈希
mp[key]++;
```

### ✅ **8. 离散化 + map**

**离散化（coordinate compression） = 把巨大范围的值，映射成从 0 开始的小整数。**

例如原本有值：

```c++
[-2000000000, 10, 999999999]
```

范围太大，如果你做：

- 开数组 arr[1e9]：直接爆炸
- 或需要排序/统计的时候不方便

所以我们把它们压缩成：

```c++
-2000000000 → 0
10           → 1
999999999    → 2
```

**这样所有值都变成可控的小下标（0,1,2…）**

```c++
map<int, int> mp; //有序
int id = 0;
for (int x : arr) {
    if (!mp.count(x)) 
      mp[x] = id++; //分配id，从0开始
}
```

这段代码的作用就是：

### 🔍 **如果 x 第一次出现**

→ 给它分配一个新的 ID（从 0 开始）
 → 下次遇到相同 x，就复用这个 ID。

**mp[x] = id++** 保证了每个不同的数匹配到不同的小编号。

✔ 把大范围值→换成小整数
 ✔ 自动按 key 排序
 ✔ 下标从 0 到 unique_count-1
 ✔ 用于区间、树状数组、扫描线、图论等场景

> 2016 Dec Silver_1-Counting Haybales

***

### ✅ **9. map + lower_bound/upper_bound**

因为 `map` 是 **有序（红黑树）结构**，key 自动按升序排列。

第一个 ≥ x 的 key → `lower_bound`

第一个 > x 的 key → `upper_bound`

### case 1：找到第一个 >= x 的 key（最常用场景）**

比如你有一些牛的位置，需要找到离位置 x 最近的**右侧牛**。

```c++
map<int, int> mp;  // key: 牛的位置, val: 其他信息
auto it = mp.lower_bound(x);
if (it != mp.end()) {
    cout << "第一个 >= x 的位置是 " << it.first << "\n";
}
```

### case **2：找到第一个 > x 的 key**

常用于处理严格区间，例如 (x, +∞)。

```c++
auto it = mp.upper_bound(x);
if (it != mp.end()) {
    cout << "第一个 > x 的位置是 " << it.first << "\n";
}
```

### **case 3：在有序 map 中找某个区间内的 key**

比如你有若干农场编号，想找到区间 [L, R] 内所有的农场。

```c++
auto it = mp.lower_bound(L);  // 第一个 >= L
while (it != mp.end() && it.first <= R) {
    cout << "农场: " << it.first << "\n";
    it++;
}
```

### case **4：查找最接近 x 的点（USACO 非常常考）**

例如要找距离某个位置最近的牛：

```c++
auto it = mp.lower_bound(x);
int best=1e18;

// right side
if (it != mp.end())
    best = min(best, abs(it.first - x));

// left side
if (it != mp.begin()) {
    it--;
    best = min(best, abs(it.first - x));
}
```

***

### 📌 2、优先队列 priority_queue

优先队列是一种特殊的队列：

> **取出的永远是“最优的那个元素”（最大或最小）**
>  而不是先进先出。

优先队列底层使用 **二叉堆（binary heap）** 实现。

### 🧠为什么竞赛喜欢用优先队列？

因为它速度快：

| 操作               | 时间复杂度 |
| ------------------ | ---------- |
| 插入               | O(log n)   |
| 取最值             | O(log n)   |
| 查询最值（不删除） | O(1)       |

适用于：

- 找当前最大的 / 最小的
- 动态加入、动态删除
- 不断取最优解（贪心）

属于 **USACO 银组常用的数据结构**。

### ① 默认：最大堆（取最大值）

```c++
priority_queue<int> pq;
pq.push(5);
pq.push(1);
pq.push(10);
cout << pq.top();   // 10
pq.pop();           // 删除 10
```

### ② 最小堆（USACO 更常用）

要写比较器：

```c++
priority_queue<int, vector<int>, greater<int>> pq;
//创建一个以 vector 为底层容器、存 int、并按照小的优先级在上面的“最小堆”。
```

现在 `top()` 就是**最小值**。

### ③ 存 pair（按第一个排序）

```c++
priority_queue<pair<int,int>> pq;  // 默认最大堆
//比较 first, 若相同，再比较 second
```

### ④ 最小堆 + pair（竞赛常用）

```c++
priority_queue<
    pair<int,int>,
    vector<pair<int,int>>,
    greater<pair<int,int>>
> pq;
```

### 👉 优先队列在 USACO 银组的典型用途

### ① 贪心（频率 or 权重最大/最小）

例如：

- 选当前“最紧急”的任务
- 选当前“最小代价”的操作
- 选当前“最大产量”
- 堆模拟调度（schedule simulation）

### ② K 小 / K 大元素

#### 情况一：**已经有全部数据，只是想拿出 K 个最小 / 最大**

这时候最简单的想法就是：

- **K 个最小**：用**最小堆**，弹 K 次
- **K 个最大**：用**最大堆**，弹 K 次

对应代码：

```c++
// 找 K 个最小元素：
priority_queue<int, vector<int>, greater<int>> pq; // 最小堆
for (int x : arr) pq.push(x);
for (int i = 0; i < K; i++) {
    cout << pq.top() << "\n"; // 从小到大
    pq.pop();
}

// 找 K 个最大元素：
priority_queue<int> pq2; // 最大堆
for (int x : arr) pq2.push(x);
for (int i = 0; i < K; i++) {
    cout << pq2.top() << "\n"; // 从大到小
    pq2.pop();
}
```

#### 情况二：**在线维护“前 K 大 / 前 K 小”（数据流/只留 K 个）**

但在算法题里，更常见的是这种模式：

> 数据很多，只想**保留 K 个最优的**，不想存全部。

这时候常用的技巧是：

### ⭐ 保留 K 个**最大**值（Top K largest）

用 **“最小堆 + 只存 K 个”**：

```c++
priority_queue<int, vector<int>, greater<int>> pq; // 最小堆

for (int x : arr) {
    if ((int)pq.size() < K) pq.push(x);         // 先填满
    else if (x > pq.top()) {                    // 比堆顶（当前第 K 大）更大
        pq.pop();
        pq.push(x);
    }
}
// 最后 pq 里是“前 K 大”，堆顶是“第 K 大（最小的那个）”
```

### ⭐ 保留 K 个**最小**值（Top K smallest）

用 **“最大堆 + 只存 K 个”**：

```c++
#include<bits/stdc++.h>
using namespace std;
int main() {
    vector<int> arr = {3, 2, 8, 5, 1, 7, 4, 6};
    int K = 4; // 要找前4小的元素
    // 最大堆（堆顶最大）
    priority_queue<int> pq;
    for (int x : arr) {
        if ((int)pq.size() < K) {
            pq.push(x);
        } else if (x < pq.top()) {   // 比当前最大的小
            pq.pop();
            pq.push(x);
        }
    }
    // 输出结果
    cout << "前 " << K << " 小的元素是: ";
    // 注意：priority_queue 只能访问堆顶，要获取所有元素需要弹出
    vector<int> result;
    while (!pq.empty()) {
        result.push_back(pq.top());
        pq.pop();
    }
    // 由于是最大堆，弹出的顺序是从大到小，需要反转
    reverse(result.begin(), result.end());
    for (int x : result) cout << x << " ";
    cout<<endl;
    return 0;
}
// 最后 pq 里是“前 K 小”，堆顶是“第 K 小里最大的那个”
```

在**这种“只维护前 K 个”的套路**里：

- **前 K 大** → 用最小堆（我之前写的是这个思路）
- **前 K 小** → 用最大堆

### ③ 多路合并（k-way merge）

例如有多条升序序列，要合并成一个序列
 → 把每一条的第一个放入最小堆 → 每次取最小 → 推入下一项
 （和合并 k 个有序链表一个思路）

### ④ 动态维护最优值（典型银组套路）

例如“每次取最大值，做一些操作，再放回去”。

```
push → top → pop → push → top → pop → …
```

优先队列特别适合这种循环。

***

