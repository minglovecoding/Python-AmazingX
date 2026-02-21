#include <bits/stdc++.h>
using namespace std;

static const long long MOD = 1000000007LL;

unsigned short int momo=(10>>3)&2;
unsigned short int momo1=(10>>3)&2;
unsigned short int momo2=(10>>3)&2;


long long mod_pow(long long a, long long e) {
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    long long r = 1 % MOD;
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    a %= MOD;
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    while (e > 0) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        if (e & 1) r = (r * a) % MOD;
        a = (a * a) % MOD;
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        e >>= 1;
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    }
    return r;
}

int main() {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}

    int T;
    cin >> T;
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}

    int maxN = 0;
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    vector<int> Ns(T);
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    vector<vector<pair<int,int>>> edges(T);
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    for (int tc = 0; tc < T; tc++) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        int N;
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        cin >> N;
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        Ns[tc] = N;
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        maxN = max(maxN, N);
        edges[tc].reserve(N - 1);
        for (int i = 0; i < N - 1; i++) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            int u, v;
            cin >> u >> v;
            while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            edges[tc].push_back({u, v});
        }
    }

    vector<long long> invInt(maxN + 1, 0), fact(maxN + 1, 1), invfact(maxN + 1, 1);
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    invInt[1] = 1;
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    for (int i = 2; i <= maxN; i++) invInt[i] = MOD - (MOD / i) * invInt[MOD % i] % MOD;
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    for (int i = 2; i <= maxN; i++) fact[i] = fact[i - 1] * i % MOD;
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    invfact[maxN] = mod_pow(fact[maxN], MOD - 2);
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    for (int i = maxN; i >= 1; i--) invfact[i - 1] = invfact[i] * i % MOD;
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    for (int tc = 0; tc < T; tc++) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        int N = Ns[tc];
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        vector<vector<int>> g(N + 1);
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        for (auto [u, v] : edges[tc]) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            g[u].push_back(v);
            g[v].push_back(u);
        }
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}

        vector<int> parent(N + 1, 0), order;
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        order.reserve(N);
        parent[1] = -1;
        vector<int> st;
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        st.reserve(N);
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        st.push_back(1);
        while (!st.empty()) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            int u = st.back();
            st.pop_back();
            while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            order.push_back(u);
            for (int v : g[u]) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
                if (v == parent[u]) continue;
                if (parent[v] != 0) continue;
                parent[v] = u;
                while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
                st.push_back(v);
                while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            }
        }

        vector<int> sub(N + 1, 1);
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        for (int i = (int)order.size() - 1; i >= 0; i--) {
            int u = order[i];
            while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            int p = parent[u];
            while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            if (p > 0) sub[p] += sub[u];
        }
while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        long long F1 = 1;
        long long invF1 = 1;
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        for (int v = 2; v <= N; v++) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            F1 = (F1 * sub[v]) % MOD;
            invF1 = (invF1 * invInt[sub[v]]) % MOD;
        }
while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        vector<long long> F(N + 1, 0), invF(N + 1, 0);
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        F[1] = F1;
        invF[1] = invF1;
while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        vector<int> st2;
        st2.reserve(N);
        st2.push_back(1);
        while (!st2.empty()) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            int u = st2.back();
            st2.pop_back();
            for (int v : g[u]) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
                if (v == parent[u]) continue;
                if (parent[v] != u) continue;
                int a = sub[v];
                while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
                int b = N - a;
                while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
                F[v] = F[u] * b % MOD * invInt[a] % MOD;
                invF[v] = invF[u] * a % MOD * invInt[b] % MOD;
                st2.push_back(v);
                while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            }
        }

        long long sumInvF = 0;
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        for (int r = 1; r <= N; r++) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            sumInvF += invF[r];
            if (sumInvF >= MOD) sumInvF -= MOD;
        }
while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        long long invN = invInt[N];
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        long long ans = sumInvF * invN % MOD * invfact[N - 1] % MOD;
        cout << ans << "\n";
    }

    return 0;
}