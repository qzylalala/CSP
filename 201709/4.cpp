#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int N = 1010;
vector<vector<int>> g1(N, vector<int>());
vector<vector<int>> g2(N, vector<int>());
bool st1[N], st2[N];
int n, m;

void bfs(int a, vector<vector<int>>& g, bool st[]) {
    queue<int> q;
    q.push(a);
    st[a] = true;

    while(q.size()) {
        int x = q.front();
        q.pop();

        for (int i = 0; i < g[x].size(); i++) {
            int node = g[x][i];
            if (st[node]) continue;

            q.push(node);
            st[node] = true;
        }
    }
}

int main() {
    cin >> n >> m;

    while(m --) {
        int a, b;
        cin >> a >> b;  
        g1[a].push_back(b);
        g2[b].push_back(a);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        memset(st1, false, sizeof st1);
        memset(st2, false, sizeof st2);
        bfs(i, g1, st1);
        bfs(i, g2, st2);

        int cnt = 0;
        for (int i = 1; i <= n; i++) {
            if (st1[i] || st2[i]) {
                cnt ++;
            }
        } 

        if (cnt == n) ans ++;
    }

    cout << ans << endl;

    return 0;
}