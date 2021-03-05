#include <iostream>
#include <cstring>
#include <algorithm>

#define x first
#define y second

using namespace std;

typedef pair<int, int> pii;

pii p[20];
char g[20][20];
char a[5][5];
int sy, cnt;

int main() {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 10; j++) {
            cin >> g[i][j];
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> a[i][j];
        }
    }
    cin >> sy;
    sy -= 1;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (a[i][j] == '1') {
                p[cnt ++] = {i, j + sy};
            }
        }
    }

    bool flag = true;
    while(true) {
        for (int i = 0; i < cnt; i++) {
            pii po = p[i];
            int x = po.x, y = po.y;
            if (x >= 15 || g[x][y] == '1') {
                flag = false;
                break;
            }
        }

        if (!flag) break;
        else {
            for (int i = 0; i < cnt; i++) {
                p[i].x = p[i].x + 1;
            }
        }
    }

    for (int i = 0; i < cnt; i++) {
        int x = p[i].x - 1, y = p[i].y;
        g[x][y] = '1';
    }

    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 10; j++) {
            cout << g[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}