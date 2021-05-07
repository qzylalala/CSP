#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long LL;

const int N = 1010, M = 100010, MOD = 1e9 + 7;

int n;
int a[N];
int f[N];
vector<int> q[M];
bool st[M];

int main() {
    for (int i = 1; i < M; i ++ ) {
        for (int j = i * 2; j < M; j += i) {
            q[j].push_back(i);
        }
    }

    scanf("%d", &n);
    for (int i = 0; i < n; i ++ ) scanf("%d", &a[i]);

    f[0] = 1;
    for (int i = 1; i < n; i ++ ) {
        memset(st, 0, sizeof st);
        for (int j = i - 1; j >= 0; j -- ) {
            int d = a[i] - a[j], cnt = 0;
            for (int k : q[d]) {
                if (!st[k]) {
                    cnt ++ ;
                    st[k] = true;
                }
            }
            st[d] = true;
            f[i] = (f[i] + (LL)f[j] * cnt) % MOD;
        }
    }

    printf("%d\n", f[n - 1]);
    return 0;
}