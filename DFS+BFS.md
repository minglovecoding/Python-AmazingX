### 🚀 DFS（Depth-First Search）深度优先搜索

### ✔️ 伪代码（DFS）

核心思想：**沿着一条路一直往深处走，到头后再回到分叉点继续探索其他路径。**

DFS 是典型的 **递归 + 回溯** 思想。

### ✔️（1）递归写法

```c++
void dfs(int u) {
    vis[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) dfs(v);
    }
}
```

### ✔️（2）手动栈写法（避免爆栈）

```c++
stack<int> st;
st.push(start);
vis[start] = true;
while (!st.empty()) {
    int u = st.top(); st.pop();
    for (int v : adj[u]) {
        if (!vis[v]) {
            vis[v] = true;
            st.push(v);
        }
    }
}
```

### ✔️ DFS 优点

- 写法简单（尤其递归）
- 适合树的深度相关问题
- 可以顺便做回溯（比如解迷宫、生成排列）

### ❗ DFS 缺点

- 易栈溢出（节点上限 2e5 时要注意）
- 找最短路一般不用它（因为可能先走到很远的路径）

### 🚀 BFS（Breadth-First Search）广度优先搜索

**核心思想：一圈一圈往外扩，像“水波纹”。**

```c++
queue<int> q;
q.push(start);
vis[start] = true;

while(!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : adj[u]) {
        if (!vis[v]) {
            vis[v] = true;
            q.push(v);
        }
    }
}
```

### ✔️ BFS 优点

- 能保证无权图最短路
- 不会栈溢出
- 多源 BFS 特别强（USACO 高频）

### ❗ BFS 缺点

- 需要队列
- 不能像 DFS 那样方便地做回溯

***

[P1596](https://www.luogu.com.cn/problem/P1596)

```c++
#include<cstdio>
using namespace std;
char a[101][101];
int ans;
int n,m;
void dfs(int x,int y){
    a[x][y]='.';
    int dx,dy;
    for(int i=-1;i<=1;i++){
        for(int j=-1;j<=1;j++){
            dx=x+i;
            dy=y+j;
            if(dx>=0&&dx<=n&&dy>=0&&dy<m&&a[dx][dy]=='W'){
                dfs(dx,dy);
            }
        }
    }
    return;
} 
int main(){
    scanf("%d%d",&n,&m);
    for(int i=0;i<=n;i++){
    	scanf("%s",a[i]);//避免换行带来问题这里直接读入字符串
    }
    for(int i=0;i<=n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j]=='W'){//如果是W的话就直接开始遍历
                dfs(i,j);
                ans++;//水潭加一处
            }
        }
    }
    printf("%d",ans);
    return 0;
}
```

[P1825](https://www.luogu.com.cn/problem/P1825)

```c++
#include<iostream>
#include<queue>
using namespace std;
const int N=350;
struct point{
    int x;
    int y;
    int t;
};
queue<point> que;
char a[N][N];
bool vis[N][N];
int n,m;
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
int sx;
int sy;

void goto_another(int &nx,int &ny,int k)//goto_another函数用于寻找另一个传送门，nx、ny代表当前点的坐标，记得要加上取地址符'&'，因为每当贝西踏入一个传送门，它就会立即被传送至另一个传送门，不能在原地停留
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(a[i][j]==a[nx][ny]&&(i!=nx||j!=ny))//如果a[i][j]这个点的是一个与a[nx][ny]相同的传送门，并且a[i][j]与a[nx][ny]不是同一个点
            {
                nx=i;//改变当前坐标，将贝西强行移动至另一个传送门处
                ny=j;
                return ;//告辞
            }
        }
    }
}
int main()
{
    cin>>n>>m;
    string s;
    for(int i=1;i<=n;i++)
    {
        cin>>s;//由于输入奇奇怪怪地没有空格，于是乎窝便使用字符串读入
        for(int j=1;j<=m;j++)
        {
            a[i][j]=s[j-1];
            if(a[i][j]=='@')//获取起点坐标
            {
                sx=i;
                sy=j;
            }
        }
    }
    que.push((point){sx,sy,0});
    while(!que.empty())
    {
        point f=que.front();
        que.pop();
        if(a[f.x][f.y]=='=')
        {
            cout<<f.t;
            return 0;
        }
        if(a[f.x][f.y]>='A'&&a[f.x][f.y]<='Z')//特判部分，如果当前点是一个传送门，那么就传送至另一个传送门
        {
            goto_another(f.x,f.y,f.t);
        }
        for(int i=0;i<=3;i++)
        {
            int nx=f.x+dx[i];
            int ny=f.y+dy[i];
            if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&a[nx][ny]!='#'&&!vis[nx][ny])
            {
                vis[nx][ny]=true;
                que.push((point){nx,ny,f.t+1});
            }
        }
    }
    return 0;
}
```

📌 USACO 2021 US Open, Silver, Problem 1. Maze Tac Toe

```c++
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

//状态压缩
//图搜索
//预处理+去重
```