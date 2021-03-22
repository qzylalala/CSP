#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>

#define x first
#define y second

using namespace std;

typedef pair<int, int> pii;
int m;
pii p[100010];
int les[100010];
int more[100010];
map<int, int> mp;
map<int, pii> info;
int thres[100010];

int main() {
    cin >> m;

    for (int i = 1; i <= m; i++) {
        int thre, result;
        cin >> thre >> result;
        p[i] = {thre, result};
        mp[thre] ++;
        if (result == 0) info[thre].x ++;
        else info[thre].y ++;
    }

    sort(p + 1, p + m + 1);

    int n = 1;
    for (int i = 1; i <= m; i++) {
        if (i == 1) thres[n ++] = p[i].x;
        else {
            if (p[i].x == p[i - 1].x) continue;
            else thres[n ++] = p[i].x;
        }
    }

    n --;
    int cnt = 0;
    for (int i = 2; i <= n; i++) {
        cnt += info[thres[i - 1]].x;
        les[i] = cnt;
    }

    cnt = 0;
    for (int i = n; i >= 1; i--) {
        cnt += info[thres[i]].y;
        more[i] = cnt;
    }

    int sum = 0, ans;
    for (int i = 1; i <= n; i++) {
        int cur = les[i] + more[i];
        // cout << i << " : " << les[i] << " " << more[i] << endl;
        if (cur >= sum) {
            sum = cur;
            ans = thres[i];
        }
    }

    cout << ans << endl;
    return 0;
}