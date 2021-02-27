#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 11;

int n, m;
struct Window {
    int x1, y1, x2, y2;
    int id;
}w[N];

int get(int x, int y) {
    for (int i = n; i; i -- ) {
        if (x >= w[i].x1 && x <= w[i].x2 && y >= w[i].y1 && y <= w[i].y2)
            return i;
    }
    return -1;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i ++ ) {
        cin >> w[i].x1 >> w[i].y1 >> w[i].x2 >> w[i].y2;
        w[i].id = i;
    }

    while (m -- ) {
        int x, y;
        cin >> x >> y;
        int id = get(x, y);
        if (id == -1) puts("IGNORED");
        else
        {
            cout << w[id].id << endl;
            Window window = w[id];
            for (int i = id; i < n; i ++ )
                w[i] = w[i + 1];
            w[n] = window;
        }
    }
    return 0;
}