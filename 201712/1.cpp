#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int a[1010];
int n;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + 1 + n);

    int ans = 0x3f3f3f3f;
    for (int i = 2; i <= n; i++) {
        ans = min(ans, a[i] - a[i - 1]);
    }

    cout << ans << endl;

    return 0;
}