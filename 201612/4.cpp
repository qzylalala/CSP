// cv DP huffman树
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 5010, INF = 1e9;

int n;
int s[N], f[N][N], p[N][N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ )
    {
        scanf("%d", &s[i]);
        s[i] += s[i - 1];
    }

    for (int i = 1; i <= n; i ++ ) p[i][i] = i;
    for (int len = 2; len <= n; len ++ )
        for (int i = 1; i + len - 1 <= n; i ++ )
        {
            int j = i + len - 1;
            f[i][j] = INF;
            for (int k = p[i][j - 1]; k <= p[i + 1][j]; k ++ )
            {
                int t = f[i][k] + f[k + 1][j] + s[j] - s[i - 1];
                if (f[i][j] >= t)
                {
                    f[i][j] = t;
                    p[i][j] = k;
                }
            }
        }

    printf("%d\n", f[1][n]);

    return 0;
}