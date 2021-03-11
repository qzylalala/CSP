#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 10010, M = 200010, INF = 0x3f3f3f3f;

int n, m;
int h[N], e[M], w[M], ne[M], idx;
int dist[N], q[N];
bool st[N];

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

void spfa() {
    int hh = 0, tt = 1;
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    q[0] = 1;

    while (hh != tt) {
        int t = q[hh ++ ];
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
}

int main() {
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    while (m -- ) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c), add(b, a, c);
    }
    spfa();

    int res = 0;
    for (int a = 2; a <= n; a ++ ) {
        int minw = INF;
        for (int j = h[a]; ~j; j = ne[j]) {
            int b = e[j];
            if (dist[a] == dist[b] + w[j])
                minw = min(minw, w[j]);
        }
        res += minw;
    }

    printf("%d\n", res);
    return 0;
}