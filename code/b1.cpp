#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N;
        long long K;
        cin >> N >> K;
        long long d = llabs(K);

        vector<long long> a(N);
        for (int i = 0; i < N; i++) cin >> a[i];

        vector<vector<long long>> groups(d);
        for (int i = 0; i < N; i++) {
            long long r = a[i] % d;          
            if (r < 0) r += d;
            long long q = (a[i] - r) / d;
            groups[r].push_back(q);
        }

        long long ans = 0;

        if (K > 0) {
            for (auto &v : groups) {
                if (v.empty()) continue;
                sort(v.begin(), v.end());
                long long prev = LLONG_MIN / 4;
                for (long long q : v) {
                    long long x = max(q, prev + 1);
                    ans += (x - q);
                    prev = x;
                }
            }
        } else {
            for (auto &v : groups) {
                if (v.empty()) continue;
                sort(v.begin(), v.end(), greater<long long>());
                long long prev = LLONG_MAX / 4;
                for (long long q : v) {
                    long long x = min(q, prev - 1);
                    ans += (q - x);
                    prev = x;
                }
            }
        }

        cout << ans << "\n";
    }
    return 0;
}
