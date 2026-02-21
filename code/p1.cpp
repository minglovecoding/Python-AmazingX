#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>

using namespace std;

struct Region {
    int type;
    long long x, y;
    int e;
};

Region get_region(long long x, long long y, int z) {
    if (z == 0) return {0, x, y, 0};
    if (z == 1) return {0, x, y, 1};
    if (z == 2) return {1, x-1, y, 1};
    if (z == 3) return {1, x-1, y, 2};
    if (z == 4) return {0, x-1, y, 2};
    if (z == 5) return {0, x-1, y, 0};
    if (z == 6) return {1, x-1, y-1, 0};
    if (z == 7) return {1, x-1, y-1, 1};
    if (z == 8) return {0, x, y-1, 1};
    if (z == 9) return {0, x, y-1, 2};
    if (z == 10) return {1, x, y-1, 2};
    if (z == 11) return {1, x, y-1, 0};
    return {0,0,0,0};
}

vector<long long> get_center(Region r) {
    if (r.type == 0) {
        return {r.x + r.y + 1, -r.x, -r.y};
    } else {
        return {r.x + r.y + 2, -r.x, -r.y};
    }
}

vector<long long> get_V(Region r) {
    Region across = {0,0,0,0};
    if (r.type == 0) {
        if (r.e == 0) across = {1, r.x, r.y-1, 0};
        if (r.e == 1) across = {1, r.x-1, r.y, 1};
        if (r.e == 2) across = {1, r.x, r.y, 2};
    } else {
        if (r.e == 0) across = {0, r.x, r.y+1, 0};
        if (r.e == 1) across = {0, r.x+1, r.y, 1};
        if (r.e == 2) across = {0, r.x, r.y, 2};
    }
    return get_center(across);
}

void solve() {
    int N;
    if (!(cin >> N)) return;
    
    vector<vector<long long>> u(N), v(N);
    for (int i = 0; i < N; i++) {
        long long x, y;
        int z;
        cin >> x >> y >> z;
        Region r = get_region(x, y, z);
        u[i] = get_center(r);
        v[i] = get_V(r);
    }
    
    long long total_D_uu = 0;
    for (int c = 0; c < 3; c++) {
        vector<long long> vals(N);
        for (int i = 0; i < N; i++) vals[i] = u[i][c];
        sort(vals.begin(), vals.end());
        long long sum_so_far = 0;
        for (int i = 0; i < N; i++) {
            total_D_uu += vals[i] * (long long)i - sum_so_far;
            sum_so_far += vals[i];
        }
    }
    
    long long ans = 2LL * total_D_uu - (long long)N * (N - 1LL) / 2LL;
    
    vector<vector<long long>> sorted_u(3, vector<long long>(N));
    for (int c = 0; c < 3; c++) {
        for (int j = 0; j < N; j++) sorted_u[c][j] = u[j][c];
        sort(sorted_u[c].begin(), sorted_u[c].end());
    }
    
    long long sum_greater = 0;
    for (int i = 0; i < N; i++) {
        int c = 0;
        if (v[i][1] != u[i][1]) c = 1;
        if (v[i][2] != u[i][2]) c = 2;
        
        long long delta = v[i][c] - u[i][c];
        long long val = u[i][c];
        
        if (delta == 1) {
            auto it = upper_bound(sorted_u[c].begin(), sorted_u[c].end(), val);
            long long count = distance(sorted_u[c].begin(), it);
            sum_greater += count - 1LL; 
        } else {
            auto it = lower_bound(sorted_u[c].begin(), sorted_u[c].end(), val);
            long long count = N - distance(sorted_u[c].begin(), it);
            sum_greater += count - 1LL;
        }
    }
    ans += sum_greater;
    
    long long penalty = 0;
    for (int c = 0; c < 3; ++c) {
        unordered_map<long long, long long> count_minus;
        for (int i = 0; i < N; ++i) {
            if (v[i][c] - u[i][c] == -1) {
                count_minus[u[i][c]]++;
            }
        }
        for (int i = 0; i < N; ++i) {
            if (v[i][c] - u[i][c] == 1) {
                if (count_minus.count(u[i][c] + 1)) {
                    penalty += count_minus[u[i][c] + 1];
                }
            }
        }
    }
    
    map<vector<long long>, long long> edge_counts;
    for (int i = 0; i < N; ++i) {
        edge_counts[{u[i][0], u[i][1], u[i][2], v[i][0], v[i][1], v[i][2]}]++;
    }
    
    long long reverse_pairs = 0;
    for (auto const& pair : edge_counts) {
        vector<long long> edge = pair.first;
        long long count = pair.second;
        vector<long long> rev_edge = {edge[3], edge[4], edge[5], edge[0], edge[1], edge[2]};
        if (edge < rev_edge && edge_counts.count(rev_edge)) {
            reverse_pairs += count * edge_counts[rev_edge];
        }
    }
    
    ans += penalty - reverse_pairs;
    
    long long same_region_pairs = 0;
    for (auto const& pair : edge_counts) {
        long long count = pair.second;
        same_region_pairs += count * (count - 1LL) / 2LL;
    }
    ans -= same_region_pairs;
    
    cout << ans << "\n";
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