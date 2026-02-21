#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Result {
    bool possible;
    long long min_sum;
    long long max_sum;
    long long parity;
};

Result solve_multiset(const vector<int>& S) {
    if (S.empty()) {
        return {true, 0, 0, 0};
    }

    vector<pair<int, int>> freqs;
    int cur_val = S[0];
    int cur_count = 1;
    for (size_t i = 1; i < S.size(); ++i) {
        if (S[i] == cur_val) {
            cur_count++;
        } else {
            freqs.push_back({cur_val, cur_count});
            cur_val = S[i];
            cur_count = 1;
        }
    }
    freqs.push_back({cur_val, cur_count});

    long long total_min = 0;
    long long total_max = 0;
    long long total_parity = 0;

    vector<int> f;
    auto process_component = [&]() -> bool {
        if (f.empty()) return true;
        int L = f.size() - 1;
        if (L == 0) {
            if (f[0] % 2 != 0) {
                f.clear();
                return false;
            }
            f.clear();
            return true;
        }

        vector<int> r(L, 0);
        r[0] = f[0] % 2;
        for (int i = 1; i < L; ++i) {
            r[i] = (f[i] - r[i - 1]) % 2;
            if (r[i] < 0) r[i] += 2; 
        }

        if (r[L - 1] != f[L] % 2) {
            f.clear();
            return false;
        }

        vector<int> U(L, 0);
        for (int i = 0; i < L; ++i) {
            int limit = min(f[i + 1], f[i] - (i == 0 ? 0 : r[i - 1]));
            if (limit % 2 != r[i]) {
                limit--;
            }
            U[i] = limit;
            if (U[i] < r[i]) {
                f.clear();
                return false;
            }
        }

        long long min_S = 0;
        for (int i = 0; i < L; ++i) {
            min_S += r[i];
        }

        vector<int> P(L + 1, 0);
        P[L] = 0;
        long long max_S = 0;
        for (int i = L - 1; i >= 0; --i) {
            int limit = min(U[i], f[i + 1] - P[i + 1]);
            if (limit % 2 != r[i]) {
                limit--;
            }
            P[i] = limit;
            max_S += P[i];
        }

        total_min += min_S;
        total_max += max_S;
        total_parity = (total_parity + min_S) % 2;
        f.clear();
        return true;
    };

    for (size_t i = 0; i < freqs.size(); ++i) {
        f.push_back(freqs[i].second);
        if (i + 1 == freqs.size() || freqs[i + 1].first != freqs[i].first + 1) {
            if (!process_component()) {
                return {false, 0, 0, 0};
            }
        }
    }

    return {true, total_min, total_max, total_parity};
}

void solve() {
    int N;
    if (!(cin >> N)) return;

    vector<int> X(N), Y(N);
    for (int i = 0; i < N; ++i) {
        cin >> X[i] >> Y[i];
    }

    sort(X.begin(), X.end());
    sort(Y.begin(), Y.end());

    Result resX = solve_multiset(X);
    Result resY = solve_multiset(Y);

    if (!resX.possible || !resY.possible) {
        cout << "NO\n";
        return;
    }

    long long N_half = N / 2;
    long long X_par = resX.parity;
    long long Y_par = resY.parity;

    long long target_parity = (N_half - Y_par) % 2;
    if (target_parity < 0) target_parity += 2;

    if (X_par != target_parity) {
        cout << "NO\n";
        return;
    }

    long long L_bound = max(resX.min_sum, N_half - resY.max_sum);
    long long R_bound = min(resX.max_sum, N_half - resY.min_sum);

    if (L_bound <= R_bound) {
        long long H_start = L_bound;
        if (H_start % 2 != X_par) {
            H_start++;
        }
        if (H_start <= R_bound) {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    if (cin >> T) {
        while (T--) {
            solve();
        }
    }
    return 0;
}