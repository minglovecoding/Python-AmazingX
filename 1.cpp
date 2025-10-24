#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> P(N + 1);
    for (int i = 1; i <= N; i++)
        cin >> P[i];

    vector<int> num_child(N + 1, 0);
    vector<int> length(N + 1, 0);

    // 计算每个节点的深度与子节点数
    for (int i = 1; i <= N; i++) {
        length[i] = length[P[i]] + 1;
        num_child[P[i]]++;
    }

    // 统计叶子节点数
    int M = 0;
    for (int i = 0; i <= N; i++) {
        if (num_child[i] == 0)
            M++;
    }

    // 模拟 M 次操作
    for (int _ = 0; _ < M; _++) {
        int x;
        cin >> x;

        while (true) {
            assert(num_child[x] == 0);  // 必须是叶子

            if (x == 0) {  // 到达根节点
                cout << 0 << "\n";
                break;
            }

            if (num_child[P[x]] == 1) {
                x = P[x];
                num_child[x] = 0;
                continue;
            }

            cout << length[x] << "\n";
            num_child[P[x]]--;
            break;
        }
    }

    return 0;
}