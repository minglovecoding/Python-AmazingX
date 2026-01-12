#include <bits/stdc++.h>
using namespace std;
static const long long MOD = 1000000007LL;

struct SegTree {
    int n;
    vector<long long> sum, lazy; 

    SegTree(int n_) : n(n_) {
        sum.assign(4 * n + 5, 0);
        lazy.assign(4 * n + 5, 1);
    }

    inline long long modMul(long long a, long long b) {
        return (a * b) % MOD;
    }

    void push(int node) {
        if (lazy[node] == 1) return;
        long long mul = lazy[node];
        int lc = node * 2, rc = node * 2 + 1;

        sum[lc] = modMul(sum[lc], mul);
        lazy[lc] = modMul(lazy[lc], mul);

        sum[rc] = modMul(sum[rc], mul);
        lazy[rc] = modMul(lazy[rc], mul);

        lazy[node] = 1;
    }

    void rangeMul(int node, int l, int r, int ql, int qr, long long mul) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            sum[node] = modMul(sum[node], mul);
            lazy[node] = modMul(lazy[node], mul);
            return;
        }
        push(node);
        int mid = (l + r) >> 1;
        rangeMul(node * 2, l, mid, ql, qr, mul);
        rangeMul(node * 2 + 1, mid + 1, r, ql, qr, mul);
        sum[node] = (sum[node * 2] + sum[node * 2 + 1]) % MOD;
    }

    long long rangeSum(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) return sum[node];
        push(node);
        int mid = (l + r) >> 1;
        return (rangeSum(node * 2, l, mid, ql, qr) +
                rangeSum(node * 2 + 1, mid + 1, r, ql, qr)) % MOD;
    }

    void pointAdd(int node, int l, int r, int idx, long long val) {
        if (l == r) {
            sum[node] = (sum[node] + val) % MOD;
            return;
        }
        push(node);
        int mid = (l + r) >> 1;
        if (idx <= mid) pointAdd(node * 2, l, mid, idx, val);
        else pointAdd(node * 2 + 1, mid + 1, r, idx, val);
        sum[node] = (sum[node * 2] + sum[node * 2 + 1]) % MOD;
    }

    void rangeMul(int l, int r, long long mul) {
        if (l > r) return;
        rangeMul(1, 1, n, l, r, mul);
    }
    long long rangeSum(int l, int r) {
        if (l > r) return 0;
        return rangeSum(1, 1, n, l, r);
    }
    void pointAdd(int idx, long long val) {
        pointAdd(1, 1, n, idx, val);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    long long D;
    cin >> N >> D;

    vector<long long> p(N + 1);
    vector<int> o(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> p[i] >> o[i];
    }

    SegTree st(N);

    long long total = 1; 
    int ptr = 1;         

    for (int i = 1; i <= N; i++) {
        if (o[i] == 1) {
            st.pointAdd(i, total);
            total = (2 * total) % MOD;
        } else {
            long long need = p[i] - D;
            while (ptr < i && p[ptr] < need) ptr++;
            int L = ptr;

            long long eligible_sum = st.rangeSum(L, i - 1);
            st.rangeMul(L, i - 1, 2);
            total += eligible_sum;
            if (total >= MOD) total -= MOD;
        }
    }

    long long ans = total - 1; 
    if (ans < 0) ans += MOD;
    cout << ans << "\n";
    return 0;
}