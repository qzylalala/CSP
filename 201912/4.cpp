// 可持久化链表
#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

typedef vector<int> VI;
const int N = 510, M = 20010;

int n, m, w, Q;
int h[N], e[M], ne[M], idx;
vector<VI> g;
int node[N];

struct Op
{
    int t, id, pid, hid;
    bool operator< (const Op& r) const
    {
        return t > r.t;
    }
};
priority_queue<Op> heap;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void eval()
{
    auto t = heap.top();
    heap.pop();

    auto &a = g[node[t.id]], &b = g[t.hid];
    if (b.size() > a.size() || b.size() == a.size() && b.back() < a.back())
    {
        node[t.id] = t.hid;
        for (int i = h[t.id]; ~i; i = ne[i])
            if (e[i] != t.pid && e[i] != t.id)
                heap.push({t.t + w, e[i], t.id, t.hid});
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    g.push_back({0});
    memset(h, -1, sizeof h);
    while (m -- )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b), add(b, a);
    }

    scanf("%d%d", &w, &Q);
    getchar();
    char str[100];
    while (Q -- )
    {
        fgets(str, 100, stdin);
        stringstream ssin(str);
        int a[3], cnt = 0;
        while (ssin >> a[cnt]) cnt ++ ;
        if (cnt == 3)
        {
            while (heap.size() && heap.top().t <= a[1]) eval();
            g.push_back(g[node[a[0]]]);
            g.back().push_back(a[2]);
            node[a[0]] = g.size() - 1;
            for (int i = h[a[0]]; ~i; i = ne[i])
                if (e[i] != a[0])
                    heap.push({a[1] + w, e[i], a[0], node[a[0]]});
        }
        else
        {
            while (heap.size() && heap.top().t <= a[1]) eval();
            printf("%d ", g[node[a[0]]].size());
            for (auto x: g[node[a[0]]])
                printf("%d ", x);
            puts("");
        }
    }
    return 0;
}