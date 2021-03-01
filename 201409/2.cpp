#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 110;
bool state[N][N];
int n;

int main() {
    cin >> n;
    
    for (int i = 1; i <= n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        for (int x = x1; x < x2; x ++) {
            for (int y = y1; y < y2; y++) {
                state[x][y] = true;
            }
        }
    }

    int ans = 0;
    for (int i = 0; i <= 105; i++) {
        for (int j = 0; j <= 105; j++) {
            if (state[i][j]) ans ++;
        }
    }

    cout << ans << endl;

    return 0;
}