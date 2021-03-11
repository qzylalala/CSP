#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int r, y, g, n;

int main() {
    cin >> r >> y >> g;
    cin >> n;

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int k, t;
        cin >> k >> t;

        if (k == 0) ans += t;
        else if (k == 1) ans += t;
        else if (k == 2) ans += t + r;
        else continue;
    }

    cout << ans << endl;

    return 0;
}