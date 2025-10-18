#include <bits/stdc++.h>
using namespace std;
using int64 = long long; // 题目范围 1 ≤ a,b,c,d ≤ 1e18

// 处理单个测试用例
long long solve(long long a, long long b, long long c, long long d) {
    long long ops = 0;
    while (true) {
        // 如果已经到达目标
        if (a == c && b == d) return ops;

        // 确保 c >= d，否则交换两堆（对应 Python 里的 if c < d: swap）
        if (c < d) {
            swap(a, b);
            swap(c, d);
        }

        // 不可能情况
        if (a > c || b > d || d == 0) return -1;

        // 如果 b == d，可以直接检查 c 是否能通过加若干次 d 变成目标
        if (b == d && (c - a) % d == 0) {
            ops += (c - a) / d;
            return ops;
        }

        // 否则，做一次类似 "c %= d" 的大步跳跃
        ops += c / d;
        c %= d;
    }
    return ops;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        long long a, b, c, d;
        cin >> a >> b >> c >> d;
        cout << solve(a, b, c, d) << "\n";
    }
    return 0;
}
