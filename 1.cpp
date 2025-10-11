#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int N, K;
        cin >> N >> K;
        vector<int> a(N);
        for (int i = 0; i < N; ++i) cin >> a[i];

        const int INF = 1e9;
        vector<vector<int>> dp(N, vector<int>(N, INF));
        vector<vector<bool>> allSame(N, vector<bool>(N, false));

        // Precompute allSame
        for (int l = 0; l < N; ++l) {
            allSame[l][l] = true;
            for (int r = l + 1; r < N; ++r) {
                allSame[l][r] = allSame[l][r - 1] && (a[r] == a[l]);
            }
        }

        // Helper to check if a[l..r] == k repeats of a[l..l+p-1]
        auto isRepeat = [&](int l, int r, int p) -> bool {
            int len = r - l + 1;
            if (p <= 0 || len % p) return false;
            for (int i = l + p; i <= r; ++i) {
                if (a[i] != a[l + (i - l) % p]) return false;
            }
            return true;
        };

        for (int len = 1; len <= N; ++len) {
            for (int l = 0; l + len - 1 < N; ++l) {
                int r = l + len - 1;

                // If all equal -> 1 PRINT with a REP
                if (allSame[l][r]) {
                    dp[l][r] = 1;
                }

                // Concatenation
                for (int k = l; k < r; ++k) {
                    dp[l][r] = min(dp[l][r], dp[l][k] + dp[k + 1][r]);
                }

                // Repetition (use smaller base pattern if it tiles the whole segment)
                for (int p = 1; p < len; ++p) { // p = base pattern length
                    if (isRepeat(l, r, p)) {
                        dp[l][r] = min(dp[l][r], dp[l][l + p - 1]);
                    }
                }
            }
        }

        cout << (dp[0][N - 1] <= K ? "YES" : "NO") << "\n";
    }
    return 0;
}
