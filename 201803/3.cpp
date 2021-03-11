#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 110;

int n, m;
struct Url
{
    string path, name;
}url[N];

string get_number(string& str)
{
    string res;
    for (auto c: str)
        if (c >= '0' && c <= '9')
            res += c;
        else
        {
            res.clear();
            return res;
        }

    // 去掉前导0
    int k = 0;
    while (k + 1 < res.size() && res[k] == '0') k ++ ;
    return res.substr(k);
}

vector<string> get(string& path, string& str)
{
    vector<string> res(1);
    int i, j;
    for (i = 1, j = 1; i < path.size() && j < str.size();)
    {
        int u = i + 1, v = j + 1;
        while (u < path.size() && path[u] != '/') u ++ ;
        while (v < str.size() && str[v] != '/') v ++ ;
        string a = path.substr(i, u - i), b = str.substr(j, v - j);
        if (a == "<str>")
        {
            res.push_back(b);
            i = u + 1, j = v + 1;
        }
        else if (a == "<int>")
        {
            auto t = get_number(b);
            if (t.empty())
            {
                res.clear();
                return res;
            }
            res.push_back(t);
            i = u + 1, j = v + 1;
        }
        else if (a == "<path>")
        {
            res.push_back(str.substr(j));
            return res;
        }
        else if (a != b)
        {
            res.clear();
            return res;
        }
        else i = u + 1, j = v + 1;
    }

    if (i - path.size() != j - str.size()) res.clear();
    return res;
}


void work(string& str)
{
    for (int i = 0; i < n; i ++ )
    {
        auto res = get(url[i].path, str);
        if (res.size())
        {
            cout << url[i].name;
            for (int j = 1; j < res.size(); j ++ )
                cout << ' ' << res[j];
            cout << endl;
            return;
        }
    }
    puts("404");
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i ++ ) cin >> url[i].path >> url[i].name;
    while (m -- )
    {
        string str;
        cin >> str;
        work(str);
    }

    return 0;
}