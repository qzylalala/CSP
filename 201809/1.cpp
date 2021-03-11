#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int a[1010];
int b[1010];
int n;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; i++) {
        if (i == 1) {
            b[i] = (a[i] + a[i + 1]) / 2;    
        }
        else if (i == n) {
            b[n] = (a[n] + a[n - 1]) / 2;
        }
        else b[i] = (a[i - 1] + a[i + 1] + a[i]) / 3;

        cout << b[i] << " ";
    }

    cout << endl;
    return 0;
}