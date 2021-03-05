#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

#define x first
#define y second

using namespace std;

typedef pair<int, int> pii;

const int N = 110;
bool visited[N][N];
char g[N][N];
int st[N][N];
int m, n, q;


// st  0 : '.'    1 : '-'   2 : '|'   3 : '+'
void op0(int x1, int y1, int x2, int y2) {
    if (y1 == y2) {
        int x_min = min(x1, x2), x_max = max(x1, x2);
        for (int i = x_min; i <= x_max; i++) {
            if (st[i][y1] == 0) st[i][y1] = 2;
            else if (st[i][y1] == 1) st[i][y1] = 3;
            else continue;
        }
    }
    else {
        int y_min = min(y1, y2), y_max = max(y1, y2);
        for (int i = y_min; i <= y_max; i++) {
            if (st[x1][i] == 0) st[x1][i] = 1;
            else if (st[x1][i] == 2) st[x1][i] = 3;
            else continue;
        }
    }
}

void op1(int sx, int sy, char ch) {
    int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
    memset(visited, false, sizeof visited);
    queue<pii> q;
    q.push({sx, sy});
    visited[sx][sy] = true;

    while(q.size()) {
        pii p = q.front();
        q.pop();
        int x = p.x, y = p.y;

        g[x][y] = ch;
        for (int i = 0; i < 4; i++) {
            int a = x + dx[i], b = y + dy[i];
            if (a < 0 || a >= n || b < 0 || b >= m || visited[a][b]) continue;
            if (st[a][b] != 0) continue;

            q.push({a, b});
            visited[a][b] = true;        
        }
    }
}

int main() {
    cin >> m >> n >> q;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            g[i][j] = '.';
        }
    }

    while(q --) {
        int op;
        cin >> op;
        if (op == 0) {
            int x1, x2, y1, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            op0(n - 1 - y1, x1, n - 1 - y2, x2);
        }
        else {
            int x, y;
            char ch;
            cin >> x >> y >> ch;
            op1(n - 1 - y, x, ch);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (st[i][j] == 1) g[i][j] = '-';
            if (st[i][j] == 2) g[i][j] = '|';
            if (st[i][j] == 3) g[i][j] = '+';

            cout << g[i][j];
        }
        cout << endl;
    }



    return 0;
}