#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb push_back
bool sgn(ll x) { return (x > 0); }
class Obj {
   public:
    bool fixed;
    ll cost, inc, st, en;
    Obj(ll x, ll y) {
        fixed = true;
        st = x;
        cost = y;
        inc = 0LL;
        en = st;
    }
    Obj(ll a, ll b, ll c, ll d) {
        fixed = false;
        st = a;
        inc = b;
        en = c;
        if (st == en) {
            fixed = true;
            inc = 0;
        }
        cost = d;
    }
};
ll compat(Obj a, Obj b, ll try_val = -1LL) {
    if (a.fixed != b.fixed) {
        if (!a.fixed) {
            swap(a, b);
        }
    }
    if (a.fixed && b.fixed) {
        if (try_val >= 0 && try_val != a.st) {
            return -1LL;
        }
        if (a.st == b.st) {
            return a.st;
        }
        return -1LL;
    } else if (a.fixed || b.fixed) {
        bool didSwap = false;
        if (b.fixed) {
            didSwap = true;
            swap(a, b);
        }
        if (try_val >= 0LL && a.st != try_val) {
            return -1LL;
        }
        ll l = min(b.st, b.en);
        ll r = max(b.st, b.en);
        ll ret;
        if (a.st >= l && a.st <= r &&
            ((a.st % llabs(b.inc)) == (l % llabs(b.inc)))) {
            ret = a.st;
        } else {
            ret = -1LL;
        }
        if (didSwap) {
            swap(a, b);
        }
        return ret;
    } else {
        assert(!a.fixed && !b.fixed);

        ll a_l = min(a.st, a.en);
        ll a_r = max(a.st, a.en);
        ll b_l = min(b.st, b.en);
        ll b_r = max(b.st, b.en);

        if (try_val >= 0LL) {
            if (a_l % llabs(a.inc) != (try_val % llabs(a.inc))) {
                return -1LL;
            }
            if (b_l % llabs(b.inc) != (try_val % llabs(b.inc))) {
                return -1LL;
            }
            if (try_val < a_l || try_val < b_l || try_val > a_r ||
                try_val > b_r) {
                return -1LL;
            }
            assert(a.inc < 0LL);
			return try_val;
        } else {
            if (llabs(a.inc) != llabs(b.inc)) {
                return -1LL;
            }
            if ((a_l % llabs(a.inc)) != (b_l % llabs(a.inc))) {
                return -1LL;
            }
            try_val = min(a_r, b_r);
            if (try_val < min(a_l, b_l)) {
                return -1LL;
            }
            return try_val;
        }
    }
}
ll solve(vector<ll> x, vector<ll> y) {
    ll cnt = 0;
    bool done = true;
    for (int i = 0; i < 2; i++) {
        if (x[i] != y[i]) {
            done = false;
        }
    }
    if (done) {
        return 0;
    }
    for (int i = 0; i < 2; i++) {
        if (x[i] == 0) {
            x[i] += x[1 - i];
            cnt++;
        }
    }
    if (cnt == 2) {
        return -1;
    }
    assert((x[0] != 0) && (x[1] != 0));
    done = true;
    for (int i = 0; i < 2; i++) {
        if (x[i] != y[i]) {
            done = false;
        }
    }
    if (done) {
        return cnt;
    }
    int tmpY = 0;
    for (int i = 0; i < 2; i++) {
        if (y[i] == 0) {
            y[i] -= y[1 - i];
            cnt++;
            tmpY++;
        }
    }
    if (tmpY == 2) {
        return -1;
    }
    assert((y[0] != 0) && (y[1] != 0));
    done = true;
    for (int i = 0; i < 2; i++) {
        if (x[i] != y[i]) {
            done = false;
        }
    }
    if (done) {
        return cnt;
    }
    // Case 1: same sign
    if ((x[0] > 0) == (x[1] > 0)) {
        if (x[0] < 0) {
            for (int i = 0; i < 2; i++) {
                x[i] = -x[i];
                y[i] = -y[i];
            }
        }
        if (min(y[0], y[1]) <= 0) {
            return -1;
        }
        while (y[0] >= x[0] && y[1] >= x[1] &&
               ((x[0] + x[1]) != (y[0] + y[1])) && min(y[0], y[1]) > 0) {
            if (y[0] == y[1]) {
                break;
            } else if (y[0] > y[1]) {
                ll can = (y[0] - max(x[0], y[1]) - 1) / y[1] + 1;
                y[0] -= y[1] * can;
                cnt += can;
            } else {
                ll can = (y[1] - max(x[1], y[0]) - 1) / y[0] + 1;
                y[1] -= y[0] * can;
                cnt += can;
            }
        }
        if (x[0] == y[0] && x[1] == y[1]) {
            return cnt;
        } else {
            return -1;
        }
    } else {
        if (sgn(x[0]) != sgn(y[0]) && sgn(x[1]) != sgn(y[1])) {
            return -1;
        }
        if (sgn(x[0]) == sgn(y[0]) && sgn(x[1]) == sgn(y[1])) {
            if (x[0] < 0) {
                for (int i = 0; i < 2; i++) {
                    x[i] = -x[i];
                    y[i] = -y[i];
                }
            }
            // x0=+, y0=+, x1=-, y1=-
            assert(x[0] > 0LL && y[0] > 0LL && x[1] < 0LL && y[1] < 0LL);
            x[1] = llabs(x[1]);
            y[1] = llabs(y[1]);
            while (y[0] <= x[0] && y[1] <= x[1] &&
                   (x[0] + x[1]) != (y[0] + y[1])) {
                if (x[0] == x[1]) {
                    break;
                } else if (x[0] > x[1]) {
                    ll can =
                        max(0LL, x[0] - max(x[1], y[0]) - 1LL) / x[1] + 1LL;
                    x[0] -= x[1] * can;
                    cnt += can;
                } else {
                    ll can =
                        max(0LL, x[1] - max(x[0], y[1]) - 1LL) / x[0] + 1LL;
                    x[1] -= x[0] * can;
                    cnt += can;
                }
            }
            if (x[0] == y[0] && x[1] == y[1]) {
                return cnt;
            } else {
                return -1;
            }
        } else {
            if (sgn(x[0]) != sgn(y[0])) {
                swap(x[0], x[1]);
                swap(y[0], y[1]);
            }
            if (x[0] < 0) {
                for (int i = 0; i < 2; i++) {
                    x[i] = -x[i];
                    y[i] = -y[i];
                }
            }
            assert(x[0] > 0 && y[0] > 0 && x[1] < 0 && y[1] > 0);
            vector<pair<Obj, Obj>> pos_li;

            while (y[0] > 0 && y[1] > 0) {
                if (y[0] == y[1]) {
                    Obj l = Obj(y[0], cnt);
                    Obj r = Obj(y[1], cnt);
                    pos_li.pb(make_pair(l, r));
                    break;
                } else if (y[0] > y[1]) {
                    ll can = (y[0] - y[1] - 1LL) / y[1] + 1LL;
                    Obj l = Obj(y[0], -y[1], y[0] - y[1] * (can - 1LL), cnt);
                    Obj r = Obj(y[1], cnt);
                    pos_li.pb(make_pair(l, r));
                    y[0] -= y[1] * can;
                    cnt += can;
                } else {
                    ll can = (y[1] - y[0] - 1LL) / y[0] + 1LL;
                    Obj l = Obj(y[0], cnt);
                    Obj r = Obj(y[1], -y[0], y[1] - y[0] * (can - 1LL), cnt);
                    pos_li.pb(make_pair(l, r));
                    y[1] -= y[0] * can;
                    cnt += can;
                }
            }
            vector<pair<Obj, Obj>> mix_li;
            cnt = 0LL;
            // x0=+, y0=+, x1=-, y1=+
            while (x[0] > 0LL) {
                if (x[1] >= 0) {
                    if (x[1] == 0) {
                        cnt++;
                        x[1] = x[0];
                    }
                    Obj l = Obj(x[0], cnt);
                    Obj r = Obj(x[1], cnt);
                    mix_li.pb(make_pair(l, r));
                    break;
                }
                if (llabs(x[0]) == llabs(x[1])) {
                    x[1] = x[0];
                    cnt += 2;
                    Obj l = Obj(x[0], cnt);
                    Obj r = Obj(x[1], cnt);
                    mix_li.pb(make_pair(l, r));
                    break;
                }
                if (x[0] > llabs(x[1])) {
                    ll can = (x[0] - llabs(x[1]) - 1LL) / llabs(x[1]) + 1;
                    Obj l =
                        Obj(x[0], x[1], x[0] + x[1] * (can - 1LL), cnt + 1LL);
                    Obj r = Obj(x[1] + x[0], x[1],
                                x[1] + x[0] + x[1] * (can - 1LL), cnt + 1LL);
                    x[0] += x[1] * can;
                    cnt += can;
                    mix_li.pb(make_pair(l, r));
                } else {
                    ll can = (llabs(x[1]) - x[0] - 1LL) / x[0] + 1LL;
                    x[1] += x[0] * can;
                    cnt += can;
                }
            }
            ll INF = (ll)(2e18) + 10LL;
            ll ans = INF;
            int point = 0;
            for (int i = 0; i < pos_li.size(); i++) {
                for (int j = point; j < mix_li.size(); j++) {
                    ll pos_min = pos_li[i].first.en + pos_li[i].second.en;
                    ll pos_max = pos_li[i].first.st + pos_li[i].second.st;
                    ll mix_min = mix_li[j].first.en + mix_li[j].second.en;
                    ll mix_max = mix_li[j].first.st + mix_li[j].second.st;
                    if (pos_min > mix_max) {
                        break;
                    }
                    if (j == point && (mix_min > pos_max)) {
                        point++;
                        continue;
                    }
                    auto pos = pos_li[i];
                    auto mix = mix_li[j];
                    int do_first = 0;
                    if (pos.second.fixed) {
                        do_first = 1;
                    }
                    ll meet = -1LL;
                    if (do_first == 1) {
                        swap(pos.first, pos.second);
                        swap(mix.first, mix.second);
                    }
                    assert(pos.first.fixed);
                    ll got = compat(pos.first, mix.first);
                    vector<ll> meets(2);
                    if (got == -1LL) {
                        if (do_first == 1) {
                            swap(pos.first, pos.second);
                            swap(mix.first, mix.second);
                        }
                        continue;
                    }
                    meets[0] = pos.first.st;
                    if (!mix.first.fixed) {
                        ll num_iters =
                            (meets[0] - mix.first.st) / mix.first.inc;
                        meet = mix.second.st + num_iters * mix.second.inc;
                        got = compat(pos.second, mix.second, meet);
                        if (got == -1LL) {
                            if (do_first == 1) {
                                swap(pos.first, pos.second);
                                swap(mix.first, mix.second);
                            }
                            continue;
                        }
                        meets[1] = meet;
                    } else {
                        meet = compat(pos.second, mix.second);
                        if (meet == -1LL) {
                            if (do_first == 1) {
                                swap(pos.first, pos.second);
                                swap(mix.first, mix.second);
                            }
                            continue;
                        }
                        meets[1] = meet;
                    }
                    ll cur_cost = pos.first.cost + mix.first.cost;
                    vector<ll> move_amt(2);
                    if (pos.first.inc != 0) {
                        move_amt[0] = (meets[0] - pos.first.st) / pos.first.inc;
                    } else if (pos.second.inc != 0) {
                        move_amt[0] =
                            (meets[1] - pos.second.st) / pos.second.inc;
                    }
                    if (mix.first.inc != 0) {
                        move_amt[1] = (meets[0] - mix.first.st) / mix.first.inc;
                    } else if (mix.second.inc != 0) {
                        move_amt[1] =
                            (meets[1] - mix.second.st) / mix.second.inc;
                    }
                    cur_cost += move_amt[0] + move_amt[1];
                    ans = min(ans, cur_cost);

                    if (do_first == 1) {
                        swap(pos.first, pos.second);
                        swap(mix.first, mix.second);
                    }
                }
            }
            if (ans == INF) {
                ans = -1LL;
            }
            return ans;
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int Q;
    cin >> Q;
    for (int q = 1; q <= Q; q++) {
        vector<ll> x(2);
        vector<ll> y(2);
        cin >> x[0] >> x[1] >> y[0] >> y[1];
        cout << solve(x, y) << "\n";
    }
}