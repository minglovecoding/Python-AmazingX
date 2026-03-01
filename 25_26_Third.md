### USACO 2026 Third Contest, Silver

### Problem 1. Clash!（周期 + 贪心 + 单调函数 + 大 t 处理）

🧩 题意：一共有 N 张牌，编号 1..N，第 i 张牌的费用是 a_i。任意时刻手牌固定有 H 张，手牌是 1..H，其余牌 H+1..N 在“抽牌队列”里，顺序不变（队头到队尾）。假设你从手里打出一张牌 X：

1. 从抽牌队列的队头抽一张牌补到手里；
2. 把刚打出的牌 X 放到抽牌队列的队尾。

所以整套牌是在一个“循环队列”里不断轮转的，只是手牌永远保持 H 张。对每个整数时间点 t=1,2,3：在到达时刻 t 之前，moolixir 先 +1。然后在时刻 t，你可以选择打出至多一张手牌（也可以不打）。只要你的手牌里存在至少一张 win-condition，那么你下一次打出的牌必须是 win-condition。问在给定时间 t 以内，最多能打出多少张 win-condition。

🎯 思路：

1.用“必须打 win 就打最便宜 win；否则打最便宜 non”生成一条确定的打牌序列

2.把每步费用/是否赢牌做前缀和

1 ... L           L+1 ... L+C
|---过渡期---|----完整周期----|
查询逻辑：

如果 t 落在前面 → 二分 prefix

如果 t 很大 →
先吃掉前 L 步
再计算多少个完整周期
再在一个周期内二分补齐

```C++
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
void solve() {
    int N, H;
    cin >> N >> H;
    vector<long long> a(N + 1);
    for (int i = 1; i <= N; ++i) {
        cin >> a[i];
    }
    // K = win-condition 的数量
    int K;
    cin >> K;
    // is_wc[i] = 是否是 win-condition
    vector<bool> is_wc(N + 1, false);
    for (int i = 0; i < K; ++i) {
        int x;
        cin >> x;
        is_wc[x] = true;
    }
    /*
    两个最小堆：
    hand_wc  : 当前手牌里的 win-condition（按费用升序）
    hand_non : 当前手牌里的普通牌（按费用升序）
    策略：
    - 如果手里有 win，必须打 win
    - 并且为了最大化数量，应当打费用最小的
    */
    priority_queue<pair<long long, int>,
                   vector<pair<long long, int>>,
                   greater<pair<long long, int>>> hand_wc;

    priority_queue<pair<long long, int>,
                   vector<pair<long long, int>>,
                   greater<pair<long long, int>>> hand_non;
    // 初始化手牌为 1..H
    for (int i = 1; i <= H; ++i) {
        if (is_wc[i]) {
            hand_wc.push({a[i], i});
        } else {
            hand_non.push({a[i], i});
        }
    }
    // 抽牌队列，初始为 H+1..N
    queue<int> q;
    for (int i = H + 1; i <= N; ++i) {
        q.push(i);
    }
    /*
    预处理步数：
    L = 2N       -> 过渡阶段（确保系统进入稳定周期）
    设置2N是让每张牌都至少经历了一次“被打出 + 回到队尾”的过程。
    C = N-H+1    -> 稳定后周期长度
    total_steps = L + C
    我们预模拟 total_steps 步，
    后面假设从第 L+1 步开始进入周期
    */
    int L = 2 * N;
    int C = N - H + 1;//手牌窗口在环上完整滑动一圈所需要的步数
    int total_steps = L + C;
    /*
    T[step] = 第 step 次打出的牌的费用
    W[step] = 第 step 次是否为 win (1/0)
    prefix_T = 前缀费用和
    prefix_W = 前缀 win 数量
    */
    vector<long long> T(total_steps + 1, 0);
    vector<int> W(total_steps + 1, 0);
    vector<long long> prefix_T(total_steps + 1, 0);
    vector<long long> prefix_W(total_steps + 1, 0);
    /*
    预模拟 total_steps 次打牌顺序
    每一步代表“下一张会打的牌”
    */
    for (int step = 1; step <= total_steps; ++step) {
        pair<long long, int> played;
        // 如果手里有 win，必须打 win
        if (!hand_wc.empty()) {
            played = hand_wc.top();
            hand_wc.pop();
        }
        // 否则打最便宜普通牌
        else {
            played = hand_non.top();
            hand_non.pop();
        }
        // 记录费用
        T[step] = played.first;
        // 记录是否为 win
        W[step] = is_wc[played.second] ? 1 : 0;
        // 更新前缀和
        prefix_T[step] = prefix_T[step - 1] + T[step];
        prefix_W[step] = prefix_W[step - 1] + W[step];
        /*
        更新牌堆结构：
        1）打出的牌放到队尾
        2）从队头抽一张补到手牌
        */
        q.push(played.second);
        int drawn = q.front();
        q.pop();
        if (is_wc[drawn]) {
            hand_wc.push({a[drawn], drawn});
        } else {
            hand_non.push({a[drawn], drawn});
        }
    }
    int Q;
    cin >> Q;
    while (Q--) {
        long long t;
        cin >> t;
        /*
        情况1：
        如果 t 在我们预处理范围内
        直接在 prefix_T 中二分
        找最大 step 使 prefix_T[step] <= t
        */
        if (t <= prefix_T[total_steps]) {
            int low = 0, high = total_steps;
            int ans_idx = 0;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (prefix_T[mid] <= t) {
                    ans_idx = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
            cout << prefix_W[ans_idx] << "\n";
        }
        /*
        情况2：
        t 非常大，超过预处理范围

        认为：
        - 前 L 步为过渡期
        - 后面长度为 C 的区间为周期
        */
        else {
            // 去掉前 L 步的时间
            long long time_after_prefix = t - prefix_T[L];
            // 一个周期的总费用
            long long cycle_T = prefix_T[L + C] - prefix_T[L];
            // 一个周期的 win 数
            long long cycle_W = prefix_W[L + C] - prefix_W[L];
            // 可以完整走多少个周期
            long long num_cycles = time_after_prefix / cycle_T;
            long long rem_time = time_after_prefix % cycle_T;
            // 先加上前 L 步 + 完整周期的 win 数
            long long total_wc = prefix_W[L] + num_cycles * cycle_W;
            /*
            再在一个周期内部二分，
            看剩余 rem_time 还能走多少步
            */
            int low = 0, high = C;
            int ans_j = 0;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (prefix_T[L + mid] - prefix_T[L] <= rem_time) {
                    ans_j = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
            total_wc += (prefix_W[L + ans_j] - prefix_W[L]);
            cout << total_wc << "\n";
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
//前缀合+最小堆+二分查找
```

