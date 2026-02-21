#include <bits/stdc++.h>
using namespace std;

static const long long MOD = 1000000007LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        string s;
        cin >> s;

        bool all01 = true;
        for (char c : s) {
            if (c != '0' && c != '1') { all01 = false; break; }
        }

        auto binValueMod = [&](const string& b, int upto) -> long long {
            long long v = 0;
            for (int i = 0; i < upto; i++) {
                v = (v * 2 + (b[i] - '0')) % MOD;
            }
            return v;
        };

        long long ans = 0;

        if (all01) {
            int L = (int)s.size();
            long long V = binValueMod(s, L);
            long long half = (L >= 2) ? binValueMod(s, L - 1) : 0; 
            ans = (V + half) % MOD;
        } else {
            string p = s;
            for (int i = 0; i < (int)p.size(); i++) {
                int d = p[i] - '0';
                p[i] = (d & 1) ? '1' : '0';
            }

            int pos = 0;
            while (pos < (int)p.size() && p[pos] == '0') pos++;

            if (pos == (int)p.size()) {
                ans = 1;
            } else {
                string b = p.substr(pos);
                int L = (int)b.size();
                long long V = binValueMod(b, L);
                long long half = (L >= 2) ? binValueMod(b, L - 1) : 0;
                ans = (1 + V + half) % MOD;
            }
        }

        cout << ans << "\n";
    }
    return 0;
}
