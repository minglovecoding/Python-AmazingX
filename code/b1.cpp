#include <bits/stdc++.h>
using namespace std;

int main() {

    int T, E_T;
    cin >> T >> E_T;
    while (T--) {
        int N;
        string S;
        cin >> N >> S;

        cout << "YES\n";
        if (E_T == 1) {
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
