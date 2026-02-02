#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long ll;

struct Event {
    ll pos;
    int type;

    bool operator<(const Event& other) const {
        return pos < other.pos;
    }
};

int n;
ll k;
vector<ll> a, b;

bool check(ll D) {
    vector<Event> events;
    events.reserve(2 * n);
    for (int i = 0; i < n; ++i) {
        
        ll L = a[i] - D;
        ll R = b[i];
        
        if (L <= R) {
            events.push_back({L, 1});
            events.push_back({R, 1});
        } else {
            
            ll sum = L + R;
            if (sum % 2 == 0) {
                events.push_back({sum / 2, 2});
            } else {
                events.push_back({(sum - 1) / 2, 1});
                events.push_back({(sum + 1) / 2, 1});
            }
        }
    }

    sort(events.begin(), events.end());

    ll current_slope = -n;
    ll optimal_y = events.back().pos;
    
    for (const auto& e : events) {
        current_slope += e.type;
        if (current_slope >= 0) {
            optimal_y = e.pos;
            break;
        }
    }

    ll total_cost = 0;
    for (int i = 0; i < n; ++i) {
        ll term1 = optimal_y - b[i];
        ll term2 = (a[i] - D) - optimal_y;
        ll cost = 0;
        if (term1 > cost) cost = term1;
        if (term2 > cost) cost = term2;
        
        total_cost += cost;
        if (total_cost > k) return false;
    }
    
    return total_cost <= k;
}

void solve() {
    if (!(cin >> n >> k)) return;
    a.resize(n);
    b.resize(n);
    
    ll max_a = -2e18, min_b = 2e18;
    
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (a[i] > max_a) max_a = a[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
        if (b[i] < min_b) min_b = b[i];
    }

    ll low = -2000000000000000000LL;
    ll high = 2000000000LL;
    
    ll ans = high;
    
    while (low <= high) {
        ll mid = low + (high - low) / 2;
        if (check(mid)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}