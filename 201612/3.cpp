#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>

using namespace std;

typedef pair<string, int> pii;

int p, r, u, q;
map<string, int> mp;                // 各权限 最高等级
map<string, vector<pii>> roles;     // 各角色 对应权限等级
map<string, vector<string>> users;  // 各user 对应角色

int main() {
    cin >> p;
    // -1 表示无权限等级
    for (int i = 1; i <= p; i++) {
        string str;
        cin >> str;
        int n = str.size();
        if (str[n - 2] == ':') {
            mp[str.substr(0, n - 2)] = str[n - 1] - '0';
        }
        else {
            mp[str] = -1;
        }
    }

    cin >> r;
    for (int i = 0; i < r; i++) {
        string role;
        int num;
        cin >> role >> num;
        while(num --) {
            string str;
            cin >> str;
            int n = str.size();
            if (str[n - 2] == ':') {
                roles[role].push_back({str.substr(0, n - 2), str[n - 1] - '0'});
            }
            else {
                roles[role].push_back({str, -1});
            }
        }
    }

    cin >> u;
    for (int i = 0; i < u; i++) {
        string name;
        int num;
        cin >> name >> num;

        while(num --) {
            string role;
            cin >> role;
            users[name].push_back(role);
        }
    }

    cin >> q;
    for (int i = 0; i < q; i++) {
        string name, str;
        cin >> name >> str;
        int n = str.size();
        if (n >= 2 && str[n - 2] == ':') {
            string query = str.substr(0, n - 2);
            int level = str[n - 1] - '0';

            vector<string> allRoles = users[name];
            int  maxL = -1;
            for (auto role : allRoles) {
                for (pii p : roles[role]) {
                    if (p.first == query) {
                        maxL = max(maxL, p.second);
                    }
                }
            }

            if (maxL >= level) puts("true");
            else puts("false");
        }
        else {
            string query = str;

            vector<string> allRoles = users[name];
            int  maxL = -2;
            for (auto role : allRoles) {
                for (pii p : roles[role]) {
                    if (p.first == query) {
                        maxL = max(maxL, p.second);
                    }
                }
            }

            if (maxL == -2) puts("false");
            else if (maxL == -1) puts("true");
            else cout << maxL << endl;
        }
    }

    return 0;
}