#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 33;

int n, m;
int g[N][N];
bool st[N][N];

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i ++ )
        for (int j = 0; j < m; j ++ )
            cin >> g[i][j];

    for (int i = 0; i < n; i ++ )
        for (int j = 0; j < m; j ++ ) {
            int l = j, r = j, u = i, d = i, x = g[i][j];
            while (l >= 0 && g[i][l] == x) l -- ;
            while (r < m && g[i][r] == x) r ++ ;
            while (u >= 0 && g[u][j] == x) u -- ;
            while (d < n && g[d][j] == x) d ++ ;
            st[i][j] = r - l - 1 >= 3 || d - u - 1 >= 3;
        }

    for (int i = 0; i < n; i ++ ) {
        for (int j = 0; j < m; j ++ )
            if (st[i][j]) cout << 0 << ' ';
            else cout << g[i][j] << ' ';
        cout << endl;
    }
    return 0;
}