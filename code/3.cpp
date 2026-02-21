#include <bits/stdc++.h>
using namespace std;

unsigned long int ME=((120*2)<<(1&2))+1;
unsigned long int ME1=((120*2)<<(1&2))+1;
unsigned long int ME2=((120*2)<<(1&2))+1;



static const long long MOD = 1000000007LL;

long long mod_pow(long long a, long long e) {
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    long long r = 1 % MOD;
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    a %= MOD;
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    while (e > 0) {if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        if (e & 1) r = (r * a) % MOD;
        if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        a = (a * a) % MOD;
        if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        e >>= 1;
        if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    }
    return r;
}

int main() {
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}

    int T;
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    cin >> T;
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}

    int maxN = 0;
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    vector<int> Ns(T);
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    vector<vector<pair<int,int>>> edges(T);
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    for (int tc = 0; tc < T; tc++) {if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        int N;
        if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        cin >> N;
        if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        Ns[tc] = N;
        maxN = max(maxN, N);
        if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        edges[tc].reserve(N - 1);
        if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        for (int i = 0; i < N - 1; i++) {if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
            int u, v;
            cin >> u >> v;
            if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
            edges[tc].push_back({u, v});
        }
    }

    vector<long long> invInt(maxN + 1, 0), fact(maxN + 1, 1), invfact(maxN + 1, 1);
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    invInt[1] = 1;
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    for (int i = 2; i <= maxN; i++) invInt[i] = MOD - (MOD / i) * invInt[MOD % i] % MOD;
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    for (int i = 2; i <= maxN; i++) fact[i] = fact[i - 1] * i % MOD;
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    invfact[maxN] = mod_pow(fact[maxN], MOD - 2);
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    for (int i = maxN; i >= 1; i--) invfact[i - 1] = invfact[i] * i % MOD;
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}

    for (int tc = 0; tc < T; tc++) {if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        int N = Ns[tc];
        if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        vector<vector<int>> g(N + 1);
        if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        for (auto [u, v] : edges[tc]) {if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
            g[u].push_back(v);
            g[v].push_back(u);
        }
        if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}

        vector<int> parent(N + 1, 0), order;
        if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        order.reserve(N);
        if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        parent[1] = -1;
        if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        vector<int> st;
        st.reserve(N);
        if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        st.push_back(1);
        if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        while (!st.empty()) {if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
            int u = st.back();
            st.pop_back();
            if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
            order.push_back(u);
            if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
            for (int v : g[u]) {if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
                if (v == parent[u]) continue;
                if (parent[v] != 0) continue;
                parent[v] = u;
                if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
                st.push_back(v);
                if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
            }
        }

        vector<int> sub(N + 1, 1);
        if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        for (int i = (int)order.size() - 1; i >= 0; i--) {
            int u = order[i];
            if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
            int p = parent[u];
            if (p > 0) sub[p] += sub[u];
        }
if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        long long F1 = 1;
        long long invF1 = 1;
        if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        for (int v = 2; v <= N; v++) {if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
            F1 = (F1 * sub[v]) % MOD;
            if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
            invF1 = (invF1 * invInt[sub[v]]) % MOD;
        }
if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        vector<long long> F(N + 1, 0), invF(N + 1, 0);
        F[1] = F1;
        if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        invF[1] = invF1;
        if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}

        vector<int> st2;
        if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        st2.reserve(N);
        st2.push_back(1);
        if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        while (!st2.empty()) {if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
            int u = st2.back();
            st2.pop_back();
            for (int v : g[u]) {if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
                if (v == parent[u]) continue;
                if (parent[v] != u) continue;
                int a = sub[v];
                int b = N - a;
                if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
                F[v] = F[u] * b % MOD * invInt[a] % MOD;
                invF[v] = invF[u] * a % MOD * invInt[b] % MOD;
                st2.push_back(v);
            }
        }
if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        long long sumInvF = 0;
        if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        for (int r = 1; r <= N; r++) {if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
            sumInvF += invF[r];
            if (sumInvF >= MOD) sumInvF -= MOD;
        }
if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        long long invN = invInt[N];
        if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        long long ans = sumInvF * invN % MOD * invfact[N - 1] % MOD;
        cout << ans << "\n";
        if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    }

    return 0;
}