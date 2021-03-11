#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int a[1010];
int mp[1010];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];

    sort(a, a + n);

    bool flag = false;
    for (int i = 0; i < n; i++) {
        int l = i, r = i;
        while(l >= 0 && a[l] == a[i]) l --;
        while(r < n && a[r] == a[i]) r ++;

        int mi = l + 1, ma = n - r;
        if (mi == ma) {
            cout << a[i] << endl;
            flag = true;
            break;
        }
    }
    if(!flag) puts("-1");

    return 0;
}