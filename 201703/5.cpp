// 网络流
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 5050;

int n, m, A, B, Q, X;
int r[N][N], c[N][N];
LL d[N];

int main()
{
    scanf("%d%d%d%d%d%d", &n, &m, &A, &B, &Q, &X);
    for (int i = 1; i <= n - 1; i ++ )
        for (int j = 1; j <= m; j ++ )
            c[i][j] = X = ((LL)A * X + B) % Q;
    for (int i = 2; i <= n - 1; i ++ )
        for (int j = 1; j <= m - 1; j ++ )
            r[i][j] = X = ((LL)A * X + B) % Q;

    for (int j = 1; j <= m; j ++ )
    {
        for (int i = 1; i < n; i ++ )
            d[i] += c[i][j];
        for (int i = 2; i < n; i ++ )
            d[i] = min(d[i], d[i - 1] + r[i][j]);
        for (int i = n - 2; i; i -- )
            d[i] = min(d[i], d[i + 1] + r[i + 1][j]);
    }
    LL res = 1e18;
    for (int i = 1; i < n; i ++ ) res = min(res, d[i]);
    printf("%lld\n", res);
    return 0;
}