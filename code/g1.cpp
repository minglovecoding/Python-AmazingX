#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<long long> bit;
    Fenwick() : n(0) {}
    Fenwick(int n_) { init(n_); }
    void init(int n_) { n = n_; bit.assign(n + 1, 0); }
    void add(int i, long long v) {
        for (i++; i <= n; i += i & -i) bit[i] += v;
    }
    long long sumPrefix(int i) const {
        long long r = 0;
        for (i++; i > 0; i -= i & -i) r += bit[i];
        return r;
    }
    long long sumRange(int l, int r) const {
        if (l > r) return 0;
        return sumPrefix(r) - (l ? sumPrefix(l - 1) : 0);
    }
    long long sumAll() const { return sumPrefix(n - 1); }
};

struct SegTree {
    int n;
    vector<pair<int,int>> st;
    static constexpr int NEG = -1000000000;
    SegTree() : n(0) {}
    SegTree(int n_) { init(n_); }
    void init(int n_) {
        n = 1;
        while (n < n_) n <<= 1;
        st.assign(2 * n, {NEG, 0});
    }
    static pair<int,int> better(const pair<int,int>& a, const pair<int,int>& b) {
        return (a.first > b.first) ? a : b;
    }
    void setPoint(int idx, pair<int,int> val) {
        int p = idx + n;
        st[p] = val;
        for (p >>= 1; p; p >>= 1) st[p] = better(st[p<<1], st[p<<1|1]);
    }
    pair<int,int> query(int l, int r) const {
        pair<int,int> resL = {NEG, 0}, resR = {NEG, 0};
        l += n; r += n;
        while (l <= r) {
            if (l & 1) resL = better(resL, st[l++]);
            if (!(r & 1)) resR = better(st[r--], resR);
            l >>= 1; r >>= 1;
        }
        return better(resL, resR);
    }
};

struct CycleDS {
    int k;
    Fenwick fw;
    set<int> parties;
    vector<int> partyType;
    long long* globalCnt;
    CycleDS() : k(0), globalCnt(nullptr) {}
    CycleDS(int k_, long long* gc) { init(k_, gc); }
    void init(int k_, long long* gc) {
        k = k_;
        fw.init(k);
        parties.clear();
        partyType.assign(k, 0);
        globalCnt = gc;
    }
    long long rangeSumCircular(int l, int r) const {
        if (k == 0) return 0;
        if (l <= r) return fw.sumRange(l, r);
        return fw.sumRange(l, k - 1) + fw.sumRange(0, r);
    }
    int nextPartyPos(int pos) const {
        if (parties.empty()) return -1;
        auto it = parties.lower_bound(pos);
        if (it == parties.end()) it = parties.begin();
        return *it;
    }
    int prevPartyPos(int pos) const {
        if (parties.empty()) return -1;
        auto it = parties.lower_bound(pos);
        if (it == parties.begin()) it = parties.end();
        --it;
        return *it;
    }
    void update_w(int pos, long long delta) {
        if (delta == 0) return;
        fw.add(pos, delta);
        if (parties.empty()) return;
        int p = nextPartyPos(pos);
        int tp = partyType[p];
        if (tp) globalCnt[tp] += delta;
    }
    void insert_party(int pos, int tp) {
        if (partyType[pos] != 0) return;
        if (parties.empty()) {
            parties.insert(pos);
            partyType[pos] = tp;
            long long all = fw.sumAll();
            globalCnt[tp] += all;
            return;
        }
        int nxt = nextPartyPos(pos);
        int prv = prevPartyPos(pos);
        int tpN = partyType[nxt];
        long long oldSeg = rangeSumCircular((prv + 1) % k, nxt);
        long long segToNew = rangeSumCircular((prv + 1) % k, pos);
        long long segToNxt = rangeSumCircular((pos + 1) % k, nxt);
        globalCnt[tpN] -= oldSeg;
        globalCnt[tp] += segToNew;
        globalCnt[tpN] += segToNxt;
        parties.insert(pos);
        partyType[pos] = tp;
    }
    void erase_party(int pos, int tp) {
        if (partyType[pos] == 0) return;
        if ((int)parties.size() == 1) {
            long long all = fw.sumAll();
            globalCnt[tp] -= all;
            parties.erase(pos);
            partyType[pos] = 0;
            return;
        }
        int prv = prevPartyPos(pos);
        auto it = parties.upper_bound(pos);
        if (it == parties.end()) it = parties.begin();
        int nxt = *it;
        int tpN = partyType[nxt];
        long long segPos = rangeSumCircular((prv + 1) % k, pos);
        long long segNxt = rangeSumCircular((pos + 1) % k, nxt);
        long long merged = rangeSumCircular((prv + 1) % k, nxt);
        globalCnt[tp] -= segPos;
        globalCnt[tpN] -= segNxt;
        globalCnt[tpN] += merged;
        parties.erase(pos);
        partyType[pos] = 0;
    }
    void change_type(int pos, int oldTp, int newTp) {
        if (partyType[pos] == 0) return;
        if (oldTp == newTp) return;
        int prv = prevPartyPos(pos);
        long long seg = rangeSumCircular((prv + 1) % k, pos);
        globalCnt[oldTp] -= seg;
        globalCnt[newTp] += seg;
        partyType[pos] = newTp;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int FjString;
    cin >> FjString;
    int N = FjString;
    vector<int> a(N + 1);
    for (int i = 1; i <= N; i++) cin >> a[i];

    vector<vector<int>> rev(N + 1);
    vector<int> indeg(N + 1, 0);
    for (int i = 1; i <= N; i++) {
        rev[a[i]].push_back(i);
        indeg[a[i]]++;
    }

    vector<int> isCycle(N + 1, 1);
    queue<int> q;
    for (int i = 1; i <= N; i++) if (indeg[i] == 0) q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        isCycle[u] = 0;
        int v = a[u];
        indeg[v]--;
        if (indeg[v] == 0) q.push(v);
    }

