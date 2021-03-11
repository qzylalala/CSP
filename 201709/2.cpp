#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1010;
int a[N];
int n, k;

struct Op {
    int id, type, tm;

    bool operator< (const Op& nop) {
        if (tm != nop.tm) return tm < nop.tm;
        if (type != nop.type) return type < nop.type;
        return id < nop.id;
    }
}op[N * 2];

int main() {
    cin >> n >> k;

    for (int i = 1; i <= n; i++) a[i] = i;
    int cnt = 0;
    while(k --) {
        int w, s, c;
        cin >> w >> s >> c;

        op[cnt ++] = {w, 1, s};
        op[cnt ++] = {w, 0, s + c};
    }

    sort(op, op + cnt);

    for (int i = 0; i < cnt; i++) {
        int id = op[i].id, type = op[i].type;

        if (type == 0) {
            for (int j = 1; j <= n; j++) {
                if (a[j] == 0) {
                    a[j] = id;
                    break;
                }
            }
        }
        else {
            for (int j = 1; j <= n; j++) {
                if (a[j] == id) {
                    a[j] = 0;
                    break;
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << a[i] << " ";
    }


    return 0;
}