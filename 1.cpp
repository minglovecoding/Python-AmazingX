#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;
const int MAXSTATE = 19683; // 3^9

int N;
bool wall[MAXN][MAXN];
int start_x, start_y;

// 对于每个格子，如果是一步棋，则记录它对应的棋盘位置和放置的是 M(1) 还是 O(2)
int moveIdx[MAXN][MAXN]; // 0..8, -1 表示没有
int moveVal[MAXN][MAXN]; // 1 = M, 2 = O

bool visited[MAXN][MAXN][MAXSTATE];
bool winState[MAXSTATE];
int pow3[10];

// 预处理：判断一个 3^9 状态是否为获胜局面
void precompute_win() {
    pow3[0] = 1;
    for (int i = 1; i <= 9; i++) pow3[i] = pow3[i-1] * 3;
    //state = a0 + a1*3 + a2*3^2 + ... + a8*3^8
    for (int s = 0; s < MAXSTATE; s++) {
        int tmp = s;
        int a[9];
        for (int i = 0; i < 9; i++) {
            a[i] = tmp % 3; // 0: ., 1: M, 2: O
            tmp /= 3;
        }
        bool ok = false;

        auto checkLine = [&](int x, int y, int z) {
            int p = a[x], q = a[y], r = a[z];
            if (p == 1 && q == 2 && r == 2) return true; // MOO
            if (p == 2 && q == 2 && r == 1) return true; // OOM (逆向 MOO)
            return false;
        };

        if (checkLine(0,1,2) || checkLine(3,4,5) || checkLine(6,7,8) ||   // rows
            checkLine(0,3,6) || checkLine(1,4,7) || checkLine(2,5,8) ||   // cols
            checkLine(0,4,8) || checkLine(2,4,6)) {                      // diags
            ok = true;
        }
        winState[s] = ok;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    string line;
    // 初始化
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            wall[i][j] = false; //不是墙
            moveIdx[i][j] = -1; //没有棋盘落子 0~8 → （0 = 左上角，8 = 右下角）
            moveVal[i][j] = 0; //没有棋盘落子内容，1 → 'M'，2 → 'O'
        }
    }

    // 读取迷宫，每个格子 3 个字符
    for (int i = 0; i < N; i++) {
        cin >> line; // 长度 3N
        for (int j = 0; j < N; j++) {
            string cell = line.substr(j * 3, 3);
            if (cell == "###") {
                wall[i][j] = true;
            } else if (cell == "..." ) {
                // 空地
            } else if (cell == "BBB") {
                start_x = i;
                start_y = j;
            } else {
                // 一个移动：Mij 或 Oij
                char c = cell[0];       // 'M' or 'O'
                int r = cell[1] - '1';  // 0..2
                int c2 = cell[2] - '1'; // 0..2
                int idx = r * 3 + c2;
                moveIdx[i][j] = idx;
                moveVal[i][j] = (c == 'M' ? 1 : 2);
            }
        }
    }

    precompute_win();

    // BFS 状态：(x, y, boardState)
    queue<tuple<int,int,int>> q;
    int startState = 0; // 空棋盘
    visited[start_x][start_y][startState] = true;
    q.emplace(start_x, start_y, startState);

    set<int> winningBoards;

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    while (!q.empty()) {
        auto [x, y, state] = q.front();
        q.pop();

        for (int dir = 0; dir < 4; dir++) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
            if (wall[nx][ny]) continue;

            int newState = state;
            // 如果这个格子有一步棋，尝试落子
            if (moveIdx[nx][ny] != -1) {
                int idx = moveIdx[nx][ny];
                int v = moveVal[nx][ny]; // 1 or 2
                int cur = (state / pow3[idx]) % 3;  // 当前棋盘这个格子的内容
                if (cur == 0) { // 空才会下
                    newState = state + v * pow3[idx]; // 在这里落 M 或 O
                }
            }

            if (visited[nx][ny][newState]) continue;
            visited[nx][ny][newState] = true;

            if (winState[newState]) {
                // 一旦赢了，记录这个棋盘，不再从这里继续扩展
                winningBoards.insert(newState);
                continue;
            }

            q.emplace(nx, ny, newState);
        }
    }

    cout << winningBoards.size() << "\n";
    return 0;
}