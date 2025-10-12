#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Restr {
    ll r, l;
    int t;
    bool operator<(const Restr& o) const {
        if (r != o.r) return r < o.r;
        if (l != o.l) return l < o.l;
        return t < o.t;
    }
};

void solve() {
    int N, K;
    if (!(cin >> N >> K)) return;

    vector<ll> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];

    vector<Restr> R(K);
    for (int i = 0; i < K; ++i) {
        ll l, r; int t;
        cin >> l >> r >> t;
        R[i] = {r, l, t}; // 与 Python: (r, l, t) 一致
    }

    sort(R.begin(), R.end()); // 按 r 递增
    sort(A.begin(), A.end()); // 树位置排序

    vector<ll> stk;      // 可选且 <= 当前 r 的树（栈，后进先出，保证尽量取靠右）
    vector<ll> planted;  // 已“保留”的树，保持有序（用于区间计数）
    planted.reserve(N);
    stk.reserve(N);

    int idx = 0; // 指向 A 中下一个 <= r 的位置

    for (const auto& q : R) {
        // 把所有 <= r 的树加入栈
        while (idx < N && A[idx] <= q.r) {
            stk.push_back(A[idx]);
            ++idx;
        }

        // 计算 planted 中位于 [l, r] 的个数：upper_bound - lower_bound
        auto itL = lower_bound(planted.begin(), planted.end(), q.l);
        auto itR = upper_bound(planted.begin(), planted.end(), q.r);
        int current_t = int(itR - itL);

        // 需要补到 t：每次从 stk 末尾弹出（即尽可能靠右的树），并插入到 planted（有序）
        while (current_t < q.t) {
            if (stk.empty()) {
                // 按题意“不应发生”（初始可行），这里防御性退出
                // 你也可以改为 assert(false);
                // cerr << "No available tree but constraint not satisfied\n";
                break;
            }
            ll pos = stk.back();
            stk.pop_back();
            auto it = lower_bound(planted.begin(), planted.end(), pos);
            planted.insert(it, pos); // 保持有序
            ++current_t;
        }
    }

    cout << (N - (int)planted.size()) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) solve();
    return 0;
}
