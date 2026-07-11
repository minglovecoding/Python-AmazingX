## 📚线段树（Segment Tree）

### 🧠 1) 线段树的核心概念

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
