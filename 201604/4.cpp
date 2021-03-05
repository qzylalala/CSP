#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

#define x first
#define y second

using namespace std;

typedef pair<int, int> pii;

const int N = 110;
bool st[N][N];
int danger[N][N][2];
int n, m, t, ans;

void bfs(int sx, int sy) {
    int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
    queue<pii> q;
    q.push({sx, sy});
    st[sx][sy] = true;

    while(q.size()) {
        int size = q.size();
        ans ++;
        for (int i = 0; i < size; i++) {
            pii p = q.front();
            q.pop();

            int x = p.x, y = p.y;

            for (int j = 0; j < 4; j++) {
                int a = x + dx[j],  b = y + dy[j];

                if (a < 1 || a > n || b < 1 || b > m) continue;
                int mi = danger[a][b][0], ma = danger[a][b][1];
                if (ans >= mi && ans <= ma) continue;
                if (st[a][b]) continue;

                if (a == n && b == m) return ;
                else {
                    q.push({a, b});
                    st[a][b] = true;
                }
            }
            st[x][y] = false;
        }
    }
}

int main() {
    cin >> n >> m >> t;
    while(t --) {
        int r, c, a, b;
        cin >> r >> c >> a >> b;
        danger[r][c][0] = a, danger[r][c][1] = b;
    }

    bfs(1, 1);

    cout << ans << endl;

    return 0;
}