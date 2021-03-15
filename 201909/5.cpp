// 树型DP 分组背包
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 50010, M = N * 2;

int n, m, K;
int h[N], e[M], w[M], ne[M], idx;
LL f[N][110];
bool st[N];
int sz[N];
LL ans = 1e18;

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

void dfs(int u, int fa)
{
    f[u][0] = 0;
    if (st[u]) f[u][1] = 0;
    sz[u] = 1;
    for (int i = h[u]; ~i; i = ne[i])  // 枚举物品组
    {
        int ver = e[i];
        if (ver == fa) continue;
        dfs(ver, u);
        sz[u] += sz[ver];
        for (int j = min(sz[u], K); j >= 0; j -- )  // 枚举体积
            for (int k = 0; k <= min(j, sz[ver]); k ++ )  // 枚举决策
                f[u][j] = min(f[u][j], f[u][j - k] + f[ver][k] + (LL)w[i] * k * (K - k));
    }

    ans = min(ans, f[u][K]);
}

int main()
{
    scanf("%d%d%d", &n, &m, &K);
    memset(h, -1, sizeof h);
    while (m -- )
    {
        int x;
        scanf("%d", &x);
        st[x] = true;
    }
    for (int i = 0; i < n - 1; i ++ )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c), add(b, a, c);
    }

    memset(f, 0x3f, sizeof f);
    dfs(1, -1);
    printf("%lld\n", ans);
    return 0;
}