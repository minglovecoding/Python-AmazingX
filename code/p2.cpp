#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T, M;
    cin >> T >> M;
    while (T--) {
        int N;
        cin >> N;
        vector<ll> v(N + 2, 0);
        for (int i = 1; i <= N; i++) cin >> v[i];

        vector<ll> a(N + 2, 0);
        if (N == 1) {
            a[1] = v[1];
        } else {
            for (int i = 1; i <= N - 1; i++) {
                ll have = a[i - 1] + a[i] + a[i + 1];
                ll need = v[i] - have;
                if (need <= 0) continue;

                ll add = min(need, v[i + 1] - a[i + 1]);
                a[i + 1] += add;
                need -= add;

                if (need > 0) {
                    add = min(need, v[i] - a[i]);
                    a[i] += add;
                    need -= add;
                }

                if (need > 0 && i - 1 >= 1) {
                    add = min(need, v[i - 1] - a[i - 1]);
                    a[i - 1] += add;
                    need -= add;
                }
            }
            ll haveN = a[N - 1] + a[N];
            if (v[N] > haveN) a[N] += (v[N] - haveN);
        }

        ll ans = 0;
        for (int i = 1; i <= N; i++) ans += a[i];
        cout << ans << "\n";
        if (M == 0) continue;

        vector<char> need(N + 2, 0), done(N + 2, 0);
        vector<ll> slack(N + 2, 0), pred(N + 2, 0);
        int rem = 0;
        for (int i = 1; i <= N; i++) {
            if (a[i] > 0) {
                need[i] = 1;
                rem++;
            }
            slack[i] = v[i] - a[i];
        }

        auto safe = [&](int i) -> bool {
            if (i < 1 || i > N) return false;
            if (!need[i] || done[i]) return false;
            if (pred[i] > slack[i]) return false;
            if (i - 1 >= 1 && need[i - 1] && !done[i - 1]) {
                if (pred[i - 1] + a[i] > slack[i - 1]) return false;
            }
            if (i + 1 <= N && need[i + 1] && !done[i + 1]) {
                if (pred[i + 1] + a[i] > slack[i + 1]) return false;
            }
            return true;
        };

        deque<int> q;
        for (int i = 1; i <= N; i++) if (safe(i)) q.push_back(i);

        vector<pair<int,ll>> runs;
        runs.reserve(rem);

        while (rem > 0) {
            while (!q.empty() && !safe(q.front())) q.pop_front();
            if (q.empty()) {
                for (int i = 1; i <= N; i++) {
                    if (safe(i)) { q.push_back(i); break; }
                }
                while (!q.empty() && !safe(q.front())) q.pop_front();
            }
            int i = q.front(); q.pop_front();

            done[i] = 1;
            rem--;
            runs.push_back({i, a[i]});

            if (i - 1 >= 1 && need[i - 1] && !done[i - 1]) pred[i - 1] += a[i];
            if (i + 1 <= N && need[i + 1] && !done[i + 1]) pred[i + 1] += a[i];

            for (int k = i - 2; k <= i + 2; k++) {
                if (safe(k)) q.push_back(k);
            }
        }

        cout << runs.size() << "\n";
        for (auto &pr : runs) cout << pr.first << " " << pr.second << "\n";
    }
    return 0;
}