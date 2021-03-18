#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1010;
int n, m;
struct Point{
    int x, y, type;
}p[N];
int a, b, c;

long long cacl(int x, int y) {
    return (long long)(a) * x + (long long)(b) * y + c;
}

int main() {
    cin >> n >> m;

    for (int i = 1; i <= n; i++ ) {
        int x, y;
        char type;
        cin >> x >> y >> type;
        if (type == 'A') p[i] = {x, y, 0};
        else p[i] = {x, y, 1};
    }

    for (int i = 1; i <= m; i++) {
        cin >> c >> a >> b;

        bool flag = true;
        for (int j = 1; j <= n; j++) {
            if (cacl(p[j].x, p[j].y) > 0 && p[j].type == 0) continue;
            if (cacl(p[j].x, p[j].y) < 0 && p[j].type == 1) continue;
            flag = false;
            break;
        }

        if (flag) {
            puts("Yes");
            continue;
        }

        for (int j = 1; j <= n; j++) {
            if (cacl(p[j].x, p[j].y) < 0 && p[j].type == 0) {
                flag = true;
                continue;
            }
            if (cacl(p[j].x, p[j].y) > 0 && p[j].type == 1) {
                flag = true;
                continue;
            }
            flag = false;
            break;
        }

        if (flag) puts("Yes");
        else puts("No");
    }

    return 0;
}