#include <iostream>
#include <cstring>
#include <algorithm>

#define x first
#define y second

using namespace std;

typedef pair<int, int> pii;

int n, x, y;
pii p[1010];

int calc(int x, int y, int a, int b) {
    return ((x - a)*(x - a) + (y - b)*(y - b));
}

int main() {
    cin >> n >> x >> y;

    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        p[i] = {a, b};
    }

    vector<int> dist(n + 1, 0);
    for (int i = 1; i <= n; i++) dist[i] = i;

    sort(dist.begin() + 1, dist.end(), [&](int u, int v) {
        if (calc(p[u].x, p[u].y, x, y) < calc(p[v].x, p[v].y, x, y)) return true;
        else if (calc(p[u].x, p[u].y, x, y) > calc(p[v].x, p[v].y, x, y)) return false;
        else return u < v;
    });

    for (int i = 1; i <= 3; i++) cout << dist[i] << endl;

    return 0;
}