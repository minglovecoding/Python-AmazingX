//2≤N≤10^5 1≤K≤2×10^5 
//1.初始化cowAt[i]=i，每头奶牛先记录自己的位置。
//2.只模拟一轮K次交换，记录visited[cow]。
//3.根据一轮结束后的排列，求finalPos[cow]。
//4.将finalPos分解为若干置换环。
//5.对每个环，合并环内所有奶牛的visited位置。
//6.环内所有奶牛的答案都是这个并集的大小。
//7.按奶牛编号输出答案。

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    //cowAt[pos]：当前位置pos上是哪头奶牛
    vector<int> cowAt(N + 1);

    //visited[cow]：奶牛cow在一轮内经过的位置
    vector<vector<int>> visited(N + 1);

    for (int i = 1; i <= N; i++) {
        cowAt[i] = i;
        visited[i].push_back(i);
    }

    //模拟完整的一轮K次交换
    for (int i = 0; i < K; i++) {
        int a, b;
        cin >> a >> b;

        int cowA = cowAt[a];
        int cowB = cowAt[b];

        //交换后，两头奶牛到达的新位置
        visited[cowA].push_back(b);
        visited[cowB].push_back(a);

        swap(cowAt[a], cowAt[b]);
    }

    /*
     * nextCow[cow]表示：
     * 一轮结束后，奶牛cow所在的位置。
     *
     * 下一轮中，它会经历初始时位于这个位置的奶牛
     * 在第一轮中走过的路线。
     */
    vector<int> nextCow(N + 1);

    for (int pos = 1; pos <= N; pos++) {
        int cow = cowAt[pos];
        nextCow[cow] = pos;
    }

    vector<bool> usedCow(N + 1, false);
    vector<int> answer(N + 1);

    /*
     * positionMark[pos]记录位置pos最近在哪个置换环中出现。
     * 使用编号而不是每次清空整个数组。
     */
    vector<int> positionMark(N + 1, 0);
    int cycleId = 0;

    //分解置换环
    for (int start = 1; start <= N; start++) {
        if (usedCow[start]) continue;

        cycleId++;

        vector<int> cycle;
        int current = start;

        while (!usedCow[current]) {
            usedCow[current] = true;
            cycle.push_back(current);
            current = nextCow[current];
        }

        //统计当前环内所有visited集合的并集大小
        int count = 0;

        for (int cow : cycle) {
            for (int pos : visited[cow]) {
                if (positionMark[pos] != cycleId) {
                    positionMark[pos] = cycleId;
                    count++;
                }
            }
        }

        //同一个置换环中的奶牛答案相同
        for (int cow : cycle) {
            answer[cow] = count;
        }
    }

    for (int cow = 1; cow <= N; cow++) {
        cout << answer[cow] << '\n';
    }

    return 0;
}