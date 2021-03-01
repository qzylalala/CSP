#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>

using namespace std;

const int N = 110;
int n, m;
string a[N];
map<string, string> mp;

void output(string str) {
    int n = (int)str.size();
    int l = 0;
    string ans;
    while(l < n) {
        if (str[l] == '{') {
            if (l + 2 < n && str[l + 1] == '{' && str[l + 2] == ' ') {
                string var;
                l += 3;
                while(l < n && str[l] != ' ') {
                    var += str[l];
                    l ++;
                }
                ans += mp[var];
                l += 3;
            }
            else {
                ans += str[l];
                l ++;
            }
        }
        else {
            ans += str[l];
            l ++;
        }
    }

    cout << ans << endl;
}

int main() {
    cin >> m >> n;
    getchar();

    for (int i = 0; i < m; i++) {
        getline(cin, a[i]);
    }

    for (int i = 0; i < n; i++) {
        string var, val;
        string line;
        getline(cin, line);

        int k = 0, n = line.size();
        while(k < n) {
            if (line[k] != ' ') var += line[k], k ++;
            else break;
        }

        val = line.substr(k + 2, n - k - 3);
        mp[var] = val;
    }

    for (int i = 0; i < m; i++) {
        output(a[i]);
    }

    return 0;
}