#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;
const int N = 10010, M = 20010, INF = 0x3f3f3f3f;

int n, m, k;
int type[N];
int h[N], e[M], w[M], ne[M], idx;
int dist[N];
bool st[N];
int q[N];
int ds[N][1010];
int cnt;

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

void spfa(int start) {
    memset(dist, 0x3f, sizeof dist);
    dist[start] = 0;
    int hh = 0, tt = 1;
    q[0] = start;

    while (hh != tt) {
        auto t = q[hh ++ ];
        if (hh == N) hh = 0;
        st[t] = false;

        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                if (!st[j]) {
                    q[tt ++ ] = j;
                    if (tt == N) tt = 0;
                    st[j] = true;
                }
            }
        }
    }

    for (int i = 1; i <= n; i ++ ) ds[i][cnt] = dist[i];
}

int main() {
    cin >> n >> m >> k;

    for (int i = 1; i <= n; i ++ ) scanf("%d", &type[i]);
    memset(h, -1, sizeof h);
    while (m -- ) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c), add(b, a, c);
    }

    for (int i = 1; i <= n; i ++ ) {
        if (type[i]) {
            spfa(i);
            cnt ++ ;
        }
    }

    for (int i = 1; i <= n; i ++ ) {
        sort(ds[i], ds[i] + cnt);
        int res = 0;
        for (int j = 0; j < k && j < cnt; j ++ )
            if (ds[i][j] != INF)
                res += ds[i][j];

        printf("%d\n", res);
    }

    return 0;
}