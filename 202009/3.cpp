#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 3010, M = N * 5;

int m, n;
int w[N], f[N];
int h[N], e[M], ne[M], idx;
int q[N], d[N];
vector<int> in[M], out[M];

int get(char* str) {
    string names[] = {
        "AND", "OR", "NOT", "XOR", "NAND", "NOR"
    };
    for (int i = 0; i < 6; i ++ )
        if (names[i] == str)
            return i;
    return -1;
}

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
    d[b] ++ ;
}

bool topsort() {
    int hh = 0, tt = -1;
    for (int i = 1; i <= m + n; i ++ )
        if (!d[i])
            q[ ++ tt] = i;
    while (hh <= tt) {
        int t = q[hh ++ ];
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if ( -- d[j] == 0)
                q[ ++ tt] = j;
        }
    }
    return tt == m + n - 1;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T -- ) {
        scanf("%d%d", &m, &n);
        memset(h, -1, sizeof h);
        idx = 0;
        memset(d, 0, sizeof d);
        char str[100];
        for (int i = 1; i <= n; i ++ ) {
            int cnt;
            scanf("%s%d", str, &cnt);
            f[m + i] = get(str);
            while (cnt -- ) {
                scanf("%s", str);
                int t = atoi(str + 1);
                if (str[0] == 'I') add(t, m + i);
                else add(m + t, m + i);
            }
        }
        int Q;
        scanf("%d", &Q);
        for (int i = 0; i < Q; i ++ ) {
            in[i].clear();
            for (int j = 0; j < m; j ++ ) {
                int x;
                scanf("%d", &x);
                in[i].push_back(x);
            }
        }
        for (int i = 0; i < Q; i ++ ) {
            out[i].clear();
            int cnt;
            scanf("%d", &cnt);
            while (cnt -- ) {
                int x;
                scanf("%d", &x);
                out[i].push_back(x);
            }
        }
        if (!topsort()) {
            puts("LOOP");
            continue;
        }

        for (int i = 0; i < Q; i ++ ) {
            for (int j = 0; j < m; j ++ ) w[j + 1] = in[i][j];
            for (int j = m + 1; j <= m + n; j ++ )
                if (f[j] == 0 || f[j] == 5) w[j] = 1;
                else w[j] = 0;
            for (int j = 0; j < m + n; j ++ ) {
                int t = q[j], v = w[t];
                for (int k = h[t]; ~k; k = ne[k]) {
                    int u = e[k];
                    if (f[u] == 0) w[u] &= v;
                    else if (f[u] == 1) w[u] |= v;
                    else if (f[u] == 2) w[u] = !v;
                    else if (f[u] == 3) w[u] ^= v;
                    else if (f[u] == 4) w[u] |= !v;
                    else w[u] &= !v;
                }
            }
            for (auto x: out[i])
                printf("%d ", w[m + x]);
            puts("");
        }
    }
    return 0;
}