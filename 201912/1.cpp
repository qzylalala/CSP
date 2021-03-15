#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int a[4];

bool check(int x) {
    if (x % 7 == 0) return true;

    while (x) {
        int mod = x % 10;
        x /= 10;
        if (mod == 7) return true;
    }

    return false;
}

int main() {
    cin >> n;

    int cnt = 0;
    int num = 0;
    int idx = 0;
    while(num < n) {
        cnt ++;
        while (check(cnt)) {
            cnt ++;
            a[idx] ++;
            idx = (idx + 1) % 4;
        }

        idx = (idx + 1) % 4;
        num ++;
    }

    for (int i = 0; i < 4; i++) cout << a[i] << endl;

    return 0;
}