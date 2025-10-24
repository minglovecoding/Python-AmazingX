## 二分查找（Binary Search）

------

## 🥇 一、核心思想

**二分查找（Binary Search）** 是一种在有序区间内查找目标值的算法。
 它利用“单调性”性质，每次把搜索空间缩小一半，从而在
$$
O(\log N)
$$
时间内找到答案。

------

### ✅ 基本思路：

假设有一个升序数组 `a[0...N-1]`，我们要查找一个目标值 `x`：

1. 取中点 `mid = (l + r) / 2`
2. 比较 `a[mid]` 和 `x`
3. 根据结果缩小搜索区间：
   - 若 `a[mid] < x` → 搜右边；
   - 若 `a[mid] > x` → 搜左边；
   - 若相等 → 找到目标。

------

### 🔁 动态示意图：

```
初始： l=0        mid        r=N-1
         ↓---------↓----------↓

若 a[mid] < x → 往右移 l
若 a[mid] > x → 往左移 r
```

每一步搜索区间都减半。

------

## 🧱 二、模板代码（基础版）

```c++
int binary_search(vector<int>& a, int x) {
    int l = 0, r = a.size() - 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (a[mid] == x) return mid;   // 找到
        else if (a[mid] < x) l = mid + 1;
        else r = mid - 1;
    }
    return -1; // 没找到
}
```

------

## 🧮 三、模板代码（查找“最小满足条件”）

这是 USACO 和算法竞赛中最常用的二分形式 👇

```c++
int l = 0, r = N; // 区间 [l, r)
while (l < r) {
    int mid = (l + r) / 2;
    if (check(mid)) r = mid;   // 条件成立，往左找更小解
    else l = mid + 1;          // 条件不成立，往右找更大解
}
cout << l; // l 即最小满足条件的值
```

**关键在于：**

- `check(mid)` 表示“当前 mid 是否可行”；
- 整个搜索空间必须**单调**（即可行性不会来回跳变）。

***

### 🐮 USACO 2019 Dec Bronze

**题意简述：**
 给一个字符串，找最小的 k，使得所有长度为 k 的子串都唯一。

**思路分析：**

- 若长度 k 可行（所有子串唯一） → 长度 > k 也可行；
- 若长度 k 不可行 → 长度 < k 也不可行。
   这就构成了单调性结构。

**所以可用二分法** 找最小可行 k。

```c++
bool unique(int k, string s) {
    unordered_set<string> seen;
    for (int i = 0; i + k <= s.size(); i++) {
        string sub = s.substr(i, k);
        if (seen.count(sub)) return false;
        seen.insert(sub);
    }
    return true;
}

int main() {
    int n; string s;
    cin >> n >> s;
    int l = 1, r = n, ans = n;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (unique(mid, s)) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    cout << ans;
}
//二分查找
//哈希表
//string
```

***

## 🧭 USACO 双指针（Two Pointers）

### 🥇 一、核心思想

**双指针（Two Pointers）** 是一种常见的数组遍历与区间控制技巧。
 通过 **两个变量（指针）i, j** 同时在数组上移动，
 避免多重循环，从而把 O(N²) 降为 O(N)。

------

### ✅ 核心原理：

> 当数组或序列具有“**单调性**”时，我们可以让两个指针分别代表 **区间的左右端点**，
>  通过调整它们的位置，动态维护一个满足条件的区间。

------

### 举个直观例子 👇

要找所有满足 `a[j] - a[i] <= K` 的区间：

```c++
int j = 0;
for (int i = 0; i < N; i++) {
    while (j < N && a[j] - a[i] <= K) j++;
    // 此时区间 [i, j-1] 都满足条件
}
```

这就是典型的 “滑动窗口 / 双指针” 思想。

------

## 🧩 二、双指针的常见类型

