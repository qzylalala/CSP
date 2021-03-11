// cv 概率论
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 15, M = 1 << N;

int n, m;
double p[N][N], s1[N], s2[N];
double f[2][M], w[M][N];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i ++ )
        for (int j = i + 1; j < n; j ++ )
        {
            scanf("%lf", &p[i][j]);
            p[j][i] = 1 - p[i][j];
        }

    for (int i = 1; i + 1 < 1 << n; i ++ )
    {
        memset(s1, 0, sizeof s1);
        memset(s2, 0, sizeof s2);
        for (int j = 0; j < n; j ++ )
            if (i >> j & 1)
            {
                for (int k = 0; k < n; k ++ )
                    if (!(i >> k & 1))
                        s1[j] += p[j][k];
            }
            else
            {
                for (int k = 0; k < n; k ++ )
                    if (i >> k & 1)
                        s2[j] += p[j][k];
            }

        double sum1 = 0, sum2 = 0;
        for (int j = 0; j < n; j ++ )
        {
            sum1 += s1[j];
            sum2 += s2[j];
        }
        for (int j = 0; j < n; j ++ )
            if (i >> j & 1)
            {
                for (int k = 0; k < n; k ++ )
                    if (!(i >> k & 1))
                        w[i][j] += s1[j] / sum1 * s2[k] / sum2 * p[k][j];
            }
            else
            {
                for (int k = 0; k < n; k ++ )
                    if (i >> k & 1)
                        w[i][j] += s2[j] / sum2 * s1[k] / sum1 * p[k][j];
            }
    }

    for (int k = 1; k <= 1000; k ++ )
    {
        memset(f[k & 1], 0, sizeof f[k & 1]);
        f[k & 1][(1 << n) - 1] = 1;
        for (int i = 1; i + 1 < 1 << n; i ++ )
            for (int j = 0; j < n; j ++ )
                f[k & 1][i] += f[k - 1 & 1][i ^ (1 << j)] * w[i][j];
    }

    while (m -- )
    {
        int state = 0;
        for (int i = 0; i < n; i ++ )
        {
            int x;
            scanf("%d", &x);
            state += x << i;
        }
        printf("%.5lf\n", f[0][state]);
    }
    return 0;
}