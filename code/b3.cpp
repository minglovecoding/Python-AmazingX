#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    const long long INF = (1LL<<62);

    vector<long long> c(31, INF);
    for (int i = 0; i < N; i++) {
        long long a;
        cin >> a;
        if (i <= 30) c[i] = min(c[i], a);
        else c[30] = min(c[30], a);
    }

    for (int i = 1; i <= 30; i++) {
        c[i] = min(c[i], 2LL * c[i-1]);
    }

    while (Q--) {
        long long x;
        cin >> x;

        long long rem = x;
        long long cur = 0;
        long long best = INF;

        for (int i = 30; i >= 0; i--) {
            long long sz = 1LL << i;
            long long take = rem / sz;
            cur += take * c[i];
            rem -= take * sz;
            best = min(best, cur + (rem > 0 ? c[i] : 0));
        }

        cout << best << "\n";
    }
    return 0;
}
