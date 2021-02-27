#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1010;
int a[N];
int n;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    int area = 0;
    for (int i = 1; i <= n; i++) {
        int mi = a[i];
        for (int j = i; j <= n; j++) {
            mi = min(mi, a[j]);
            area = max(area, (j - i + 1) * mi);
        }
    }

    cout << area << endl;
    return 0;
}