// 这题不会, 直接cv, 官方数据有误, 只能拿30分
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 210, INF = 0x3f3f3f3f;

int n;
int c[N][3];
int f[2][N][N][N];

int main()
{
    cin >> n;
    int m = 0;
    for (int i = 1; i <= n; i ++ )
    {
        int x, y, z, t;
        cin >> x >> y >> z >> t;
        c[i][0] = x, c[i][1] = z, c[i][2] = min(y, t);
        m += x;
    }
    m = (m + 1) / 2;
    memset(f, 0x3f, sizeof f);
    f[0][0][0][0] = 0;
    for (int u = 1; u <= n; u ++ )
        for (int i = 0; i <= m; i ++ )
            for (int j = 0; j <= m; j ++ )
                for (int k = 0; k <= m; k ++ )
                {
                    int& v = f[u & 1][i][j][k];
                    register int x = c[u][0], y = c[u][1], z = c[u][2], t = u - 1 & 1;
                    v = f[t][i][j][k] + z;
                    if (i >= x) v = min(v, f[t][i - x][j][k]);
                    if (j >= x) v = min(v, f[t][i][j - x][k]);
                    if (i >= y && k >= y) v = min(v, f[t][i - y][j][k - y]);
                    if (j >= y && k >= y) v = min(v, f[t][i][j - y][k - y]);
                }

    int res = INF;
    for (int i = 0; i <= m; i ++ )
        for (int j = 0; j <= m; j ++ )
            for (int k = 0; k <= m; k ++ )
                res = min(res, f[n & 1][i][j][k] + max(i, max(j, k)));
    cout << res << endl;
    return 0;
}