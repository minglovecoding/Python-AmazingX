#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long square_sums[505][505]; 
int grid[505][505];              

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, K;
    if (!(cin >> N >> K)) return 0;

    int Q;
    cin >> Q;

    long long current_max = 0;

    for (int q = 0; q < Q; ++q) {
        int r, c, v;
        cin >> r >> c >> v;

        r--; 
        c--;

        int diff = v - grid[r][c];
        grid[r][c] = v;

        int start_i = max(0, r - K + 1);
        int end_i = min(N - K, r);

        int start_j = max(0, c - K + 1);
        int end_j = min(N - K, c);

        for (int i = start_i; i <= end_i; ++i) {
            for (int j = start_j; j <= end_j; ++j) {
                square_sums[i][j] += diff;
                
                if (square_sums[i][j] > current_max) {
                    current_max = square_sums[i][j];
                }
            }
        }

        cout << current_max << "\n";
    }

    return 0;
}