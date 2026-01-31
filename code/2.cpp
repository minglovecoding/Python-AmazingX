#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    int K;
    cin >> N >> K;

    int n2 = N - 1;
    int SZ2 = 1 << n2;
    int SZ = 1 << N;

    vector<vector<int>> pos(N, vector<int>(N, -1));
    for (int x = 0; x < N; x++) {
        int idx = 0;
        for (int j = 0; j < N; j++) {
            if (j == x) continue;
            pos[x][j] = idx++;
        }
    }

    vector<vector<int>> baseAll(N, vector<int>(SZ2, 0));

    for (int i = 0; i < K; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        --x; --y; --z;
        int ry = pos[x][y];
        int rz = pos[x][z];
        int p = (1 << ry) | (1 << rz);
        baseAll[x][p] += 1;
    }

    vector<int> score(SZ, 0);

    for (int x = 0; x < N; x++) {
        auto &dp = baseAll[x];

        for (int b = 0; b < n2; b++) {
            for (int m = 0; m < SZ2; m++) {
                if (m & (1 << b)) dp[m] += dp[m ^ (1 << b)];
            }
        }

        int lowMask = (1 << x) - 1;
        for (int r = 0; r < SZ2; r++) {
            int full = (r & lowMask) | ((r >> x) << (x + 1));
            score[full] += dp[r];
        }
    }

    int best = 0;
    for (int m = 0; m < SZ; m++) best = max(best, score[m]);

    long long cnt = 0;
    for (int m = 0; m < SZ; m++) if (score[m] == best) cnt++;

    cout << best << " " << cnt << "\n";
    return 0;
}
