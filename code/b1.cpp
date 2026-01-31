#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T, ElsieTypingMode;
    cin >> T >> ElsieTypingMode;
    while (T--) {
        int N;
        string S;
        cin >> N >> S;

        cout << "YES\n";
        if (ElsieTypingMode == 1) {
            string ans(N, 'M');
            bool flip = false;
            for (int i = N - 1; i >= 0; --i) {
                char c = S[i];
                if (flip) c = (c == 'M' ? 'O' : 'M');
                ans[i] = c;
                if (c == 'O') flip = !flip;
            }
            cout << ans << "\n";
        }
    }
    return 0;
}
