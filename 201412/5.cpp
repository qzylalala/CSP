// 网络流  暂时是CV的, 复习之后重做
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 710, M = (N * 3 + 500 * 7 * 2) * 2 + 10, INF = 0x3f3f3f3f;

int n, m, S, T;
int h[N], e[M], f[M], w[M], ne[M], idx;
int q[N], d[N], pre[N], incf[N];
bool st[N];

int get(int a, int b)
{
    if (b == 8) b = 1;
    return (a - 1) * 7 + b;
}

void add(int a, int b, int c, int d)
{
    e[idx] = b, f[idx] = c, w[idx] = d, ne[idx] = h[a], h[a] = idx ++ ;
    e[idx] = a, f[idx] = 0, w[idx] = -d, ne[idx] = h[b], h[b] = idx ++ ;
}

bool spfa()
{
    int hh = 0, tt = 1;
    memset(d, 0x3f, sizeof d);
    memset(incf, 0, sizeof incf);
    q[0] = S, d[S] = 0, incf[S] = INF;
    while (hh != tt)
    {
        int t = q[hh ++ ];
        if (hh == N) hh = 0;
        st[t] = false;

        for (int i = h[t]; ~i; i = ne[i])
        {
            int ver = e[i];
            if (f[i] && d[ver] > d[t] + w[i])
            {
                d[ver] = d[t] + w[i];
                pre[ver] = i;
                incf[ver] = min(incf[t], f[i]);
                if (!st[ver])
                {
                    q[tt ++ ] = ver;
                    if (tt == N) tt = 0;
                    st[ver] = true;
                }
            }
        }
    }
    return incf[T] > 0;
}

void EK(int& flow, int& cost)
{
    flow = cost = 0;
    while (spfa())
    {
        int t = incf[T];
        flow += t, cost += t * d[T];
        for (int i = T; i != S; i = e[pre[i] ^ 1])
        {
            f[pre[i]] -= t;
            f[pre[i] ^ 1] += t;
        }
    }
}

int main()
{
    cin >> n >> m;
    S = 0, T = n * 7 + 1;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i ++ )
    {
        int c, d;
        for (int j = 1; j <= 7; j ++ )
        {
            cin >> c;
            add(S, get(i, j), c, 0);
        }
        for (int j = 1; j <= 7; j ++ )
        {
            cin >> c;
            add(get(i, j), T, c, 0);
        }
        cin >> c >> d;
        for (int j = 1; j <= 7; j ++ )
            add(get(i, j), get(i, j + 1), c, d);
    }
    while (m -- )
    {
        int a, b, c;
        cin >> a >> b >> c;
        for (int i = 1; i <= 7; i ++ )
        {
            add(get(a, i), get(b, i), INF, c);
            add(get(b, i), get(a, i), INF, c);
        }
    }
    int flow, cost;
    EK(flow, cost);
    cout << cost << endl;
    return 0;
}