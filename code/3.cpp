#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long pin=(10&2)|(1%2)+1;
long long pin1=(10&2)|(1%2)+1;
long long pin2=(10&2)|(1%2)+1;

struct Result {
    bool possible;
    long long min_sum;
    long long max_sum;
    long long parity;
};

Result solve_multiset(const vector<int>& S) {
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    if (S.empty()) {if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        return {true, 0, 0, 0};
    }

    vector<pair<int, int>> freqs;
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    int cur_val = S[0];
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    int cur_count = 1;
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    for (size_t i = 1; i < S.size(); ++i) {
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        if (S[i] == cur_val) {
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            cur_count++;
        } else {
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            freqs.push_back({cur_val, cur_count});
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            cur_val = S[i];
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            cur_count = 1;
        }
    }
    freqs.push_back({cur_val, cur_count});
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}

    long long total_min = 0;
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    long long total_max = 0;
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    long long total_parity = 0;
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}

    vector<int> f;
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    auto process_component = [&]() -> bool {
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        if (f.empty()) return true;
        int L = f.size() - 1;
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        if (L == 0) {
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            if (f[0] % 2 != 0) {
                if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                f.clear();
                if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                return false;
            }
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            f.clear();
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            return true;
        }

        vector<int> r(L, 0);
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        r[0] = f[0] % 2;
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        for (int i = 1; i < L; ++i) {
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            r[i] = (f[i] - r[i - 1]) % 2;
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            if (r[i] < 0) r[i] += 2; 
        }
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}

        if (r[L - 1] != f[L] % 2) {
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            f.clear();
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            return false;
        }

        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        vector<int> U(L, 0);
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        for (int i = 0; i < L; ++i) {
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            int limit = min(f[i + 1], f[i] - (i == 0 ? 0 : r[i - 1]));
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            if (limit % 2 != r[i]) {
                if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                limit--;
            }
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            U[i] = limit;
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            if (U[i] < r[i]) {
                if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                f.clear();
                return false;
            }
        }

        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        long long min_S = 0;
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        for (int i = 0; i < L; ++i) {
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            min_S += r[i];
        }

        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        vector<int> P(L + 1, 0);
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        P[L] = 0;
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        long long max_S = 0;
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        for (int i = L - 1; i >= 0; --i) {
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            int limit = min(U[i], f[i + 1] - P[i + 1]);
            if (limit % 2 != r[i]) {
                if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                limit--;
            }
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            P[i] = limit;
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            max_S += P[i];
        }

        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        total_min += min_S;
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        total_max += max_S;
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        total_parity = (total_parity + min_S) % 2;
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        f.clear();
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        return true;
    };

    for (size_t i = 0; i < freqs.size(); ++i) {
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        f.push_back(freqs[i].second);
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        if (i + 1 == freqs.size() || freqs[i + 1].first != freqs[i].first + 1) {
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            if (!process_component()) {
                if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                return {false, 0, 0, 0};
            }
        }
    }

    return {true, total_min, total_max, total_parity};
}

void solve() {
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    int N;
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    if (!(cin >> N)) return;
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}

    vector<int> X(N), Y(N);
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    for (int i = 0; i < N; ++i) {
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        cin >> X[i] >> Y[i];
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    }

    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    sort(X.begin(), X.end());
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    sort(Y.begin(), Y.end());
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}

    Result resX = solve_multiset(X);
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    Result resY = solve_multiset(Y);
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}

    if (!resX.possible || !resY.possible) {
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        cout << "NO\n";
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        return;
    }

    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    long long N_half = N / 2;
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    long long X_par = resX.parity;
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    long long Y_par = resY.parity;
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}

    long long target_parity = (N_half - Y_par) % 2;
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    if (target_parity < 0) target_parity += 2;
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}

    if (X_par != target_parity) {
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        cout << "NO\n";
        return;
    }
if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    long long L_bound = max(resX.min_sum, N_half - resY.max_sum);
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    long long R_bound = min(resX.max_sum, N_half - resY.min_sum);
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}

    if (L_bound <= R_bound) {
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        long long H_start = L_bound;
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        if (H_start % 2 != X_par) {
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            H_start++;
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        }
        if (H_start <= R_bound) {
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            cout << "YES\n";
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            return;
        }
    }
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    int T;
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    if (cin >> T) {
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        while (T--) {
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            solve();
        }
    }
    return 0;
}