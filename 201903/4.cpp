// 90 分
#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>

using namespace std;

const int N =10010;
int n, T;

bool solve(vector<vector<string>>& g, vector<vector<vector<int>>>& st) {
    vector<int> idxs(n, 0);  // 维护每行当前走到的位置

    while(true) {
        vector<int> nidxs = idxs;

        for (int i = 0; i < n; i++) {
            int idx = idxs[i];

            if (idx == g[i].size()) continue;

            for (int j = 0; j < st[i][idx].size(); j++) {
                int nidx = st[i][idx][j];
                int task = stoi(g[i][idx].substr(1));

                if (idxs[task] == nidx) {
                    idxs[i] ++;
                    idxs[task] ++;
                    break;
                }
                else continue;
            }
        }

        if (nidxs == idxs) break;
    }

    for (int i = 0; i < n; i++) {
        if (idxs[i] != g[i].size()){
            // cout << "line" << i << " : " << idxs[i] << ", " << g[i].size() << endl; 
            return false;
        }
    }

    return true;
}

int main() {
    cin >> T >> n;
    getchar();

    while(T --) {
        vector<vector<string>> g(n, vector<string>());       // 存储指令
        vector<vector<vector<int>>> st(n, vector<vector<int>>()); // 每一个任务 每一条指令能够匹配的 对应任务的指令 idx
        for (int i = 0; i < n; i++) {
            string line;
            getline(cin, line);
            stringstream ssin(line);
            string str;
            while (ssin >> str) g[i].push_back(str);
        }

        for (int i = 0; i < n; i++) {
            st[i] = vector<vector<int>>(g[i].size(), vector<int>());
            for (int k = 0; k < g[i].size(); k++) {
                string str = g[i][k];
                int j = stoi(str.substr(1));
                for (int s = 0; s < g[j].size(); s++) {
                    int num = stoi(g[j][s].substr(1));
                    if (num == i && ((str[0] == 'S' && g[j][s][0] == 'R') || (str[0] == 'R' && g[j][s][0] == 'S'))) {
                        st[i][k].push_back(s);
                    }
                }
            }
        }

        if (solve(g, st)) puts("0");
        else puts("1");
    }

    return 0;
}