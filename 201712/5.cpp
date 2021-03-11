// 60分
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 100010;
const LL MOD = 1e18;

int n;
LL v[N];
int p[N], w[N], f[N];
LL ans[N];

int main()
{
    int T;
    scanf("%d", &T);
    while (T -- )
    {
        scanf("%d", &n);
        memset(ans, 0, sizeof ans);
        for (int i = 1; i <= n; i ++ )
            scanf("%d%d%lld%d", &p[i], &w[i], &v[i], &f[i]);
        for (int i = n; i; i -- )
        {
            int k = p[i], d = w[i];
            while (k)
            {
                ans[k] = max(ans[k], v[k] - (LL)(f[k] - d) * (f[k] - d) + ans[i]);
                d += w[k];
                k = p[k];
            }
        }
        LL res = 0;
        for (int i = 1; i <= n; i ++ )
            res = (res + ans[i]) % MOD;
        printf("%lld\n", res);
    }
    return 0;
}