    vector<int> cycleId(N + 1, -1), posInCycle(N + 1, -1), rootOf(N + 1, 0);
    vector<vector<int>> cycles;
    vector<int> visC(N + 1, 0);

    for (int i = 1; i <= N; i++) {
        if (isCycle[i] && !visC[i]) {
            vector<int> nodes;
            int cur = i;
            while (!visC[cur]) {
                visC[cur] = 1;
                nodes.push_back(cur);
                cur = a[cur];
            }
            int id = (int)cycles.size();
            cycles.push_back(nodes);
            for (int j = 0; j < (int)nodes.size(); j++) {
                int u = nodes[j];
                cycleId[u] = id;
                posInCycle[u] = j;
                rootOf[u] = u;
            }
        }
    }

    vector<int> parent(N + 1, 0), depth(N + 1, 0);
    vector<int> tin(N + 1, 0), tout(N + 1, 0), sub(N + 1, 0);
    vector<int> orderTin;
    orderTin.reserve(N + 1);
    int timer = 0;

    vector<int> roots;
    roots.reserve(N);
    for (auto &cy : cycles) for (int u : cy) roots.push_back(u);

    vector<int> stack;
    vector<int> itidx;
    stack.reserve(N);
    itidx.reserve(N);

    for (int r : roots) {
        parent[r] = 0;
        depth[r] = 0;
        rootOf[r] = r;

        stack.clear();
        itidx.clear();
        stack.push_back(r);
        itidx.push_back(0);

        while (!stack.empty()) {
            int u = stack.back();
            int &it = itidx.back();
            if (it == 0) {
                tin[u] = timer++;
                orderTin.push_back(u);
            }
            if (it < (int)rev[u].size()) {
                int v = rev[u][it++];
                if (isCycle[v]) continue;
                parent[v] = u;
                depth[v] = depth[u] + 1;
                rootOf[v] = r;
                stack.push_back(v);
                itidx.push_back(0);
            } else {
                tout[u] = timer - 1;
                stack.pop_back();
                itidx.pop_back();
            }
        }
    }

    vector<int> post;
    post.reserve(N);
    vector<int> stk;
    vector<int> iter2;

    for (int r : roots) {
        stk.clear();
        iter2.clear();
        stk.push_back(r);
        iter2.push_back(0);
        while (!stk.empty()) {
            int u = stk.back();
            int &it = iter2.back();
            if (it < (int)rev[u].size()) {
                int v = rev[u][it++];
                if (isCycle[v]) continue;
                stk.push_back(v);
                iter2.push_back(0);
            } else {
                post.push_back(u);
                stk.pop_back();
                iter2.pop_back();
            }
        }
    }

    for (int u : post) {
        int s = 1;
        for (int v : rev[u]) {
            if (isCycle[v]) continue;
            if (parent[v] == u) s += sub[v];
        }
        sub[u] = s;
    }

    vector<int> heavy(N + 1, -1);
    vector<int> sz(N + 1, 0);
    for (int u : post) {
        sz[u] = 1;
        int best = -1, bestSz = 0;
        for (int v : rev[u]) {
            if (isCycle[v]) continue;
            if (parent[v] != u) continue;
            sz[u] += sz[v];
            if (sz[v] > bestSz) {
                bestSz = sz[v];
                best = v;
            }
        }
        heavy[u] = best;
    }

    vector<int> head(N + 1, 0), hpos(N + 1, 0);
    int curPos = 0;
    for (int r : roots) {
        int u = r;
        int start = u;
        vector<int> stackNodes;
        stackNodes.reserve(1024);
        stackNodes.push_back(r);
        while (!stackNodes.empty()) {
            int x = stackNodes.back();
            stackNodes.pop_back();
            int y = x;
            while (y != -1) {
                head[y] = x;
                hpos[y] = curPos++;
                for (int v : rev[y]) {
                    if (isCycle[v]) continue;
                    if (parent[v] != y) continue;
                    if (v == heavy[y]) continue;
                    stackNodes.push_back(v);
                }
                y = heavy[y];
            }
        }
    }

    SegTree seg(curPos);

    vector<int> nodeAtTin(timer, 0);
    for (int i = 0; i < timer; i++) nodeAtTin[tin[orderTin[i]]] = orderTin[i];

