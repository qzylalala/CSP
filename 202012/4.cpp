#include <iostream>
#include <cstring>
#include <algorithm>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;
const int N = 110, M = 10, S = 1 << M;

int n, m, k;
int need[N][M];
int h[N], e[N * 2], w[N * 2], ne[N * 2], idx;
int d[N][M];
int f[S], state[N];

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

PII dfs(int u, int fa, int v) {
    PII res(0, -1);
    if (need[u][v]) res.y = 0;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (j == fa) continue;
        auto t = dfs(j, u, v);
        if (t.y != -1) {
            res.x += t.x + w[i] * 2;
            res.y = max(res.y, t.y + w[i]);
        }
    }
    return res;
}

bool check(int mid) {
    memset(state, 0, sizeof state);
    for (int i = 1; i <= n; i ++ )
        for (int j = 0; j < k; j ++ )
            if (d[i][j] <= mid)
                state[i] |= 1 << j;
    memset(f, 0x3f, sizeof f);
    f[0] = 0;
    for (int i = 0; i < 1 << k; i ++ )
        for (int j = 1; j <= n; j ++ )
            f[i | state[j]] = min(f[i | state[j]], f[i] + 1);
    return f[(1 << k) - 1] <= m;
}

int main() {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i ++ )
        for (int j = 0; j < k; j ++ )
            cin >> need[i][j];
    memset(h, -1, sizeof h);
    for (int i = 0; i < n - 1; i ++ ) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c), add(b, a, c);
    }

    for (int i = 1; i <= n; i ++ )
        for (int j = 0; j < k; j ++ ) {
            auto t = dfs(i, -1, j);
            if (t.y != -1) d[i][j] = t.x - t.y;
        }

    int l = 0, r = 2e8;
    while (l < r) {
        int mid = l + r >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }

    printf("%d\n", r);
    return 0;
}