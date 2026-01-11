#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <cmath>
#include <algorithm>

using namespace std;

void solve() {
    int N, K;
    if (!(cin >> N >> K)) return;
    string R;
    cin >> R;

    vector<pair<int, int>> chains; 
    chains.reserve(K);

    for (int rem = 0; rem < K; ++rem) {
        int cnt0 = 0; 
        int cnt1 = 0; 
        
        int curr = rem;
        int current_rel_val = 0; 
        
        if (current_rel_val == 0) cnt0++; else cnt1++;
        
        while (curr + K < N) {
            int diff = (R[curr] - '0') ^ (R[curr+1] - '0');
            current_rel_val ^= diff;
            
            if (current_rel_val == 0) cnt0++; else cnt1++;
            
            curr += K;
        }
 
        chains.push_back({cnt1, cnt0});
    }

    int target_parity = R[0] - '0';

    long long min_total = 0;
    int current_parity = 0;
    int min_diff = 1e9 + 7;

    for (const auto& p : chains) {
        int cost_start_0 = p.first;
        int cost_start_1 = p.second;
        
        if (cost_start_0 < cost_start_1) {
            min_total += cost_start_0;
        } else {
            min_total += cost_start_1;
            current_parity ^= 1;
        }
        min_diff = min(min_diff, abs(cost_start_0 - cost_start_1));
    }

    if (current_parity != target_parity) {
        min_total += min_diff;
    }

    long long max_total = 0;
    current_parity = 0;
    min_diff = 1e9 + 7;

    for (const auto& p : chains) {
        int cost_start_0 = p.first;
        int cost_start_1 = p.second;
        
        if (cost_start_0 > cost_start_1) {
            max_total += cost_start_0;
        } else {
            max_total += cost_start_1;
            current_parity ^= 1;
        }
        min_diff = min(min_diff, abs(cost_start_0 - cost_start_1));
    }

    if (current_parity != target_parity) {
        max_total -= min_diff;
    }

    cout << min_total << " " << max_total << "\n";
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