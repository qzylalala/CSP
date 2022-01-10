/**
 * @file 4.cpp
 * @author qzylalala
 * @brief 状态DP, 现场做出来了, 感觉挺套路的。
 * @version 0.1
 * @date 2022-01-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 16, M = 1 << N;

int n, m;
double p[N];
double f[M][N * 5 + 1];

double dp(int state, int coins, int r) {
    auto& v = f[state][coins];
    if (v >= 0) return v;
    if (coins >= r * m) return v = 0;

    v = 0;
    for (int i = 0; i < n; i ++ )
        if (state >> i & 1)
            v += p[i] * (dp(state, coins + 1, r) + 1);
        else
            v += p[i] * (dp(state | (1 << i), coins, r - 1) + 1);

    return v;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i ++ ) scanf("%lf", &p[i]);

    memset(f, -1, sizeof f);

    printf("%.10lf\n", dp(0, 0, n));

    return 0;
}