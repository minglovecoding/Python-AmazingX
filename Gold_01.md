## 🏅USACO金组

| 知识模块                                               | 主要内容                                                | 对应金组真题                                                 |
| ------------------------------------------------------ | ------------------------------------------------------- | ------------------------------------------------------------ |
| **线性与序列 DP。                                   ** | 状态定义、多维状态、连续分组、序列合并、最优值转移      | [Teamwork](https://usaco.org/index.php?page=viewproblem2&cpid=863)（2018.12）：枚举最后一组的长度，进行分组 DP；[Cow Checklist](https://usaco.org/index.php?page=viewproblem2&cpid=670)（2016.12）：记录两类奶牛各访问多少头，以及当前停在哪一类 |
| **背包 DP**                                            | 0/1 背包、完全背包、资源限制、状态压缩、排序后背包      | [Bribing Friends](https://usaco.org/index.php?page=viewproblem2&cpid=1257)（2022.12）：两种资源、排序与背包状态优化；[Talent Show](https://usaco.org/index.php?page=viewproblem2&cpid=839)（2018 US Open）：二分收益比，用背包进行可行性判定 |
| **区间 DP**                                            | 按区间长度枚举、区间划分、合并、端点关系                | [248](https://usaco.org/index.php?page=viewproblem2&cpid=647)（2016 US Open）：判断区间能否合并成一个数；[Modern Art 3](https://usaco.org/index.php?page=viewproblem2&cpid=1114)（2021.02）：合并同色位置的染色操作，求最少笔画 |
| **状态压缩 DP**                                        | 位运算表示集合、子集状态、集合转移、排列计数与优化      | [Guard Mark](https://usaco.org/index.php?page=viewproblem2&cpid=494)（2014.12）：用集合表示已选择的奶牛，维护堆叠安全值；[Uddered but not Herd](https://usaco.org/index.php?page=viewproblem2&cpid=1089)（2021.01）：用集合表示已安排的字母，优化字母表顺序 |
| **计数 DP**                                            | 方案数、取模、分类计数、避免重复、乘法原理              | [Cow Poetry](https://usaco.org/index.php?page=viewproblem2&cpid=897)（2019.01）：统计音节组合，再根据押韵要求合并方案；[Drought](https://usaco.org/index.php?page=viewproblem2&cpid=1185)（2022.01）：统计可行初始数组，并按 N 的奇偶分类 |
| **DP 转移优化**                                        | 前缀和优化、预处理区间代价、维护最优转移、滚动数组      | [Drought](https://usaco.org/index.php?page=viewproblem2&cpid=1185)（2022.01）：用前缀和加速状态求和；[Moortal Cowmbat](https://usaco.org/index.php?page=viewproblem2&cpid=971)（2019.12）：最短路预处理转换费用，结合前缀和与分段 DP |
| **树形 DP 与换根**                                     | 子树状态、父子合并、树上计数、换根转移                  | [Barn Painting](https://usaco.org/index.php?page=viewproblem2&cpid=766)（2017.12）：按节点颜色统计子树染色方案；[Directory Traversal](https://usaco.org/index.php?page=viewproblem2&cpid=814)（2018.02）：先统计子树文件，再换根计算路径长度总和 |
| **树上倍增、LCA 与 DFS 序**                            | 最近公共祖先、祖先跳跃、子树区间化、树上路径信息        | [Cow Land](https://usaco.org/index.php?page=viewproblem2&cpid=921)（2019.02）：LCA、DFS 序与动态路径异或；[Milk Visits](https://usaco.org/index.php?page=viewproblem2&cpid=970)（2019.12）：查询树上路径是否出现指定类型，可结合 LCA 与离线处理 |
| **BFS 与扩展状态图**                                   | 多源 BFS、0-1 BFS、位置与方向或类型组成状态、隐式图建模 | [Replication](https://usaco.org/index.php?page=viewproblem2&cpid=1065)（2020.12）：多源 BFS 求岩石距离，再搜索中心并扩张覆盖；[Telephone](https://usaco.org/index.php?page=viewproblem2&cpid=1090)（2021.01）：位置与类型组成状态，可建模为 0-1 BFS；[Lasers and Mirrors](https://usaco.org/index.php?page=viewproblem2&cpid=671)（2016.12）：将横线、竖线之间的转向关系建图，求最少反射次数 |
| **带权最短路**                                         | Dijkstra、Floyd、多源最短路、增加状态维度、虚拟源点     | [Fine Dining](https://usaco.org/index.php?page=viewproblem2&cpid=861)（2018.12）：先求到终点距离，再以不同初始距离进行多源 Dijkstra；[Why Did the Cow Cross the Road](https://usaco.org/index.php?page=viewproblem2&cpid=717)（2017.02）：将位置与步数模 3 组成状态，运行 Dijkstra |
| **拓扑排序与 DAG DP**                                  | 有向无环图、入度、先后约束、最长路、字典序拓扑序        | [Timeline](https://usaco.org/index.php?page=viewproblem2&cpid=1017)（2020.02）：将时间约束转成有向边，按拓扑序更新最早时间；[Milking Order](https://usaco.org/index.php?page=viewproblem2&cpid=838)（2018 US Open）：二分有效约束数量，拓扑判环并构造字典序最小顺序 |
| **并查集**                                             | 连通块合并、集合大小、离线加边、等价关系传播            | [Closing the Farm](https://usaco.org/index.php?page=viewproblem2&cpid=646)（2016 US Open）：倒序开放节点，维护连通性；[Favorite Colors](https://usaco.org/index.php?page=viewproblem2&cpid=1042)（2020 US Open）：传播必须同色的约束，合并等价集合 |
| **最小生成树**                                         | Kruskal、Prim、瓶颈生成树、减少候选边                   | [Moocast](https://usaco.org/index.php?page=viewproblem2&cpid=669)（2016.12）：最小化使全图连通所需的最大边权；[Moo Network](https://usaco.org/index.php?page=viewproblem2&cpid=1211)（2022.02）：利用纵坐标范围小的性质筛选候选边，再求最小生成树 |
| **树状数组**                                           | 单点修改、前缀和、区间计数、逆序对、排名统计            | [Haircut](https://usaco.org/index.php?page=viewproblem2&cpid=1041)（2020 US Open）：统计逆序对，按较小值分类累加贡献；[Why Did the Cow Cross the Road III](https://usaco.org/index.php?page=viewproblem2&cpid=719)（2017.02）：统计交错出现的端点对 |
| **线段树**                                             | 单点修改、区间求和、区间最值、信息合并                  | [Marathon](https://usaco.org/index.php?page=viewproblem2&cpid=495)（2014.12）：维护路径长度和跳过一个检查点的最大收益；[Cow Land](https://usaco.org/index.php?page=viewproblem2&cpid=921)（2019.02）：结合树上展开维护修改与路径异或查询 |
| **贪心与单调结构**                                     | 交换论证、不可逆决策、单调栈、二分定位                  | [Dishwashing](https://usaco.org/index.php?page=viewproblem2&cpid=922)（2019.02）：维护多个盘子栈的顺序关系，判断可处理的最长前缀；[Sleepy Cow Sorting](https://usaco.org/index.php?page=viewproblem2&cpid=898)（2019.01）：保留递增后缀，结合树状数组构造插入位置 |
| **双指针与区间维护**                                   | 滑动窗口、维护区间和与最大值、单调队列、multiset        | [Haybale Feast](https://usaco.org/index.php?page=viewproblem2&cpid=767)（2017.12）：双指针维护美味值总和，用单调队列或 multiset 维护最大辣度 |
| **二分答案与综合判定**                                 | 答案单调性、二分加 DP、二分加图算法、分数规划           | [Talent Show](https://usaco.org/index.php?page=viewproblem2&cpid=839)（2018 US Open）：二分比值，转成背包判定；[Milking Order](https://usaco.org/index.php?page=viewproblem2&cpid=838)（2018 US Open）：二分约束前缀，用拓扑排序检查 |
| **离线处理与逆向思考**                                 | 重排查询、倒序操作、删除转添加、状态单调性              | [Closing the Farm](https://usaco.org/index.php?page=viewproblem2&cpid=646)（2016 US Open）：关闭转成倒序开放；[Farm Updates](https://usaco.org/index.php?page=viewproblem2&cpid=1186)（2022.01）：倒序恢复道路与活跃农场，传播相关状态 |
| **组合计数与容斥**                                     | 贡献法、补集、容斥、子集枚举、模运算、快速幂            | [Cowpatibility](https://usaco.org/index.php?page=viewproblem2&cpid=862)（2018.12）：枚举口味子集，用容斥统计相容奶牛对；[Help Yourself](https://usaco.org/index.php?page=viewproblem2&cpid=1018)（2020.02）：将所有子集的连通块数量转成贡献求和 |
| **数论与排列周期**                                     | 质数、质因数分解、最大公约数、最小公倍数、置换环        | [Exercise](https://usaco.org/index.php?page=viewproblem2&cpid=1043)（2020 US Open）：置换周期等于环长的最小公倍数，转成质数幂选择与 DP |
| **概率与期望**                                         | 概率分布、期望、最优决策、概率 DP、重复转移优化         | [Cow Camp](https://usaco.org/index.php?page=viewproblem2&cpid=1210)（2022.02）：二项分布、停止或继续的决策，以及期望递推优化 |
| **字符串与哈希**                                       | 字符串哈希、子串判等、集合判重、二分长度                | [Bovine Genomics](https://usaco.org/index.php?page=viewproblem2&cpid=741)（2017 US Open）：寻找能区分两组字符串的最短公共位置区间，可结合哈希与二分 |
| **矩形几何与二维优化**                                 | 坐标处理、二维差分、二维前缀和、矩形枚举、最大子矩形    | [Painting the Barn](https://usaco.org/index.php?page=viewproblem2&cpid=923)（2019.02）：二维差分恢复涂层，转成增益矩阵并选择两个不相交矩形；[Square Pasture](https://usaco.org/index.php?page=viewproblem2&cpid=1067)（2020.12）：固定边界、枚举正方形覆盖集合并去重 |
| **构造与不变量**                                       | 必要条件、结构转换、构造合法方案、正确性证明            | [Tests for Haybales](https://usaco.org/index.php?page=viewproblem2&cpid=1187)（2022.01）：将第一个越界位置转成父节点，利用树的层级与 DFS 顺序构造数组；[Drought](https://usaco.org/index.php?page=viewproblem2&cpid=1185)（2022.01）：利用交错和不变量解释奇偶差异 |

## 📚线段树（Segment Tree）

###  1) 线段树的核心概念

```C++
                         st[1] = 52
                           [1,6] 
                     /               \
             st[2] = 20            st[3] = 32
                [1,3]                  [4,6]
              /       \              /       \
      st[4] = 9   st[5] = 11  st[6] = 29  st[7] = 3
         [1,2]       [3,3]       [4,5]       [6,6]
         /   \                    /   \
   st[8]=3  st[9]=6       st[12]=21 st[13]=8
     [1,1]    [2,2]          [4,4]    [5,5]
     //a = {0, 3, 6, 11, 21, 8, 3};
     //        1  2   3   4  5  6
```

给你一个数组 `a[1..N]`，要反复做两类操作：

1. 查询一个区间 [L, R] 的信息
    例如：区间和、区间最小值、区间最大值、最大子段和、gcd……
2. 修改数组
   - 单点改：`a[pos] = x`
   - 区间改：`a[L..R] += x` 或 `赋值成 x`

如果用朴素方法：

- 每次区间求和/最值 O(N)
- 多次操作会炸（N,Q 到 2e5 时必超时）

而**线段树**把每次操作降到 **O(log N)**。

```java
                         [1,8]
                   /               \
             [1,4]                   [5,8]
           /       \               /        \
       [1,2]       [3,4]       [5,6]        [7,8]
      /    \      /     \      /     \      /     \
   [1]    [2]  [3]     [4]  [5]     [6]  [7]     [8]
```

线段树是一棵**“把数组区间不断二分”的二叉树**：

- 根节点管 `[1, N]`
- 左儿子管 `[1, mid]`
- 右儿子管 `[mid+1, N]`
- 直到区间长度为 1（叶子节点）

`每个节点存一个“这段区间的**答案**”（比如 sum/min/max）。

每次查询/修改都沿着树往下走：

- 树高约 `log2(N)`
- 你最多访问 `O(log N)` 层
- 所以单次操作 `O(log N)`

因此时间复杂度是**O(log N)**。

### 📌 2）区间查询 + 单点修改

```c++
//求区间和与单点修改
//如果是要求最小值与最大值，只需要把mergeVal值修改即可
#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    int n;
    vector<long long> st; // st[p] 存节点 p 对应区间的答案（这里是区间和）

    SegTree(int n=0) { init(n); }

    void init(int n_) {
        n = n_;
        st.assign(4 * n + 4, 0);
    }

    // 合并左右儿子的信息
    long long mergeVal(long long leftVal, long long rightVal) {
        return leftVal + rightVal; // 区间和
    }

    // 建树：把原数组 a[1..n] 建到 st 里
    void build(int p, int l, int r, const vector<long long>& a) {
      //p：当前线段树节点的编号
      //l：当前节点管理区间的左端点
      //r：当前节点管理区间的右端点
      //a：需要建立线段树的原数组
        if (l == r) {
            st[p] = a[l];
            return;
        }
        int m = (l + r) >> 1;
        build(p<<1, l, m, a);
        build(p<<1|1, m+1, r, a);
        st[p] = mergeVal(st[p<<1], st[p<<1|1]);
    }

    // 单点修改idx：a[idx] = val
    void update(int p, int l, int r, int idx, long long val) {
        if (l == r) {   //如果是叶子节点，直接更新
            st[p] = val;
            return;
        }
        int m = (l + r) >> 1;
        if (idx <= m) update(p<<1, l, m, idx, val); //更新左子树
        else update(p<<1|1, m+1, r, idx, val);      //更新右子树
        st[p] = mergeVal(st[p<<1], st[p<<1|1]);
    }

    // 区间查询：求 [ql, qr] 的区间和
    long long query(int p, int l, int r, int ql, int qr) {//线段树节点 p管[l, r]区间
      //p 当前线段树节点编号
      //[l,r] 当前节点 p 管理的原数组区间
      //[ql,qr] 用户真正想查询的区间
        if (ql <= l && r <= qr) return st[p]; 
     // [l,r] 被 [ql,qr]完全覆盖，能整段使用，就不继续访问叶子节点。
        int m = (l + r) >> 1;
        long long ans = 0;
        //如果查询区间左端 ql 不在右半边之外（即查询和左儿子有交集）
        if (ql <= m) ans = mergeVal(ans, query(p<<1, l, m, ql, qr));
        //如果查询区间右端 qr 覆盖到右半边（即查询和右儿子有交集）
        if (qr >  m) ans = mergeVal(ans, query(p<<1|1, m+1, r, ql, qr));
        return ans;
    }//例query(1, 0, 5, 2, 4);
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<long long> a(n+1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    SegTree st(n);
    st.build(1, 1, n, a);

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int pos; long long x;
            cin >> pos >> x;
            st.update(1, 1, n, pos, x); //单点修改
        } else {
            int l, r;
            cin >> l >> r;
            cout << st.query(1, 1, n, l, r) << "\n"; //查询区间和
        }
    }
}
```

#### 改成区间最小值/最大值怎么改？

- 把 `mergeVal` 改成 `min` 或 `max`
- 查询的初值要换成“单位元”：
  - min：`+INF`
  - max：`-INF`

### 📌 3）区间加法 + 区间修改（Lazy Propagation）

- `add(L, R, x)`：让区间每个数都加 x
- `sum(L, R)`：区间和

如果还用上面的版本，你得改每个点，会变成 O(N)。

### 所以要用 **lazy 标记**：节点先“记账”，等需要往下走时再下放。

> Lazy值尽量停留在大的区间。
>
> 这个区间下面的所有元素，还“欠”一次 +lazy[p] 的更新

```c++
                              [1,8]
                               lazy=0
                     /---------------------\
                 [1,4]                   [5,8]
                  0                         0
              /---------\              /---------\
           [1,2]       [3,4]*        [5,6]*     [7,8]
             0           lazy=5        lazy=5      0
          /-----\     /-----\      /-----\     /-----\
        [1]    [2]  [3]    [4]  [5]    [6]  [7]    [8]
         0      0     0      0     0      0     0      0
```

> `1 l r x`：对 `[l,r]` 全部加 `x`
>  `2 l r`：查询 `[l,r]` 区间和

```C++
#include <bits/stdc++.h>
using namespace std;

struct SegTreeLazy {
    int n;
    vector<long long> st;    // 区间和
    vector<long long> lazy;  // 懒标记：这个区间整体需要加多少

    SegTreeLazy(int n=0) { init(n); }

    void init(int n_) { //线段树大小通常为原数据的4倍
        n = n_;
        st.assign(4*n+4, 0);
        lazy.assign(4*n+4, 0);
    }

    void build(int p, int l, int r, const vector<long long>& a) {
        if (l == r) {
            st[p] = a[l];
            return;
        }
        int m = (l + r) >> 1;
        build(p<<1, l, m, a);
        build(p<<1|1, m+1, r, a);
        st[p] = st[p<<1] + st[p<<1|1];
    }

    // 把“给节点 p 的区间整体加 add”落实到 st[p]，并把 lazy[p] 累加
    void apply(int p, int l, int r, long long add) {
        st[p] += add * (r - l + 1);
        lazy[p] += add;
    }

    // 下放懒标记：在访问子区间前，把父区间欠的账分给左右儿子
    void push(int p, int l, int r) {
        if (lazy[p] == 0) return;
        if (l == r) { // 叶子节点不需要/不能下传
            lazy[p] = 0;
            return;
        }
        int m = (l + r) >> 1;
        apply(p<<1, l, m, lazy[p]);
        apply(p<<1|1, m+1, r, lazy[p]);
        lazy[p] = 0;
    }

    // 区间加法：a[ql..qr] += val
    void rangeAdd(int p, int l, int r, int ql, int qr, long long val) {
        if (ql <= l && r <= qr) {
            apply(p, l, r, val);
            return;
        }
        push(p, l, r); //要往下走前必须 push，确保子树数据正确
        int m = (l + r) >> 1;
        if (ql <= m) rangeAdd(p<<1, l, m, ql, qr, val);
        if (qr >  m) rangeAdd(p<<1|1, m+1, r, ql, qr, val);
        st[p] = st[p<<1] + st[p<<1|1];
    }

    // 区间求和
    long long rangeSum(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return st[p];
        push(p, l, r);
        int m = (l + r) >> 1;
        long long ans = 0;
        if (ql <= m) ans += rangeSum(p<<1, l, m, ql, qr);
        if (qr >  m) ans += rangeSum(p<<1|1, m+1, r, ql, qr);
        return ans;
    }

    // ===== 对外封装（写题更方便）=====
    void build(const vector<long long>& a) {
        // 要求 a 是 1-index（a[0] 可随便放）
        build(1, 1, n, a);
    }
    void rangeAdd(int l, int r, long long val) {
        rangeAdd(1, 1, n, l, r, val);
    }
    long long rangeSum(int l, int r) {
        return rangeSum(1, 1, n, l, r);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    SegTreeLazy seg(n);
    seg.build(a);

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r;
            long long x;
            cin >> l >> r >> x;
            seg.rangeAdd(l, r, x);
        } else if (type == 2) {
            int l, r;
            cin >> l >> r;
            cout << seg.rangeSum(l, r) << "\n";
        }
    }
    return 0;
}
//a={0, 3, 6, 11, 21, 8, 3};
//1：[4,6] +1
//2: [4,5] +1
```
```C++
                          st[1]=55
                           [1,6]
                     /                 \
               st[2]=20               st[3]=35
                [1,3]                [4,6]
              lazy=0                 lazy=1
              /       \              /       \
         st[4]=9    st[5]=11    st[6]=29   st[7]=3
          [1,2]       [3,3]       [4,5]      [6,6]
          lazy=0      lazy=0       lazy=0     lazy=0
          /   \                    /   \
     st[8]=3 st[9]=6        st[12]=21 st[13]=8
       [1,1]   [2,2]           [4,4]    [5,5]
```

// [SegTree_Video](https://www.bilibili.com/video/BV1vhPoeXEFf/?spm_id_from=333.337.search-card.all.click&vd_source=1161690079eded438f62622c2b6c537f)

> 2026 Third Contest-Problem 2. Milk Buckets

***

[P3372](https://www.luogu.com.cn/problem/P3372)

```c++
#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

struct SegTree {
    int n;
    vector<int64> sum;   // 当前区间和
    vector<int64> lazy;  // 懒标记：该区间整体要加的值

    SegTree(int n=0): n(n), sum(4*n+4, 0), lazy(4*n+4, 0) {}

    void build(int p, int l, int r, const vector<int64>& a) {
        if (l == r) {
            sum[p] = a[l];
            return;
        }
        int m = (l + r) >> 1;
        build(p<<1, l, m, a);
        build(p<<1|1, m+1, r, a);
        sum[p] = sum[p<<1] + sum[p<<1|1];
    }

    // 把“给区间整体 +v”作用到节点 p 上
    inline void apply(int p, int l, int r, int64 v) {
        sum[p] += v * (r - l + 1);
        lazy[p] += v;
    }

    // 把 p 的懒标记下推到子节点
    void push(int p, int l, int r) {
        if (lazy[p] == 0 || l == r) return;
        int m = (l + r) >> 1;
        apply(p<<1, l, m, lazy[p]);
        apply(p<<1|1, m+1, r, lazy[p]);
        lazy[p] = 0;
    }

    // 区间加：给 [ql, qr] 每个元素 +v
    void range_add(int p, int l, int r, int ql, int qr, int64 v) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            apply(p, l, r, v);
            return;
        }
        push(p, l, r);
        int m = (l + r) >> 1;
        range_add(p<<1, l, m, ql, qr, v);
        range_add(p<<1|1, m+1, r, ql, qr, v);
        sum[p] = sum[p<<1] + sum[p<<1|1];
    }

    // 区间和查询：返回 [ql, qr] 的和
    int64 range_sum(int p, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return sum[p];
        push(p, l, r);
        int m = (l + r) >> 1;
        return range_sum(p<<1, l, m, ql, qr) +
               range_sum(p<<1|1, m+1, r, ql, qr);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int64> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    SegTree st(n);
    st.build(1, 1, n, a);

    while (m--) {
        int tp;
        cin >> tp;
        if (tp == 1) {
            int x, y;
            int64 k;
            cin >> x >> y >> k;
            st.range_add(1, 1, n, x, y, k);
        } else {
            int x, y;
            cin >> x >> y;
            cout << st.range_sum(1, 1, n, x, y) << "\n";
        }
    }
    return 0;
}
```
