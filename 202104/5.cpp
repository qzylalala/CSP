#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

#define x first
#define y second

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

const int N = 510;
const LL INF = 0x3f3f3f3f3f3f3f3fll;

int n, m;
int len[N];
struct Node {
    int cid, sum, pid;
};
vector<Node> ps[N];
vector<PII> line[N];  // x表示节点编号；y表示到下一个点的距离
LL dist[N], ans[N];
int pid[N];
bool st[N];

LL exgcd(LL a, LL b, LL &x, LL &y) { // 扩展欧几里得算法, 求x, y，使得ax + by = gcd(a, b)
    if (!b) {
        x = 1; y = 0;
        return a;
    }
    LL d = exgcd(b, a % b, y, x);
    y -= (a / b) * x;

    return d;
}


void dijkstra() {
    memset(dist, 0x3f, sizeof dist);
    for (int i = 0; i < m; i ++ ) {
        int d = 0;
        for (int j = 0; j < line[i].size(); j ++ ) {
            if (line[i][j].x == 1) {
                dist[i] = d;
                pid[i] = j;
                break;
            }

            d += line[i][j].y;
        }
    }

    for (int i = 0; i < m; i ++ ) {
        int t = -1;
        for (int j = 0; j < m; j ++ )
            if (!st[j] && (t == -1 || dist[j] < dist[t]))
                t = j;
        st[t] = true;

        auto& l = line[t];
        auto d = dist[t];
        for (int j = pid[t], k = 0; k < l.size(); j = (j + 1) % l.size(), k ++ ) {
            for (auto& c: ps[l[j].x]) {
                if (st[c.cid]) continue;  // 优化很重要
                LL a = d, b = len[t];
                LL x = c.sum, y = len[c.cid];
                LL X, Y;
                LL D = exgcd(b, y, X, Y);
                if ((x - a) % D) continue;
                X = (x - a) / D * X;
                y /= D;
                X = (X % y + y) % y;

                if (dist[c.cid] > a + b * X) {
                    dist[c.cid] = a + b * X;
                    pid[c.cid] = c.pid;
                }
            }

            d += l[j].y;
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i ++ ) {
        int cnt, sum = 0;
        scanf("%d", &cnt);
        for (int j = 0; j < cnt; j ++ ) {
            int ver, t;
            scanf("%d%d", &ver, &t);
            ps[ver].push_back({i, sum, j});
            line[i].push_back({ver, t});
            sum += t;
        }

        len[i] = sum;
    }

    dijkstra();
    memset(ans, 0x3f, sizeof ans);
    for (int i = 0; i < m; i ++ ) {
        if (dist[i] == INF) continue;
        LL d = dist[i];
        for (int j = pid[i], k = 0; k < line[i].size(); j = (j + 1) % line[i].size(), k ++ ) {
            int ver = line[i][j].x;
            ans[ver] = min(ans[ver], d);
            d += line[i][j].y;
        }
    }

    for (int i = 2; i <= n; i ++ ) {
        if (ans[i] == INF) puts("inf");
        else printf("%lld\n", ans[i]);
    }

    return 0;
}