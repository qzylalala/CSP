#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int a[25];

int main() {
    cin >> n;
    for (int i = 1; i <= 20; i++) a[i] = 5;
    for (int i = 1; i <= n; i++) {
        int num;
        cin >> num;

        int j;
        for (j = 1; j <= 20; j++) {
            if (a[j] >= num) {
                for (int k = 1; k <= num; k ++) {
                    int x = 5 * j - a[j] + k;
                    cout << x << " ";
                }
                cout << endl;
                a[j] -= num;
                break;
            }
        }

        if (j == 21) {
            for (j = 1; j <= 20; j ++) {
                if (a[j] > 0 && a[j] <= num) {
                    for (int k = 1; k <= a[j]; k ++) {
                        int x = 5 * j - a[j] + k;
                        cout << x << " ";
                    }
                    num -= a[j];
                    a[j] = 0;
                }
                else if(a[j] > 0 && a[j] > num) {
                    for (int k = 1; k <= num; k ++) {
                        int x = 5 * j - a[j] + k;
                        cout << x << " ";
                    }
                    a[j]-= num;
                    num = 0;
                }
            }
            cout << endl;
        }
    }

    return 0;
}