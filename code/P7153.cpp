#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct Point {
    ll x, y;
    int id;
};

struct Result {
    ll total;  // 宽度 >= 高度的子集数量
    ll equal;  // 宽度 == 高度的子集数量
};

Result countSubsets(vector<Point> cows) {
    int n = cows.size();

    sort(cows.begin(), cows.end(),
         [](const Point& a, const Point& b) {
             return a.x < b.x;
         });

    ll total = 0;
    ll equal = 0;

    // 枚举最左边和最右边的奶牛
    for (int l = 0; l < n; l++) {
        for (int r = l; r < n; r++) {
            ll width = cows[r].x - cows[l].x;

            vector<Point> current;

            // 只保留横坐标位于 [x_l, x_r] 中的奶牛
            for (int i = l; i <= r; i++) {
                current.push_back(cows[i]);
            }

            sort(current.begin(), current.end(),
                 [](const Point& a, const Point& b) {
                     return a.y < b.y;
                 });

            vector<ll> ys;
            int posL = -1;
            int posR = -1;

            for (int i = 0; i < (int)current.size(); i++) {
                ys.push_back(current[i].y);

                if (current[i].id == cows[l].id) {
                    posL = i;
                }

                if (current[i].id == cows[r].id) {
                    posR = i;
                }
            }

            int p = min(posL, posR);
            int q = max(posL, posR);

            // 枚举子集中 y 坐标最小的奶牛
            for (int a = 0; a <= p; a++) {
                ll highestY = ys[a] + width;

                int maxB =
                    upper_bound(ys.begin(), ys.end(), highestY)
                    - ys.begin() - 1;

                if (maxB >= q) {
                    total += maxB - q + 1;
                }

                // 统计高度恰好等于宽度的情况
                auto it = lower_bound(
                    ys.begin(), ys.end(), highestY
                );

                if (it != ys.end() && *it == highestY) {
                    int b = it - ys.begin();

                    if (b >= q) {
                        equal++;
                    }
                }
            }
        }
    }

    return {total, equal};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Point> cows(n);

    for (int i = 0; i < n; i++) {
        cin >> cows[i].x >> cows[i].y;
        cows[i].id = i;
    }

    // 统计宽度 >= 高度
    Result horizontal = countSubsets(cows);

    
    // 交换 x、y，统计原问题中高度 >= 宽度
    for (Point& cow : cows) {
        swap(cow.x, cow.y);
    }

    Result vertical = countSubsets(cows);

    //第一次枚举左右端点只处理“横向跨度更大”的子集；后用同样算法处理“纵向跨度更大”的子集，最后去除宽高相等造成的重复。
    // 正方形包围盒在两次统计中都出现，因此减掉一次
    ll answer =
        horizontal.total
        + vertical.total
        - horizontal.equal
        + 1;  // 空集

    cout << answer << '\n';

    return 0;
}