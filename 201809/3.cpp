#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <vector>
#include <stack>

using namespace std;

int n, m;
vector<string> strs;

struct Node
{
    int tab;
    string tag, id;
    int k;  // 当前节点最多可以匹配到第几个位置

    Node(string str)
    {
        int i = 0;
        while (str[i] == '.') i ++ ;
        tab = i;
        while (i < str.size() && str[i] != ' ')
            tag += tolower(str[i ++ ]);
        i ++ ; // 过滤掉空格
        while (i < str.size()) id += str[i ++ ];
        k = 0;
    }
    bool check(string& word)
    {
        if (word[0] == '#') return word == id;
        return word == tag;
    }
};

void work(vector<string>& ws)
{
    vector<int> res;
    stack<Node> stk;
    for (int i = 0; i < strs.size(); i ++ )
    {
        string str = strs[i];
        Node t(str);
        while (stk.size() && stk.top().tab >= t.tab) stk.pop();
        if (stk.size()) t.k = stk.top().k;
        if (t.k == ws.size()) t.k -- ;
        if (t.check(ws[t.k]))
        {
            t.k ++ ;
            if (t.k == ws.size()) res.push_back(i + 1);
        }
        stk.push(t);
    }
    cout << res.size();
    for (auto x: res) cout << ' ' << x;
    cout << endl;
}

int main()
{
    cin >> n >> m;
    getchar();
    string str;
    while (n -- )
    {
        getline(cin, str);
        strs.push_back(str);
    }
    while (m -- )
    {
        getline(cin, str);
        stringstream ssin(str);
        vector<string> ws;
        while (ssin >> str)
        {
            if (str[0] != '#')
                for (auto& c: str)
                    c = tolower(c);
            ws.push_back(str);
        }
        work(ws);
    }
    return 0;
}