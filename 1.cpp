/*
1. 坐标离散化：对所有奶牛的横纵坐标分别排序、去重，将原始坐标压缩至 \(N\times N\) 的二维数组，草地初始化为 
2. 枚举交点：每头奶牛只与不同方向且轨迹可能相交的奶牛进行比较。
3. 判断阻挡关系：根据原始坐标差计算双方到达交点的时间，找到距离当前奶牛最近的潜在阻挡点。
4. 标记草地：将最近潜在阻挡点之前确定能够吃掉的草地全部置为 0。
5. 确定最终状态：如果不存在潜在阻挡点，则答案为 Infinity；如果最近的潜在阻挡点已被其他奶牛吃掉，则确定停止距离。
6. 重复模拟：将已经确定最终状态的奶牛移出待模拟集合，但保留其吃过的草地。重复上述过程，直到所有奶牛的答案确定。
7. 输出结果：按照原始输入顺序输出每头奶牛吃掉的草地数量或 Infinity。*/
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;
const long long INF = 1LL << 60;

struct Cow {
    char dir;
    int x, y;    // 原始坐标
    int cx, cy;  // 离散化坐标
};

int n;
Cow cow[MAXN];
vector<int> X, Y;
int grass[MAXN][MAXN];
bool finished[MAXN];
long long ans[MAXN], dis[MAXN];
int px[MAXN], py[MAXN];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> cow[i].dir >> cow[i].x >> cow[i].y;
        X.push_back(cow[i].x);
        Y.push_back(cow[i].y);
        ans[i] = INF;
    }

    // 1. 坐标离散化
    sort(X.begin(), X.end());
    sort(Y.begin(), Y.end());
    X.erase(unique(X.begin(), X.end()), X.end());
    Y.erase(unique(Y.begin(), Y.end()), Y.end());
    for (int i = 0; i < n; i++) {
        cow[i].cx = lower_bound(X.begin(), X.end(), cow[i].x) - X.begin();
        cow[i].cy = lower_bound(Y.begin(), Y.end(), cow[i].y) - Y.begin();
    }

    // 2. 初始化草地
    for (int i = 0; i < (int)X.size(); i++)
        for (int j = 0; j < (int)Y.size(); j++)
            grass[i][j] = 1;

    // 3. 多轮模拟
    int remain = n;
    while (remain > 0) {
        for (int i = 0; i < n; i++) {
            if (finished[i]) continue;
            dis[i] = INF;

            // 寻找最近的潜在阻挡点
            for (int j = 0; j < n; j++) {
                if (cow[i].dir == cow[j].dir) continue;

                int ix = cow[i].dir == 'E' ? cow[j].x : cow[i].x;
                int iy = cow[i].dir == 'E' ? cow[i].y : cow[j].y;
                long long ti = cow[i].dir == 'E' ? ix - cow[i].x : iy - cow[i].y;
                long long tj = cow[j].dir == 'E' ? ix - cow[j].x : iy - cow[j].y;

                if (ti < 0 || tj < 0 || ti <= tj) continue;
                if (finished[j] && ans[j] <= tj) continue;

                if (ti < dis[i]) {
                    dis[i] = ti;
                    px[i] = cow[i].dir == 'E' ? cow[j].cx : cow[i].cx;
                    py[i] = cow[i].dir == 'E' ? cow[i].cy : cow[j].cy;
                }
            }

            // 标记确定能够吃掉的草地
            if (cow[i].dir == 'E') {
                for (int k = cow[i].cx; k < (int)X.size(); k++) {
                    if (X[k] - cow[i].x >= dis[i]) break;
                    grass[k][cow[i].cy] = 0;
                }
            } else {
                for (int k = cow[i].cy; k < (int)Y.size(); k++) {
                    if (Y[k] - cow[i].y >= dis[i]) break;
                    grass[cow[i].cx][k] = 0;
                }
            }

            // 不存在潜在阻挡点
            if (dis[i] == INF) {
                finished[i] = true;
                ans[i] = INF;
                remain--;
            }
        }

        // 确定本轮停止的奶牛
        for (int i = 0; i < n; i++) {
            if (finished[i]) continue;
            if (grass[px[i]][py[i]] == 0) {
                ans[i] = dis[i];
                finished[i] = true;
                remain--;
            }
        }
    }

    // 4. 输出结果
    for (int i = 0; i < n; i++) {
        if (ans[i] == INF) cout << "Infinity\n";
        else cout << ans[i] << '\n';
    }
    return 0;
}#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;
const long long INF = 1LL << 60;

