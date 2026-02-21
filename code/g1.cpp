#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int N;
    if (!(cin >> N)) return;
    vector<int> p(N);
    for (int i = 0; i < N; i++) {
        cin >> p[i];
    }
    
    vector<int> A(2 * N);
    for (int i = 0; i < 2 * N; i++) {
        A[i] = p[i % N];
    }
    
    vector<int> L(2 * N, -1);
    vector<int> st;
    for (int i = 0; i < 2 * N; i++) {
        while (!st.empty() && A[st.back()] <= A[i]) {
            st.pop_back();
        }
        if (!st.empty()) L[i] = st.back();
        st.push_back(i);
    }
    
    vector<int> R(2 * N, 2 * N);
    st.clear();
    for (int i = 2 * N - 1; i >= 0; i--) {
        while (!st.empty() && A[st.back()] >= A[i]) {
            st.pop_back();
        }
        if (!st.empty()) R[i] = st.back();
        st.push_back(i);
    }
    
    vector<int> diff(N + 1, 0);
    for (int i = 0; i < 2 * N; i++) {
        if (L[i] != -1 && R[i] != 2 * N && R[i] - L[i] < N) {
            int start = R[i] - N + 1;
            int end = L[i];
            start = max(start, 0);
            end = min(end, N - 1);
            if (start <= end) {
                diff[start]++;
                diff[end + 1]--;
            }
        }
    }
    
    vector<int> valid_s;
    int cur = 0;
    for (int i = 0; i < N; i++) {
        cur += diff[i];
        if (cur == 0) {
            valid_s.push_back((N - i) % N);
        }
    }
    
    sort(valid_s.begin(), valid_s.end());
    cout << valid_s.size() << "\n";
    for (int i = 0; i < valid_s.size(); i++) {
        cout << valid_s[i] << (i + 1 == valid_s.size() ? "" : " ");
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    if (cin >> T) {
        while (T--) solve();
    }
    return 0;
}