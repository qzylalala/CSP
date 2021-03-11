#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 100010;

int n;
struct IP
{
    string v;
    int k;
    bool operator< (const IP& t) const
    {
        if (v != t.v) return v < t.v;
        return k < t.k;
    }
    bool is_substr(IP& t)
    {
        if (t.k < k) return false;
        if (v.substr(0, k) != t.v.substr(0, k)) return false;
        return true;
    }

    int get_number(string str)
    {
        int res = 0;
        for (int i = 0; i < 8; i ++ )
            res = res * 2 + str[i] - '0';
        return res;
    }

    void print()
    {
        for (int i = 0; i < 32; i += 8)
        {
            if (i) printf(".");
            printf("%d", get_number(v.substr(i, 8)));
        }
        printf("/%d\n", k);
    }
}ip[N];

IP merge(IP& a, IP& b)
{
    IP res;
    res.k = -1;
    if (a.k != b.k) return res;
    if (a.v.substr(0, a.k - 1) != b.v.substr(0, b.k - 1)) return res;
    res.k = a.k - 1;
    res.v = a.v.substr(0, a.k - 1);
    while (res.v.size() <= 32) res.v += '0';
    return res;
}

int main()
{
    scanf("%d", &n);
    char str[20];
    int d[4];
    for (int i = 0; i < n; i ++ )
    {
        scanf("%s", str);
        memset(d, 0, sizeof d);
        int cnt = 0;
        ip[i].k = -1;
        for (int j = 0; str[j]; j ++ )
        {
            if (str[j] == '/')
            {
                ip[i].k = atoi(str + j + 1);
                break;
            }
            if (str[j] == '.') continue;
            while (str[j] && str[j] != '.' && str[j] != '/')
                d[cnt] = d[cnt] * 10 + str[j ++ ] - '0';
            j -- ;
            cnt ++ ;
        }
        for (int j = 0; j < 4; j ++ )
            for (int k = 7; k >= 0; k -- )
                if (d[j] >> k & 1)
                    ip[i].v += '1';
                else
                    ip[i].v += '0';
        if (ip[i].k == -1) ip[i].k = cnt * 8;
    }

    sort(ip, ip + n);

    int k = 1;
    for (int i = 1; i < n; i ++ )
        if (!ip[k - 1].is_substr(ip[i]))
            ip[k ++ ] = ip[i];
    n = k;

    k = 1;
    for (int i = 1; i < n; i ++ )
    {
        ip[k ++ ] = ip[i];
        while (k >= 2)
        {
            auto t = merge(ip[k - 2], ip[k - 1]);
            if (t.k != -1)
            {
                k -= 2;
                ip[k ++ ] = t;
            }
            else break;
        }
    }

    n = k;
    for (int i = 0; i < n; i ++ )
        ip[i].print();
    return 0;
}