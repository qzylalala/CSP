#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 50010, M = 100010;

int n, m;       // n是点数，m是边数
int p[N];       // 并查集的父节点数组

struct Edge     // 存储边
{
    int a, b, w;

    bool operator< (const Edge &W)const
    {
        return w < W.w;
    }
}edges[M];

int find(int x)     // 并查集核心操作
{
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int kruskal() {
    sort(edges, edges + m);

    for (int i = 1; i <= n; i ++ ) p[i] = i;    // 初始化并查集

    int res = 0, cnt = 0;
    for (int i = 0; i < m; i ++ ) {
        int a = edges[i].a, b = edges[i].b, w = edges[i].w;

        a = find(a), b = find(b);
        if (a != b)     // 如果两个连通块不连通，则将这两个连通块合并
        {
            p[a] = b;
            res = max(res, w);
            cnt ++ ;
        }
    }

    return res;
}

int main() {
    int root;
    cin >> n >> m >> root;

    int cnt = 0;
    for (int i = 1; i <= m; i++) {
        int u, v, t;
        cin >> u >> v >> t;
        edges[cnt ++] = {u, v, t};
    }

    sort(edges, edges + cnt);

    cout << kruskal() << endl;

    return 0;
}