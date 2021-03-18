// 网络流
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 20010, M = (10000 * 3 + 100000) * 2 + 10, INF = 1e9;

int n, m, S, T;
int h[N], e[M], ne[M], idx;
LL f[M];
int q[N], d[N], cur[N];

void add(int a, int b, int c)
{
    e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
    e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx ++ ;
}

bool bfs()
{
    int hh = 0, tt = 0;
    memset(d, -1, sizeof d);
    q[0] = S, d[S] = 0, cur[S] = h[S];
    while (hh <= tt)
    {
        int t = q[hh ++ ];
        for (int i = h[t]; ~i; i = ne[i])
        {
            int ver = e[i];
            if (d[ver] == -1 && f[i])
            {
                d[ver] = d[t] + 1;
                cur[ver] = h[ver];
                if (ver == T) return true;
                q[ ++ tt] = ver;
            }
        }
    }
    return false;
}

LL find(int u, LL limit)
{
    if (u == T) return limit;
    LL flow = 0;
    for (int i = cur[u]; ~i && flow < limit; i = ne[i])
    {
        cur[u] = i;
        int ver = e[i];
        if (d[ver] == d[u] + 1 && f[i])
        {
            LL t = find(ver, min(f[i], limit - flow));
            if (!t) d[ver] = -1;
            f[i] -= t, f[i ^ 1] += t, flow += t;
        }
    }
    return flow;
}

LL dinic()
{
    LL r = 0, flow;
    while (bfs()) while (flow = find(S, 1e18)) r += flow;
    return r;
}

int calc_f(int x, int a, int b, int c)
{
    return a * x * x + b * x + c;
}

int calc(int x1, int x2, int a, int b, int c)
{
    int x[5] = {x1, x2};
    if (a)
    {
        x[2] = -b / (a * 2);
        x[3] = x[2] - 1, x[4] = x[2] + 1;
    }
    int res = -INF;
    for (auto v: x)
        if (v >= x1 && v <= x2)
            res = max(res, calc_f(v, a, b, c));
    return res;
}

int main()
{
    scanf("%d%d", &n, &m);
    S = 0, T = n * 2 + 1;
    memset(h, -1, sizeof h);

    LL tot = 0;
    for (int i = 1; i <= n; i ++ )
    {
        int l, r, a, b, c;
        scanf("%d%d%d%d%d", &l, &r, &a, &b, &c);
        int w1 = calc(l + 1, r - 1, a, b, c);
        int w2 = calc(l, r, a, b, c) - w1;
        if (w1 > 0) add(S, i, w1), tot += w1;
        else add(i, T, -w1);
        if (w2 > 0) add(S, n + i, w2), tot += w2;
        else add(n + i, T, -w2);
        add(n + i, i, INF);
    }
    while (m -- )
    {
        int c, a, b;
        scanf("%d%d%d", &c, &a, &b);
        if (c == 1) add(b, a, INF);
        else add(n + b, a, INF);
    }
    printf("%lld\n", tot - dinic());
    return 0;
}