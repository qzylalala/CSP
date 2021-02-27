#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

#define x first
#define y second

using namespace std;

typedef pair<int, int> pii;

const int N = 1010;
int n, m, k, d;
int g[N][N];
int dist[N][N];
queue<pii> q;

int kx[N * N], ky[N * N], kc[N * N];
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

void bfs() {
    while(q.size()) {
        pii p = q.front();
        q.pop();

        int x = p.x, y = p.y;
        for (int i = 0; i < 4; i++) {
            int a = x + dx[i], b = y + dy[i];

            if (a < 1 || a > n || b < 1 || b > n || g[a][b] == -2 || g[a][b] == -1) continue;
            if (!dist[a][b]) {
                dist[a][b] = dist[x][y] + 1;
                q.push({a, b});
            }
        }
    }
}


// g[i][j] 
// 0 : 正常   -1 : 分店   num : 客户   -2 : 不能经过
int main() {
    scanf("%d%d%d%d", &n, &m, &k, &d);
    for (int i = 1; i <= m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        g[x][y] = -1;
        q.push({x, y});
        dist[x][y] = 0;
    }

    for (int i = 1; i <= k; i++) {
        int x, y, c;
        scanf("%d%d%d", &x, &y, &c);
        g[x][y] = c;
        kx[i] = x, ky[i] = y, kc[i] = c;
    }

    for (int i = 1; i <= d; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        g[x][y] = -2;
    }

    bfs();

    long long ans = 0;
    for (int i = 1; i <= k; i++) {
        int x = kx[i], y = ky[i], c = kc[i];
        ans += dist[x][y] * c;
    }

    cout << ans << endl;

    return 0;
}