### Problem 2. Milk Buckets（分层周期翻转 + 丢失流量离散时间模拟问题）

🧩 题意：一叠 N 个桶，第 i 个桶容量为 `a_i`,顶部水龙头：每秒 1 加仑，最底部是一个 pool。每个桶 **正常状态下 **每秒最多接收 1 加仑，容量满时停止累积。**满后** 在 第 t+1 秒开始时，它翻转把所有水倒入下一个桶（最后一桶倒入pool），这一秒不能接水，在第 t+1 秒结束时恢复正常。每个查询修改某个桶容量，问：t 秒后 pool 里有多少水？

🎯 思路：第 i 个桶的翻转时间取决于a1+a2+⋯+ai，每个桶 i 翻转的周期 = a_i + 1。这个题本质在问在 t 秒内，有多少次“穿过最后一个桶”的事件？

逐秒模拟时间复杂度过高，所以整套桶系统可以抽象成：

- 稳定之后，底部桶（第 N 桶）会以某个固定“节拍”把水倒进 pool
- 每次倒入 pool 的量≈ **a_N**（第 N 桶翻转时倒出自身容量）
- 所以答案 ≈（倒入次数）× **a_N**

构造了一组因子 `f[1..N]`，并把它们的乘积当作总周期 **P = Π f[i]**

顶部输入是 1 gallon/second（节拍最快），经历桶 1 后，向桶 2 的“有效输出节拍”会变慢，每一层 i 对节拍的放慢倍数就是 `f[i]`，所以到最底层的整体放慢倍数就是乘积 **P**

