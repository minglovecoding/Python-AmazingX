//最朴素、不需要排序、枚举折扣次数
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
    // 剩余现金、剩余冰淇淋对应的最大人气
    vector<vector<int>> dp(
        A + 1, vector<int>(B + 1, -1)
    );
    dp[A][B] = 0;
    for (const auto &f : friends) {
        // 不邀请当前朋友
        vector<vector<int>> next = dp;
        for (int money = 0; money <= A; money++) {
            for (int cones = 0; cones <= B; cones++) {
                if (dp[money][cones] == -1) continue;
                // 现金不够时，至少需要抵扣这些
                int minDiscount = max(0, f.cost - money);
                // 不能抵扣超过原价，也不能超过冰淇淋能兑换的量
                int maxDiscount = min(
                    f.cost, cones / f.exchange
                );
                for (int discount = minDiscount;
                     discount <= maxDiscount;
                     discount++) {
                    int moneyNeeded = f.cost - discount;
                    int conesNeeded = discount * f.exchange;
                    int newMoney = money - moneyNeeded;
                    int newCones = cones - conesNeeded;
                    next[newMoney][newCones] = max(
                        next[newMoney][newCones],
                        dp[money][cones] + f.popularity
                    );
                }
            }
        }
        dp.swap(next);
    }
    int answer = 0;
    for (int money = 0; money <= A; money++) {
        for (int cones = 0; cones <= B; cones++) {
            answer = max(answer, dp[money][cones]);
        }
    }
    cout << answer << '\n';
    return 0;
}