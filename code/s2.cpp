#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, C;
    cin >> N >> C;

    vector<int> f(C + 1);
    for (int j = 1; j <= C; j++) cin >> f[j];

    vector<int> p(N + 1);
    for (int i = 1; i <= N; i++) cin >> p[i];

    vector<vector<int>> crit(C + 1);
    crit.reserve(C + 1);

    for (int i = 1; i <= N; i++) {
        int ni;
        cin >> ni;
        while (ni--) {
            int c;
            cin >> c;
            crit[c].push_back(i);
        }
    }

    for (int j = 1; j <= C; j++) sort(crit[j].begin(), crit[j].end());

    const int INF = C + 1;
    vector<int> stage(N + 1, INF);
    vector<char> declined(N + 1, 0);
    vector<int> ptr(C + 1, 0);
    vector<int> cnt(C + 1, 0);
    long long sum = 0;

    priority_queue<int, vector<int>, greater<int>> pq;
    vector<char> inq(C + 1, 0);

    auto push_need = [&](int j) {
        if (j >= 1 && j <= C && cnt[j] < f[j] && !inq[j]) {
            inq[j] = 1;
            pq.push(j);
        }
    };

    auto fill = [&](int j) {
        while (cnt[j] < f[j]) {
            auto &v = crit[j];
            while (ptr[j] < (int)v.size()) {
                int u = v[ptr[j]++];
                if (declined[u]) continue;
                if (stage[u] <= j) continue;

                int old = stage[u];
                if (old == INF) {
                    sum += u;
                } else {
                    cnt[old]--;
                    push_need(old);
                }

                stage[u] = j;
                cnt[j]++;
                break;
            }
            if (cnt[j] < f[j]) {
                if (ptr[j] >= (int)crit[j].size()) break;
            }
        }
    };

    for (int j = 1; j <= C; j++) {
        if (f[j] > 0) {
            fill(j);
        }
    }

    for (int t = 0; t <= N - 1; t++) {
        cout << sum << "\n";

        int r = p[t + 1];
        declined[r] = 1;
        int s = stage[r];
        if (s != INF) {
            stage[r] = INF;
            cnt[s]--;
            sum -= r;
            push_need(s);
        }

        while (!pq.empty()) {
            int j = pq.top();
            pq.pop();
            inq[j] = 0;
            if (cnt[j] < f[j]) fill(j);
        }
    }

    return 0;
}
