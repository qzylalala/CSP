// 欧拉路径
#include <iostream>
#include <cstring>
#include <algorithm>
#include <set>

using namespace std;

const int N = 10010, M = 100010;

int n, m;
set<int> g[N];
int p[N];
int ans[M], top;

int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

void dfs(int u) {
    while (g[u].size()) {
        int t = *g[u].begin();
        g[u].erase(t), g[t].erase(u);
        dfs(t);
    }
    ans[ ++ top] = u;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++ ) p[i] = i;
    while (m -- ) {
        int a, b;
        scanf("%d%d", &a, &b);
        g[a].insert(b), g[b].insert(a);
        p[find(a)] = find(b);
    }

    int s = 0;
    for (int i = 1; i <= n; i ++ ) {
        if (find(i) != find(1)) {
            puts("-1");
            return 0;
        }
        else if (g[i].size() % 2) s ++ ;
    }

    // 存在欧拉路径 则 奇顶点个数为 0 或 2 且 如果为2，则起点度数为奇数
    if (s != 0 && s != 2 || s == 2 && g[1].size() % 2 == 0) {
        puts("-1");
        return 0;
    }

    dfs(1);

    for (int i = top; i; i --) printf("%d ", ans[i]);

    return 0;
}