```c++
#include <bits/stdc++.h>
using namespace std;
/*
核心思想（非常重要）：
整套“桶翻转系统”可以等价抽象为：
1）第 i 层会把节拍“放慢”一个倍数 f[i]
2）最终底层的整体周期 = 所有 f[i] 的乘积 P
3）系统稳定后，每隔 P 秒，第 N 桶翻转一次
4）每次翻转向 pool 倒出 a[N]
5）前面有一个固定传播延迟 shift = N-1
从水龙头到第 N 桶第一次可能产生稳定输出，需要至少经过每层 1 秒的“传递延迟”
所以先减掉一个N−1 的启动时间
因此：
    pool(t) = floor((t - shift) / P) * a[N]
*/
// 防止乘积爆 1e18
static const long long LIM = (long long)1e18 + 5;
/*
安全乘法：
使用 __int128 计算
如果超过 LIM 就截断
*/
static inline long long cap_mul(long long a, long long b) {
    __int128 x = ( __int128 )a * b;
    if (x > LIM) return LIM;
    return (long long)x;
}
/*
线段树：
维护区间乘积 Π f[i]
因为单点修改，查询全局乘积
*/
struct SegTree {
    int n;
    vector<long long> st; // 存区间乘积
    SegTree(int n=0): n(n), st(4*n+4, 1) {}
    // 建树
    void build(int p, int l, int r, const vector<long long>& arr) {
        if (l == r) { 
            st[p] = arr[l]; 
            return; 
        }
        int m = (l + r) >> 1;
        build(p<<1, l, m, arr);
        build(p<<1|1, m+1, r, arr);
        // 区间乘积
        st[p] = cap_mul(st[p<<1], st[p<<1|1]);
    }
    // 单点更新
    void update(int p, int l, int r, int idx, long long val) {
        if (l == r) { 
            st[p] = val; 
            return; 
        }
        int m = (l + r) >> 1;
        if (idx <= m) 
            update(p<<1, l, m, idx, val);
        else 
            update(p<<1|1, m+1, r, idx, val);
        st[p] = cap_mul(st[p<<1], st[p<<1|1]);
    }

    // 查询整体周期 P
    long long query_all() const { 
        return st[1]; 
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    vector<long long> a(N+1);
    for (int i = 1; i <= N; i++) 
        cin >> a[i];
    //f[i] = 第 i 层对节拍的“放慢倍数”
    vector<long long> f(N+1, 1);
    /*
    计算第 idx 层的放慢倍数
    情况1：idx == 1
        桶1需要 a[1] 秒装满
        下一秒翻转
        所以周期 = a[1] + 1
    情况2：idx >= 2
        第 i 桶要翻转一次
        至少需要 ceil(a[i] / a[i-1]) 次上层翻转
        所以倍数 = ceil(a[i] / a[i-1])
    */
    auto calc_factor = [&](int idx) -> long long {
        if (idx == 1) {
            long long v = a[1] + 1;
            if (v > LIM) v = LIM;
            return v;
        } else {
            long long num = a[idx];
            long long den = a[idx-1];
            // ceil(num / den)
            long long v = (num + den - 1) / den;
            if (v > LIM) v = LIM;
            return v;
        }
    };
    // 初始化所有 f[i]
    for (int i = 1; i <= N; i++) 
        f[i] = calc_factor(i);
    // 用线段树维护乘积
    SegTree st(N);
    st.build(1, 1, N, f);
    int Q;
    cin >> Q;
    while (Q--) {
        int i;
        long long v, t;
        cin >> i >> v >> t;
        //更新桶容量
        a[i] = v;
        /*
        修改a[i]只会影响：
        f[i]     （依赖 a[i]和a[i-1]）
        f[i+1]   （依赖 a[i+1]和a[i]）
        */
        f[i] = calc_factor(i);
        st.update(1, 1, N, i, f[i]);
        if (i+1 <= N) {
            f[i+1] = calc_factor(i+1);
            st.update(1, 1, N, i+1, f[i+1]);
        }
        //整体稳定周期
        long long P = st.query_all(); 
        /*
        启动传播延迟：
        至少经过 N-1 秒水才可能传到第 N 层
        */
        long long shift = (long long)(N - 1);
        //计算第 N 桶翻转次数
        long long dumps = 0;
        if (t > shift) {
            long long x = t - shift;
            dumps = x / P;
        }
        //每次翻转倒出 a[N]
        __int128 ans = ( __int128 )dumps * a[N];
        cout << (long long)ans << "\n";
    }
    return 0;
}
```

### Problem 3. Point Elimination

题意：在只能交换 y 坐标的前提下，是否可以把所有点两两配对，使每一对之间曼哈顿距离为 1？

