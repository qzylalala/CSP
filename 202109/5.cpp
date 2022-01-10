/**
 * @file 5.cpp
 * @author qzylalala
 * @brief 动态树, 二分
 * @version 0.1
 * @date 2022-01-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

#define x first
#define y second

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

const int N = 300010;

int n, p, T;

struct Node
{
    int s[2], p, v;
    int rev;
    int sum, mul;
}tr[N];
int stk[N], idx;  // 栈
int fa[N], dep[N];
int A;
vector<PII> level[N];

void pushrev(int x)
{
    swap(tr[x].s[0], tr[x].s[1]);
    tr[x].rev ^= 1;
}

void pushup(int x)
{
    tr[x].sum = tr[x].v;
    int l = tr[x].s[0], r = tr[x].s[1];
    if (l) tr[x].sum = (tr[x].sum + tr[l].sum) % p;
    if (r) tr[x].sum += tr[r].sum;
    tr[x].sum %= p;
}

void pushdown(int x)
{
    if (tr[x].rev)
    {
        pushrev(tr[x].s[0]), pushrev(tr[x].s[1]);
        tr[x].rev = 0;
    }

    auto &root = tr[x], &left = tr[tr[x].s[0]], &right = tr[tr[x].s[1]];
    if (root.mul != 1)
    {
        LL mul = root.mul;
        left.v = left.v * mul % p;
        left.sum = left.sum * mul % p;
        left.mul = left.mul * mul % p;

        right.v = right.v * mul % p;
        right.sum = right.sum * mul % p;
        right.mul = right.mul * mul % p;

        root.mul = 1;
    }
}

bool isroot(int x)  // 判断x是否为原树的根节点
{
    return tr[tr[x].p].s[0] != x && tr[tr[x].p].s[1] != x;
}

void rotate(int x)  // splay的旋转操作
{
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;
    if (!isroot(y)) tr[z].s[tr[z].s[1] == y] = x;
    tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushup(y), pushup(x);
}

void splay(int x)  // splay操作
{
    int top = 0, r = x;
    stk[ ++ top] = r;
    while (!isroot(r)) stk[ ++ top] = r = tr[r].p;
    while (top) pushdown(stk[top -- ]);
    while (!isroot(x))
    {
        int y = tr[x].p, z = tr[y].p;
        if (!isroot(y))
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        rotate(x);
    }
}

void access(int x)  // 建立一条从根到x的路径，同时将x变成splay的根节点
{
    int z = x;
    for (int y = 0; x; y = x, x = tr[x].p)
    {
        splay(x);
        tr[x].s[1] = y, pushup(x);
    }
    splay(z);
}

void makeroot(int x)  // 将x变成原树的根节点
{
    access(x);
    pushrev(x);
}

int findroot(int x)  // 找到x所在原树的根节点, 再将原树的根节点旋转到splay的根节点
{
    access(x);
    while (tr[x].s[0]) pushdown(x), x = tr[x].s[0];
    splay(x);
    return x;
}

void split(int x, int y)  // 给x和y之间的路径建立一个splay，其根节点是y
{
    makeroot(x);
    access(y);
}

void link(int x, int y)  // 如果x和y不连通，则加入一条x和y之间的边
{
    makeroot(x);
    if (findroot(y) != x) tr[x].p = y;
}

int find(int x, int y)
{
    int l = 0, r = level[x].size() - 1;
    while (l < r)
    {
        int mid = l + r + 1 >> 1;
        if (level[x][mid].x <= y) l = mid;
        else r = mid - 1;
    }
    return level[x][r].y;
}

int main()
{
    scanf("%d%d%d", &n, &p, &T);

    int cur = 0;
    for (int i = 1; i <= n; i ++ )
    {
        int op;
        scanf("%d", &op);
        if (op == 1)
        {
            int x;
            scanf("%d", &x);
            x ^= A;
            if (x > 0)
            {
                ++ idx;
                tr[idx].sum = tr[idx].v = x;
                tr[idx].mul = 1;
                if (cur) link(cur, idx);
                fa[idx] = cur, dep[idx] = dep[cur] + 1;
                cur = idx;
                level[dep[cur]].push_back({i, cur});
            }
            else
            {
                cur = fa[cur];
            }
        }
        else if (op == 2)
        {
            int s, l, r, y;
            scanf("%d%d%d%d", &s, &l, &r, &y);
            y ^= A;
            l = find(l, s), r = find(r, s);
            split(l, r);
            tr[r].v = tr[r].v * (LL)y % p;
            tr[r].sum = tr[r].sum * (LL)y % p;
            tr[r].mul = tr[r].mul * (LL)y % p;
        }
        else
        {
            int s, l, r;
            scanf("%d%d%d", &s, &l, &r);
            l = find(l, s), r = find(r, s);
            split(l, r);

            printf("%d\n", tr[r].sum);
            if (T) A = tr[r].sum;
        }
    }

    return 0;
}
