#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 260;

int n, m, L;
int s[N];

int main() {
    scanf("%d%d%d", &n, &m, &L);
    for (int i = 0; i < n; i ++ )
        for (int j = 0; j < m; j ++ ) {
            int x;
            scanf("%d", &x);
            s[x] ++ ;
        }

    for (int i = 0; i < L; i ++ )
        printf("%d ", s[i]);

    return 0;
}