#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, target;
    cin >> n >> target;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (a[i] + a[j] == target) {
                cout << i << " " << j << "\n";  // 0-based 下标
                return 0;
            }

    cout << -1 << "\n"; // 没找到
    return 0;
}