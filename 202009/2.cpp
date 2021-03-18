#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int n, k, t, xl, xr, yd, yu;

bool check(int x, int y) {
    return (x >= xl && x <= xr && y <= yu && y >= yd);
}

int main() {
    cin >> n >> k >> t >> xl >> yd >> xr >> yu;

    int appear = 0, stay = 0;
    for (int i = 1; i <= n; i++ ) {
        int cnt = 0;
        int stay_cnt = 0;
        bool flag = false;
        for (int j = 1; j <= t; j++) {
            int x, y;
            cin >> x >> y;

            if (check(x, y)) {
                cnt ++;
                stay_cnt ++;
                if (stay_cnt >= k) flag = true; 
            }
            else stay_cnt = 0;
        }

        if (cnt > 0) appear ++;
        if (flag) stay ++;
    }

    cout << appear << endl;
    cout << stay << endl;

    return 0;
}