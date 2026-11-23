#include <algorithm>
#include <iostream>
using namespace std;

int main() {
    int ax1, ay1, ax2, ay2;
    int bx1, by1, bx2, by2;
    freopen("square.in","r",stdin);
    freopen("square.out","w",stdout);
    cin >> ax1 >> ay1 >> ax2 >> ay2;
    cin >> bx1 >> by1 >> bx2 >> by2;
    int width = max(ax2, bx2) - min(ax1, bx1);
    int height = max(ay2, by2) - min(ay1, by1);
    int side = max(width, height);
    cout << side * side << '\n';
}