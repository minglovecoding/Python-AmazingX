#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct BIT {
    int n;
    vector<int> tr;
    BIT(int n=0){ init(n); }
    void init(int n_) { n = n_; tr.assign(n + 1, 0); }
    void add(int x, int v) {
        for (; x <= n; x += x & -x) tr[x] += v;
    }
    ll sum(int x) const {
        ll r = 0;
        for (; x > 0; x -= x & -x) r += tr[x];
        return r;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<ll> a(n + 1);
        vector<ll> b;
        b.reserve(n);
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            b.push_back(a[i]);
        }
        sort(b.begin(), b.end());
        b.erase(unique(b.begin(), b.end()), b.end());
        int m = (int)b.size();

        vector<int> rk(n + 1);
        for (int i = 1; i <= n; i++) {
            rk[i] = (int)(lower_bound(b.begin(), b.end(), a[i]) - b.begin()) + 1;
        }

        vector<ll> s(n + 1), g(n + 1);
        BIT bit(m);

        for (int i = 1; i <= n; i++) {
            int r = rk[i];
            s[i] = bit.sum(r - 1);
            bit.add(r, 1);
        }

        bit.init(m);
        for (int i = n; i >= 1; i--) {
            int r = rk[i];
            g[i] = bit.sum(r - 1);
            bit.add(r, 1);
        }

        vector<vector<int>> pos(m + 1);
        for (int i = 1; i <= n; i++) pos[rk[i]].push_back(i);

        ll ans = 0;
        for (int r = 1; r <= m; r++) {
            auto &v = pos[r];
            int k = (int)v.size();
            ll totg = 0;
            for (int i = 0; i < k; i++) totg += g[v[i]];

            ll preS = 0, preG = 0;
            ll best = (ll)4e18;

            for (int t = 0; t <= k; t++) {
                best = min(best, preS + (totg - preG));
                if (t == k) break;
                preS += s[v[t]];
                preG += g[v[t]];
            }
            ans += best;
        }

        cout << ans << "\n";
    }
    return 0;
}