#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 610;

int n, L, r, t;
int s[N][N];

int get_sum(int x1, int y1, int x2, int y2) {
    return s[x2][y2] - s[x1 - 1][y2] - s[x2][y1 - 1] + s[x1 - 1][y1 - 1];
}

int get_cnt(int x1, int y1, int x2, int y2) {
    return (x2 - x1 + 1) * (y2 - y1 + 1);
}

int main() {
    scanf("%d%d%d%d", &n, &L, &r, &t);
    for (int i = 1; i <= n; i ++ )
        for (int j = 1; j <= n; j ++ ) {
            int x;
            scanf("%d", &x);
            s[i][j] = x + s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
        }

    int res = 0;
    for (int i = 1; i <= n; i ++ )
        for (int j = 1; j <= n; j ++ ) {
            int x1 = max(1, i - r), y1 = max(1, j - r);
            int x2 = min(n, i + r), y2 = min(n, j + r);
            if (get_sum(x1, y1, x2, y2) <= t * get_cnt(x1, y1, x2, y2))
                res ++ ;
        }

    printf("%d\n", res);

    return 0;
}