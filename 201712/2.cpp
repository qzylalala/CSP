#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int n, k;
int a[1010];

int main() {
    cin >> n >> k;
    int cnt = 0;
    for (int i = 1; i <= n; i++) a[i] = i;

    int cur = n, idx = 0;
    while(cur > 1) {
        cnt ++;
        idx = (idx % n) + 1;
        while(a[idx] == 0) idx = (idx % n) + 1;
        if (cnt % k == 0 || cnt % 10 == k) {
            a[idx] = 0;
            cur --;
        }
    } 

    int ans;
    for (int i = 1; i <= n; i++) {
        if (a[i] != 0) {
            ans = i;
            break;
        }
    }

    cout << ans << endl;

    return 0;
}