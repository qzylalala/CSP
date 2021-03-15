// 多路归并
#include <iostream>
#include <cstring>
#include <algorithm>
#include <set>
#include <vector>
#include <unordered_map>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;
const int N = 55;

int m, n;
set<PII> g[N];
unordered_map<int, int> f[N];
int sum[N], cnt[N];
set<PII>::reverse_iterator it[N];
vector<int> ans[N];

int main()
{
    scanf("%d%d", &m, &n);
    for (int i = 1; i <= n; i ++ )
    {
        int id, score;
        scanf("%d%d", &id, &score);
        for (int j = 0; j < m; j ++ )
        {
            f[j][id] = score;
            g[j].insert({score, -id});
        }
    }

    int Q;
    scanf("%d", &Q);
    while (Q -- )
    {
        int t;
        scanf("%d", &t);
        if (t == 1)
        {
            int type, id, score;
            scanf("%d%d%d", &type, &id, &score);
            f[type][id] = score;
            g[type].insert({score, -id});
        }
        else if (t == 2)
        {
            int type, id;
            scanf("%d%d", &type, &id);
            g[type].erase({f[type][id], -id});
            f[type].erase(id);
        }
        else
        {
            int tot;
            scanf("%d", &tot);
            for (int i = 0; i < m; i ++ )
            {
                scanf("%d", &sum[i]);
                it[i] = g[i].rbegin();
                cnt[i] = 0;
                ans[i].clear();
            }
            while (tot -- )
            {
                int k = -1;
                for (int i = 0; i < m; i ++ )
                    if (it[i] != g[i].rend() && cnt[i] < sum[i])
                        if (k == -1 || it[i]->x > it[k]->x)
                            k = i;
                if (k == -1) break;
                ans[k].push_back(-it[k]->y);
                cnt[k] ++ ;
                it[k] ++ ;
            }
            for (int i = 0; i < m; i ++ )
                if (ans[i].empty()) puts("-1");
                else
                {
                    for (auto x: ans[i])
                        printf("%d ", x);
                    puts("");
                }
        }
    }
    return 0;
}