#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 3, INF = 1e8;

int g[N][N];

bool check(int x)
{
    for (int i = 0; i < 3; i ++ )
    {
        int s = 0;
        for (int j = 0; j < 3; j ++ )
            if (g[i][j] == x)
                s ++ ;
        if (s == 3) return true;
        s = 0;
        for (int j = 0; j < 3; j ++ )
            if (g[j][i] == x)
                s ++ ;
        if (s == 3) return true;
    }
    if (g[0][0] == x && g[1][1] == x && g[2][2] == x) return true;
    if (g[2][0] == x && g[1][1] == x && g[0][2] == x) return true;
    return false;
}

int evaluate()
{
    int s = 0;
    for (int i = 0; i < 3; i ++ )
        for (int j = 0; j < 3; j ++ )
            if (!g[i][j])
                s ++ ;
    if (check(1)) return s + 1;
    if (check(2)) return -(s + 1);
    if (!s) return 0;
    return INF;
}

int dfs(int u)
{
    int t = evaluate();
    if (t != INF) return t;

    if (!u)  // Alice
    {
        int res = -INF;
        for (int i = 0; i < 3; i ++ )
            for (int j = 0; j < 3; j ++ )
                if (!g[i][j])
                {
                    g[i][j] = 1;
                    res = max(res, dfs(1));
                    g[i][j] = 0;
                }
        return res;
    }
    else  // Bob
    {
        int res = INF;
        for (int i = 0; i < 3; i ++ )
            for (int j = 0; j < 3; j ++ )
                if (!g[i][j])
                {
                    g[i][j] = 2;
                    res = min(res, dfs(0));
                    g[i][j] = 0;
                }
        return res;
    }
}

int main()
{
    int T;
    cin >> T;
    while (T -- )
    {
        for (int i = 0; i < 3; i ++ )
            for (int j = 0; j < 3; j ++ )
                cin >> g[i][j];
        cout << dfs(0) << endl;
    }
    return 0;
}