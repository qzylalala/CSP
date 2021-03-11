// 树状数组  线段树
#include <iostream>
#include <cstring>
#include <algorithm>
#include <set>

using namespace std;

typedef long long LL;
const int N = 100010, M = 1000010;

int n, m;
set<int> pos[M];
LL tr[N];
set<int> vs;
struct Query
{
    int t, l, r, v;
}q[N];
int w[N];

int lowbit(int x)
{
    return x & -x;
}

void add(int x, int v)
{
    for (int i = x; i <= n; i += lowbit(i)) tr[i] += v;
}

LL query(int x)
{
    LL res = 0;
    for (int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++ )
    {
        scanf("%d", &w[i]);
        add(i, w[i]);
    }
    for (int i = 0; i < m; i ++ )
    {
        int t, l, r, v;
        scanf("%d%d%d", &t, &l, &r);
        if (t == 1)
        {
            scanf("%d", &v);
            q[i] = {t, l, r, v};
            if (v != 1) vs.insert(v);
        }
        else q[i] = {t, l, r};
    }
    for (int i = 1; i <= n; i ++ )
        for (int j = 1; j * j <= w[i]; j ++ )
            if (w[i] % j == 0)
            {
                if (vs.count(j)) pos[j].insert(i);
                if (w[i] / j != j && vs.count(w[i] / j))
                    pos[w[i] / j].insert(i);
            }

    for (int i = 0; i < m; i ++ )
        if (q[i].t == 1)
        {
            int v = q[i].v;
            auto it = pos[v].lower_bound(q[i].l);
            while (it != pos[v].end() && *it <= q[i].r)
            {
                int k = *it;
                it ++ ;
                add(k, -w[k] + w[k] / v);

                for (int j = 1; j * j <= w[k]; j ++ )
                    if (w[k] % j == 0)
                    {
                        pos[j].erase(k);
                        if (w[k] / j != j) pos[w[k] / j].erase(k);
                    }
                w[k] /= v;
                for (int j = 1; j * j <= w[k]; j ++ )
                    if (w[k] % j == 0)
                    {
                        if (vs.count(j)) pos[j].insert(k);
                        if (w[k] / j != j && vs.count(w[k] / j))
                            pos[w[k] / j].insert(k);
                    }
            }
        }
        else printf("%lld\n", query(q[i].r) - query(q[i].l - 1));
    return 0;
}