    vector<int> type(N + 1, 0);
    vector<long long> childSum(N + 1, 0);
    vector<int> parentMarked(N + 1, 0);
    set<int> markedTin;

    vector<long long> capturedSum(N + 1, 0);

    long long globalCnt[4] = {0, 0, 0, 0};

    vector<CycleDS> cycDS(cycles.size());
    for (int id = 0; id < (int)cycles.size(); id++) {
        cycDS[id].init((int)cycles[id].size(), globalCnt);
    }

    for (int id = 0; id < (int)cycles.size(); id++) {
        auto &cy = cycles[id];
        for (int j = 0; j < (int)cy.size(); j++) {
            int r = cy[j];
            long long fall = sub[r] - capturedSum[r];
            cycDS[id].fw.add(j, fall);
        }
    }

    auto applyExclusiveDelta = [&](int u, long long delta) {
        if (delta == 0) return;
        int tp = type[u];
        if (tp) globalCnt[tp] += delta;
        int r = rootOf[u];
        capturedSum[r] += delta;
        int cid = cycleId[r];
        if (cid != -1) {
            int pos = posInCycle[r];
            cycDS[cid].update_w(pos, -delta);
        }
    };

    auto queryNearestMarked = [&](int u) -> int {
        int r = rootOf[u];
        pair<int,int> best = {SegTree::NEG, 0};
        int x = u;
        while (head[x] != head[r]) {
            best = SegTree::better(best, seg.query(hpos[head[x]], hpos[x]));
            x = parent[head[x]];
        }
        best = SegTree::better(best, seg.query(hpos[r], hpos[x]));
        return best.second;
    };

    auto scanTopChildren = [&](int u, int p) {
        vector<int> res;
        auto it = markedTin.lower_bound(tin[u]);
        while (it != markedTin.end() && *it <= tout[u]) {
            int x = nodeAtTin[*it];
            if (x == u) {
                ++it;
                continue;
            }
            if (parentMarked[x] == p) {
                res.push_back(x);
                it = markedTin.lower_bound(tout[x] + 1);
            } else {
                int y = parentMarked[x];
                if (y == 0) {
                    ++it;
                } else {
                    it = markedTin.lower_bound(tout[y] + 1);
                }
            }
        }
        return res;
    };

    auto insertMark = [&](int u, int newTp) {
        int p = queryNearestMarked(u);
        auto children = scanTopChildren(u, p);

        type[u] = newTp;
        parentMarked[u] = p;
        childSum[u] = 0;

        markedTin.insert(tin[u]);
        seg.setPoint(hpos[u], {depth[u], u});

        applyExclusiveDelta(u, sub[u]);

        if (p != 0) {
            childSum[p] += sub[u];
            applyExclusiveDelta(p, -sub[u]);
        }

        for (int x : children) {
            if (p != 0) {
                childSum[p] -= sub[x];
                applyExclusiveDelta(p, +sub[x]);
            }
            childSum[u] += sub[x];
            applyExclusiveDelta(u, -sub[x]);
            parentMarked[x] = u;
        }
    };

    auto eraseMark = [&](int u) {
        int oldTp = type[u];
        int p = parentMarked[u];
        auto children = scanTopChildren(u, u);

        for (int x : children) {
            childSum[u] -= sub[x];
            applyExclusiveDelta(u, +sub[x]);

            parentMarked[x] = p;
            if (p != 0) {
                childSum[p] += sub[x];
                applyExclusiveDelta(p, -sub[x]);
            }
        }

        if (p != 0) {
            childSum[p] -= sub[u];
            applyExclusiveDelta(p, +sub[u]);
        }

        long long ex = sub[u] - childSum[u];
        applyExclusiveDelta(u, -ex);

        type[u] = 0;
        parentMarked[u] = 0;
        childSum[u] = 0;

        markedTin.erase(tin[u]);
        seg.setPoint(hpos[u], {SegTree::NEG, 0});

        (void)oldTp;
    };

    auto charToTp = [&](char c) -> int {
        if (c == 'C') return 1;
        if (c == 'O') return 2;
        return 3;
    };

    int M;
    cin >> M;

    for (int i = 0; i < M; i++) {
        int c;
        char v;
        cin >> c >> v;
        int newTp = charToTp(v);
        int oldTp = type[c];

        if (oldTp != newTp) {
            bool cyc = (cycleId[c] != -1);

            if (oldTp == 0 && newTp != 0) {
                insertMark(c, newTp);
                if (cyc) {
                    cycDS[cycleId[c]].insert_party(posInCycle[c], newTp);
                }
            } else if (oldTp != 0 && newTp == 0) {
                if (cyc) {
                    cycDS[cycleId[c]].erase_party(posInCycle[c], oldTp);
                }
                eraseMark(c);
            } else {
                if (cyc) {
                    cycDS[cycleId[c]].change_type(posInCycle[c], oldTp, newTp);
                }
                long long ex = sub[c] - childSum[c];
                globalCnt[oldTp] -= ex;
                globalCnt[newTp] += ex;
                type[c] = newTp;
            }
        }

        cout << globalCnt[1] << " " << globalCnt[2] << " " << globalCnt[3] << "\n";
    }

    return 0;
}