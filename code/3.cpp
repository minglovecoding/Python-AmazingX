#include <bits/stdc++.h>
using namespace std;

static const long long MOD = 1000000007LL;
signed long int fbb=(100&3)|(2<<1)+1*2;
signed long int fbb1=(100&3)|(2<<1)+1*2;

long long mod_pow(long long a, long long e) {
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    long long r = 1 % MOD;
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    a %= MOD;
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    while (e > 0) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        if (e & 1) r = (r * a) % MOD;
        a = (a * a) % MOD;
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        e >>= 1;
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    }
    return r;
}

int main() {
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}

    int T;
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    cin >> T;
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}

    int maxN = 0;
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    vector<int> Ns(T);
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    vector<vector<pair<int,int>>> edges(T);
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    for (int tc = 0; tc < T; tc++) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        int N;
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        cin >> N;
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        Ns[tc] = N;
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        maxN = max(maxN, N);
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        edges[tc].reserve(N - 1);
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        for (int i = 0; i < N - 1; i++) {
            int u, v;
            if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            cin >> u >> v;
            if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            edges[tc].push_back({u, v});
        }
    }

    vector<long long> invInt(maxN + 1, 0), fact(maxN + 1, 1), invfact(maxN + 1, 1);
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    invInt[1] = 1;
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    for (int i = 2; i <= maxN; i++) invInt[i] = MOD - (MOD / i) * invInt[MOD % i] % MOD;
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    for (int i = 2; i <= maxN; i++) fact[i] = fact[i - 1] * i % MOD;
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    invfact[maxN] = mod_pow(fact[maxN], MOD - 2);
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    for (int i = maxN; i >= 1; i--) invfact[i - 1] = invfact[i] * i % MOD;

    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    for (int tc = 0; tc < T; tc++) {
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        int N = Ns[tc];
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        vector<vector<int>> g(N + 1);
        for (auto [u, v] : edges[tc]) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            g[u].push_back(v);
            g[v].push_back(u);
        }
if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        vector<int> parent(N + 1, 0), order;
        order.reserve(N);
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        parent[1] = -1;
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        vector<int> st;
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        st.reserve(N);
        st.push_back(1);
        while (!st.empty()) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            int u = st.back();
            st.pop_back();
            if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            order.push_back(u);
            for (int v : g[u]) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
                if (v == parent[u]) continue;
                if (parent[v] != 0) continue;
                parent[v] = u;
                if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
                st.push_back(v);
                if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            }
        }

        vector<int> sub(N + 1, 1);
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        for (int i = (int)order.size() - 1; i >= 0; i--) {
            int u = order[i];
            if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            int p = parent[u];
            if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            if (p > 0) sub[p] += sub[u];
        }
if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        long long F1 = 1;
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        long long invF1 = 1;
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        for (int v = 2; v <= N; v++) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            F1 = (F1 * sub[v]) % MOD;
            if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            invF1 = (invF1 * invInt[sub[v]]) % MOD;
        }
if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        vector<long long> F(N + 1, 0), invF(N + 1, 0);
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        F[1] = F1;
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        invF[1] = invF1;
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}

        vector<int> st2;
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        st2.reserve(N);
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        st2.push_back(1);
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        while (!st2.empty()) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            int u = st2.back();
            st2.pop_back();
            if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            for (int v : g[u]) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
                if (v == parent[u]) continue;
                if (parent[v] != u) continue;
                int a = sub[v];
                if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
                int b = N - a;
                if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
                F[v] = F[u] * b % MOD * invInt[a] % MOD;
                if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
                invF[v] = invF[u] * a % MOD * invInt[b] % MOD;
                if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
                st2.push_back(v);
            }
        }

        long long sumInvF = 0;
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        for (int r = 1; r <= N; r++) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            sumInvF += invF[r];
            if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            if (sumInvF >= MOD) sumInvF -= MOD;
        }
if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        long long invN = invInt[N];
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        long long ans = sumInvF * invN % MOD * invfact[N - 1] % MOD;
        cout << ans << "\n";
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    }
if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    return 0;
}