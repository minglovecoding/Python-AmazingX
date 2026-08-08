#include <bits/stdc++.h>
using namespace std;

struct CheeseBlock {
    int n;
    int res;
    vector<vector<int>> xy, xz, yz;

    CheeseBlock(int n_) : n(n_), res(0),
        xy(n, vector<int>(n, n)),
        xz(n, vector<int>(n, n)),
        yz(n, vector<int>(n, n)) {}

    void carve(int x, int y, int z) {
        --xy[x][y];
        --xz[x][z];
        --yz[y][z];
        res += (xy[x][y] == 0) + (xz[x][z] == 0) + (yz[y][z] == 0);
    }

    int ans() const { return res; }
};

int main() {
  
    int N, Q;
    cin >> N >> Q;

    CheeseBlock cb(N);
    for (int i = 0; i < Q; ++i) {
        int x, y, z;
        cin >> x >> y >> z;   // assumes 0-based indices as in the Python version
        cb.carve(x, y, z);
        cout << cb.ans() << '\n';
    }
    return 0;
}
//struct或class
//二维数组vector<vector<int>>用法
//空间几何