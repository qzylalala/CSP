#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 55;
char g[N][N];
bool st1[N][N], st2[N][N];
int m, n;
int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};

// 检查 是否满足 (x1, y1) -> (x2, y2)
bool check(int x1, int y1, int x2, int y2) {
    if (g[x1][y1] == '+' || g[x1][y1] == 'S' || g[x1][y1] == 'T') return true;
    if (g[x1][y1] == '-') {
        if (x2 == x1) return true;
        else return false;
    }
    if (g[x1][y1] == '|') {
        if (y2 == y1) return true;
        else return false;
    }
    if (g[x1][y1] == '.') {
        if (x2 == x1 + 1 && y2 == y1) return true;
        else return false;
    }
} 

// S 出发能到达的地方
void dfs1(int x, int y) {
    st1[x][y] = true;
    for (int i = 0; i < 4; i++) {
        int a = x + dx[i], b = y + dy[i];
        if (a < 0 || a >= m || b < 0 || b >= n || g[a][b] == '#') continue;
        if (st1[a][b]) continue;
        if (check(x, y, a, b)) dfs1(a, b);
    }
}


// 从 T 走能回溯到的 地方
void dfs2(int x, int y) {
    st2[x][y] = true;
    for (int i = 0; i < 4; i++) {
        int a = x + dx[i], b = y + dy[i];
        if (a < 0 || a >= m || b < 0 || b >= n || g[a][b] == '#') continue;
        if (st2[a][b]) continue;
        if (check(a, b, x, y)) dfs2(a, b);
    }
}


int main() {
    cin >> m >> n;
    int sx, sy, tx, ty;
    for (int i = 0; i < m; i ++) {
        for (int j = 0; j < n; j++) {
            cin >> g[i][j];
            if (g[i][j] == 'S') {
                sx = i, sy = j;
            }
            if (g[i][j] == 'T') {
                tx = i, ty = j;
            }
        }
    }

    dfs1(sx, sy);
    dfs2(tx, ty);

    int cnt = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (st1[i][j] && !st2[i][j]) cnt ++;
        }
    }

    if (!st2[sx][sy]) puts("I'm stuck!");
    else cout << cnt << endl;

    return 0;
}