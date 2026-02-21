#include <bits/stdc++.h>
using namespace std;

struct Rule {
    int kind, l, r, k, id;
};

struct MaxCmp {
    bool operator()(const pair<int,int>& a, const pair<int,int>& b) const {
        if (a.first != b.first) return a.first < b.first;
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        return a.second < b.second;
    }
};
struct MinCmp {
    bool operator()(const pair<int,int>& a, const pair<int,int>& b) const {
        if (a.first != b.first) return a.first > b.first;
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        return a.second > b.second;
    }
};

template <class HeapCmp>
static inline void heap_prune(
    priority_queue<pair<int,int>, deque<pair<int,int>>, HeapCmp>& heap,
    unordered_map<int,int>& dead
) {
    while (!heap.empty()) {
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        int id = heap.top().second;
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        auto it = dead.find(id);
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        if (it == dead.end() || it->second == 0) break;
        if (--it->second == 0) dead.erase(it);
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        heap.pop();
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
    }
}

static void solve() {
    int N, Q;
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}
    if (!(cin >> N >> Q)) return;

    deque<Rule> rule(Q + 1);
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}
    deque<deque<int>> enter1(N + 2), leave1(N + 2);
    deque<deque<int>> enter2(N + 2), leave2(N + 2);

    for (int i = 1; i <= Q; i++) {
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        cin >> rule[i].kind >> rule[i].l >> rule[i].r >> rule[i].k;
        rule[i].id = i;
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        if (rule[i].kind == 1) {if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            enter1[rule[i].r].push_back(i);
            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            if (rule[i].l - 1 >= 0) leave1[rule[i].l - 1].push_back(i);
        } else {if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            enter2[rule[i].r].push_back(i);
            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            if (rule[i].l - 1 >= 0) leave2[rule[i].l - 1].push_back(i);
        }
    }

    priority_queue<pair<int,int>, deque<pair<int,int>>, MaxCmp> lowerPick;
    priority_queue<pair<int,int>, deque<pair<int,int>>, MinCmp> upperPick;
    unordered_map<int,int> deadLower, deadUpper;
    deadLower.reserve((size_t)Q * 2);
    deadUpper.reserve((size_t)Q * 2);

    deque<int> lo(N + 1, 0), hi(N + 1, 1000000000);
    deque<int> endA(N + 1, 0), endB(N + 1, 0);

    for (int pos = N; pos >= 1; --pos) {
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        for (int id : enter1[pos]) lowerPick.push({rule[id].k, id});
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        for (int id : enter2[pos]) upperPick.push({rule[id].k, id});
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}

        for (int id : leave1[pos - 1]) deadLower[id]++; 
        for (int id : leave2[pos - 1]) deadUpper[id]++;
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        heap_prune(lowerPick, deadLower);
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        heap_prune(upperPick, deadUpper);
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}

        int a = 0, b = 0;
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        if (!lowerPick.empty()) {
            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            lo[pos] = lowerPick.top().first;
            a = lowerPick.top().second;
            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        }
        if (!upperPick.empty()) {
            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            hi[pos] = upperPick.top().first;
            b = upperPick.top().second;
            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        }

        if (lo[pos] > hi[pos]) {
            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            cout << -1 << "\n";
            return;
        }
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}

        endA[pos] = a;
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        endB[pos] = b;
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
    }

    if (false&&true){bool flag = true;if (flag){flag = !flag;}}
    deque<deque<int>> hits(Q + 1);
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}
    deque<int> remain(Q + 1, 0);
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}

    for (int pos = N; pos >= 1; --pos) {
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        int a = endA[pos], b = endB[pos];
        if (a) hits[a].push_back(pos);
        if (b) hits[b].push_back(pos);
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
    }
    for (int i = 1; i <= Q; ++i) {
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        remain[i] = (int)hits[i].size();
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        if (remain[i] == 0) {
            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            cout << -1 << "\n";
            return;
        }
    }
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}
    deque<int> stackLike;
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}
    for (int i = 1; i <= Q; ++i) if (remain[i] == 1) stackLike.push_back(i);
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}
    deque<char> taken(N + 1, 0);
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}
    deque<int> pickedPos(Q + 1, 0);
    int done = 0;
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}

    auto grab_free_pos = [&](int cid) -> int {
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        while (!hits[cid].empty() && taken[hits[cid].front()]) hits[cid].pop_front();
        return hits[cid].empty() ? 0 : hits[cid].front();
    };
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}


    auto other_end = [&](int pos, int cid) -> int {
        int a = endA[pos], b = endB[pos];
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        return (cid == a) ? b : a;
    };

    for (int fallback = 1; done < Q; ) {
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        int cur = 0;
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        if (!stackLike.empty()) {
            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            cur = stackLike.back();
            stackLike.pop_back();
            if (pickedPos[cur]) continue;
        } else {if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            while (fallback <= Q && pickedPos[fallback]) ++fallback;
            if (fallback > Q) break;
            cur = fallback;
        }

        int pos = grab_free_pos(cur);
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        if (pos == 0) {
            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            cout << -1 << "\n";
            return;
        }

        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        pickedPos[cur] = pos;
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        taken[pos] = 1;
        done++;

        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        int mate = other_end(pos, cur);
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        if (mate && !pickedPos[mate]) {
            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            if (--remain[mate] == 1) stackLike.push_back(mate);
        }
    }

    if (done != Q) {
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        cout << -1 << "\n";
        return;
    }

    deque<int> out(N + 1);
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}
    for (int pos = 1; pos <= N; ++pos) out[pos] = lo[pos];
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}
    for (int i = 1; i <= Q; ++i) out[pickedPos[i]] = rule[i].k;
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}

    for (int pos = 1; pos <= N; ++pos) {
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        cout << out[pos] << (pos == N ? "" : " ");
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}
    if (!(cin >> T)) return 0;
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}
    while (T--) solve();
    return 0;
}