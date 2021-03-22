#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long LL;
const int N = 80010, MOD = 1e9 + 7;

int n, m;
struct Q {
    int t, l, r, k, a, b, c;
}q[N];
vector<int> xs;
struct Node {
    int l, r, k;
    int a[3], b[3], s[3];

    int get_len() {
        return xs[r] - xs[l - 1];
    }
}tr[N * 4];

int get(int x) {
    return lower_bound(xs.begin(), xs.end(), x) - xs.begin();
}

void pushup(int u) {
    auto l = tr[u << 1].s, r = tr[u << 1 | 1].s;
    for (int i = 0; i < 3; i ++ )
        tr[u].s[i] = (l[i] + r[i]) % MOD;
}

void rotate(int a[]) {
    int t = a[0];
    a[0] = a[1], a[1] = a[2], a[2] = t;
}

void eval(int u, int k) {
    k %= 3;
    for (int i = 0; i < k; i ++ ) {
        rotate(tr[u].a), rotate(tr[u].b), rotate(tr[u].s);
    }
    tr[u].k += k;
}

void eval(int u, int a[], int b[]) {
    for (int i = 0; i < 3; i ++ ) {
        tr[u].s[i] = ((LL)tr[u].s[i] * a[i] + (LL)tr[u].get_len() * b[i]) % MOD;
        int c = (LL)tr[u].a[i] * a[i] % MOD;
        int d = ((LL)tr[u].b[i] * a[i] + b[i]) % MOD;
        tr[u].a[i] = c, tr[u].b[i] = d;
    }
}

void pushdown(int u) {
    eval(u << 1, tr[u].k), eval(u << 1 | 1, tr[u].k);
    tr[u].k = 0;

    eval(u << 1, tr[u].a, tr[u].b), eval(u << 1 | 1, tr[u].a, tr[u].b);
    for (int i = 0; i < 3; i ++ )
        tr[u].a[i] = 1, tr[u].b[i] = 0;
}

void build(int u, int l, int r) {
    tr[u] = {l, r};
    for (int i = 0; i < 3; i ++ ) tr[i].a[i] = 1;
    if (l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
}

void update(int u, int l, int r, int k, int a[], int b[]) {
    if (tr[u].l >= l && tr[u].r <= r) eval(u, k), eval(u, a, b);
    else {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) update(u << 1, l, r, k, a, b);
        if (r > mid) update(u << 1 | 1, l, r, k, a, b);
        pushup(u);
    }
}

vector<int> query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) return {tr[u].s[0], tr[u].s[1], tr[u].s[2]};
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    vector<int> res(3);
    if (l <= mid) res = query(u << 1, l, r);
    if (r > mid) {
        auto t = query(u << 1 | 1, l, r);
        for (int i = 0; i < 3; i ++ )
            res[i] = (res[i] + t[i]) % MOD;
    }
    return res;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i ++ ) {
        q[i].k = 1;
        scanf("%d%d%d", &q[i].t, &q[i].l, &q[i].r);
        if (q[i].t == 1) scanf("%d%d%d", &q[i].a, &q[i].b, &q[i].c);
        else if (q[i].t == 2) scanf("%d", &q[i].k);
        xs.push_back(q[i].l - 1), xs.push_back(q[i].r);
    }
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());

    build(1, 0, xs.size() - 1);
    for (int i = 0; i < m; i ++ ) {
        int t = q[i].t, l = get(q[i].l - 1) + 1, r = get(q[i].r);
        int a[] = {q[i].k, q[i].k, q[i].k}, b[] = {q[i].a, q[i].b, q[i].c};
        if (t == 1 || t == 2)
            update(1, l, r, 0, a, b);
        else if (t == 3)
            update(1, l, r, 1, a, b);
        else {
            auto t = query(1, l, r);
            LL sum = 0;
            for (int i = 0; i < 3; i ++ )
                sum += (LL)t[i] * t[i];
            printf("%lld\n", sum % MOD);
        }
    }
    return 0;
}