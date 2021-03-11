// cv 线段树
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;
const int N = 300010;

int n, m;
vector<int> xs;
PII p[N];
int up[N], down[N];
struct Tree {
    int l, r, v, c;
}tr[N * 4];
int best;

int get(int x) {
    return lower_bound(xs.begin(), xs.end(), x) - xs.begin();
}

bool cmp(PII& a, PII& b) {
    if (a.y != b.y) return a.y < b.y;
    return a.x < b.x;
}

void pushup(int u) {
    Tree &l = tr[u << 1], &r = tr[u << 1 | 1];
    tr[u].v = max(l.v, r.v);
    tr[u].c = l.c + r.c;
}

void build(int u, int l, int r) {
    tr[u] = {l, r};
    if (l == r) tr[u].v = tr[u].c = 0;
    else {
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}

void update(int u, int x) {
    if (tr[u].l == tr[u].r) {
        tr[u].v = min(up[x], down[x]);
        if (tr[u].v >= best) tr[u].c = 1;
        else tr[u].c = 0;
    }
    else {
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid) update(u << 1, x);
        else update(u << 1 | 1, x);
        pushup(u);
    }
}

PII query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) return {tr[u].v, tr[u].c};
    else {
        int mid = tr[u].l + tr[u].r >> 1;
        PII res(-1, 0);
        if (l <= mid) res = query(u << 1, l, r);
        if (r > mid) {
            PII t = query(u << 1 | 1, l, r);
            res.x = max(res.x, t.x);
            res.y += t.y;
        }
        return res;
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i ++ ) {
        scanf("%d%d", &p[i].x, &p[i].y);
        xs.push_back(p[i].x);
    }
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());

    for (int i = 0; i < n; i ++ ) {
        p[i].x = get(p[i].x);
        down[p[i].x] ++ ;
    }

    sort(p, p + n, cmp);

    build(1, 0, xs.size() - 1);

    for (int i = 0; i < n; i ++ ) {
        int j = i;
        while (j < n && p[j].y == p[i].y) {
            int x = p[j ++ ].x;
            up[x] ++, down[x] -- ;
            update(1, x);
        }
        for (int k = i; k + 1 < j; k ++ ) {
            if (p[k].x + 1 <= p[k + 1].x - 1) {
                PII t = query(1, p[k].x + 1, p[k + 1].x - 1);
                best = max(best, min(t.x, min(k - i + 1, j - k - 1)));
            }
        }
        i = j - 1;
    }

    if (m == 1) printf("%d\n", best);
    else {
        memset(down, 0, sizeof down);
        memset(up, 0, sizeof up);

        for (int i = 0; i < n; i ++ ) down[p[i].x] ++ ;

        build(1, 0, xs.size() - 1);

        int res = 0;
        for (int i = 0; i < n; i ++ ) {
            int j = i;
            while (j < n && p[j].y == p[i].y) {
                int x = p[j ++ ].x;
                up[x] ++, down[x] -- ;
                update(1, x);
            }
            for (int k = i; k + 1 < j; k ++ ) {
                if (k - i + 1 >= best && j - k - 1 >= best && p[k].x + 1 <= p[k + 1].x - 1) {
                    PII t = query(1, p[k].x + 1, p[k + 1].x - 1);
                    res += t.y;
                }
            }
            i = j - 1;
        }
        printf("%d\n", res);
    }

    return 0;
}