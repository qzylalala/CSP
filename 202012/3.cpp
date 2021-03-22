// cv
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

typedef long long LL;
const int N = 2000010;

int n;
struct Node {
    string name;
    int id, type;  // type == 0: 文件夹；type == 1：文件
    mutable LL ld, lr;
    mutable LL sd, sr;
    bool operator< (const Node& t) const {
        return name < t.name;
    }
};
set<Node> son[N];
int idx;
char str[N];
bool F;
int U;
LL SZ;

vector<string> get(char* str) {
    vector<string> res(1, "root");
    for (int i = 0; str[i]; i ++ ) {
        if (str[i] == '/') continue;
        string s;
        int j = i;
        while (str[j] && str[j] != '/') s += str[j ++ ];
        res.push_back(s);
        i = j - 1;
    }

    return res;
}

LL dfs_remove(vector<string>& t, int u, int p) {
    string name = t[u];
    if (!son[p].count({name})) return -1;
    auto it = son[p].find({name});
    if (u == t.size() - 1) {
        if (it->type) t[u] = "#file";
        auto sz = it->sr;
        son[p].erase(it);
        return sz;
    }
    if (it->type) return -1;
    auto sz = dfs_remove(t, u + 1, it->id);
    if (sz >= 0) {
        it->sr -= sz;
        if (t[u + 1] == "#file") it->sd -= sz;
    }
    return sz;
}

bool dfs_create(vector<string>& t, int u, int p, LL sz) {
    string name = t[u];
    if (u == t.size() - 1) {
        if (son[p].count({name})) {
            auto it = son[p].find({name});
            if (it->type == 0) return false;
            SZ = dfs_remove(t, 0, 0);
            Node cur{name, ++ idx, 1, 0, 0, 0, sz};
            son[p].insert(cur);
            return true;
        }
        else {
            Node cur{name, ++ idx, 1, 0, 0, 0, sz};
            son[p].insert(cur);
            return true;
        }
    }
    else {
        if (!son[p].count({name})) {
            if (U == -1) U = u;
            Node cur{name, ++ idx, 0, 0, 0, 0, 0};
            son[p].insert(cur);
        }

        auto it = son[p].find({name});
        if (it->type) return false;
        auto res = dfs_create(t, u + 1, it->id, sz);
        if (res) {
            it->sr += sz;
            if (u + 1 == t.size() - 1) it->sd += sz;

            if (it->lr && it->sr > it->lr) F = false;
            if (it->ld && it->sd > it->ld) F = false;
        }
        return res;
    }
}

bool create(char* str, LL sz) {
    auto t = get(str);
    F = true, U = -1, SZ = -1;
    auto res = dfs_create(t, 0, 0, sz);

    auto ans = res && F;
    if (res && !F) {
        auto t = get(str);
        if (U != -1) {
            while (t.size() - 1 > U) t.pop_back();
        }
        dfs_remove(t, 0, 0);
        if (SZ != -1) create(str, SZ);
    }
    return ans;
}

bool update(char* str, LL d, LL r) {
    auto t = get(str);
    int p = 0;
    for (int i = 0; i < t.size(); i ++ ) {
        string& s = t[i];
        auto it = son[p].find({s});
        if (it == son[p].end()) return false;
        if (it->type) return false;
        if (i == t.size() - 1) {
            if (d && d < it->sd) return false;
            if (r && r < it->sr) return false;
            it->ld = d, it->lr = r;
        }
        p = it->id;
    }
    return true;
}

int main() {
    scanf("%d", &n);
    char op[2];
    sprintf(str, "/tmp");
    create(str, 1);
    auto t = get(str);
    dfs_remove(t, 0, 0);
    while (n -- ) {
        scanf("%s", op);
        bool res;
        if (*op == 'C') {
            LL sz;
            scanf("%s%lld", str, &sz);
            res = create(str, sz);
        }
        else if (*op == 'R') {
            scanf("%s", str);
            auto t = get(str);
            dfs_remove(t, 0, 0);
            res = true;
        }
        else {
            LL d, r;
            scanf("%s%lld%lld", str, &d, &r);
            res = update(str, d, r);
        }
        if (res) puts("Y");
        else puts("N");
    }
    return 0;
}