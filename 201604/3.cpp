#include <iostream>
#include <cstring>
#include <algorithm>
#include <stack>

using namespace std;

int p;
string cur;

vector<string> walk(string path) {
    vector<string> res;
    path += string(1, '/');

    int n = path.size();
    int l = 0, r = 1;
    while(r < n) {
        while(r < n && path[r] != '/') r ++;
        res.push_back(path.substr(l + 1, r - l - 1));
        l = r;
        r ++;
    }

    return res;
}

void output(string path) {
    vector<string> res;
    if (path.size() == 1 && path[0] == '/') {
        cout << string(1, '/') << endl; 
        return ;
    }
    else if (path[0] == '/') {
        res = walk(path);
    }
    else {
        path = cur + string(1, '/') + path;
        res = walk(path);
    }

    stack<string> stk;
    for (auto& str : res) {
        if (str == ".") continue;
        else if (str == "..") {
            if (stk.empty()) continue;
            else stk.pop();
        }
        else stk.push(str);
    }

    vector<string> ans;
    while(stk.size()) {
        ans.push_back(stk.top());
        stk.pop();
    }
    reverse(ans.begin(), ans.end());

    string outp(1, '/');
    for (auto s : ans) {
        outp += s + string(1, '/');
    }

    if (outp.size() == 1) cout << "/" << endl;
    else cout << outp.substr(0, outp.size() - 1) << endl;
}

string pretreat(string path) {
    string ans;
    int n = path.size();

    int cur = 0;
    while(cur < n) {
        if (path[cur] == '/') {
            cur ++;
            ans += string(1, '/');
            while(path[cur] == '/') cur ++;
        }
        else {
            ans += path[cur];
            cur ++;
        }
    } 
    if (ans.size() == 1 && ans[0] == '/') return string(1, '/');
    else if (ans[ans.size() - 1] == '/') return ans.substr(0, ans.size() - 1);
    else return ans;
}

int main() {
    cin >> p;
    cin >> cur;
    cur = pretreat(cur);
    getchar();

    while(p --) {
        string tmp;
        getline(cin, tmp);
        if (tmp.empty()) tmp = cur;
        tmp = pretreat(tmp);
        output(tmp);
    }

    return 0;
}