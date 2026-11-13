#include <bits/stdc++.h>
using namespace std;

struct Friend {
    int popularity;
    int cost;
    int exchange;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, A, B;
    cin >> N >> A >> B;

    vector<Friend> friends(N);
    for (auto &f : friends) {
        cin >> f.popularity >> f.cost >> f.exchange;
    }

    // 预算不超过 money、cones 时的最大人气
    vector<vector<int>> dp(A + 1, vector<int>(B + 1, 0));

    for (const auto &f : friends) {
        // 不邀请当前朋友
        vector<vector<int>> next = dp;

        for (int money = 0; money <= A; money++) {
            for (int cones = 0; cones <= B; cones++) {
                int minDiscount = max(0, f.cost - money);
                int maxDiscount = min(f.cost, cones / f.exchange);

                // 枚举用冰激凌抵扣多少现金
                for (int discount = minDiscount;
                     discount <= maxDiscount;
                     discount++) {

                    int moneyNeeded = f.cost - discount;
                    int conesNeeded = discount * f.exchange;

                    // 给当前朋友分配资源后，
                    // 剩余预算用于前面处理过的朋友
                    next[money][cones] = max(
                        next[money][cones],
                        dp[money - moneyNeeded][cones - conesNeeded]
                            + f.popularity
                    );
                }
            }
        }

        dp.swap(next);
    }

    cout << dp[A][B] << '\n';
    return 0;
}