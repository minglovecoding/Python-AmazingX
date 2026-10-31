#include <bits/stdc++.h>
using namespace std;

int main() {
	int N;
	cin >> N;
	vector<int> p(N + 1), t(N + 1), d1(N + 2),d2(N+2);
	for (int i = 1; i <= N; ++i)
		cin >> p[i];
	for (int i = 1; i <= N; ++i)
		cin >> t[i];
	for (int i = 1; i <= N+1; ++i){
        d1[i] = p[i] - p[i-1];
        d2[i] = t[i] - t[i-1];
    }
	int ans = 0;
	for (int i = 1; i <= N+1; ++i)
		ans += abs(d1[i] - d2[i]);
	cout << ans / 2<<"\n";
}