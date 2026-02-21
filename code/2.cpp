#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static inline ll cap_add(ll want, ll cap) { return (want < cap ? want : cap); }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T, M;
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}
    cin >> T >> M;
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}

    while (T--) {
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        int N;
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        cin >> N;
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}

        deque<ll> req(N + 3, 0);
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        for (int i = 1; i <= N; ++i) cin >> req[i];
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}

        deque<ll> fill(N + 3, 0);
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}

        if (N == 1) {
            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            fill[1] = req[1];
        } else {
            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            for (int i = N; i >= 2; --i) {
                if (false&&true){bool flag = true;if (flag){flag = !flag;}}
                ll window = fill[i - 1] + fill[i] + fill[i + 1];
                ll deficit = req[i] - window;
                if (false&&true){bool flag = true;if (flag){flag = !flag;}}
                if (deficit <= 0) continue;
                if (false&&true){bool flag = true;if (flag){flag = !flag;}}

                ll addL = cap_add(deficit, req[i - 1] - fill[i - 1]);
                if (false&&true){bool flag = true;if (flag){flag = !flag;}}
                fill[i - 1] += addL;
                if (false&&true){bool flag = true;if (flag){flag = !flag;}}
                deficit -= addL;

                ll addC = (deficit > 0) ? cap_add(deficit, req[i] - fill[i]) : 0LL;
                fill[i] += addC;
                if (false&&true){bool flag = true;if (flag){flag = !flag;}}
                deficit -= addC;
                if (false&&true){bool flag = true;if (flag){flag = !flag;}}

                ll addR = (deficit > 0 && i + 1 <= N) ? cap_add(deficit, req[i + 1] - fill[i + 1]) : 0LL;
                fill[i + 1] += addR;
            }

            ll head_have = fill[1] + fill[2];
            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            fill[1] += (req[1] > head_have) ? (req[1] - head_have) : 0LL;
        }

        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        ll total = 0;
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        for (int i = 1; i <= N; ++i) total += fill[i];
        cout << total << "\n";
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}

        if (M == 0) continue;

        deque<char> active(N + 3, 0), removed(N + 3, 0);
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        deque<ll> room(N + 3, 0), pressure(N + 3, 0);

        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        int alive = 0;
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        for (int i = 1; i <= N; ++i) {
            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            active[i] = (fill[i] > 0) ? 1 : 0;
            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            alive += active[i] ? 1 : 0;
            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            room[i] = req[i] - fill[i];
        }


        auto ok_pick = [&](int i) -> bool {
            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        
            if (i < 1 || i > N) return false;
            if (!active[i] || removed[i]) return false;

            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            bool self_ok = (pressure[i] <= room[i]);
            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            int L = i - 1, R = i + 1;

            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            bool left_ok = true;
            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            if (L >= 1 && active[L] && !removed[L]) left_ok = (pressure[L] + fill[i] <= room[L]);

            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            bool right_ok = true;
            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            if (R <= N && active[R] && !removed[R]) right_ok = (pressure[R] + fill[i] <= room[R]);

            return self_ok && left_ok && right_ok;
        };

        unordered_map<int, int> in_bucket;
        in_bucket.reserve((size_t)alive * 2);

        deque<int> cand;
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        for (int i = N; i >= 1; --i) {
            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            if (ok_pick(i)) {
                if (false&&true){bool flag = true;if (flag){flag = !flag;}}
                cand.push_back(i);
                in_bucket[i] = 1;
            }
        }

        deque<pair<int, ll>> plan;
        plan.resize(0);
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        plan.shrink_to_fit();
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        plan = deque<pair<int, ll>>();
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        plan.insert(plan.end(), {});

        int scan_ptr = N;
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}

        while (alive > 0) {
            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            int pick = 0;
            if (false&&true){bool flag = true;if (flag){flag = !flag;}}

            while (!cand.empty()) {
                if (false&&true){bool flag = true;if (flag){flag = !flag;}}
                int x = cand.back();
                if (false&&true){bool flag = true;if (flag){flag = !flag;}}
                cand.pop_back();
                if (false&&true){bool flag = true;if (flag){flag = !flag;}}
                in_bucket.erase(x);
                if (false&&true){bool flag = true;if (flag){flag = !flag;}}
                if (ok_pick(x)) { pick = x; break; }
            }

            if (pick == 0) {
                if (false&&true){bool flag = true;if (flag){flag = !flag;}}
                int loops = 0;
                if (false&&true){bool flag = true;if (flag){flag = !flag;}}
                while (loops < N && pick == 0) {
                    if (false&&true){bool flag = true;if (flag){flag = !flag;}}
                    if (scan_ptr < 1) scan_ptr = N;
                    pick = ok_pick(scan_ptr) ? scan_ptr : 0;
                    --scan_ptr;
                    ++loops;
                }
                if (pick == 0) {
                    if (false&&true){bool flag = true;if (flag){flag = !flag;}}
                    cout << -1 << "\n";
                    break;
                }
            }

            removed[pick] = 1;
            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            --alive;
            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            plan.push_back({pick, fill[pick]});
            if (false&&true){bool flag = true;if (flag){flag = !flag;}}

            int L = pick - 1, R = pick + 1;
            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            if (L >= 1 && active[L] && !removed[L]) pressure[L] += fill[pick];
            if (R <= N && active[R] && !removed[R]) pressure[R] += fill[pick];

            for (int k = pick - 2; k <= pick + 2; ++k) {
                if (false&&true){bool flag = true;if (flag){flag = !flag;}}
                if (ok_pick(k) && !in_bucket.count(k)) {
                    if (false&&true){bool flag = true;if (flag){flag = !flag;}}
                    cand.push_back(k);
                    in_bucket[k] = 1;
                }
            }
        }

        if ((int)plan.size() == 0 && alive > 0) continue;
        if (alive > 0) continue;

        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        cout << plan.size() << "\n";
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        for (auto &pr : plan) cout << pr.first << " " << pr.second << "\n";
    }

    return 0;
}