// AC 自动机
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 110;
const LL INF = 1e18;

int n;
LL m;
int tr[N][26], cnt[N], ne[N], idx;
int q[N];
LL ans[N][N], w[N][N];

void insert(char* str) {
    int p = 0;
    for (int i = 0; str[i]; i ++ ) {
        int u = str[i] - 'a';
        if (!tr[p][u]) tr[p][u] = ++ idx;
        p = tr[p][u];
    }
    cnt[p] ++ ;
}

void build() {
    int hh = 0, tt = -1;
    for (int i = 0; i < 26; i ++ )
        if (tr[0][i])
            q[ ++ tt] = tr[0][i];
    while (hh <= tt) {
        int t = q[hh ++ ];
        for (int i = 0; i < 26; i ++ ) {
            int p = tr[t][i];
            if (!p) tr[t][i] = tr[ne[t]][i];
            else {
                ne[p] = tr[ne[t]][i];
                cnt[p] += cnt[ne[p]];
                q[ ++ tt] = p;
            }
        }
    }
}

void mul(LL c[][N], LL a[][N], LL b[][N]) {
    static LL tmp[N][N];
    memset(tmp, -0x3f, sizeof tmp);
    for (int i = 0; i <= idx; i ++ )
        for (int j = 0; j <= idx; j ++ )
            for (int k = 0; k <= idx; k ++ )
                tmp[i][j] = max(tmp[i][j], a[i][k] + b[k][j]);
    memcpy(c, tmp, sizeof tmp);
}

int main() {
    cin >> n >> m;
    char str[N];
    while (n -- ) {
        cin >> str;
        insert(str);
    }
    build();

    memset(w, -0x3f, sizeof w);
    for (int i = 0; i <= idx; i ++ )
        for (int j = 0; j < 26; j ++ ) {
            int k = tr[i][j];
            w[i][k] = max(w[i][k], (LL)cnt[k]);
        }

    for (int i = 1; i <= idx; i ++ ) ans[0][i] = -INF;
    while (m) {
        if (m & 1) mul(ans, ans, w);
        mul(w, w, w);
        m >>= 1;
    }
    LL res = 0;
    for (int i = 0; i <= idx; i ++ ) res = max(res, ans[0][i]);
    cout << res << endl;

    return 0;
}