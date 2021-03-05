// cv 连通性DP
#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>

using namespace std;

const int N = 510, M = 1 << 6, H = 1e6, INF = 0x3f3f3f3f;

int n, m, p;
int w[N][6], es[N], ec[N][M];
int f[2][H], fs[2][H], ft[2];
char g[N];
int fa[7];
int fstate[224695][M];

int get(int state, int k)
{
    return state >> k * 3 & 7;
}

void update(int i, int state, int cost)
{
    if (state == -1) return;
    if (f[i][state] != -1) f[i][state] = min(f[i][state], cost);
    else
    {
        f[i][state] = cost;
        fs[i][ft[i] ++ ] = state;
    }
}

void clear(int k)
{
    for (int i = 0; i < ft[k]; i ++ )
        f[k][fs[k][i]] = -1;
    ft[k] = 0;
}

int find(int x)
{
    if (fa[x] != x) fa[x] = find(fa[x]);
    return fa[x];
}

int get_state(int state, int k)  // 给最小表示法state增加边集k
{
    if (k == 1) k = 0;
    if (fstate[state][k / 2] >= -1) return fstate[state][k / 2];
    for (int i = 0; i <= p; i ++ )
        if (get(state, i) || (k >> i & 1))
            fa[i] = i;
        else fa[i] = -1;
    for (int i = 0; i <= p; i ++ )
        if (get(state, i))
            for (int j = i + 1; j <= p; j ++ )
                if (get(state, j) == get(state, i))
                    fa[find(j)] = find(i);

    for (int i = 0; i <= p; i ++ )
        if (k >> i & 1)
        {
            for (int j = i + 1; j <= p; j ++ )
                if (k >> j & 1)
                    fa[find(j)] = find(i);
            break;
        }

    if (fa[0] != -1)  // 第一个点要么没被选，要么所在集合大小至少为2
    {
        bool flag = false;
        for (int i = 1; i <= p; i ++ )
            if (fa[i] != -1 && find(i) == find(0))
            {
                flag = true;
                break;
            }
        if (!flag) return fstate[state][k / 2] = -1;
    }

    int res = 0;
    for (int i = 1, cnt = 1; i <= p; i ++ )
        if (!get(res, i - 1) && fa[i] != -1)
        {
            res += cnt << (i - 1) * 3;
            for (int j = i + 1; j <= p; j ++ )
                if (!get(res, j - 1) && fa[j] != -1 && find(j) == find(i))
                    res += cnt << (j - 1) * 3;
            cnt ++ ;
        }
    return fstate[state][k / 2] = res;
}

int main()
{
    memset(fstate, -0x3f, sizeof fstate);
    int T;
    scanf("%d", &T);
    while (T -- )
    {
        scanf("%d%d%d", &n, &m, &p);
        memset(w, -1, sizeof w);
        scanf("%s", g + 1);
        while (m -- )
        {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            w[a][b - a - 1] = c;
        }
        memset(es, 0, sizeof es);
        memset(ec, 0, sizeof ec);
        for (int i = 1; i <= n; i ++ )
        {
            for (int j = 0; j < p; j ++ )
                if (w[i][j] != -1)
                {
                    es[i] += 1 << j;
                }
            for (int j = 0; j < 1 << p; j ++ )
                if ((j & es[i]) == j)
                    for (int k = 0; k < p; k ++ )
                        if (j >> k & 1)
                            ec[i][j] += w[i][k];
        }
        memset(f, -1, sizeof f);
        update(1, 0, 0);
        int res = INF, maxp;
        for (int i = 1; i <= n; i ++ )
            if (g[i] == '1')
                maxp = i;
        for (int i = 1; i <= n; i ++ )
        {
            clear(i + 1 & 1);
            for (int j = 0; j < ft[i & 1]; j ++ )
            {
                int state = fs[i & 1][j], cost = f[i & 1][state];
                for (int k = 0; k < 1 << p; k ++ )
                {
                    if ((k & es[i]) != k) continue;
                    if (g[i] == '1' && !get(state, 0) && !k) continue;
                    update(i + 1 & 1, get_state(state, k * 2 + 1), cost + ec[i][k]);
                }
                if (i >= maxp && state == 1) res = min(res, cost);
            }
        }
        printf("%d\n", res);
    }

    return 0;
}