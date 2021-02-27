#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1010;
int g[N][N];
int m, n;

int main() {
    cin >> m >> n;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> g[i][j];
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < m; j++) {
            cout << g[j][i] << " ";
        }
        cout << endl;
    }

    return 0;
}