```c++
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
Result: solve_multiset 返回的一维配对可行性信息

possible : 是否能把 multiset S 完全配成 N/2 对，每对差值只能是 0 或 1
min_sum  : 在所有可行配对里，“差 1 的对数”的最小值
max_sum  : 在所有可行配对里，“差 1 的对数”的最大值
parity   : 所有可行方案中，“差 1 的对数”的奇偶（0=偶,1=奇）
          这一点很关键：在每个连续值组件内，差1对数的奇偶是被频次奇偶强制固定的
*/
struct Result {
    bool possible;
    long long min_sum;
    long long max_sum;
    long long parity;
};

/*
solve_multiset(S):
给一个排好序的整数 multiset S（例如所有 x 或所有 y），判断能否把所有元素两两配对，
每对要么相等(差0)，要么相邻(差1)。
并返回“差1对数”的最小/最大范围以及固定奇偶。

核心模型（在每个连续整数组件内）：
- 组件值为 v0..vL，频次为 f[0..L]
- 令 t_i 为在 v_i 与 v_{i+1} 之间配的差1对数
- 对每个点值 v_i：剩余 f[i]-t_{i-1}-t_i 必须为非负偶数（内部用差0对消化）
*/
Result solve_multiset(const vector<int>& S) {
    if (S.empty()) {
        return {true, 0, 0, 0};
    }

    // 1) 压缩成 (值, 频次) 列表
    vector<pair<int, int>> freqs;
    int cur_val = S[0];
    int cur_count = 1;
    for (size_t i = 1; i < S.size(); ++i) {
        if (S[i] == cur_val) {
            cur_count++;
        } else {
            freqs.push_back({cur_val, cur_count});
            cur_val = S[i];
            cur_count = 1;
        }
    }
    freqs.push_back({cur_val, cur_count});

    long long total_min = 0;     // 各组件 min(差1对数) 之和
    long long total_max = 0;     // 各组件 max(差1对数) 之和
    long long total_parity = 0;  // 各组件 min 的奇偶累加（等价于总奇偶）

    // f 存放当前“连续整数组件”的频次数组
    // 例如值为 5,6,7 且频次为 3,1,2，则 f=[3,1,2]
    vector<int> f;

    /*
    处理一个连续组件 f[0..L]（长度 L+1 个点值，L 条边）：
    - 变量 t_i 表示第 i 条边（值 i 与 i+1）上配的“差1对数”
    - 约束：对每个 i，f[i]-t_{i-1}-t_i 必须为非负偶数
    - 我们要求 sum(t_i) 的最小/最大可能值以及是否可行
    */
    auto process_component = [&]() -> bool {
        if (f.empty()) return true;

        int L = (int)f.size() - 1; // L 条边（若 f.size()==1，则 L=0 无边）

        // 组件只有一个值：只能内部配(差0)。所以频次必须为偶数。
        if (L == 0) {
            if (f[0] % 2 != 0) {
                f.clear();
                return false;
            }
            f.clear();
            return true;
        }

        /*
        r[i] = t_i mod 2
        由于 f[i]-t_{i-1}-t_i 必须为偶数：
            (f[i] mod2) = (t_{i-1}+t_i mod2)
        在路径上可以递推得到每条边的奇偶 r[i]，并且最后必须和 f[L] 一致，否则无解。
        */
        vector<int> r(L, 0);
        r[0] = f[0] % 2;
        for (int i = 1; i < L; ++i) {
            // 由 f[i] ≡ r[i-1] + r[i] (mod2) 得 r[i] ≡ f[i] - r[i-1]
            r[i] = (f[i] - r[i - 1]) % 2;
            if (r[i] < 0) r[i] += 2;
        }

        // 边界条件：f[L] ≡ r[L-1] (mod2) 必须成立（因为 t_L=0）
        if (r[L - 1] != f[L] % 2) {
            f.clear();
            return false;
        }

        /*
        计算每条边 t_i 的可取上界 U[i]（还要满足奇偶 r[i]）：
        基础上界：t_i <= min(f[i], f[i+1])
        但还要保证左端点 i 留给左边的最小需求（r[i-1]）后，仍有足够给这条边用。
        */
        vector<int> U(L, 0);
        for (int i = 0; i < L; ++i) {
            // 左端点 i 至少要留给左边边 r[i-1]（如果 i>0）
            int left_need = (i == 0 ? 0 : r[i - 1]);
            int limit = min(f[i + 1], f[i] - left_need);

            // 调整到满足奇偶 r[i]
            if (limit % 2 != r[i]) limit--;
            U[i] = limit;

            // 最小也得 >= r[i]，否则连奇偶要求的最小 t_i 都做不到
            if (U[i] < r[i]) {
                f.clear();
                return false;
            }
        }

        // 最小差1对数：每条边取最小满足奇偶的 r[i]（0 或 1）
        long long min_S = 0;
        for (int i = 0; i < L; ++i) {
            min_S += r[i];
        }

        /*
        求最大差1对数：
        从右往左贪心决定 t_i（用 P[i] 表示），尽量大，
        同时保证右端点 i+1 不会被用爆：
            t_i + (t_{i+1} 在右边消耗的量) <= f[i+1]
        用 P[i+1] 代表右侧边对 v_{i+1} 的消耗。
        */
        vector<int> P(L + 1, 0);
        P[L] = 0; // 最右端无边

        long long max_S = 0;
        for (int i = L - 1; i >= 0; --i) {
            // 不能超过这条边的上界 U[i]
            // 也不能让右端点 i+1 被右侧用掉 P[i+1] 后不够给这条边
            int limit = min(U[i], f[i + 1] - P[i + 1]);

            // 调整奇偶到 r[i]
            if (limit % 2 != r[i]) limit--;
            P[i] = limit;
            max_S += P[i];
        }

        // 组件结果累加到总结果
        total_min += min_S;
        total_max += max_S;

        // 由于每个组件内“可行 sum(t_i) 的奇偶固定”，总奇偶也固定
        total_parity = (total_parity + min_S) % 2;

        f.clear();
        return true;
    };

    /*
    将 freqs 按“值是否连续”拆成多个组件：
    例如值序列 1,2,3 是一组件；5,6 是另一组件；中间断开就必须独立处理
    */
    for (size_t i = 0; i < freqs.size(); ++i) {
        f.push_back(freqs[i].second);
        if (i + 1 == freqs.size() || freqs[i + 1].first != freqs[i].first + 1) {
            if (!process_component()) {
                return {false, 0, 0, 0};
            }
        }
    }

    return {true, total_min, total_max, total_parity};
}

void solve() {
    int N;
    if (!(cin >> N)) return;

    vector<int> X(N), Y(N);
    for (int i = 0; i < N; ++i) {
        cin >> X[i] >> Y[i];
    }

    // 只需要 x multiset 与 y multiset（交换 y 使得点间“哪个 y 跟哪个 x”可重排）
    sort(X.begin(), X.end());
    sort(Y.begin(), Y.end());

    // resX: X 轴上可实现的“差1对数 H”的范围与奇偶（差1=水平对）
    // resY: Y 轴上可实现的“差1对数 V”的范围与奇偶（差1=竖直对）
    Result resX = solve_multiset(X);
    Result resY = solve_multiset(Y);

    if (!resX.possible || !resY.possible) {
        cout << "NO\n";
        return;
    }

    long long N_half = N / 2;

    // H 的奇偶固定为 resX.parity；V 的奇偶固定为 resY.parity
    long long X_par = resX.parity;
    long long Y_par = resY.parity;

    /*
    因为 H + V = N/2，
    若 V 的奇偶固定为 Y_par，那么 H 的奇偶必须等于 (N/2 - Y_par) mod2
    这就是下面的奇偶必要条件。
    */
    long long target_parity = (N_half - Y_par) % 2;
    if (target_parity < 0) target_parity += 2;

    if (X_par != target_parity) {
        cout << "NO\n";
        return;
    }

    /*
    现在只剩“范围交集”判定：
    - H 必须在 [resX.min_sum, resX.max_sum]
    - 同时 V = N/2 - H 必须在 [resY.min_sum, resY.max_sum]
      => H 必须在 [N/2 - resY.max_sum, N/2 - resY.min_sum]
    所以取交集区间 [L_bound, R_bound]。
    */
    long long L_bound = max(resX.min_sum, N_half - resY.max_sum);
    long long R_bound = min(resX.max_sum, N_half - resY.min_sum);

    // 再检查交集里是否存在满足奇偶的 H
    if (L_bound <= R_bound) {
        long long H_start = L_bound;
        if (H_start % 2 != X_par) {
            H_start++; // 调到正确奇偶
        }
        if (H_start <= R_bound) {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    if (cin >> T) {
        while (T--) {
            solve();
        }
    }
    return 0;
}
```