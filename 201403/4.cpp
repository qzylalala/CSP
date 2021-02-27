#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <map>

#define x first
#define y second

using namespace std;

typedef pair<int, int> pii;
typedef long long LL;
const int N = 210, M = N * N;

struct Point{
    int x, y, id;
}p[N];

int n, m, k, r;
map<int, vector<int>> mp;
int dist[N][N];

bool check(Point a, Point b) {
    LL dx = a.x - b.x;
    LL dy = a.y - b.y;
    return dx * dx + dy * dy <= (LL)r * r;
}


int bfs() {
    queue<pii> q;
    q.push({1, 0});
    memset(dist, 0x3f, sizeof dist);
    dist[1][0] = 0;

    while (q.size()) {
        auto t = q.front();
        q.pop();

        for (int i = 0; i < (int)mp[t.first].size(); i++) {
            int x = mp[t.x][i], y = t.y;
            if (x > n) y ++ ;
            if (y <= k) {
                if (dist[x][y] > dist[t.x][t.y] + 1) {
                    dist[x][y] = dist[t.x][t.y] + 1;
                    q.push({x, y});
                }
            }
        }
    }

    int res = 1e8;
    for (int i = 0; i <= k; i ++ )
        res = min(res, dist[2][i]);
    return res - 1;
}

int main() {
    cin >> n >> m >> k >> r;

    for (int i = 1; i <= n + m; i ++ ){
         cin >> p[i].x >> p[i].y;
         p[i].id = i;
    }

    for (int i = 1; i <= n + m; i ++ )
        for (int j = i + 1; j <= n + m; j ++ )
            if (check(p[i], p[j]))
                mp[i].push_back(j), mp[j].push_back(i);

    cout << bfs() << endl;

    return 0;
}