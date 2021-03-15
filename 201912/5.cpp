// 线段树
#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#include <queue>

using namespace std;

typedef __int128 I128;
typedef unsigned long long ULL;
const int N = 1000010, M = 33;
const ULL MOD = 2009731336725594113ull;

int n, m;
unordered_map<ULL, int> v2id;
ULL id2v[M], prod[N][M];
int g[M][M], id;
ULL U[] = {
    314882150829468584ull,
    427197303358170108ull,
    1022292690726729920ull,
    1698479428772363217ull,
    2006101093849356424ull,
};

struct Node
{
    int l, r, k;
    int s[M];
}tr[N << 2];

void init()
{
    queue<ULL> q;
    q.push(1);
    v2id[1] = ++ id;
    id2v[id] = 1;
    while (q.size())
    {
        auto t = q.front();
        q.pop();
        for (int i = 0; i < 5; i ++ )
        {
            auto r = (I128)t * U[i] % MOD;
            if (!v2id.count(r))
            {
                v2id[r] = ++ id;
                id2v[id] = r;
                q.push(r);
            }
        }
    }
    for (int i = 1; i <= id; i ++ )
        for (int j = 1; j <= id; j ++ )
            g[i][j] = v2id[(I128)id2v[i] * id2v[j] % MOD];
    for (int i = 1; i <= n; i ++ )
        for (int j = 1; j <= id; j ++ )
            prod[i][j] = (prod[i - 1][j] + id2v[j]) % MOD;
}

void pushup(int u)
{
    auto l = tr[u << 1].s, r = tr[u << 1 | 1].s;
    for (int i = 1; i <= id; i ++ )
        tr[u].s[i] = l[i] + r[i];
}

void eval(int u, int k)
{
    static int tmp[M];
    for (int i = 1; i <= id; i ++ ) tmp[i] = tr[u].s[g[i][k]];
    for (int i = 1; i <= id; i ++ ) tr[u].s[i] = tmp[i];
    if (tr[u].k) tr[u].k = g[tr[u].k][k];
    else tr[u].k = k;
}

void pushdown(int u)
{
    int k = tr[u].k;
    if (k)
    {
        eval(u << 1, k), eval(u << 1 | 1, k);
        tr[u].k = 0;
    }
}

void build(int u, int l, int r)
{
    tr[u] = {l, r};
    if (l == r)
    {
        for (int i = 1; i <= id; i ++ )
            tr[u].s[i] = prod[l][i] % 2019;
        return;
    }
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    pushup(u);
}

void update(int u, int l, int r, int k)
{
    if (tr[u].l >= l && tr[u].r <= r) eval(u, k);
    else
    {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) update(u << 1, l, r, k);
        if (r > mid) update(u << 1 | 1, l, r, k);
        pushup(u);
    }
}

int query(int u, int l, int r)
{
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].s[1];
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1, res = 0;
    if (l <= mid) res = query(u << 1, l, r);
    if (r > mid) res += query(u << 1 | 1, l, r);
    return res;
}

int main()
{
    scanf("%d%d", &n, &m);
    init();
    build(1, 1, n);

    while (m -- )
    {
        int l, r;
        scanf("%d%d", &l, &r);
        int t = query(1, l, r);
        printf("%d\n", t);
        update(1, l, r, t % 5 + 2);
    }

    return 0;
}