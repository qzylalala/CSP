#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_map>

#define x first
#define y second

using namespace std;

typedef unordered_map<string, int> MPSI;

MPSI dfs(string& str, int& u)
{
    MPSI res;
    while (u < str.size())
    {
        if (str[u] == '(')
        {
            u ++ ;  // 过滤掉 '('
            auto t = dfs(str, u);
            u ++ ;  // 过滤掉 ')'
            int cnt = 1, k = u;
            while (k < str.size() && isdigit(str[k])) k ++ ;
            if (k > u)
            {
                cnt = stoi(str.substr(u, k - u));
                u = k;
            }
            for (auto c: t)
                res[c.x] += c.y * cnt;
        }
        else if (str[u] == ')') break;
        else
        {
            int k = u + 1;
            while (k < str.size() && str[k] >= 'a' && str[k] <= 'z') k ++ ;
            auto key = str.substr(u, k - u);
            u = k;
            int cnt = 1;
            while (k < str.size() && isdigit(str[k])) k ++ ;
            if (k > u)
            {
                cnt = stoi(str.substr(u, k - u));
                u = k;
            }
            res[key] += cnt;
        }
    }
    return res;
}

MPSI work(string str)
{
    MPSI res;
    for (int i = 0; i < str.size(); i ++ )
    {
        int j = i + 1;
        while (j < str.size() && str[j] != '+') j ++ ;
        auto item = str.substr(i, j - i);
        i = j;
        int cnt = 1, k = 0;
        while (k < item.size() && isdigit(item[k])) k ++ ;
        if (k) cnt = stoi(item.substr(0, k));
        auto t = dfs(item, k);
        for (auto c: t)
            res[c.x] += c.y * cnt;
    }
    return res;
}

int main()
{
    int n;
    cin >> n;
    while (n -- )
    {
        string str;
        cin >> str;
        int k = str.find('=');
        auto left = work(str.substr(0, k)), right = work(str.substr(k + 1));
        if (left == right) puts("Y");
        else puts("N");
    }
    return 0;
}