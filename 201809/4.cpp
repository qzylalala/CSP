#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 310, M = N * 3;

int n;
int h[N], e[M], w[M], ne[M], idx;
int dist[N], q[N];
int b[N];
bool st[N];

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

void spfa()
{
    int hh = 0, tt = 1;
    memset(dist, -0x3f, sizeof dist);
    dist[0] = 0;
    q[0] = 0;
    while (hh != tt)
    {
        int t = q[hh ++ ];
        if (hh == N) hh = 0;
        st[t] = false;

        for (int i = h[t]; ~i; i = ne[i])
        {
            int j = e[i];
            if (dist[j] < dist[t] + w[i])
            {
                dist[j] = dist[t] + w[i];
                if (!st[j])
                {
                    q[tt ++ ] = j;
                    if (tt == N) tt = 0;
                    st[j] = true;
                }
            }
        }
    }
}

int main()
{
    cin >> n;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i ++ ) cin >> b[i];
    for (int i = 2; i < n; i ++ )
    {
        add(i - 2, i + 1, b[i] * 3);
        add(i + 1, i - 2, -(b[i] * 3 + 2));
    }
    add(0, 2, b[1] * 2), add(2, 0, -(b[1] * 2 + 1));
    add(n - 2, n, b[n] * 2), add(n, n - 2, -(b[n] * 2 + 1));
    for (int i = 1; i <= n; i ++ ) add(i - 1, i, 1);
    spfa();

    for (int i = 1; i <= n; i ++ )
        cout << dist[i] - dist[i - 1] << ' ';
    return 0;
}