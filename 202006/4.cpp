#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long LL;
const int N = 14, MOD = 998244353;

int n;
string S;
int id[100];
vector<int> vers{
    1, 2, 4, 6, 16, 26, 41, 42, 44,
    46, 61, 62, 64, 66
};
vector<vector<int>> g{
    {2}, {4}, {1, 6, 16}, {6, 4, 64}, {26},
    {46}, {62}, {64}, {61}, {66}, {42},
    {44}, {41}, {46}
};
int tr[N][N];

void init()
{
    memset(id, -1, sizeof id);
    for (int i = 0; i < N; i ++ ) id[vers[i]] = i;
    for (int i = 0; i < N; i ++ )
        for (auto x: g[i])
            tr[i][id[x]] ++ ;
}

void mul(int c[][N], int a[][N], int b[][N])
{
    static int tmp[N][N];
    memset(tmp, 0, sizeof tmp);
    for (int i = 0; i < N; i ++ )
        for (int j = 0; j < N; j ++ )
            for (int k = 0; k < N; k ++ )
                tmp[i][j] = (tmp[i][j] + (LL)a[i][k] * b[k][j]) % MOD;
    memcpy(c, tmp, sizeof tmp);
}

int qmi(int k, int id)
{
    if (id == -1) return 0;
    int res[N][N] = {0}, w[N][N];
    memcpy(w, tr, sizeof w);
    res[0][0] = 1;

    while (k)
    {
        if (k & 1) mul(res, res, w);
        mul(w, w, w);
        k >>= 1;
    }
    return res[0][id];
}

string get(string str)
{
    string res;
    for (int i = 0; i < str.size(); i ++ )
        if (str[i] == '2') res += '1';
        else if (str[i] == '4') res += '2';
        else if (str[i] == '1')
        {
            if (i + 1 == str.size() || str[i + 1] == '6') res += '4', i ++ ;
            else return "";
        }
        else
        {
            if (i + 1 == str.size() || str[i + 1] == '4') res += '6', i ++ ;
            else return "";
        }
    return res;
}

int dfs(int k, string& str)
{
    if (str.size() <= 2) return qmi(k, id[stoi(str)]);
    int res = 0;
    for (string s: {"", "1", "6"})
    {
        auto t = get(s + str);
        if (t.size()) res = (res + dfs(k - 1, t)) % MOD;
    }
    return res;
}

int main()
{
    init();
    cin >> n >> S;
    cout << dfs(n, S) << endl;
    return 0;
}