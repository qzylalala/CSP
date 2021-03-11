#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int N = 510, M = 200010, INF = 1e6;

int n, m;
int h[N], e[M], f[M], w[M], ne[M], idx;
int dist[N][1010];
bool st[N][1010];
struct Node
{
    int x, y, v;
    bool operator< (const Node& t) const
    {
        return v > t.v;
    }
};

void add(int t, int a, int b, int c)
{
    e[idx] = b, f[idx] = t, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

void dijkstra()
{
    priority_queue<Node> heap;
    heap.push({1, 0, 0});
    memset(dist, 0x3f, sizeof dist);
    dist[1][0] = 0;
    while (heap.size())
    {
        auto t = heap.top();
        heap.pop();

        if (st[t.x][t.y]) continue;
        st[t.x][t.y] = true;
        for (int i = h[t.x]; ~i; i = ne[i])
        {
            int x = e[i], y = t.y;
            if (f[i])
            {
                y += w[i];
                if (y <= 1000)
                {
                    if (dist[x][y] > t.v - t.y * t.y + y * y)
                    {
                        dist[x][y] = t.v - t.y * t.y + y * y;
                        if (dist[x][y] <= INF)
                            heap.push({x, y, dist[x][y]});
                    }
                }
            }
            else
            {
                if (dist[x][0] > t.v + w[i])
                {
                    dist[x][0] = t.v + w[i];
                    if (dist[x][0] <= INF)
                        heap.push({x, 0, dist[x][0]});
                }
            }
        }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    while (m -- )
    {
        int t, a, b, c;
        scanf("%d%d%d%d", &t, &a, &b, &c);
        add(t, a, b, c), add(t, b, a, c);
    }

    dijkstra();
    int res = INF;
    for (int i = 0; i <= 1000; i ++ ) res = min(res, dist[n][i]);
    printf("%d\n", res);

    return 0;
}