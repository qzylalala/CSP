#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef unsigned char UC;
const int N = 1080, M = 1920;

int m, n, p, q;
UC g[N][M][3];

inline int get(char c) {
    if (c <= '9') return c - '0';
    return c - 'a' + 10;
}

inline char get(int x) {
    if (x <= 9) return x + '0';
    return x - 10 + 'A';
}

inline void print(char* str) {
    for (int i = 0; str[i]; i ++ )
        printf("\\x%c%c", get(str[i] / 16), get(str[i] % 16));
}

int main() {
    scanf("%d%d%d%d", &m, &n, &p, &q);
    char str[100];
    for (int i = 0; i < n; i ++ )
        for (int j = 0; j < m; j ++ ) {
            scanf("%s", str);
            int len = strlen(str);
            if (len == 2) {
                int t = get(str[1]);
                for (int k = 0; k < 3; k ++ )
                    g[i][j][k] = t * 16 + t;
            }
            else if (len == 4) {
                for (int k = 0; k < 3; k ++ ) {
                    int t = get(str[1 + k]);
                    g[i][j][k] = t * 16 + t;
                }
            }
            else {
                for (int k = 0; k < 3; k ++ )
                    g[i][j][k] = get(str[1 + k * 2]) * 16 + get(str[2 + k * 2]);
            }
        }

    int bg[3] = {0};
    for (int i = 0; i < n / q; i ++ ) {
        for (int j = 0; j < m / p; j ++ ) {
            int cur[3] = {0};
            for (int x = 0; x < q; x ++ )
                for (int y = 0; y < p; y ++ )
                    for (int z = 0; z < 3; z ++ )
                        cur[z] += g[i * q + x][j * p + y][z];

            for (int k = 0; k < 3; k ++ ) cur[k] /= p * q;

            if (cur[0] == bg[0] && cur[1] == bg[1] && cur[2] == bg[2]) ;  // pass
            else if (!cur[0] && !cur[1] && !cur[2]) print("\033[0m");
            else {
                sprintf(str, "\033[48;2;%d;%d;%dm", cur[0], cur[1], cur[2]);
                print(str);
            }

            for (int k = 0; k < 3; k ++ ) bg[k] = cur[k];
            print(" ");
        }
        if (bg[0] || bg[1] || bg[2]) {
            print("\033[0m");
            for (int k = 0; k < 3; k ++ ) bg[k] = 0;
        }
        print("\n");
    }
    return 0;
}