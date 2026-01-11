#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T, k;
    if (!(cin >> T >> k)) return 0;

    char pick[3][3] = {
        {'C','C','W'},
        {'C','C','O'},
        {'W','O','C'}
    };

    int pos[3][3] = {
        {0,1,2},
        {2,0,1},
        {1,2,0}
    };

    auto typ = [&](char c) -> int {
        if (c == 'C') return 0;
        if (c == 'O') return 1;
        return 2;
    };

    while (T--) {
        int FjString;
        cin >> FjString;
        int N = FjString;
        string S;
        cin >> S;
        int L = 3 * N;

        if (N % 2 == 1) {
            cout << -1 << "\n";
            continue;
        }

        int mid = L / 2;
        bool square = true;
        for (int i = 0; i < mid; i++) {
            if (S[i] != S[mid + i]) { square = false; break; }
        }

        if (square) {
            cout << 1 << "\n";
            for (int i = 0; i < L; i++) {
                if (i) cout << ' ';
                cout << 1;
            }
            cout << "\n";
            continue;
        }

        int half = N / 2;
        vector<int> assign(L, 0);

        for (int i = 0; i < half; i++) {
            int lb = 3 * i;
            int rb = 3 * (i + half);

            int t1 = typ(S[lb]);
            int t2 = typ(S[rb]);
            char ch = pick[t1][t2];

            int idx;
            if (ch == 'C') idx = 0;
            else if (ch == 'O') idx = 1;
            else idx = 2;

            int p1 = pos[t1][idx];
            int p2 = pos[t2][idx];

            assign[lb + p1] = 1;
            assign[lb + (p1 + 1) % 3] = 2;
            assign[lb + (p1 + 2) % 3] = 2;

            assign[rb + p2] = 1;
            assign[rb + (p2 + 1) % 3] = 2;
            assign[rb + (p2 + 2) % 3] = 2;
        }

        cout << 2 << "\n";
        for (int i = 0; i < L; i++) {
            if (i) cout << ' ';
            cout << assign[i];
        }
        cout << "\n";
    }

    return 0;
}
