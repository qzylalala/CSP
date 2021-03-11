#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int get(int n) {
    if (n <= 3500) return n;
    else {
        int a[8] = {0, 1500, 4500, 9000, 35000, 55000, 80000, 1000000000};
        double b[8] = {0, 0.03, 0.1, 0.2, 0.25, 0.3, 0.35, 0.45};

        double res = 0;
        n -= 3500;
        for (int i = 1; i <= 7; i ++ )
            if (a[i] <= n)
                res += (a[i] - a[i - 1]) * b[i];
            else {
                res += (n - a[i - 1]) * b[i];
                break;
            }
        return n - res + 3500 + 1e-6;
    }
}

int main() {
    int n;
    cin >> n;

    int l = 0, r = 1e9;
    while (l < r) {
        int mid = l + r >> 1;
        if (get(mid) >= n) r = mid;
        else l = mid + 1;
    }

    cout << r << endl;
    return 0;
}