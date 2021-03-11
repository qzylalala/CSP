// cv 点分治
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 100010, M = N * 2, MOD = 1e9 + 7;

int n, m, L, R;
int w[N];
int h[N], father[N], e[M], ne[M], idx;
int depth[N], fa[N][17];
int path[N], d[N], que[N];
int pos[N], root[N];
bool st[N];
int tr[N];
struct Node
{
    int d, w, id;
    bool operator< (const Node& t) const
    {
        return d < t.d;
    }
}q[N], p[N];

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

inline int lowbit(int x)
{
    return x & -x;
}

inline void update(int x, int v, int k)
{
    for (int i = x; i <= k; i += lowbit(i)) tr[i] = (tr[i] + v) % MOD;
}

inline int query(int x, int k)
{
    x = min(x, k);
    int res = 0;
    for (int i = x; i > 0; i -= lowbit(i)) res = (res + tr[i]) % MOD;
    return res;
}

void bfs()
{
    memset(depth, 0x3f, sizeof depth);
    depth[0] = 0, depth[1] = 1;
    int hh = 0, tt = 0;
    que[0] = 1;
    while (hh <= tt)
    {
        int t = que[hh ++ ];
        for (int i = h[t]; ~i; i = ne[i])
        {
            int j = e[i];
            if (depth[j] > depth[t] + 1)
            {
                depth[j] = depth[t] + 1;
                que[ ++ tt] = j;
                fa[j][0] = t;
                for (int k = 1; k <= 16; k ++ )
                    fa[j][k] = fa[fa[j][k - 1]][k - 1];
            }
        }
    }
}

inline int lca(int a, int b)
{
    if (depth[a] < depth[b]) swap(a, b);
    for (int k = 16; k >= 0; k -- )
        if (depth[fa[a][k]] >= depth[b])
            a = fa[a][k];
    if (a == b) return a;
    for (int k = 16; k >= 0; k -- )
        if (fa[a][k] != fa[b][k])
        {
            a = fa[a][k];
            b = fa[b][k];
        }
    return fa[a][0];
}

void dfs(int u, int fa)
{
    d[u] = (d[fa] + path[u]) % MOD;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (j == fa) continue;
        dfs(j, u);
    }
}

int get_size(int u, int fa)
{
    if (st[u]) return 0;
    int res = 1;
    for (int i = h[u]; ~i; i = ne[i])
        if (e[i] != fa)
            res += get_size(e[i], u);
    return res;
}

int get_wc(int u, int fa, int tot, int& wc)
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

void get_dist(int u, int fa, int dist, int sum, int& qt)
{
    if (st[u]) return;
    q[ ++ qt] = {dist, sum, u};
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (j != fa)
            get_dist(j, u, dist + 1, (sum + w[j]) % MOD, qt);
    }
}

inline int get(Node a[], int k, int limit, int wu, int& pu)
{
    sort(a + 1, a + k + 1);
    static int sum[N];
    int res = 0;
    for (int i = 1; i <= k; i ++ ) sum[i] = (sum[i - 1] + a[i].w) % MOD;
    for (int i = 1, j = k; i < j; i ++ )
    {
        while (j > i && a[j].d + a[i].d - 1 > limit) j -- ;
        if (j > i && a[j].d + a[i].d - 1 <= limit)
        {
            res = (res + (LL)sum[j] - sum[i] + (LL)(j - i) * a[i].w - (LL)wu * (j - i)) % MOD;
            pu = (pu + j - i) % MOD;
        }
    }
    return res;
}

int dfs_path(int u, int fa, int dist, int maxd)
{
    if (st[u]) return 0;
    int res = (query(R + 1 - dist, maxd) - query(L - dist, maxd)) % MOD;
    if (dist >= L && dist <= R) res = (res + 1) % MOD;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (j != fa)
            res = (res + dfs_path(j, u, dist + 1, maxd)) % MOD;
    }
    path[u] = (path[u] + res) % MOD;
    return res;
}

int calc(int u)
{
    if (st[u]) return 0;
    get_wc(u, -1, get_size(u, -1), u);
    st[u] = true;

    int res = 0, pt = 0;
    if (L <= 1 && R >= 1) res = w[u], path[u] = (path[u] + 1) % MOD;
    int cnt = 0, maxd = 0;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i], qt = 0;
        if (st[j]) continue;
        get_dist(j, -1, 2, (w[u] + w[j]) % MOD, qt);
        int pR = 0, pL = 0;
        res = (res - (LL)(get(q, qt, R, w[u], pR) - get(q, qt, L - 1, w[u], pL))) % MOD;
        path[u] = (path[u] - (LL)(pR - pL)) % MOD;
        pos[ ++ cnt] = pt + 1;  // 每一段开头
        root[cnt] = j;  // 每一段的根节点
        for (int k = 1; k <= qt; k ++ )
        {
            if (q[k].d >= L && q[k].d <= R)
            {
                res = (res + q[k].w) % MOD;
                path[u] = (path[u] + 1) % MOD;  // 只计算从u到当前点的
            }
            p[ ++ pt] = q[k];
            maxd = max(maxd, q[k].d);
        }
    }

    pos[cnt + 1] = pt + 1;  // 哨兵

    for (int i = 1; i <= maxd; i ++ ) tr[i] = 0;
    for (int i = 1; i <= pt; i ++ ) update(p[i].d, 1, maxd);  // 插入树状数组中
    for (int i = 1; i <= cnt; i ++ )
    {
        int l = pos[i], r = pos[i + 1] - 1;
        for (int j = l; j <= r; j ++ ) update(p[j].d, -1, maxd);  // 将当前子树中的节点删掉
        dfs_path(root[i], u, 2, maxd);
        for (int j = l; j <= r; j ++ ) update(p[j].d, 1, maxd);  // 将当前子树中的节点添加回来
    }

    int pR = 0, pL = 0;
    res = (res + (LL)get(p, pt, R, w[u], pR) - get(p, pt, L - 1, w[u], pL)) % MOD;
    path[u] = (path[u] + (LL)pR - pL) % MOD;

    for (int i = h[u]; ~i; i = ne[i]) res = (res + calc(e[i])) % MOD;
    return res;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T -- )
    {
        scanf("%d%d%d%d", &n, &m, &L, &R);
        memset(h, -1, sizeof h), idx = 0;
        memset(path, 0, sizeof path);
        for (int i = 1; i <= n; i ++ ) scanf("%d", &w[i]);
        for (int i = 2; i <= n; i ++ )
        {
            int p;
            scanf("%d", &p);
            add(i, p), add(p, i);
            father[i] = p;
        }
        memset(st, 0, sizeof st);
        int res = calc(1);

        dfs(1, 0);
        bfs();
        while (m -- )
        {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            int p = lca(a, b);
            int sum = (d[a] + (LL)d[b] - d[p] * 2 + path[p]) * c % MOD;
            res = ((res + sum) % MOD + MOD) % MOD;
            printf("%d\n", res);
        }
    }

    return 0;
}