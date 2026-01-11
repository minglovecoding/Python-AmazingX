#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using i128 = __int128_t;

static inline i128 evalF(int64 A, int64 B, int64 cA, int64 cB, int64 x, int64 b) {
    i128 total = (i128)A + (i128)B + (i128)x;
    return total - (i128)b + (i128)cA * (i128)(b / cB);
}

static inline i128 worstGuaranteedA(int64 A, int64 B, int64 cA, int64 cB, int64 x) {
    int64 L = B;
    int64 R = B + x;

    vector<int64> cand;
    cand.push_back(L);
    cand.push_back(R);

    if (cA > cB) {

        int64 q0 = L / cB;
        i128 endBlock = (i128)(q0 + 1) * (i128)cB - 1; 
        int64 b1 = (endBlock > (i128)R) ? R : (int64)endBlock;
        cand.push_back(b1);
    } else {
        
        int64 delta = (R + 1) % cB;          
        int64 b2 = R - delta;                
        if (b2 >= L) cand.push_back(b2);
    }

    sort(cand.begin(), cand.end());
    cand.erase(unique(cand.begin(), cand.end()), cand.end());

    i128 ans = (i128)4e36; // big
    for (int64 b : cand) ans = min(ans, evalF(A, B, cA, cB, x, b));
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int64 A, B, cA, cB, fA;
        cin >> A >> B >> cA >> cB >> fA;

        int64 lo = 0, hi = (int64)1e18;
        while (lo < hi) {
            int64 mid = lo + (hi - lo) / 2;
            i128 w = worstGuaranteedA(A, B, cA, cB, mid);
            if (w >= (i128)fA) hi = mid;
            else lo = mid + 1;
        }
        cout << lo << "\n";
    }
    return 0;
}
