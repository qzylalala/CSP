#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 20 * 1024 * 1204 + 10;

char str[N];
vector<string> strs;

bool check_blank(string& s)
{
    for (auto c: s)
        if (c != ' ') return false;
    return true;
}

int get(string& s)
{
    if (check_blank(s)) return 0;  // 空行
    if (s.size() >= 2 && s[0] == '*' && s[1] == ' ') return 1;  // 项目
    if (s.size() >= 2 && s[0] == ' ' && s[1] == ' ') return 2;  // 项目的剩余行
    return 3;  // 其他
}

string trim(string s)
{
    int i = 0, j = s.size() - 1;
    while (i <= j && s[i] == ' ') i ++ ;
    while (i <= j && s[j] == ' ') j -- ;
    if (i > j) return "";
    return s.substr(i, j - i + 1);
}

int wc(string& s, int w)
{
    int res = 0;
    for (int i = 0; i < s.size(); i ++ )
    {
        if (s[i] == ' ') continue;
        int j = i + 1;
        while (j < s.size() && j - i + 1 <= w) j ++ ;
        res ++ ;
        i = j - 1;
    }
    return max(res, 1);
}

int main()
{
    int w;
    scanf("%d", &w);
    getchar();
    while (fgets(str, N, stdin))
    {
        strs.push_back(str);
        strs.back().pop_back();  // 删除回车
    }

    int r = -1, last = 0;  // 0表示段落，1表示项目，2表示空行
    for (int i = 0; i < strs.size();)
    {
        int t = get(strs[i]);
        if (t == 0) i ++, last = 2;
        else if (t == 1)
        {
            if (last != 1) r ++ ;
            last = 1;
            string line = trim(strs[i].substr(2));
            i ++ ;
            while (i < strs.size())
            {
                if (get(strs[i]) == 2)
                {
                    line += ' ' + trim(strs[i].substr(2));
                    i ++ ;
                }
                else break;
            }
            r += wc(line, w - 3);
        }
        else
        {
            r ++ ;
            last = 0;
            string line = trim(strs[i]);
            i ++ ;
            while (i < strs.size())
            {
                int t = get(strs[i]);
                if (t == 2 || t == 3)
                {
                    line += ' ' + trim(strs[i]);
                    i ++ ;
                }
                else break;
            }
            r += wc(line, w);
        }
    }
    printf("%d\n", r);
    return 0;
}