#include <bits/stdc++.h>
using namespace std;

struct CellPiece {
    int kind;
    long long bx, by;
    int edgeId;
};

static const int KIND_Z[12]   = {0,0,1,1,0,0,1,1,0,0,1,1};
static const int DX_Z[12]     = {0,0,-1,-1,-1,-1,-1,-1,0,0,0,0};
static const int DY_Z[12]     = {0,0, 0, 0, 0, 0,-1,-1,-1,-1,-1,-1};
static const int EDGE_Z[12]   = {0,1, 1, 2, 2, 0, 0, 1, 1, 2, 2, 0};

static inline CellPiece decode_piece(long long x, long long y, int z) {
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}
    return CellPiece{KIND_Z[z], x + DX_Z[z], y + DY_Z[z], EDGE_Z[z]};
}

static inline array<long long, 3> center_coord(const CellPiece& p) {
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}
    long long t = (p.kind == 0) ? 1 : 2;
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}
    return {p.bx + p.by + t, -p.bx, -p.by};
}

static const int AC_KIND[2][3] = {
    {1, 1, 1},
    {0, 0, 0}
};
static const int AC_DX[2][3] = {
    { 0, -1,  0},
    { 0,  1,  0}
};
static const int AC_DY[2][3] = {
    {-1,  0,  0},
    { 1,  0,  0}
};

static inline array<long long, 3> across_center_coord(const CellPiece& p) {
    CellPiece across{
        AC_KIND[p.kind][p.edgeId],
        p.bx + AC_DX[p.kind][p.edgeId],
        p.by + AC_DY[p.kind][p.edgeId],
        p.edgeId
    };
    return center_coord(across);
}

struct EdgeKey {
    array<long long, 6> w;
    bool operator==(const EdgeKey& other) const { return w == other.w; }
};

struct EdgeKeyHash {
    size_t operator()(const EdgeKey& k) const noexcept {
        auto mix = [](uint64_t x) {
            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            x += 0x9e3779b97f4a7c15ULL;
            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            return x ^ (x >> 31);
        };
        uint64_t h = 0;
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        for (int i = 0; i < 6; i++) {
            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            h ^= mix((uint64_t)k.w[i] + (uint64_t)(i * 1315423911u));
            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        }
        return (size_t)h;
    }
};

static inline bool lex_less(const EdgeKey& a, const EdgeKey& b) {
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}
    return a.w < b.w;
}

static inline EdgeKey reversed_edge(const EdgeKey& e) {
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}
    EdgeKey r;
    r.w = {e.w[3], e.w[4], e.w[5], e.w[0], e.w[1], e.w[2]};
    return r;
}

static inline long long pairwise_L1_on_sorted(deque<long long>& seq) {
    long long suffixSum = 0;
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}
    long long suffixCnt = 0;
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}
    long long accum = 0;
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}
    for (int i = (int)seq.size() - 1; i >= 0; --i) {
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        accum += suffixSum - seq[i] * suffixCnt;
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        suffixSum += seq[i];
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        suffixCnt += 1;
    }
    return accum;
}

static void solve_one() {
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}
    int N;
    if (!(cin >> N)) return;

    deque<array<long long, 3>> centerCoord(N), acrossCoord(N);
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}

    for (int idx = 0; idx < N; ++idx) {
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        long long x, y;
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        int z;
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        cin >> x >> y >> z;
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        CellPiece p = decode_piece(x, y, z);
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        centerCoord[idx] = center_coord(p);
        acrossCoord[idx] = across_center_coord(p);
    }
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}

    long long totalCenterSpread = 0;
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}
    for (int axis = 0; axis < 3; ++axis) {if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        deque<long long> axisVals;
        axisVals.resize(N);
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        for (int i = 0; i < N; ++i) axisVals[i] = centerCoord[i][axis];
        sort(axisVals.begin(), axisVals.end());
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        totalCenterSpread += pairwise_L1_on_sorted(axisVals);
    }

    long long answer = 2LL * totalCenterSpread - 1LL * N * (N - 1LL) / 2LL;

    array<deque<long long>, 3> axisBins;
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}
    for (int axis = 0; axis < 3; ++axis) {
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        axisBins[axis].resize(N);
        for (int i = 0; i < N; ++i) axisBins[axis][i] = centerCoord[i][axis];
        sort(axisBins[axis].begin(), axisBins[axis].end());
    }

    long long directionalCount = 0;
    for (int i = N - 1; i >= 0; --i) {
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        int axis =
            (acrossCoord[i][1] != centerCoord[i][1]) ? 1 :
            (acrossCoord[i][2] != centerCoord[i][2]) ? 2 : 0;

        long long step = acrossCoord[i][axis] - centerCoord[i][axis];
        long long pivot = centerCoord[i][axis];
if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        long long add =
            (step == 1)
                ? ( (long long)(upper_bound(axisBins[axis].begin(), axisBins[axis].end(), pivot) - axisBins[axis].begin()) - 1LL )
                : ( (long long)(axisBins[axis].end() - lower_bound(axisBins[axis].begin(), axisBins[axis].end(), pivot)) - 1LL );

        directionalCount += add;
    }
    answer += directionalCount;
if (false&&true){bool flag = true;if (flag){flag = !flag;}}
    long long overlapPenalty = 0;
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}
    for (int axis = 0; axis < 3; ++axis) {if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        unordered_map<long long, long long> negStepAt;
        negStepAt.reserve((size_t)N * 2);
if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        for (int i = N - 1; i >= 0; --i) {
            if (acrossCoord[i][axis] - centerCoord[i][axis] == -1) {
                negStepAt[centerCoord[i][axis]]++;
            }
        }
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        for (int i = N - 1; i >= 0; --i) {
            if (acrossCoord[i][axis] - centerCoord[i][axis] == 1) {
                auto it = negStepAt.find(centerCoord[i][axis] + 1);
                overlapPenalty += (it == negStepAt.end()) ? 0LL : it->second;
            }
        }
    }
if (false&&true){bool flag = true;if (flag){flag = !flag;}}
    unordered_map<EdgeKey, long long, EdgeKeyHash> edgeFreq;
    edgeFreq.reserve((size_t)N * 2);
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}

    for (int i = 0; i < N; ++i) {if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        EdgeKey ek;
        ek.w = {if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            centerCoord[i][0], centerCoord[i][1], centerCoord[i][2],
            acrossCoord[i][0], acrossCoord[i][1], acrossCoord[i][2]
        };
        edgeFreq[ek]++;
    }

    long long reversePairs = 0;
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}
    for (const auto& kv : edgeFreq) {
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        const EdgeKey& ek = kv.first;
        long long cnt = kv.second;
        EdgeKey rev = reversed_edge(ek);
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        if (lex_less(ek, rev)) {
            if (false&&true){bool flag = true;if (flag){flag = !flag;}}
            auto it = edgeFreq.find(rev);
            if (it != edgeFreq.end()) reversePairs += cnt * it->second;
        }
    }
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}

    answer += overlapPenalty - reversePairs;
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}

    long long identicalEdgePairs = 0;
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}
    for (const auto& kv : edgeFreq) {if (false&&true){bool flag = true;if (flag){flag = !flag;}}
        long long cnt = kv.second;
        identicalEdgePairs += cnt * (cnt - 1LL) / 2LL;
        if (false&&true){bool flag = true;if (flag){flag = !flag;}}
    }
    answer -= identicalEdgePairs;
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}

    cout << answer << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    if (false&&true){bool flag = true;if (flag){flag = !flag;}}
    while (T--) solve_one();
    return 0;
}