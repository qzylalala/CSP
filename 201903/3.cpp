#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef unsigned int UI;
const int N = 1010, M = 40 * 1024 * 8 + 10;

int n, s, l;
UI disk[N][M / 8];
bool st[N];
char str[M];
int len;

inline UI get(char c)
{
    if (c <= '9') return c - '0';
    return c - 'A' + 10;
}

inline char get(UI x)
{
    if (x <= 9) return x + '0';
    return x - 10 + 'A';
}

inline string u2s(UI x)
{
    string res;
    for (int i = 7; i >= 0; i -- )
        res += get(x >> (i << 2) & 15);
    return res;
}

inline int get_real_col(int r, int c)
{
    r %= n;
    r = n - 1 - r;
    return (r + 1 + c) % n;
}

int main()
{
    scanf("%d%d%d", &n, &s, &l);
    for (int u = 0; u < l; u ++ )
    {
        int k;
        scanf("%d", &k);
        getchar();
        fgets(str, M, stdin);
        int sz = strlen(str) - 1;
        for (int i = 0; i < sz; i += 8)
        {
            UI x = 0;
            for (int j = 0; j < 8; j ++ )
                x = (x << 4) + get(str[i + j]);
            disk[k][i >> 3] = x;
        }
        st[k] = true;
        len = max(len, sz >> 3);
    }

    int m;
    scanf("%d", &m);
    while (m -- )
    {
        int b;
        scanf("%d", &b);
        if (b >= len * (n - 1)) puts("-");
        else
        {
            int k = b / s;
            int row = k / (n - 1), col = get_real_col(row, k % (n - 1));
            int r = row * s + b % s;
            if (st[col])
                puts(u2s(disk[col][r]).c_str());
            else if (l == n - 1)
            {
                UI x = 0;
                for (int i = 0; i < n; i ++ ) x ^= disk[i][r];
                puts(u2s(x).c_str());
            }
            else puts("-");
        }
    }
    return 0;
}