| 类型                                    | 说明                                  | 示例题目                    |
| --------------------------------------- | ------------------------------------- | --------------------------- |
| **1️⃣ 滑动窗口（Sliding Window）**        | i、j 一起向右移动，维护窗口满足某条件 | Subarray with Sum ≤ K       |
| **2️⃣ 相向双指针（Opposite Directions）** | 从两端开始向中间移动                  | Two Sum、Pair Sum           |
| **3️⃣ 同向双指针（Moving Endpoints）**    | 先固定 i，再移动 j 来扩展范围         | USACO “Photoshoot” 优化     |
| **4️⃣ 多序列指针（Merge Two Lists）**     | 两个有序数组合并                      | USACO “Sleepy Cow Sorting”  |
| **5️⃣ 区间统计（Counting）**              | 用 j 的移动代替内层循环               | USACO “Angry Cows” (Silver) |

------

## 🧱 三、基础模板

### 模板 1：滑动窗口模板

```c++
int j = 0;
for (int i = 0; i < N; i++) {
    while (j < N && condition(i, j)) j++;
    // 此时 [i, j-1] 满足条件
}
```

特点：

- i 右移时，j 永不回退；
- 总复杂度 O(N)。

------

### 模板 2：相向双指针模板

```c++
int l = 0, r = N - 1;
while (l < r) {
    if (a[l] + a[r] == target) { /* found */ }
    else if (a[l] + a[r] < target) l++;
    else r--;
}
```

用于：

- 两数之和
- 找最接近目标值的一对数

------

### 模板 3：归并（Merge）模板

```c++
int i = 0, j = 0;
while (i < A.size() && j < B.size()) {
    if (A[i] < B[j]) result.push_back(A[i++]);
    else result.push_back(B[j++]);
}
```

这是 **归并排序 (Merge Sort)** 的核心思想。

------

## 🧠 四、双指针常考场景（USACO 实例）

- ### 🧮 题目：Pair Sum（双指针求两数之和）

  ### 📄 **题意**

  给定一个**有序数组** `a[0…N−1]` 和一个目标值 `target`，
   判断数组中是否存在两个不同元素 `a[i] + a[j] == target`。

  ------

  ## 💡 **思路分析**

  数组是 **升序** 的，这是关键。
   我们可以用两个指针：

  - `l` 指向最左（最小值）；
  - `r` 指向最右（最大值）。

  每次计算：

  ```c++
  sum = a[l] + a[r]
  ```

  然后根据 sum 和 target 的关系移动指针：

  | 情况            | 说明       | 下一步操作        |
  | --------------- | ---------- | ----------------- |
  | `sum == target` | 找到答案 ✅ | 返回 true         |
  | `sum < target`  | 当前和太小 | `l++`（让和变大） |
  | `sum > target`  | 当前和太大 | `r--`（让和变小） |

  由于数组是升序的，
   当我们右移左指针或左移右指针时，`sum` 的变化是**单调可预测**的。
   这样可以在 **O(N)** 的时间内找到结果。

  ------

  ## 💻 **代码实现**

  ```c++
  bool pair_sum(vector<int>& a, int target) {
      int l = 0, r = a.size() - 1;
      while (l < r) {
          int sum = a[l] + a[r];
          if (sum == target) return true;
          else if (sum < target) l++;
          else r--;
      }
      return false;
  }
  ```

  ------

  ## 🧠 **例子演示**

  假设：

  ```
  a = [1, 3, 4, 6, 8, 10]
  target = 9
  ```

  | 步骤 | l    | r    | a[l]+a[r] | 关系 | 动作   |
  | ---- | ---- | ---- | --------- | ---- | ------ |
  | 1    | 0    | 5    | 1+10=11   | >9   | r--    |
  | 2    | 0    | 4    | 1+8=9     | ==9  | ✅ 找到 |

  结果：存在。

  ------

  ## 📊 **复杂度分析**

  | 项目       | 复杂度 | 说明                  |
  | ---------- | ------ | --------------------- |
  | 时间复杂度 | O(N)   | 每个指针最多移动 N 次 |
  | 空间复杂度 | O(1)   | 仅用常数空间          |

  相比于暴力枚举 `O(N^2)`，效率显著提升。