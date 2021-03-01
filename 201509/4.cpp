// tarjan 算法
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 10010, M = 100010;

int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N];
int stk[N], top, ts;
bool in_stk[N];
int ans;

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++ ts;
    stk[ ++ top] = u, in_stk[u] = true;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        }
        else if (in_stk[j]) low[u] = min(low[u], dfn[j]);
    }

    if (dfn[u] == low[u]) {
        int y, cnt = 0;
        do {
            y = stk[top -- ];
            in_stk[y] = false;
            cnt ++ ;
        } while (y != u);
        ans += cnt * (cnt - 1) / 2;
    }
}

int main() {
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    while (m -- ) {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b);
    }

    for (int i = 1; i <= n; i ++ )
        if (!dfn[i])
            tarjan(i);
    printf("%d\n", ans);

    return 0;
}