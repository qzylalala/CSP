#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int n, m;
int a[1010];

int main() {
    cin >> n;
    cin >> m;
    for (int i = 1; i <= n; i++) a[i] = i;

    while(m --) {
        int p, q;
        cin >> p >> q;

        int idx;
        for (int i = 1; i <= n; i++) {
            if (a[i] == p) idx = i;
        }

        if (q > 0) {
            for (int i = 1; i <= q; i++) {
                int cur = idx + i - 1;
                a[cur] = a[cur + 1];
            }
            a[idx + q] = p;
        }
        else {
            q = -1 * q;
            for (int i = 1; i <= q; i++) {
                int cur = idx - i + 1;
                a[cur] = a[cur - 1];
            }
            a[idx - q] = p;
        }
    }

    for (int i = 1; i <= n; i++) cout << a[i] << " ";
    cout << endl;

    return 0;
}