#include <algorithm>
#include <iostream>
using namespace std;

struct Rect {
    long long x1, y1, x2, y2;
};
int main() {
    freopen("billboard.in","r",stdin);
    freopen("billboard.out","w",stdout);
    
    Rect a, b;
    cin >> a.x1 >> a.y1 >> a.x2 >> a.y2;
    cin >> b.x1 >> b.y1 >> b.x2 >> b.y2;
    long long left = a.x1, right = a.x2;
    long long bottom = a.y1, top = a.y2;

    if (b.x1 <= a.x1 && b.x2 >= a.x2 &&
        b.y1 <= a.y1 && b.y2 >= a.y2) {
        cout << 0 << '\n';
        return 0;
    }
    // B 贯穿 A 的整个高度，检查能否去掉左侧或右侧。
    if (b.y1 <= a.y1 && b.y2 >= a.y2) {
        if (b.x1 <= a.x1 && b.x2 > a.x1) left = b.x2;//min(a.x2, b.x2);
        if (b.x2 >= a.x2 && b.x1 < a.x2) right = a.x1;//max(a.x1, b.x1);
    }
    // B 贯穿 A 的整个宽度，检查能否去掉下侧或上侧。
    if (b.x1 <= a.x1 && b.x2 >= a.x2) {
        if (b.y1 <= a.y1 && b.y2 > a.y1) bottom = min(a.y2, b.y2);
        if (b.y2 >= a.y2 && b.y1 < a.y2) top = max(a.y1, b.y1);
    }
    cout << max(0LL, right - left) * max(0LL, top - bottom) << '\n';
}
//时间、额外空间均为 O(1)。