struct Cow {
    char dir;
    int x, y;    // 原始坐标
    int cx, cy;  // 离散化坐标
};

int n;
Cow cow[MAXN];
vector<int> X, Y;
int grass[MAXN][MAXN];
bool finished[MAXN];
long long ans[MAXN], dis[MAXN];
int px[MAXN], py[MAXN];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> cow[i].dir >> cow[i].x >> cow[i].y;
        X.push_back(cow[i].x);
        Y.push_back(cow[i].y);
        ans[i] = INF;
    }

    // 1. 坐标离散化
    sort(X.begin(), X.end());
    sort(Y.begin(), Y.end());
    X.erase(unique(X.begin(), X.end()), X.end());
    Y.erase(unique(Y.begin(), Y.end()), Y.end());
    for (int i = 0; i < n; i++) {
        cow[i].cx = lower_bound(X.begin(), X.end(), cow[i].x) - X.begin();
        cow[i].cy = lower_bound(Y.begin(), Y.end(), cow[i].y) - Y.begin();
    }

    // 2. 初始化草地
    for (int i = 0; i < (int)X.size(); i++)
        for (int j = 0; j < (int)Y.size(); j++)
            grass[i][j] = 1;

    // 3. 多轮模拟
    int remain = n;
    while (remain > 0) {
        for (int i = 0; i < n; i++) {
            if (finished[i]) continue;
            dis[i] = INF;

            // 寻找最近的潜在阻挡点
            for (int j = 0; j < n; j++) {
                if (cow[i].dir == cow[j].dir) continue;

                int ix = cow[i].dir == 'E' ? cow[j].x : cow[i].x;
                int iy = cow[i].dir == 'E' ? cow[i].y : cow[j].y;
                long long ti = cow[i].dir == 'E' ? ix - cow[i].x : iy - cow[i].y;
                long long tj = cow[j].dir == 'E' ? ix - cow[j].x : iy - cow[j].y;

                if (ti < 0 || tj < 0 || ti <= tj) continue;
                if (finished[j] && ans[j] <= tj) continue;

                if (ti < dis[i]) {
                    dis[i] = ti;
                    px[i] = cow[i].dir == 'E' ? cow[j].cx : cow[i].cx;
                    py[i] = cow[i].dir == 'E' ? cow[i].cy : cow[j].cy;
                }
            }

            // 标记确定能够吃掉的草地
            if (cow[i].dir == 'E') {
                for (int k = cow[i].cx; k < (int)X.size(); k++) {
                    if (X[k] - cow[i].x >= dis[i]) break;
                    grass[k][cow[i].cy] = 0;
                }
            } else {
                for (int k = cow[i].cy; k < (int)Y.size(); k++) {
                    if (Y[k] - cow[i].y >= dis[i]) break;
                    grass[cow[i].cx][k] = 0;
                }
            }

            // 不存在潜在阻挡点
            if (dis[i] == INF) {
                finished[i] = true;
                ans[i] = INF;
                remain--;
            }
        }

        // 确定本轮停止的奶牛
        for (int i = 0; i < n; i++) {
            if (finished[i]) continue;
            if (grass[px[i]][py[i]] == 0) {
                ans[i] = dis[i];
                finished[i] = true;
                remain--;
            }
        }
    }

    // 4. 输出结果
    for (int i = 0; i < n; i++) {
        if (ans[i] == INF) cout << "Infinity\n";
        else cout << ans[i] << '\n';
    }
    return 0;
}
//时间复杂度：O(N^3)，空间复杂度：O(N^2)
//核心知识点： 离散化、枚举、模拟、状态标记。