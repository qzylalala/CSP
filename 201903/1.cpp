#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N =100010;
int n;
int a[N];

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int mid;
    float md;
    bool flag = true;
    if (n % 2 == 0) {
        if ((a[n / 2] + a[n / 2 + 1]) % 2) {
            md = (float)(a[n / 2] + a[n / 2 + 1]) / 2;
            flag = false;
        }
        else {
            mid = (a[n / 2] + a[n / 2 + 1]) / 2;
        }
    }
    else mid = a[n / 2 + 1];

    if (a[n] >= a[1] && flag) printf("%d %d %d\n", a[n], mid, a[1]);
    else if (a[n] >= a[1]) printf("%d %.1lf %d\n", a[n], md, a[1]);
    else if (flag) printf("%d %d %d\n", a[1], mid, a[n]);
    else printf("%d %.1lf %d\n", a[1], md, a[n]);

    return 0;
}