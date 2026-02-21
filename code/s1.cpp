#include <iostream>
#include <vector>
#include <queue>
using namespace std;
void solve() {
    int N, H;
    if (!(cin >> N >> H)) return;

    vector<long long> a(N + 1);
    for (int i = 1; i <= N; ++i) {
        cin >> a[i];
    }
    int K;
    cin >> K;
    vector<bool> is_wc(N + 1, false);
    for (int i = 0; i < K; ++i) {
        int x;
        cin >> x;
        is_wc[x] = true;
    }
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> hand_wc;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> hand_non;

    for (int i = 1; i <= H; ++i) {
        if (is_wc[i]) {
            hand_wc.push({a[i], i});
        } else {
            hand_non.push({a[i], i});
        }
    }
    queue<int> q;
    for (int i = H + 1; i <= N; ++i) {
        q.push(i);
    }

    int L = 2 * N;
    int C = N - H + 1;
    int total_steps = L + C;

    vector<long long> T(total_steps + 1, 0);
    vector<int> W(total_steps + 1, 0);
    vector<long long> prefix_T(total_steps + 1, 0);
    vector<long long> prefix_W(total_steps + 1, 0);

    for (int step = 1; step <= total_steps; ++step) {
        pair<long long, int> played;
        if (!hand_wc.empty()) {
            played = hand_wc.top();
            hand_wc.pop();
        } else {
            played = hand_non.top();
            hand_non.pop();
        }
        T[step] = played.first;
        W[step] = is_wc[played.second] ? 1 : 0;

        prefix_T[step] = prefix_T[step - 1] + T[step];
        prefix_W[step] = prefix_W[step - 1] + W[step];

        q.push(played.second);
        int drawn = q.front();
        q.pop();

        if (is_wc[drawn]) {
            hand_wc.push({a[drawn], drawn});
        } else {
            hand_non.push({a[drawn], drawn});
        }
    }
    int Q;
    cin >> Q;
    while (Q--) {
        long long t;
        cin >> t;

        if (t <= prefix_T[total_steps]) {
            int low = 0, high = total_steps;
            int ans_idx = 0;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (prefix_T[mid] <= t) {
                    ans_idx = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
            cout << prefix_W[ans_idx] << "\n";
        } else {
            long long time_after_prefix = t - prefix_T[L];
            long long cycle_T = prefix_T[L + C] - prefix_T[L];
            long long cycle_W = prefix_W[L + C] - prefix_W[L];

            long long num_cycles = time_after_prefix / cycle_T;
            long long rem_time = time_after_prefix % cycle_T;

            long long total_wc = prefix_W[L] + num_cycles * cycle_W;

            int low = 0, high = C;
            int ans_j = 0;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (prefix_T[L + mid] - prefix_T[L] <= rem_time) {
                    ans_j = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }

            total_wc += (prefix_W[L + ans_j] - prefix_W[L]);
            cout << total_wc << "\n";
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
