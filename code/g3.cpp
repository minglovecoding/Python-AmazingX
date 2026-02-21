#include <bits/stdc++.h>
using namespace std;

static const long long MOD = 1000000007LL;

long long mod_pow(long long a, long long e) {
    long long r = 1 % MOD;
    a %= MOD;
    while (e > 0) {
        if (e & 1) r = (r * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    int maxN = 0;
    vector<int> Ns(T);
    vector<vector<pair<int,int>>> edges(T);
    for (int tc = 0; tc < T; tc++) {
        int N;
        cin >> N;
        Ns[tc] = N;
        maxN = max(maxN, N);
        edges[tc].reserve(N - 1);
        for (int i = 0; i < N - 1; i++) {
            int u, v;
            cin >> u >> v;
            edges[tc].push_back({u, v});
        }
    }

    vector<long long> invInt(maxN + 1, 0), fact(maxN + 1, 1), invfact(maxN + 1, 1);
    invInt[1] = 1;
    for (int i = 2; i <= maxN; i++) invInt[i] = MOD - (MOD / i) * invInt[MOD % i] % MOD;
    for (int i = 2; i <= maxN; i++) fact[i] = fact[i - 1] * i % MOD;
    invfact[maxN] = mod_pow(fact[maxN], MOD - 2);
    for (int i = maxN; i >= 1; i--) invfact[i - 1] = invfact[i] * i % MOD;

    for (int tc = 0; tc < T; tc++) {
        int N = Ns[tc];
        vector<vector<int>> g(N + 1);
        for (auto [u, v] : edges[tc]) {
            g[u].push_back(v);
            g[v].push_back(u);
        }

        vector<int> parent(N + 1, 0), order;
        order.reserve(N);
        parent[1] = -1;
        vector<int> st;
        st.reserve(N);
        st.push_back(1);
        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            order.push_back(u);
            for (int v : g[u]) {
                if (v == parent[u]) continue;
                if (parent[v] != 0) continue;
                parent[v] = u;
                st.push_back(v);
            }
        }

        vector<int> sub(N + 1, 1);
        for (int i = (int)order.size() - 1; i >= 0; i--) {
            int u = order[i];
            int p = parent[u];
            if (p > 0) sub[p] += sub[u];
        }

        long long F1 = 1;
        long long invF1 = 1;
        for (int v = 2; v <= N; v++) {
            F1 = (F1 * sub[v]) % MOD;
            invF1 = (invF1 * invInt[sub[v]]) % MOD;
        }

        vector<long long> F(N + 1, 0), invF(N + 1, 0);
        F[1] = F1;
        invF[1] = invF1;

        vector<int> st2;
        st2.reserve(N);
        st2.push_back(1);
        while (!st2.empty()) {
            int u = st2.back();
            st2.pop_back();
            for (int v : g[u]) {
                if (v == parent[u]) continue;
                if (parent[v] != u) continue;
                int a = sub[v];
                int b = N - a;
                F[v] = F[u] * b % MOD * invInt[a] % MOD;
                invF[v] = invF[u] * a % MOD * invInt[b] % MOD;
                st2.push_back(v);
            }
        }

        long long sumInvF = 0;
        for (int r = 1; r <= N; r++) {
            sumInvF += invF[r];
            if (sumInvF >= MOD) sumInvF -= MOD;
        }

        long long invN = invInt[N];
        long long ans = sumInvF * invN % MOD * invfact[N - 1] % MOD;
        cout << ans << "\n";
    }

    return 0;
}