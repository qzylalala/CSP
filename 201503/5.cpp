// cv 点分治不会
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

#define x first
#define y second

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;
const int N = 100010, M = N * 2, INF = 0x3f3f3f3f;

int n, m;
int pr[N];
int h[N], e[M], w[M], ne[M], idx;
bool st[N];
struct Query
{
    int a, b;
    LL c;
}query[N];
vector<int> Q[N];
int bel[N];
int fp[N][17], fu[N][17], dist[N], cm[N];
LL cs[N];
vector<PII> qt[N];
LL cs2[N];
int minp[N], minu[N], top;

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

int get_size(int u, int fa)  // 求子树大小
{
    if (st[u]) return 0;
    int res = 1;
    for (int i = h[u]; ~i; i = ne[i])
        if (e[i] != fa)
            res += get_size(e[i], u);
    return res;
}

int get_wc(int u, int fa, int tot, int& wc)  // 求重心
{
    if (st[u]) return 0;
    int sum = 1, ms = 0;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (j == fa) continue;
        int t = get_wc(j, u, tot, wc);
        ms = max(ms, t);
        sum += t;
    }
    ms = max(ms, tot - sum);
    if (ms <= tot / 2) wc = u;
    return sum;
}

void dfs1(int u, int fa, int id)
{
    if (st[u]) return;
    bel[u] = id, qt[u].clear();
    fp[u][0] = fa, fu[u][0] = u;
    for (int i = 1; i < 17; i ++ )
    {
        int p = fp[u][i - 1];
        fp[u][i] = fp[p][i - 1];
        if (pr[fu[u][i - 1]] <= pr[fu[p][i - 1]]) fu[u][i] = fu[u][i - 1];
        else fu[u][i] = fu[p][i - 1];
    }
    if (pr[fu[u][16]] == pr[u])  // 最小的是自己
    {
        cs[u] = (LL)dist[u] * pr[u];
        cm[u] = pr[u];
    }
    else
    {
        int x = u;
        for (int i = 16; i; i -- )
            if (pr[fu[x][i - 1]] >= pr[u])
                x = fp[x][i - 1];

        cs[u] = (LL)(dist[u] - dist[x]) * pr[u] + cs[x];
        cm[u] = cm[x];
    }

    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (j != fa && !st[j])
        {
            dist[j] = dist[u] + w[i];
            dfs1(j, u, id);
        }
    }
}

void dfs2(int u, int fa)
{
    if (st[u]) return;
    if (minp[top - 1] < pr[u]) minp[top] = minp[top - 1], minu[top] = minu[top - 1];
    else minp[top] = pr[u], minu[top] = u;
    top ++ ;

    for (int i = 0; i < qt[u].size(); i ++ )
    {
        int a = qt[u][i].x, k = qt[u][i].y;
        if (cm[a] <= minp[top - 1]) query[k].c = cs[a] + (LL)dist[u] * cm[a];
        else
        {
            int l = 0, r = top - 1;
            while (l < r)
            {
                int mid = l + r >> 1;
                if (minp[mid] < cm[a]) r = mid;
                else l = mid + 1;
            }
            int ver = minu[r];
            query[k].c = cs[a] + cs2[u] - cs2[ver] + (LL)dist[ver] * cm[a];
        }
    }

    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (j != fa && !st[j])
        {
            cs2[j] = cs2[u] + (LL)minp[top - 1] * w[i];
            dfs2(j, u);
        }
    }
    top -- ;
}

void calc(int u)
{
    if (st[u]) return;
    vector<int> q;
    q.swap(Q[u]);
    get_wc(u, -1, get_size(u, -1), u);
    st[u] = true;  // 删除重心

    for (int i = 0; i < 17; i ++ ) fp[u][i] = 0, fu[u][i] = u;
    dist[u] = cs[u] = 0, cm[u] = pr[u], bel[u] = 0, qt[u].clear();
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        dist[j] = dist[u] + w[i];
        dfs1(j, u, j);
    }

    for (int i = 0; i < q.size(); i ++ )
    {
        int k = q[i];
        int a = query[k].a, b = query[k].b;
        if (b == u) query[k].c = cs[a];
        else if (bel[a] == bel[b]) Q[bel[a]].push_back(k);
        else qt[b].push_back({a, k});
    }

    cs2[u] = 0, minp[0] = pr[u], minu[0] = u, top = 1;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        cs2[j] = cs2[u] + (LL)minp[top - 1] * w[i];
        dfs2(j, u);
    }

    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (Q[j].size()) calc(j);
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    pr[0] = INF;
    for (int i = 1; i <= n; i ++ ) scanf("%d", &pr[i]);
    memset(h, -1, sizeof h);
    for (int i = 0; i < n - 1; i ++ )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c), add(b, a, c);
    }

    for (int i = 0; i < m; i ++ )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        query[i] = {a, b};
        if (a != b) Q[1].push_back(i);
    }

    calc(1);

    for (int i = 0; i < m; i ++ )
        printf("%lld\n", query[i].c);

    return 0;
}