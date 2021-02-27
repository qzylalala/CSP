#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 130, MOD = 1e9 + 7;

LL n;
int m;
int w[N][N];

// 这里将原 n * m 方格 看为 m * n 方格, 便于理解 
// x 为 当前列状态, y 为 下一列状态, u 为当前列枚举到的方格 index
void dfs(int x, int y, int u) {
    if (u == m) w[x][y] ++ ;
    else if (x >> u & 1) dfs(x, y, u + 1);
    else {
        // 由于 列 从左往右, u(行) 从下往上 枚举, 因此共有四种转移方式
        if (u && !(y >> u & 1) && !(y >> u - 1 & 1))
            dfs(x, y + (1 << u) + (1 << u - 1), u + 1);
        if (u + 1 < m && !(y >> u & 1) && !(y >> u + 1 & 1))
            dfs(x, y + (1 << u) + (1 << u + 1), u + 1);
        if (u + 1 < m && !(x >> u + 1 & 1)) {
            if (!(y >> u & 1)) dfs(x, y + (1 << u), u + 2);
            if (!(y >> u + 1 & 1)) dfs(x, y + (1 << u + 1), u + 2);
        }
    }
}

// 矩阵乘法模板
void mul(int c[][N], int a[][N], int b[][N]) {
    static int tmp[N][N];
    memset(tmp, 0, sizeof tmp);
    for (int i = 0; i < 1 << m; i ++ )
        for (int j = 0; j < 1 << m; j ++ )
            for (int k = 0; k < 1 << m; k ++ )
                tmp[i][j] = (tmp[i][j] + (LL)a[i][k] * b[k][j]) % MOD;
    memcpy(c, tmp, sizeof tmp);
}

int main() {
    cin >> n >> m;
    // 构造转移矩阵
    for (int i = 0; i < 1 << m; i ++ )
        dfs(i, 0, 0);

    int res[N][N] = {0};
    res[0][(1 << m) - 1] = 1;

    // 快速幂
    while (n) {
        if (n & 1) mul(res, res, w);
        mul(w, w, w);
        n >>= 1;
    }
    cout << res[0][(1 << m) - 1] << endl;
    return 0;
}