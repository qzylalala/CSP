// 费用流
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 210, M = (500 + N) * 2 + 10, INF = 1e6;

int n, m, S, T;
int h[N], e[M], f[M], w[M], ne[M], idx;
int q[N], dist[N], pre[N], incf[N];
bool st[N];
int din[N], dout[N];

void add(int a, int b, int c, int d)
{
    e[idx] = b, f[idx] = c, w[idx] = d, ne[idx] = h[a], h[a] = idx ++ ;
    e[idx] = a, f[idx] = 0, w[idx] = -d, ne[idx] = h[b], h[b] = idx ++ ;
}

bool spfa()
{
    int hh = 0, tt = 1;
    memset(dist, 0x3f, sizeof dist);
    memset(incf, 0, sizeof incf);
    q[0] = S, dist[S] = 0, incf[S] = INF;
    while (hh != tt)
    {
        int t = q[hh ++ ];
        if (hh == N) hh = 0;
        st[t] = false;

        for (int i = h[t]; ~i; i = ne[i])
        {
            int j = e[i];
            if (f[i] && dist[j] > dist[t] + w[i])
            {
                dist[j] = dist[t] + w[i];
                pre[j] = i;
                incf[j] = min(f[i], incf[t]);
                if (!st[j])
                {
                    q[tt ++ ] = j;
                    if (tt == N) tt = 0;
                    st[j] = true;
                }
            }
        }
    }
    return incf[T] > 0;
}

int EK(int tot)
{
    int flow = 0, cost = 0;
    while (spfa())
    {
        int t = incf[T];
        flow += t, cost += t * dist[T];
        for (int i = T; i != S; i = e[pre[i] ^ 1])
        {
            f[pre[i]] -= t;
            f[pre[i] ^ 1] += t;
        }
    }
    if (flow != tot) return -1;
    return cost;
}

int main()
{
    int C, E;
    scanf("%d%*d%d", &C, &E);
    while (C -- )
    {
        memset(h, -1, sizeof h);
        idx = 0;
        memset(din, 0, sizeof din);
        memset(dout, 0, sizeof dout);
        scanf("%d%d", &n, &m);
        S = 0, T = n + 1;
        int down_cost = 0;
        while (m -- )
        {
            int a, b;
            char c;
            scanf("%d %d %c", &a, &b, &c);
            int down, up;
            if (c == 'A') down = 1, up = INF, down_cost += E;
            else if (c == 'B') down = up = 1, down_cost += E;
            else if (c == 'C') down = 0, up = INF;
            else down = 0, up = 1;
            add(a, b, up - down, E);
            din[b] += down, dout[a] += down;
        }
        int tot = 0;
        for (int i = 1; i <= n; i ++ )
            if (din[i] > dout[i])
            {
                add(S, i, din[i] - dout[i], 0);
                tot += din[i] - dout[i];
            }
            else add(i, T, dout[i] - din[i], 0);

        int c = EK(tot);
        if (c != -1) c += down_cost;
        printf("%d\n", c);
    }
    return 0;
}