#include <bits/stdc++.h>
using namespace std;
struct Op {
    int type;
    int x, y, p, q, k;
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N, M;
        cin >> N >> M;
        string t;
        cin >> t;

        vector<string> s(N + 1);
        for (int i = 1; i <= N; i++) cin >> s[i];

        vector<Op> ops;
        ops.reserve(2 * M);

        for (int i = 0; i < M; i++) {
            if (s[1][i] == t[i]) continue;

            char need = t[i];
            int best_r = -1, best_j = -1;

            for (int r = 2; r <= N && best_r == -1; r++) {
                for (int j = 0; j < M; j++) {
                    if (s[r][j] == need) {
                        best_r = r;
                        best_j = j;
                        break;
                    }
                }
            }

            if (best_r != -1) {
                int r = best_r, j = best_j;

                if (j != i) {
                    ops.push_back({1, r, 0, i + 1, j + 1, 0});
                    swap(s[r][i], s[r][j]);
                }

                ops.push_back({2, 1, r, 0, 0, i + 1});
                swap(s[1][i], s[r][i]);

            } else {
                int j = -1;
                for (int jj = i; jj < M; jj++) {
                    if (s[1][jj] == need) { j = jj; break; }
                }
                if (j != i) {
                    ops.push_back({1, 1, 0, i + 1, j + 1, 0});
                    swap(s[1][i], s[1][j]);
                }
            }
        }
        cout << ops.size() << "\n";
        for (auto &op : ops) {
            if (op.type == 1) {
                cout << "1 " << op.x << " " << op.p << " " << op.q << "\n";
            } else {
                cout << "2 " << op.x << " " << op.y << " " << op.k << "\n";
            }
        }
    }
    return 0;
}
