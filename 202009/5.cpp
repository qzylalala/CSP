// AC 自动机
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 55, M = 1010, MOD = 998244353;

int n, m;
int tr[N][26], cnt[N], idx;
int q[N], ne[N];
struct Node
{
    int row, next;
}g[26][N];
int f[M][N][N];
vector<string> strs;

void insert(string& str)
{
    int p = 0;
    for (char c: str)
    {
        int u = c - 'a';
        if (!tr[p][u]) tr[p][u] = ++ idx;
        p = tr[p][u];
    }
    cnt[p] ++ ;
}

void build()
{
    int hh = 0, tt = -1;
    for (int i = 0; i < 26; i ++ )
        if (tr[0][i])
            q[ ++ tt] = tr[0][i];
    while (hh <= tt)
    {
        int t = q[hh ++ ];
        for (int i = 0; i < 26; i ++ )
        {
            int p = tr[t][i];
            if (!p) tr[t][i] = tr[ne[t]][i];
            else
            {
                ne[p] = tr[ne[t]][i];
                cnt[p] += cnt[ne[p]];
                q[ ++ tt] = p;
            }
        }
    }
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < 26; i ++ )
        for (int j = 1; j <= n; j ++ )
        {
            string str;
            cin >> str;
            g[str[0] - 'a'][j] = {i, stoi(str.substr(1))};
        }
    string str;
    while (cin >> str)
    {
        insert(str);
        strs.push_back(str);
    }

    build();

    f[0][0][1] = 1;
    for (int i = 0; i <= m; i ++ )
    {
        int sum = 0;
        for (int j = 0; j <= idx; j ++ )
            for (int k = 1; k <= n; k ++ )
            {
                if (!f[i][j][k]) continue;
                sum = (sum + f[i][j][k]) % MOD;
                for (auto& s: strs)
                {
                    if (i + s.size() > m) continue;
                    bool flag = true;
                    int x = j, y = k;
                    for (auto c: s)
                    {
                        int u = c - 'a';
                        auto& t = g[u][y];
                        x = tr[x][t.row];
                        if (cnt[x])
                        {
                            flag = false;
                            break;
                        }
                        y = t.next;
                    }
                    if (flag)
                    {
                        auto& v = f[i + s.size()][x][y];
                        v = (v + f[i][j][k]) % MOD;
                    }
                }
            }
        if (i) printf("%d\n", sum);
    }
    return 0;
}