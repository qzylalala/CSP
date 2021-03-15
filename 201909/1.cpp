#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1010;
int n, m;
int a[N];
int change[N];

int main() {
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        for (int j = 1; j <= m; j++) {
            int val;
            cin >> val;
            a[i] += val;
            change[i] -= val;
        }
    }

    int T = 0, diff = 0, idx;
    for (int i = 1; i <= n; i++) {
        T += a[i];
        if (change[i] > diff) {
            diff = change[i];
            idx = i;
        }
    }

    printf("%d %d %d\n", T, idx, diff);

    return 0;
}