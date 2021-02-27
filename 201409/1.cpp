#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1010;

int n;
int a[N];

int main() {
    cin >> n;
    for (int i = 0; i < n; i ++ ) cin >> a[i];
    sort(a, a + n);

    int res = 0;
    for (int i = 1; i < n; i ++ )
        if (a[i] == a[i - 1] + 1)
            res ++ ;
    cout << res << endl;

    return 0;
}