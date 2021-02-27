#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 20010, M = N;
vector<vector<int>> g(N, vector<int>());
int m, n, ans;

int dfs(int u) {
    int d1 = 0, d2 = 0;
    for (int i = 0; i < g[u].size(); i++) {
        int idx = g[u][i];
        int d = dfs(idx);
        if (d > d1) d2 = d1, d1 = d;
        else if (d > d2) d2 = d;
    }

    ans = max(ans, d1 + d2);

    return d1 + 1;
}

int main() {
    cin >> n >> m;
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        g[p].push_back(i);
    }

    for (int i = n + 1; i <= n + m; i++) {
        int p;
        cin >> p;
        g[p].push_back(i);
    }

    dfs(1);

    cout << ans << endl;;

    return 0;
}