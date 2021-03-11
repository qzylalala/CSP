#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

int main() {
    int r, y, g;
    cin >> r >> y >> g;
    int n;
    cin >> n;

    LL res = 0;
    while(n --) {
        LL k, t;
        cin >> k >> t;

        if (k == 0) res += t;
        else {
            if (k == 1) t = r - t;
            else if (k == 2) t = r + g + y - t;
            else t = r + g - t;

            t += res;
            t %= (r + g + y);
            if (t < r) res += r - t;
            else if (t >= r + g) res += r + g + y - t + r;
        }
    }

    cout << res << endl;
    return 0;
}