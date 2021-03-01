#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1010;
int a[N];
int n, ans;

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];

    int pre = -1;
    for (int i = 0; i < n; i++) {
        if (a[i] != pre) ans ++, pre = a[i]; 
    }

    cout << ans << endl;

    return 0;
}