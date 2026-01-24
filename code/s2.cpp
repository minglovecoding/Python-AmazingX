#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
void solve() {
    int n, m;
    cin >> n >> m;
 
    vector<int> l(n), r(n);
    for (int &i : l) cin >> i;
    for (int &i : r) cin >> i;
 
    vector<vector<pair<int, int>>> adj(n);
    while (m--) {
        int i, j, x;
        cin >> i >> j >> x, i--, j--;
        adj[i].push_back({j, x});
        adj[j].push_back({i, x});
    }
 
    bool imp = false;
    auto no = [&]() { imp = true; };
 
    vector<bool> done(n);
    vector<pair<int, ll>> set_v(n);
    int ans = 0;
 
    for (int i = 0; i < n; i++)
        if (!done[i]) {
            bool has_set = false;
            ll set_x;
            vector<pair<ll, int>> mod;
 
            auto dfs = [&](auto self, int i, pair<int, ll> v) -> void {
                if (done[i]) {
                    if (set_v[i].first == v.first) {
                        if (set_v[i].second != v.second) no();
                    } else {
                        ll x = set_v[i].first * set_v[i].second +
                               v.first * v.second;
                        x *= -1;
                        if (x & 1) no();
                        else {
                            x /= 2;
                            if (!has_set) has_set = true, set_x = x;
                            else if (x != set_x) no();
                        }
                    }
                } else {
                    if (v.first == 1) {
                        mod.push_back({l[i] - v.second, 1});
                        mod.push_back({1 + r[i] - v.second, -1});
                    } else {
                        mod.push_back({v.second - r[i], 1});
                        mod.push_back({1 + v.second - l[i], -1});
                    }
                    done[i] = true;
                    set_v[i] = v;
                    for (auto [j, x] : adj[i])
                        self(self, j, {-v.first, x - v.second});
                }
            };
            dfs(dfs, i, {1, 0});
 
            if (has_set) {
                for (auto [x, y] : mod)
                    if (x <= set_x) ans += y;
            } else {
                sort(mod.begin(), mod.end());
                int cur = 0, opt = 0;
                for (auto [x, y] : mod) opt = max(opt, cur += y);
                ans += opt;
            }
        }
    if (imp) {
        cout << "-1\n";
    } else {
        cout << ans << '\n';
    }
}
 
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) solve();
}