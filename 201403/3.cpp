#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>

using namespace std;

int n;

int main() {
    string choices;
    cin >> choices;
    cin >> n;
    // mp 存储 某一字母是否为带参数选项
    map<char, bool> mp;
    int len = choices.size();
    for (int i = 0; i < len; i++) {
        if (i + 1 < len && choices[i + 1] == ':') mp[choices[i]] = true, i++;
        else mp[choices[i]] = false;
    }


    getchar();

    for (int i = 1; i <= n; i++) {
        string cmd;
        getline(cin, cmd);

        vector<string> res;
        cmd += " ";
        size_t pos = cmd.find(" ");
        while(pos != cmd.npos) {
            string temp = cmd.substr(0, pos);
            res.push_back(temp);
            //去掉已分割的字符串,在剩下的字符串中进行分割
            cmd = cmd.substr(pos+1, cmd.size());
            pos = cmd.find(" ");
        }

        cout << "Case " << i << ":";
        for (int i = 0; i < 26; i++) {
            string tmp;
            for (int j = 1; j < (int)res.size(); j ++) {
                if (res[j][0] != '-' || res[j].size() != 2) break;
                if (res[j][0] == '-' && !mp.count(res[j][1])) break;

                string choice = res[j];
                if (choice[1] == 'a' + i) {
                    if (mp[choice[1]]) {
                        if (j + 1 < (int)res.size()) {
                            tmp = " " + res[j] + " " + res[j + 1];
                            j ++;
                        }
                        else ;
                    }
                    else tmp = " " + res[j];
                }
                else {
                    if (mp[choice[1]]) j ++;
                }
            }
            cout << tmp;
        }

        cout << endl;

    }

    return 0;
}