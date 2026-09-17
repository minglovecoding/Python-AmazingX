//1.一轮时间为K，执行rounds = M / K，还剩remains=M % K 次交换。
//2.模拟一轮完整K交换，fullVisit[i]表示奶牛 i 在一整轮中经过的所有位置，包括初始位置。
//3.partVisit[i]表示奶牛 i 在一轮的前 remain 次交换中经过的位置。nextCow[i]表示奶牛 i 完成一轮后到达的位置。
//4.因此，假设奶牛在环中的位置是 i，它最终经过的位置集合为fullVisit[i]U...fullVisit[i+rounds].
//5.情况一：rounds >= 环长度,直接合并环内所有奶牛的 fullVisit，环中每头奶牛答案相同。
//6.情况二：rounds < 环长度,奶牛只经过环上连续的 rounds 个节点，再加上下一个节点的 partVisit。
//7.把每头奶牛都重新合并一次时间复杂度过高，会有O(N^2)
//8.使用滑动窗口：
/*
窗口中保存连续 rounds 个节点的 fullVisit
临时加入下一个节点的 partVisit
得到当前奶牛的答案
删除临时加入的 partVisit
删除窗口最左边节点的 fullVisit
加入下一个节点的 fullVisit
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    ll M;

    cin >> N >> K >> M;

    vector<pair<int, int>> swaps(K);

    for (int i = 0; i < K; i++) {
        cin >> swaps[i].first >> swaps[i].second;
    }

    ll rounds = M / K;        // 完整执行的轮数
    int remain = M % K;       // 最后一轮执行的交换次数

    /*
     * cowAt[pos]：当前位置 pos 上是哪头奶牛
     */
    vector<int> cowAt(N + 1);

    /*
     * fullVisit[i]：
     * 奶牛 i 在完整的一轮中经过的位置
     *
     * partVisit[i]：
     * 奶牛 i 在一轮前 remain 次交换中经过的位置
     */
    vector<vector<int>> fullVisit(N + 1);
    vector<vector<int>> partVisit(N + 1);

    for (int i = 1; i <= N; i++) {
        cowAt[i] = i;

        // 初始位置也算经过
        fullVisit[i].push_back(i);
        partVisit[i].push_back(i);
    }

    // 模拟完整的一轮
    for (int i = 0; i < K; i++) {
        auto [a, b] = swaps[i];

        int cowA = cowAt[a];
        int cowB = cowAt[b];

        // 交换后 cowA 到达 b，cowB 到达 a
        fullVisit[cowA].push_back(b);
        fullVisit[cowB].push_back(a);

        // 前 remain 次交换属于最后的不完整轮
        if (i < remain) {
            partVisit[cowA].push_back(b);
            partVisit[cowB].push_back(a);
        }

        swap(cowAt[a], cowAt[b]);
    }

    /*
     * nextCow[i]：
     * 奶牛 i 执行完一轮后，到达的位置。
     *
     * 因为初始时奶牛编号和位置编号相同，
     * 所以它下一轮相当于处于 nextCow[i] 的状态。
     */
    vector<int> nextCow(N + 1);

    for (int pos = 1; pos <= N; pos++) {
        int cow = cowAt[pos];
        nextCow[cow] = pos;
    }

    vector<int> answer(N + 1);
    vector<bool> used(N + 1, false);

    /*
     * frequency[pos]：
     * 当前滑动窗口中，位置 pos 出现了多少次
     */
    vector<int> frequency(N + 1, 0);

    int distinctCount = 0;

    auto addPositions = [&](const vector<int>& positions) {
        for (int pos : positions) {
            if (frequency[pos] == 0) {
                distinctCount++;
            }

            frequency[pos]++;
        }
    };

    auto removePositions = [&](const vector<int>& positions) {
        for (int pos : positions) {
            frequency[pos]--;

            if (frequency[pos] == 0) {
                distinctCount--;
            }
        }
    };

    // 将置换拆成若干置换环
    for (int start = 1; start <= N; start++) {
        if (used[start]) {
            continue;
        }

        vector<int> cycle;

        int current = start;

        while (!used[current]) {
            used[current] = true;
            cycle.push_back(current);
            current = nextCow[current];
        }

        int cycleLength = cycle.size();

        /*
         * 情况一：
         * 完整轮数不少于环长度。
         *
         * 奶牛已经遍历整个置换环，
         * 所以环中每头奶牛的答案相同。
         */
        if (rounds >= cycleLength) {
            for (int cow : cycle) {
                addPositions(fullVisit[cow]);
            }

            for (int cow : cycle) {
                answer[cow] = distinctCount;
            }

            // 恢复 frequency，供下一个环使用
            for (int cow : cycle) {
                removePositions(fullVisit[cow]);
            }
        }

        /*
         * 情况二：
         * 只经过环上连续 rounds 个节点，
         * 然后再执行下一节点的前 remain 次交换。
         */
        else {
            int windowLength = (int)rounds;

            /*
             * 初始窗口：
             * cycle[0] 到 cycle[windowLength - 1]
             */
            for (int i = 0; i < windowLength; i++) {
                addPositions(fullVisit[cycle[i]]);
            }

            for (int i = 0; i < cycleLength; i++) {
                /*
                 * 完成 rounds 轮后，
                 * 奶牛处于 cycle[i + windowLength] 对应的状态。
                 */
                int partialIndex =
                    (i + windowLength) % cycleLength;

                int partialCow = cycle[partialIndex];

                // 临时加入最后不完整一轮经过的位置
                addPositions(partVisit[partialCow]);

                answer[cycle[i]] = distinctCount;

                // 撤销临时加入的部分
                removePositions(partVisit[partialCow]);

                /*
                 * 窗口向后移动一格：
                 *
                 * 删除 cycle[i]
                 * 加入 cycle[i + windowLength]
                 */
                if (windowLength > 0) {
                    removePositions(fullVisit[cycle[i]]);
                    addPositions(fullVisit[partialCow]);
                }
            }

            /*
             * 滑动一整圈后，窗口回到了初始状态，
             * 将窗口删除，恢复 frequency。
             */
            for (int i = 0; i < windowLength; i++) {
                removePositions(fullVisit[cycle[i]]);
            }
        }
    }

    for (int i = 1; i <= N; i++) {
        cout << answer[i] << '\n';
    }

    return 0;
}
