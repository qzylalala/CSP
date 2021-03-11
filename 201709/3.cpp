#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

struct Obj
{
    int type;  // 1: str, 2: dict
    string str;
    Obj(){}
    Obj(string _str)
    {
        type = 1;
        str = _str;
    }
    map<string, Obj> obj;
};

string work_str(string& str, int& k)
{
    k ++ ;  // 过滤掉'\"'
    string res;
    while (str[k] != '\"')
        if (str[k] == '\\') res += str[k + 1], k += 2;
        else res += str[k ++ ];
    k ++ ;  // 过滤掉'\"'
    return res;
}

Obj work_obj(string&, int&);

void work_kv(Obj& obj, string& str, int& k)
{
    auto key = work_str(str, k);
    while (str[k] != ':') k ++ ;
    k ++ ;  // 将':'过滤掉
    while (str[k] != '\"' && str[k] != '{') k ++ ;
    if (str[k] == '\"') obj.obj[key] = Obj(work_str(str, k));
    else obj.obj[key] = work_obj(str, k);
}

Obj work_obj(string& str, int& k)
{
    Obj obj;
    obj.type = 2;
    while (str[k] != '{') k ++ ;
    k ++ ;  // 过滤掉 '{'
    while (str[k] != '}')
    {
        if (str[k] == '\"') work_kv(obj, str, k);
        else k ++ ;
    }
    k ++ ;  // 过滤掉 '}'
    return obj;
}

void query(Obj o, vector<string>& qs)
{
    for (auto& s: qs)
    {
        if (o.type == 1 || !o.obj.count(s))
        {
            puts("NOTEXIST");
            return;
        }
        auto t = o.obj[s];
        o = t;
    }

    if (o.type == 1) printf("STRING %s\n", o.str.c_str());
    else puts("OBJECT");
}

int main()
{
    int n, m;
    cin >> n >> m;
    getchar();
    string str, s;
    while (n -- )
    {
        getline(cin, s);
        str += s;
    }

    int k = 0;
    auto obj = work_obj(str, k);

    while (m -- )
    {
        getline(cin, s);
        vector<string> qs;
        for (int i = 0; i < s.size(); i ++ )
        {
            int j = i + 1;
            while (j < s.size() && s[j] != '.') j ++ ;
            qs.push_back(s.substr(i, j - i));
            i = j;
        }
        query(obj, qs);
    }
    return 0;
}