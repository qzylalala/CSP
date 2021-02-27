#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 510;
int g[N][N];
int n;

int main() {
    cin >> n;

    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= n; j ++) {
            cin >> g[j][i];
        }
    }

    bool flag = false;
    for (int diff = -(n - 1); diff <= (n - 1); diff ++) {
        if (flag) {
            for (int y = n; y > 0; y --) {
                int x = y + diff;
                if (x < 1 || x > n) continue;
                cout << g[x][y] << " ";
            }  
        }
        else {
            for (int y = 1; y <= n; y ++) {
                int x = y + diff;
                if (x < 1 || x > n) continue;
                cout << g[x][y] << " ";
            }      
        }
        flag = !flag;
    } 

    return 0;
}