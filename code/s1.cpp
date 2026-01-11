#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

ll query_type_1(ll c, ll t) {
    ll cur_t = c;
    ll cur_pos = c;
    
    while (cur_t < t) {
        ll next_step = cur_t + 1;
        ll L = next_step / 2;
        
        if (cur_pos > L) {
            ll target_time = 2 * cur_pos;
            
            if (target_time > t) {
                return cur_pos;
            }
            
            ll jump_to = target_time - 1;
            if (jump_to > cur_t) {
                cur_t = jump_to;
            } else {
                cur_t++;
            }
        } else {
            if (cur_pos == 0) {
                cur_t++;
                cur_pos = cur_t / 2;
            } else {
                ll steps = cur_pos;
                if (cur_t + steps > t) {
                    steps = t - cur_t;
                }
                cur_pos -= steps;
                cur_t += steps;
            }
        }
    }
    return cur_pos;
}

ll query_type_2(ll x, ll t) {
    ll cur_t = t;
    ll cur_pos = x;
    
    if (cur_pos == cur_t) return cur_pos;

    while (true) {
        ll L = cur_t / 2;
        
        if (cur_pos > L) {
            return cur_pos;
        }
        
        if (cur_t == 0) return 0;

        ll val = cur_t - 2 * cur_pos;
        ll steps = val / 3;
        
        if (steps <= 0) {
            if (cur_pos == L) {
                cur_pos = 0;
            } else {
                cur_pos++;
            }
            cur_t--;
        } else {
            cur_t -= steps;
            cur_pos += steps;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int Q;
    if (cin >> Q) {
        while (Q--) {
            ll type, a, b;
            cin >> type >> a >> b;
            if (type == 1) {
                cout << query_type_1(a, b) << "\n";
            } else {
                cout << query_type_2(a, b) << "\n";
            }
        }
    }
    return 0;
}