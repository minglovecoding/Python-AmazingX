#include <bits/stdc++.h>
using namespace std;

static const long long LIM = (long long)1e18 + 5;

static inline long long cap_mul(long long a, long long b) {
    __int128 x = ( __int128 )a * b;
    if (x > LIM) return LIM;
    return (long long)x;
}

struct SegTree {
    int n;
    vector<long long> st;
    SegTree(int n=0): n(n), st(4*n+4, 1) {}

    void build(int p, int l, int r, const vector<long long>& arr) {
        if (l == r) { st[p] = arr[l]; return; }
        int m = (l + r) >> 1;
        build(p<<1, l, m, arr);
        build(p<<1|1, m+1, r, arr);
        st[p] = cap_mul(st[p<<1], st[p<<1|1]);
    }

    void update(int p, int l, int r, int idx, long long val) {
        if (l == r) { st[p] = val; return; }
        int m = (l + r) >> 1;
        if (idx <= m) update(p<<1, l, m, idx, val);
        else update(p<<1|1, m+1, r, idx, val);
        st[p] = cap_mul(st[p<<1], st[p<<1|1]);
    }

    long long query_all() const { return st[1]; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<long long> a(N+1);
    for (int i = 1; i <= N; i++) cin >> a[i];

    vector<long long> f(N+1, 1);

    auto calc_factor = [&](int idx) -> long long {
        if (idx == 1) {
            long long v = a[1] + 1;
            if (v > LIM) v = LIM;
            return v;
        } else {
            long long num = a[idx];
            long long den = a[idx-1];
            long long v = (num + den - 1) / den;
            if (v > LIM) v = LIM;
            return v;
        }
    };

    for (int i = 1; i <= N; i++) f[i] = calc_factor(i);

    SegTree st(N);
    st.build(1, 1, N, f);

    int Q;
    cin >> Q;
    while (Q--) {
        int i;
        long long v, t;
        cin >> i >> v >> t;
        a[i] = v;

        f[i] = calc_factor(i);
        st.update(1, 1, N, i, f[i]);

        if (i+1 <= N) {
            f[i+1] = calc_factor(i+1);
            st.update(1, 1, N, i+1, f[i+1]);
        }

        long long P = st.query_all(); 
        long long shift = (long long)(N - 1);

        long long dumps = 0;
        if (t > shift) {
            long long x = t - shift;
            dumps = x / P;
        }
        __int128 ans = ( __int128 )dumps * a[N];
        cout << (long long)ans << "\n";
    }

    return 0;
}
